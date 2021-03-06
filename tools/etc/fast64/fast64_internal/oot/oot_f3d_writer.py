import shutil, copy, bpy, os

from ..f3d.f3d_writer import *
from ..f3d.f3d_material import *
from bpy.utils import register_class, unregister_class
from .oot_constants import *
from .oot_utility import *
from .oot_scene_room import *
from ..f3d.f3d_parser import *

class OOTModel(FModel):
	def __init__(self, f3dType, isHWv1, name, DLFormat, drawLayerOverride):
		self.drawLayerOverride = drawLayerOverride
		FModel.__init__(self, f3dType, isHWv1, name, DLFormat, GfxMatWriteMethod.WriteAll)

	def getDrawLayerV3(self, obj):
		return obj.ootDrawLayer

	def getRenderMode(self, drawLayer):
		if self.drawLayerOverride:
			drawLayerUsed = self.drawLayerOverride
		else:
			drawLayerUsed = drawLayer
		defaultRenderModes = bpy.context.scene.world.ootDefaultRenderModes
		cycle1 = getattr(defaultRenderModes, drawLayerUsed.lower() + "Cycle1")
		cycle2 = getattr(defaultRenderModes, drawLayerUsed.lower() + "Cycle2")
		return [cycle1, cycle2]

	def getTextureSuffixFromFormat(self, texFmt):
		if texFmt == 'RGBA16':
			return 'rgb5a1'
		else:
			return texFmt.lower()

	def onMaterialCommandsBuilt(self, gfxList, revertList, material, drawLayer):
		for i in range(8, 14):
			matDrawLayer = getattr(material.ootMaterial, drawLayer.lower())
			if getattr(matDrawLayer, "segment" + format(i, 'X')):
				gfxList.commands.append(SPDisplayList(
					GfxList("0x" + format(i,'X') + '000000', GfxListTag.Material, DLFormat.Static)))
		return

	def onAddMesh(self, fMesh, contextObj):
		if contextObj is not None and hasattr(contextObj, 'ootDynamicTransform'):
			if contextObj.ootDynamicTransform.billboard:
				fMesh.draw.commands.append(SPMatrix("0x01000000", "G_MTX_MODELVIEW | G_MTX_NOPUSH | G_MTX_MUL"))

class OOTDynamicMaterialDrawLayer:
	def __init__(self, opaque, transparent):
		self.opaque = opaque
		self.transparent = transparent

class OOTGfxFormatter(GfxFormatter):
	def __init__(self, scrollMethod):
		GfxFormatter.__init__(self, scrollMethod, 64)

	# This code is not functional, only used for an example
	def drawToC(self, f3d, gfxList):
		return gfxList.to_c(f3d)

	# This code is not functional, only used for an example
	def tileScrollMaterialToC(self, f3d, fMaterial):
		materialGfx = fMaterial.material
		scrollDataFields = fMaterial.scrollData.fields

		# Set tile scrolling
		for texIndex in range(2): # for each texture
			for axisIndex in range(2): # for each axis
				scrollField = scrollDataFields[texIndex][axisIndex]
				if scrollField.animType != "None":
					if scrollField.animType == "Linear":
						if axisIndex == 0:
							fMaterial.tileSizeCommands[texIndex].uls = str(fMaterial.tileSizeCommands[0].uls) + \
								" + s * " + str(scrollField.speed)
						else:
							fMaterial.tileSizeCommands[texIndex].ult = str(fMaterial.tileSizeCommands[0].ult) + \
								" + s * " + str(scrollField.speed)

		# Build commands
		data = CData()
		data.header = 'Gfx* ' + fMaterial.material.name + '(Gfx* glistp, int s, int t);\n'
		data.source = 'Gfx* ' + materialGfx.name + '(Gfx* glistp, int s, int t) {\n'
		for command in materialGfx.commands:
			data.source += '\t' + command.to_c(False) + ';\n'
		data.source += '\treturn glistp;\n}' + '\n\n'

		if fMaterial.revert is not None:
			data.append(fMaterial.revert.to_c(f3d))
		return data

