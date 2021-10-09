#include <ultra64.h>

Lights1 floor_f3d_material_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

u64 floor_floor_ci4[] = {
	0x0000001222223000, 0x0003222221000000, 0x0000001222223000, 0x0003222221000000, 0x0000001222223000, 0x0003222221000000, 0x0000001222223000, 0x0003222221000000, 
	0x0000001222223000, 0x0003222221000000, 0x0000001222223000, 0x0003222221000000, 0x1111114555556111, 0x1116555554111111, 0x2222225000007222, 0x2227000005222222, 
	0x2222225000007222, 0x2227000005222222, 0x2222225000007222, 0x2227000005222222, 0x2222225000007222, 0x2227000005222222, 0x2222225000007222, 0x2227000005222222, 
	0x3333336777778333, 0x3338777776333333, 0x0000001222223000, 0x0003222221000000, 0x0000001222223000, 0x0003222221000000, 0x0000001222223000, 0x0003222221000000, 
	0x0000001222223000, 0x0003222221000000, 0x0000001222223000, 0x0003222221000000, 0x0000001222223000, 0x0003222221000000, 0x3333336777778333, 0x3338777776333333, 
	0x2222225000007222, 0x2227000005222222, 0x2222225000007222, 0x2227000005222222, 0x2222225000007222, 0x2227000005222222, 0x2222225000007222, 0x2227000005222222, 
	0x2222225000007222, 0x2227000005222222, 0x1111114555556111, 0x1116555554111111, 0x0000001222223000, 0x0003222221000000, 0x0000001222223000, 0x0003222221000000, 
	0x0000001222223000, 0x0003222221000000, 0x0000001222223000, 0x0003222221000000, 0x0000001222223000, 0x0003222221000000, 0x0000001222223000, 0x0003222221000000, 
	
};

u64 floor_floor_ci4_pal_rgba16[] = {
	0x00019ce7ffffce73, 0x7bdf6319739d318d, 0x5295000000000000
};

Vtx floor_Plane_mesh_vtx_cull[8] = {
	{{{-100, 0, -100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-100, 0, 100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-100, 0, 100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-100, 0, -100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{100, 0, -100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{100, 0, 100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{100, 0, 100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{100, 0, -100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
};

Vtx floor_Plane_mesh_vtx_0[4] = {
	{{{-100, 0, 100},0, {-16, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{100, 0, 100},0, {1008, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{100, 0, -100},0, {1008, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-100, 0, -100},0, {-16, -16},{0x0, 0x7F, 0x0, 0xFF}}},
};

Gfx floor_Plane_mesh_tri_0[] = {
	gsSPVertex(floor_Plane_mesh_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_floor_f3d_material[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureLUT(G_TT_RGBA16),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, floor_floor_ci4_pal_rgba16),
	gsDPTileSync(),
	gsDPSetTile(0, 0, 0, 256, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTLUTCmd(7, 8),
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, floor_floor_ci4),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, 7, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 255, 1024),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 0, 0, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPSetLights1(floor_f3d_material_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_floor_f3d_material[] = {
	gsDPPipeSync(),
	gsDPSetTextureLUT(G_TT_NONE),
	gsSPEndDisplayList(),
};

Gfx floor_Plane_mesh[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(floor_Plane_mesh_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_floor_f3d_material),
	gsSPDisplayList(floor_Plane_mesh_tri_0),
	gsSPDisplayList(mat_revert_floor_f3d_material),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

