#include <ultra64.h>

Lights1 ptcl_smoke_f3d_material_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

u64 ptcl_smoke_ptcl_smoke_ia8[] = {
	0xf0f0f0f1f1f0f0f0, 0xf0f0f0f0f0f0f0f0, 0xf0f0f1f2f2f1f1f2, 0xf2f1f0f0f0f0f0f0, 0xf0f0f1f1f2f2f3f6, 0xf5f1f2f1f0f1f0f0, 0xf0f0f1f2f3f5f7f8, 0xf8f4f3f2f1f1f1f0, 
	0xf0f0f1f3f7fbfcfa, 0xf8f6f4f3f2f0f0f0, 0xf1f1f2f4f9fefffc, 0xfbf7f7f5f2f1f0f0, 0xf1f3f4f7fbfcfdfc, 0xfbf8f7f5f4f1f0f0, 0xf2f4f6f8fafbf9f9, 0xfbfbf9f6f6f2f1f0, 
	0xf1f4f8f8f8faf9f8, 0xfafffffaf9f5f3f1, 0xf1f5f7f8f8f8f9f9, 0xfbfffffffcf8f5f2, 0xf1f2f4f8fafaf9f8, 0xfafffffffdf7f5f3, 0xf0f1f4fbfffdfbf8, 0xf8fcfffff9f6f4f2, 
	0xf0f0f4fafffffcf7, 0xf7f9fcfaf7f5f4f2, 0xf0f0f2f5fafbf8f4, 0xf5f6f6f6f5f2f2f2, 0xf0f0f0f1f3f3f3f2, 0xf2f2f2f2f1f1f1f1, 0xf0f0f0f0f0f0f0f0, 0xf0f0f0f1f0f0f0f0, 
	
};

Vtx ptcl_smoke_Plane_mesh_vtx_cull[8] = {
	{{{0, -4, -4},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{0, -4, 4},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{0, 4, 4},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{0, 4, -4},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{0, -4, -4},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{0, -4, 4},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{0, 4, 4},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{0, 4, -4},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
};

Vtx ptcl_smoke_Plane_mesh_vtx_0[4] = {
	{{{0, 4, -4},0, {-16, 496},{0x81, 0xFA, 0x0, 0xFF}}},
	{{{0, -4, -4},0, {496, 496},{0x81, 0xFA, 0x0, 0xFF}}},
	{{{0, -4, 4},0, {496, -16},{0x81, 0xFA, 0x0, 0xFF}}},
	{{{0, 4, 4},0, {-16, -16},{0x81, 0xFA, 0x0, 0xFF}}},
};

Gfx ptcl_smoke_Plane_mesh_tri_0[] = {
	gsSPVertex(ptcl_smoke_Plane_mesh_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_ptcl_smoke_f3d_material[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b_LOAD_BLOCK, 1, ptcl_smoke_ptcl_smoke_ia8),
	gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 127, 1024),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 2, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPSetTileSize(0, 0, 0, 60, 60),
	//gsDPSetPrimColor(0, 0, 254, 254, 254, 255),
	//gsSPSetLights1(ptcl_smoke_f3d_material_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_ptcl_smoke_f3d_material[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsSPEndDisplayList(),
};

Gfx ptcl_smoke_Plane_mesh[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(ptcl_smoke_Plane_mesh_vtx_cull + 0, 8, 0),
	//gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsDPSetRenderMode(G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2),
	gsSPDisplayList(mat_ptcl_smoke_f3d_material),
	gsSPDisplayList(ptcl_smoke_Plane_mesh_tri_0),
	gsSPDisplayList(mat_revert_ptcl_smoke_f3d_material),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};