class OOTTriangleConverterInfo(TriangleConverterInfo):
	def __init__(self, obj, armature, f3d, transformMatrix, infoDict):
		TriangleConverterInfo.__init__(self, obj, armature, f3d, transformMatrix, infoDict)

	def getMatrixAddrFromGroup(self, groupIndex):
		return format((0x0D << 24) + MTX_SIZE * self.vertexGroupInfo.vertexGroupToMatrixIndex[groupIndex], "#010x")

class OOTVertexGroupInfo(VertexGroupInfo):
	def __init__(self):
		self.vertexGroupToMatrixIndex = {}
		VertexGroupInfo.__init__(self)

#class OOTBox:
#	def __init__(self):
#		self.minBounds = [-2**8, -2**8]
#		self.maxBounds = [2**8 - 1, 2**8 - 1]

class OOTF3DContext(F3DContext):
	def __init__(self, f3d, limbList, basePath):
		self.limbList = limbList
		self.dlList = [] # in the order they are rendered
		self.isBillboard = False
		materialContext = createF3DMat(None, preset = 'oot_shaded_solid')
		#materialContext.f3d_mat.rdp_settings.g_mdsft_cycletype = "G_CYC_1CYCLE"
		F3DContext.__init__(self, f3d, basePath, materialContext)

	def getLimbName(self, index):
		return self.limbList[index]

	def getBoneName(self, index):
		return "bone" + format(index, "03") + "_" + self.getLimbName(index)
	
	def vertexFormatPatterns(self, data):
		# position, uv, color/normal
		if "VTX" in data:
			return ["VTX\s*\(([^,]*),([^,]*),([^,]*),([^,]*),([^,]*),([^,]*),([^,]*),([^,]*),([^,]*)\)"]
		else:
			return F3DContext.vertexFormatPatterns(self, data)
	
	# For game specific instance, override this to be able to identify which verts belong to which bone.
	def setCurrentTransform(self, name):
		if name[:4].lower() == "0x0d":
			self.currentTransformName = self.getLimbName(self.dlList[int(int(name[4:], 16) / MTX_SIZE)].limbIndex)
		else:
			try:
				pointer = hexOrDecInt(name)
			except:
				self.currentTransformName = name
			else:
				if pointer >> 24 == 0x01:
					self.isBillboard = True
				else:
					print("Unhandled matrix: " + name)
	
	def processDLName(self, name):
		# Commands loaded to 0x0C are material related only.
		try:
			pointer = hexOrDecInt(name)
		except:
			return name
		else:
			segment = pointer >> 24
			print("POINTER")
			if segment >= 0x08 and segment <= 0x0D:
				print("SETTING " + str(segment))
				setattr(self.materialContext.ootMaterial.opaque, "segment" + format(segment, "1X"), True)
				setattr(self.materialContext.ootMaterial.transparent, "segment" + format(segment, "1X"), True)
			return None
		return name

	def processTextureName(self, textureName):
		try:
			pointer = hexOrDecInt(textureName)
		except:
			return textureName
		else:
			return textureName
			#if (pointer >> 24) == 0x08:
			#	print("Unhandled OOT pointer: " + textureName)

	def clearMaterial(self):
		self.isBillboard = False
		clearOOTMaterialDrawLayerProperty(self.materialContext.ootMaterial.opaque)
		clearOOTMaterialDrawLayerProperty(self.materialContext.ootMaterial.transparent)
		F3DContext.clearMaterial(self)

	def postMaterialChanged(self):
		clearOOTMaterialDrawLayerProperty(self.materialContext.ootMaterial.opaque)
		clearOOTMaterialDrawLayerProperty(self.materialContext.ootMaterial.transparent)

