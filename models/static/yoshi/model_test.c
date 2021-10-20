#include <ultra64.h>

Lights1 mario_Material_f3d_lights = gdSPDefLights1(
	0x73, 0x73, 0x73,
	0xE7, 0xE7, 0xE7, 0x28, 0x28, 0x28);

Vtx mario_Bone_001_mesh_layer_1_vtx_0[28] = {
	{{{-19, -15, 19},0, {624, 496},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{-19, 23, -19},0, {368, 240},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{-19, 23, 19},0, {368, 496},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{-19, -15, 19},0, {624, 496},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{-19, -15, -19},0, {624, 240},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{-19, 23, -19},0, {368, 240},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{19, -15, -19},0, {624, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{19, -15, 19},0, {624, 752},{0x81, 0x0, 0x0, 0xFF}}},
	{{{19, 23, 19},0, {368, 752},{0x81, 0x0, 0x0, 0xFF}}},
	{{{19, -15, -19},0, {624, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{19, 23, 19},0, {368, 752},{0x81, 0x0, 0x0, 0xFF}}},
	{{{19, 23, -19},0, {368, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{19, -15, 19},0, {880, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-19, -15, -19},0, {624, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-19, -15, 19},0, {624, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{19, -15, -19},0, {880, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{19, -15, 19},0, {624, 752},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-19, -15, 19},0, {624, 496},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-19, 23, 19},0, {368, 496},{0x0, 0x0, 0x81, 0xFF}}},
	{{{19, 23, 19},0, {368, 752},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-19, 23, 19},0, {368, 496},{0x0, 0x81, 0x0, 0xFF}}},
	{{{19, 23, -19},0, {112, 240},{0x0, 0x81, 0x0, 0xFF}}},
	{{{19, 23, 19},0, {112, 496},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-19, 23, -19},0, {368, 240},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-19, -15, -19},0, {624, 240},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{19, 23, -19},0, {368, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-19, 23, -19},0, {368, 240},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{19, -15, -19},0, {624, -16},{0x0, 0x0, 0x7F, 0xFF}}},
};

Gfx mario_Bone_001_mesh_layer_1_tri_0[] = {
	gsSPVertex(mario_Bone_001_mesh_layer_1_vtx_0 + 0, 28, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 8, 0, 9, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 15, 13, 0),
	gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
	gsSP2Triangles(20, 21, 22, 0, 20, 23, 21, 0),
	gsSP2Triangles(24, 25, 26, 0, 24, 27, 25, 0),
	gsSPEndDisplayList(),
};


Gfx mat_mario_Material_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(mario_Material_f3d_lights),
	gsSPEndDisplayList(),
};

Gfx mario_Bone_001_mesh_layer_1[] = {
	gsSPDisplayList(mat_mario_Material_f3d),
	gsSPDisplayList(mario_Bone_001_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx mario_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

