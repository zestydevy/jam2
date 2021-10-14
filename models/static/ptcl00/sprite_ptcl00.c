#include <ultra64.h>

Lights1 ptcl00_f3d_material_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

u64 ptcl00_sprite_ptcl00_i8[] = {
	0x0000000000000066, 0x0000000000000000, 0x0000000000000099, 0x0000000000000000, 0x00000000000000bb, 0x0000000000000000, 0x00000000000000dd, 0x0000000000000000, 
	0x00000000004466dd, 0x6644000000000000, 0x000000004466bbff, 0xbb66440000000000, 0x0000000066bbffff, 0xffbb660000000000, 0x6699bbddffffffff, 0xffffffddbb996600, 
	0x0000000066bbffff, 0xffbb660000000000, 0x000000004466bbff, 0xbb66440000000000, 0x00000000004466dd, 0x6644000000000000, 0x00000000000000dd, 0x0000000000000000, 
	0x00000000000000bb, 0x0000000000000000, 0x0000000000000099, 0x0000000000000000, 0x0000000000000066, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 
	
};

Vtx ptcl00_Plane_mesh_vtx_cull[8] = {
	{{{0, -4, -4},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{0, -4, 4},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{0, 4, 4},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{0, 4, -4},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{0, -4, -4},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{0, -4, 4},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{0, 4, 4},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{0, 4, -4},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
};

Vtx ptcl00_Plane_mesh_vtx_0[4] = {
	{{{0, 4, -4},0, {-16, 496},{0x81, 0xFA, 0x0, 0xFF}}},
	{{{0, -4, -4},0, {496, 496},{0x81, 0xFA, 0x0, 0xFF}}},
	{{{0, -4, 4},0, {496, -16},{0x81, 0xFA, 0x0, 0xFF}}},
	{{{0, 4, 4},0, {-16, -16},{0x81, 0xFA, 0x0, 0xFF}}},
};

Gfx ptcl00_Plane_mesh_tri_0[] = {
	gsSPVertex(ptcl00_Plane_mesh_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_ptcl00_f3d_material[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b_LOAD_BLOCK, 1, ptcl00_sprite_ptcl00_i8),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 127, 1024),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 2, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0),
	gsDPSetTileSize(0, 0, 0, 60, 60),
	gsSPSetLights1(ptcl00_f3d_material_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_ptcl00_f3d_material[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsSPEndDisplayList(),
};

Gfx ptcl00_Plane_mesh[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(ptcl00_Plane_mesh_vtx_cull + 0, 8, 0),
	gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_ptcl00_f3d_material),
	gsSPDisplayList(ptcl00_Plane_mesh_tri_0),
	gsSPDisplayList(mat_revert_ptcl00_f3d_material),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