# returns: 
# 	mesh, 
# 	anySkinnedFaces (to determine if skeleton should be flex)
def ootProcessVertexGroup(fModel, meshObj, vertexGroup, convertTransformMatrix, armatureObj, namePrefix,
	meshInfo, drawLayerOverride, convertTextureData):

	mesh = meshObj.data
	currentGroupIndex = getGroupIndexFromname(meshObj, vertexGroup)
	nextDLIndex = len(meshInfo.vertexGroupInfo.vertexGroupToMatrixIndex)
	vertIndices = [vert.index for vert in meshObj.data.vertices if\
		meshInfo.vertexGroupInfo.vertexGroups[vert.index] == currentGroupIndex]

	if len(vertIndices) == 0:
		print("No vert indices in " + vertexGroup)
		return None, False

	bone = armatureObj.data.bones[vertexGroup]
	
	# dict of material_index keys to face array values
	groupFaces = {}
	
	# dict of material_index keys to SkinnedFace objects
	skinnedFaces = {}

	handledFaces = []
	anyConnectedToUnhandledBone = False
	for vertIndex in vertIndices:
		if vertIndex not in meshInfo.vert:
			continue
		for face in meshInfo.vert[vertIndex]:
			# Ignore repeat faces
			if face in handledFaces:
				continue

			sortedLoops = {} # (group tuple) : []
			connectedToUnhandledBone = False

			# loop is interpreted as face + loop index
			groupTuple = []
			for i in range(3):
				faceVertIndex = face.vertices[i]
				vertGroupIndex = meshInfo.vertexGroupInfo.vertexGroups[faceVertIndex]
				if vertGroupIndex not in groupTuple:
					groupTuple.append(vertGroupIndex)
				if vertGroupIndex not in meshInfo.vertexGroupInfo.vertexGroupToLimb:
					# Only want to handle skinned faces connected to parent
					connectedToUnhandledBone = True
					anyConnectedToUnhandledBone = True
					break
			
			if connectedToUnhandledBone:
				continue
			groupTuple = tuple(sorted(groupTuple))

			if groupTuple == tuple([currentGroupIndex]):
				if face.material_index not in groupFaces:
					groupFaces[face.material_index] = []
				groupFaces[face.material_index].append(face)
			else:
				if groupTuple not in skinnedFaces:
					skinnedFaces[groupTuple] = {}
				skinnedFacesGroup = skinnedFaces[groupTuple]
				if face.material_index not in skinnedFacesGroup:
					skinnedFacesGroup[face.material_index] = []
				skinnedFacesGroup[face.material_index].append(face)
			
			handledFaces.append(face)

	if not (len(groupFaces) > 0 or len(skinnedFaces) > 0):
		print("No faces in " + vertexGroup)

		# OOT will only allocate matrix if DL exists.
		# This doesn't handle case where vertices belong to a limb, but not triangles.
		# Therefore we create a dummy DL
		if anyConnectedToUnhandledBone:
			fMesh = fModel.addMesh(vertexGroup, namePrefix, drawLayerOverride, False, bone)
			fModel.endDraw(fMesh, bone)
			meshInfo.vertexGroupInfo.vertexGroupToMatrixIndex[currentGroupIndex] = nextDLIndex
			return fMesh, False
		else:
			return None, False
	
	meshInfo.vertexGroupInfo.vertexGroupToMatrixIndex[currentGroupIndex] = nextDLIndex
	fMeshes = {}
	triConverterInfo = OOTTriangleConverterInfo(meshObj, armatureObj.data, fModel.f3d, convertTransformMatrix, meshInfo)

	# Usually we would separate DLs into different draw layers.
	# however it seems like OOT skeletons don't have this ability.
	# Therefore we always use the drawLayerOverride as the draw layer key.
	# This means everything will be saved to one mesh. 
	drawLayerKey = drawLayerOverride
	for material_index, faces in groupFaces.items():
		material = meshObj.material_slots[material_index].material
		#if material.mat_ver > 3:
		#	drawLayer = material.f3d_mat.draw_layer.oot
		#else:
		#	drawLayer = drawLayerOverride
		drawLayer = drawLayerOverride
		
		if drawLayerKey not in fMeshes:
			fMesh = fModel.addMesh(vertexGroup, namePrefix, drawLayer, False, bone)
			fMeshes[drawLayerKey] = fMesh
			
		checkForF3dMaterialInFaces(meshObj, material)
		fMaterial, texDimensions = \
			saveOrGetF3DMaterial(material, fModel, meshObj, drawLayer, convertTextureData)

		if fMaterial.useLargeTextures:
			currentGroupIndex = saveMeshWithLargeTexturesByFaces(material, faces, fModel, fMeshes[drawLayer],
				meshObj, drawLayer, convertTextureData, currentGroupIndex, triConverterInfo, None, None)
		else:
			currentGroupIndex = saveMeshByFaces(material, faces, fModel, fMeshes[drawLayer], 
				meshObj, drawLayer, convertTextureData, currentGroupIndex, triConverterInfo, None, None)

	for groupTuple, materialFaces in skinnedFaces.items():
		for material_index, faces in materialFaces.items():
			material = meshObj.material_slots[material_index].material
			#if material.mat_ver > 3:
			#	drawLayer = material.f3d_mat.draw_layer.oot
			#else:
			#	drawLayer = drawLayerOverride
			drawLayer = drawLayerOverride

			if drawLayerKey not in fMeshes:
				# technically skinned, but for oot we don't have separate skinned/unskinned meshes.
				fMesh = fModel.addMesh(vertexGroup, namePrefix, drawLayer, False, bone)
				fMeshes[drawLayerKey] = fMesh

			checkForF3dMaterialInFaces(meshObj, material)
			fMaterial, texDimensions = \
				saveOrGetF3DMaterial(material, fModel, meshObj, drawLayer, convertTextureData)
			if fMaterial.useLargeTextures:
				currentGroupIndex = saveMeshWithLargeTexturesByFaces(material, faces, fModel, fMeshes[drawLayer], 
					meshObj, drawLayer, convertTextureData, currentGroupIndex, triConverterInfo, None, None)
			else:
				currentGroupIndex = saveMeshByFaces(material, faces, fModel, fMeshes[drawLayer], 
					meshObj, drawLayer, convertTextureData, currentGroupIndex, triConverterInfo, None, None)

	for drawLayer, fMesh in fMeshes.items():
		fModel.endDraw(fMesh, bone)

	return fMeshes[drawLayerKey], len(skinnedFaces) > 0

ootEnumObjectMenu = [
	("Scene", "Parent Scene Settings", "Scene"),
	("Room", "Parent Room Settings", "Room"),
]

def ootConvertMeshToC(originalObj, finalTransform, f3dType, isHWv1, name, folderName, DLFormat, saveTextures,
	exportPath, isCustomExport, drawLayer, removeVanillaData):
	name = toAlnum(name)

	try:
		obj, allObjs = ootDuplicateHierarchy(originalObj, None, False,  OOTObjectCategorizer())

		fModel = OOTModel(f3dType, isHWv1, name, DLFormat, drawLayer)
		triConverterInfo = TriangleConverterInfo(obj, None, fModel.f3d, finalTransform, getInfoDict(obj))
		fMeshes = saveStaticModel(triConverterInfo, fModel, obj, finalTransform, fModel.name,
			not saveTextures, False, 'oot')

		# Since we provide a draw layer override, there should only be one fMesh.
		for drawLayer, fMesh in fMeshes.items():
			fMesh.draw.name = name

		ootCleanupScene(originalObj, allObjs)

	except Exception as e:
		ootCleanupScene(originalObj, allObjs)
		raise Exception(str(e))

	data = CData()
	data.source += '#include "ultra64.h"\n#include "global.h"\n'
	if not isCustomExport:
		data.source += '#include "' + folderName + '.h"\n\n'
	else:
		data.source += '\n'

	exportData = fModel.to_c(
		TextureExportSettings(False, saveTextures, "test"), OOTGfxFormatter(ScrollMethod.Vertex))

	data.append(exportData.all())

	path = ootGetPath(exportPath, isCustomExport, 'assets/objects/', folderName, False, False)
	writeCData(data, 
		os.path.join(path, name + '.h'),
		os.path.join(path, name + '.c'))

	if not isCustomExport:
		addIncludeFiles(folderName, path, name)
		if removeVanillaData:
			headerPath = os.path.join(path, folderName + '.h')
			sourcePath = os.path.join(path, folderName + '.c')
			removeDL(sourcePath, headerPath, name)
		
	

class OOT_DisplayListPanel(bpy.types.Panel):
	bl_label = "Display List Inspector"
	bl_idname = "OBJECT_PT_OOT_DL_Inspector"
	bl_space_type = 'PROPERTIES'
	bl_region_type = 'WINDOW'
	bl_context = "object"
	bl_options = {'HIDE_HEADER'} 

	@classmethod
	def poll(cls, context):
		return context.scene.gameEditorMode == "OOT" and \
			(context.object is not None and isinstance(context.object.data, bpy.types.Mesh))

	def draw(self, context):
		box = self.layout.box()
		box.box().label(text = 'OOT DL Inspector')
		obj = context.object

		#prop_split(box, obj, "ootDrawLayer", "Draw Layer")
		box.prop(obj, "ignore_render")
		box.prop(obj, "ignore_collision")

		# Doesn't work since all static meshes are pre-transformed
		#box.prop(obj.ootDynamicTransform, "billboard")

		#drawParentSceneRoom(box, obj)

class OOT_ImportDL(bpy.types.Operator):
	# set bl_ properties
	bl_idname = 'object.oot_import_dl'
	bl_label = "Import DL"
	bl_options = {'REGISTER', 'UNDO', 'PRESET'}

	# Called on demand (i.e. button press, menu item)
	# Can also be called from operator search menu (Spacebar)
	def execute(self, context):
		obj = None
		if context.mode != 'OBJECT':
			bpy.ops.object.mode_set(mode = "OBJECT")

		try:
			name = context.scene.ootDLImportName
			folderName = context.scene.ootDLImportFolderName
			importPath = bpy.path.abspath(context.scene.ootDLImportCustomPath)
			isCustomImport = context.scene.ootDLImportUseCustomPath
			scale = context.scene.ootActorBlenderScale
			basePath = bpy.path.abspath(context.scene.ootDecompPath)
			removeDoubles = context.scene.ootDLRemoveDoubles
			importNormals = context.scene.ootDLImportNormals
			drawLayer = bpy.context.scene.ootDLImportDrawLayer

			filepaths = [ootGetObjectPath(isCustomImport, importPath, folderName)]
			if not isCustomImport:
				filepaths.append(os.path.join(bpy.context.scene.ootDecompPath, "assets/objects/gameplay_keep/gameplay_keep.c"))

			importMeshC(filepaths, name, scale, removeDoubles, importNormals, drawLayer,
				OOTF3DContext(F3D("F3DEX2/LX2", False), [name], basePath))

			self.report({'INFO'}, 'Success!')		
			return {'FINISHED'}

		except Exception as e:
			if context.mode != 'OBJECT':
				bpy.ops.object.mode_set(mode = 'OBJECT')
			raisePluginError(self, e)
			return {'CANCELLED'} # must return a set

class OOT_ExportDL(bpy.types.Operator):
	# set bl_ properties
	bl_idname = 'object.oot_export_dl'
	bl_label = "Export DL"
	bl_options = {'REGISTER', 'UNDO', 'PRESET'}

	# Called on demand (i.e. button press, menu item)
	# Can also be called from operator search menu (Spacebar)
	def execute(self, context):
		obj = None
		if context.mode != 'OBJECT':
			bpy.ops.object.mode_set(mode = "OBJECT")
		if len(context.selected_objects) == 0:
			raise PluginError("Mesh not selected.")
		obj = context.active_object
		if type(obj.data) is not bpy.types.Mesh:
			raise PluginError("Mesh not selected.")

		finalTransform = mathutils.Matrix.Scale(context.scene.ootActorBlenderScale, 4)

		try:
			#exportPath, levelName = getPathAndLevel(context.scene.geoCustomExport, 
			#	context.scene.geoExportPath, context.scene.geoLevelName, 
			#	context.scene.geoLevelOption)

			saveTextures = bpy.context.scene.saveTextures or bpy.context.scene.ignoreTextureRestrictions
			isHWv1 = context.scene.isHWv1
			f3dType = context.scene.f3d_type

			name = context.scene.ootDLExportName
			folderName = context.scene.ootDLExportFolderName
			exportPath = bpy.path.abspath(context.scene.ootDLExportCustomPath)
			isCustomExport = context.scene.ootDLExportUseCustomPath
			drawLayer = context.scene.ootDLExportDrawLayer
			removeVanillaData = context.scene.ootDLRemoveVanillaData

			ootConvertMeshToC(obj, finalTransform, 
				f3dType, isHWv1, name, folderName, DLFormat.Static, saveTextures,
				exportPath, isCustomExport, drawLayer, removeVanillaData)

			self.report({'INFO'}, 'Success!')		
			return {'FINISHED'}

		except Exception as e:
			if context.mode != 'OBJECT':
				bpy.ops.object.mode_set(mode = 'OBJECT')
			raisePluginError(self, e)
			return {'CANCELLED'} # must return a set

class OOT_ExportDLPanel(bpy.types.Panel):
	bl_idname = "OOT_PT_export_dl"
	bl_label = "OOT DL Exporter"
	bl_space_type = 'VIEW_3D'
	bl_region_type = 'UI'
	bl_category = 'OOT'

	@classmethod
	def poll(cls, context):
		return True

	# called every frame
	def draw(self, context):
		col = self.layout.column()
		col.operator(OOT_ExportDL.bl_idname)
		
		prop_split(col, context.scene, 'ootDLExportName', "DL")
		if context.scene.ootDLExportUseCustomPath:
			prop_split(col, context.scene, 'ootDLExportCustomPath', "Folder")
		else:		
			prop_split(col, context.scene, 'ootDLExportFolderName', "Object")
		prop_split(col, context.scene, "ootDLExportDrawLayer", "Export Draw Layer")
		col.prop(context.scene, "ootDLExportUseCustomPath")
		col.prop(context.scene, "ootDLRemoveVanillaData")

		col.operator(OOT_ImportDL.bl_idname)

		prop_split(col, context.scene, 'ootDLImportName', "DL")
		if context.scene.ootDLImportUseCustomPath:
			prop_split(col, context.scene, 'ootDLImportCustomPath', "File")
		else:		
			prop_split(col, context.scene, 'ootDLImportFolderName', "Object")
		prop_split(col, context.scene, "ootDLImportDrawLayer", "Import Draw Layer")

		col.prop(context.scene, "ootDLImportUseCustomPath")
		col.prop(context.scene, "ootDLRemoveDoubles")
		col.prop(context.scene, "ootDLImportNormals")

class OOTDefaultRenderModesProperty(bpy.types.PropertyGroup):
	expandTab : bpy.props.BoolProperty()
	opaqueCycle1 : bpy.props.StringProperty(default = "G_RM_AA_ZB_OPA_SURF")
	opaqueCycle2 : bpy.props.StringProperty(default = "G_RM_AA_ZB_OPA_SURF2")
	transparentCycle1 : bpy.props.StringProperty(default = "G_RM_AA_ZB_XLU_SURF")
	transparentCycle2 : bpy.props.StringProperty(default = "G_RM_AA_ZB_XLU_SURF2")
	overlayCycle1 : bpy.props.StringProperty(default = "G_RM_AA_ZB_OPA_SURF")
	overlayCycle2 : bpy.props.StringProperty(default = "G_RM_AA_ZB_OPA_SURF2")

class OOT_DrawLayersPanel(bpy.types.Panel):
	bl_label = "OOT Draw Layers"
	bl_idname = "WORLD_PT_OOT_Draw_Layers_Panel"
	bl_space_type = 'PROPERTIES'
	bl_region_type = 'WINDOW'
	bl_context = "world"
	bl_options = {'HIDE_HEADER'} 

	@classmethod
	def poll(cls, context):
		return context.scene.gameEditorMode == "OOT"

	def draw(self, context):
		ootDefaultRenderModeProp = context.scene.world.ootDefaultRenderModes
		layout = self.layout

		inputGroup = layout.column()
		inputGroup.prop(ootDefaultRenderModeProp, 'expandTab', 
			text = 'Default Render Modes', 
			icon = 'TRIA_DOWN' if ootDefaultRenderModeProp.expandTab else 'TRIA_RIGHT')
		if ootDefaultRenderModeProp.expandTab:
			prop_split(inputGroup, ootDefaultRenderModeProp, "opaqueCycle1", "Opaque Cycle 1")
			prop_split(inputGroup, ootDefaultRenderModeProp, "opaqueCycle2", "Opaque Cycle 2")
			prop_split(inputGroup, ootDefaultRenderModeProp, "transparentCycle1", "Transparent Cycle 1")
			prop_split(inputGroup, ootDefaultRenderModeProp, "transparentCycle2", "Transparent Cycle 2")
			prop_split(inputGroup, ootDefaultRenderModeProp, "overlayCycle1", "Overlay Cycle 1")
			prop_split(inputGroup, ootDefaultRenderModeProp, "overlayCycle2", "Overlay Cycle 2")

class OOT_MaterialPanel(bpy.types.Panel):
	bl_label = "OOT Material"
	bl_idname = "MATERIAL_PT_OOT_Material_Inspector"
	bl_space_type = 'PROPERTIES'
	bl_region_type = 'WINDOW'
	bl_context = "material"
	bl_options = {'HIDE_HEADER'} 

	@classmethod
	def poll(cls, context):
		return context.material is not None and context.scene.gameEditorMode == "OOT"

	def draw(self, context):
		layout = self.layout
		mat = context.material
		col = layout.column()

		if hasattr(context, "object") and context.object is not None and \
			context.object.parent is not None and isinstance(context.object.parent.data, bpy.types.Armature):
			drawLayer = context.object.parent.ootDrawLayer
			if drawLayer != mat.f3d_mat.draw_layer.oot:
				col.label(text = "Draw layer is being overriden by skeleton.", icon = "ERROR")
		else:
			drawLayer = mat.f3d_mat.draw_layer.oot

		drawOOTMaterialProperty(col.box().column(), mat.ootMaterial, drawLayer)

def drawOOTMaterialDrawLayerProperty(layout, matDrawLayerProp, suffix):
	#layout.box().row().label(text = title)
	row = layout.row()
	for colIndex in range(2):
		col = row.column()
		for rowIndex in range(3):
			i = 8 + colIndex * 3 + rowIndex
			name = "Segment " + format(i, 'X') + " " + suffix
			col.prop(matDrawLayerProp, "segment" + format(i, 'X'), text = name)

def clearOOTMaterialDrawLayerProperty(matDrawLayerProp):
	for i in range(0x08, 0x0E):
		setattr(matDrawLayerProp, "segment" + format(i, 'X'), False)


drawLayerSuffix = {
	"Opaque" : "OPA",
	"Transparent" : 'XLU',
	"Overlay" : "OVL"
}

def drawOOTMaterialProperty(layout, matProp, drawLayer):
	if drawLayer == "Overlay":
		return
	suffix = "(" + drawLayerSuffix[drawLayer] + ")"
	layout.box().column().label(text = "OOT Dynamic Material Properties " + suffix)
	layout.label(text = "See gSPSegment calls in z_scene_table.c.")
	layout.label(text = "Based off draw config index in gSceneTable.")
	drawOOTMaterialDrawLayerProperty(layout.column(), getattr(matProp, drawLayer.lower()), suffix)
		

class OOTDynamicMaterialDrawLayerProperty(bpy.types.PropertyGroup):
	segment8 : bpy.props.BoolProperty()
	segment9 : bpy.props.BoolProperty()
	segmentA : bpy.props.BoolProperty()
	segmentB : bpy.props.BoolProperty()
	segmentC : bpy.props.BoolProperty()
	segmentD : bpy.props.BoolProperty()

# The reason these are separate is for the case when the user changes the material draw layer, but not the 
# dynamic material calls. This could cause crashes which would be hard to detect.
class OOTDynamicMaterialProperty(bpy.types.PropertyGroup):
	opaque : bpy.props.PointerProperty(type = OOTDynamicMaterialDrawLayerProperty)
	transparent : bpy.props.PointerProperty(type = OOTDynamicMaterialDrawLayerProperty)

class OOTDynamicTransformProperty(bpy.types.PropertyGroup):
	billboard : bpy.props.BoolProperty(name = "Billboard")

oot_dl_writer_classes = (
	OOTDefaultRenderModesProperty,
	OOTDynamicMaterialDrawLayerProperty,
	OOTDynamicMaterialProperty,
	OOTDynamicTransformProperty,
	OOT_ExportDL,
	OOT_ImportDL,
)

oot_dl_writer_panel_classes = (
	#OOT_ExportDLPanel,
	OOT_DisplayListPanel,
	OOT_DrawLayersPanel,
	OOT_MaterialPanel,
	OOT_ExportDLPanel,
)

def oot_dl_writer_panel_register():
	for cls in oot_dl_writer_panel_classes:
		register_class(cls)

def oot_dl_writer_panel_unregister():
	for cls in oot_dl_writer_panel_classes:
		unregister_class(cls)

def oot_dl_writer_register():
	for cls in oot_dl_writer_classes:
		register_class(cls)

	bpy.types.Object.ootDrawLayer = bpy.props.EnumProperty(items = ootEnumDrawLayers, default = 'Opaque')

	# Doesn't work since all static meshes are pre-transformed
	#bpy.types.Object.ootDynamicTransform = bpy.props.PointerProperty(type = OOTDynamicTransformProperty)
	bpy.types.World.ootDefaultRenderModes = bpy.props.PointerProperty(type = OOTDefaultRenderModesProperty)

	bpy.types.Scene.ootDLExportName = bpy.props.StringProperty(
		name = "DL Name", default = "gBoulderFragmentsDL")
	bpy.types.Scene.ootDLExportFolderName = bpy.props.StringProperty(
		name = "DL Folder", default = "gameplay_keep")
	bpy.types.Scene.ootDLExportCustomPath = bpy.props.StringProperty(
		name ='Custom DL Path', subtype = 'FILE_PATH')
	bpy.types.Scene.ootDLExportUseCustomPath = bpy.props.BoolProperty(
		name = "Use Custom Path")
	bpy.types.Scene.ootDLRemoveVanillaData = bpy.props.BoolProperty(
		name = "Replace Vanilla DLs")

	bpy.types.Scene.ootDLImportName = bpy.props.StringProperty(
		name = "DL Name", default = "gBoulderFragmentsDL")
	bpy.types.Scene.ootDLImportFolderName = bpy.props.StringProperty(
		name = "DL Folder", default = "gameplay_keep")
	bpy.types.Scene.ootDLImportCustomPath = bpy.props.StringProperty(
		name ='Custom DL Path', subtype = 'FILE_PATH')
	bpy.types.Scene.ootDLImportUseCustomPath = bpy.props.BoolProperty(
		name = "Use Custom Path")

	bpy.types.Scene.ootDLRemoveDoubles = bpy.props.BoolProperty(name = "Remove Doubles", default = True)
	bpy.types.Scene.ootDLImportNormals = bpy.props.BoolProperty(name = "Import Normals", default = True)
	bpy.types.Scene.ootDLImportDrawLayer = bpy.props.EnumProperty(name = "Draw Layer", items = ootEnumDrawLayers)

	bpy.types.Scene.ootDLExportDrawLayer = bpy.props.EnumProperty(name = "Draw Layer", items = ootEnumDrawLayers)

	bpy.types.Material.ootMaterial = bpy.props.PointerProperty(type = OOTDynamicMaterialProperty)
	bpy.types.Object.ootObjectMenu = bpy.props.EnumProperty(items = ootEnumObjectMenu)

def oot_dl_writer_unregister():
	for cls in reversed(oot_dl_writer_classes):
		unregister_class(cls)

	del bpy.types.Scene.ootDLExportName
	del bpy.types.Scene.ootDLExportFolderName
	del bpy.types.Scene.ootDLExportCustomPath
	del bpy.types.Scene.ootDLExportUseCustomPath
	del bpy.types.Scene.ootDLRemoveVanillaData

	del bpy.types.Scene.ootDLImportName
	del bpy.types.Scene.ootDLImportFolderName
	del bpy.types.Scene.ootDLImportCustomPath
	del bpy.types.Scene.ootDLImportUseCustomPath

	del bpy.types.Scene.ootDLRemoveDoubles
	del bpy.types.Scene.ootDLImportNormals
	del bpy.types.Scene.ootDLImportDrawLayer

	del bpy.types.Scene.ootDLExportDrawLayer

	del bpy.types.Material.ootMaterial
	del bpy.types.Object.ootObjectMenu