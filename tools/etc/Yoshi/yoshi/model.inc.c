Lights1 yoshi_yoshi_body_f3d_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Lights1 yoshi_yoshi_eyes_f3d_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Gfx yoshi_yoshi_body_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 yoshi_yoshi_body_rgba16[] = {
	#include "actors/mario/yoshi_body.rgba16.inc.c"
};

Gfx yoshi_yoshi_eyes_ci4_aligner[] = {gsSPEndDisplayList()};
u8 yoshi_yoshi_eyes_ci4[] = {
	0x00, 0x11, 0x12, 0x33, 0x33, 0x33, 0x33, 0x33, 
	0x00, 0x11, 0x23, 0x33, 0x33, 0x33, 0x33, 0x33, 
	0x00, 0x12, 0x44, 0x43, 0x33, 0x33, 0x33, 0x33, 
	0x00, 0x24, 0x44, 0x44, 0x35, 0x53, 0x44, 0x44, 
	0x00, 0x24, 0x44, 0x46, 0x77, 0x77, 0x64, 0x44, 
	0x00, 0x24, 0x84, 0x35, 0x77, 0x77, 0x53, 0x44, 
	0x01, 0x48, 0x88, 0x67, 0x77, 0x77, 0x76, 0x44, 
	0x01, 0x48, 0x88, 0x57, 0x77, 0x77, 0x76, 0x44, 
	0x02, 0x48, 0x88, 0x67, 0x77, 0x77, 0x76, 0x88, 
	0x02, 0x88, 0x88, 0x67, 0x77, 0x77, 0x76, 0x88, 
	0x02, 0x88, 0x88, 0x67, 0x77, 0x77, 0x79, 0x88, 
	0x02, 0x88, 0x88, 0x97, 0x79, 0x87, 0x79, 0x88, 
	0x02, 0x88, 0x88, 0xa7, 0x7a, 0x87, 0x79, 0x88, 
	0xb0, 0x88, 0x88, 0x87, 0x77, 0x77, 0x78, 0x88, 
	0xb0, 0x88, 0x88, 0x89, 0x77, 0x77, 0x68, 0x88, 
	0xb0, 0x88, 0x88, 0x88, 0x67, 0x76, 0x88, 0x88, 
	0xcb, 0xa8, 0x88, 0x88, 0x89, 0x68, 0x88, 0x88, 
	0xcb, 0x68, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 
	0xcc, 0x08, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 
	0xcc, 0xb6, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 
	0xcc, 0xcb, 0xa8, 0x88, 0x88, 0x88, 0x88, 0x88, 
	0xcc, 0xcb, 0xd8, 0x88, 0x88, 0x88, 0x88, 0x4d, 
	0xcc, 0xcc, 0xbd, 0xa8, 0x88, 0x88, 0x84, 0xdb, 
	0xcc, 0xcc, 0xcb, 0xb6, 0x94, 0x49, 0x6b, 0xbc, 
	0xcc, 0xcc, 0xcc, 0xcb, 0xbb, 0xbb, 0xbc, 0xcc, 
	0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 
	0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 
	0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 
	0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 
	0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 
	0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 
	0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 
	
};

Gfx yoshi_yoshi_eyes_ci4_pal_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 yoshi_yoshi_eyes_ci4_pal_rgba16[] = {
	0x2c, 0x07, 0x85, 0x67, 0xae, 0x2f, 0xcf, 0x39, 
	0xd7, 0x39, 0x94, 0x61, 0xbd, 0xab, 0x10, 0x41, 
	0xff, 0xff, 0xd6, 0xb3, 0xef, 0x7b, 0x35, 0x09, 
	0x3d, 0xcd, 0x6e, 0x17, 
};

Vtx yoshi_shin_L_mesh_layer_1_vtx_0[7] = {
	{{{-1, -4, 9},0, {2090, 32},{0x1D, 0xED, 0x7A, 0xFF}}},
	{{{-10, 10, 4},0, {2384, 336},{0x93, 0x3F, 0x13, 0xFF}}},
	{{{-10, -2, 5},0, {2328, 32},{0x89, 0x4, 0x2B, 0xFF}}},
	{{{2, 6, 10},0, {2058, 314},{0x20, 0x14, 0x79, 0xFF}}},
	{{{8, 6, 1},0, {1772, 356},{0x7D, 0xFE, 0xE8, 0xFF}}},
	{{{4, -4, 1},0, {1902, 32},{0x73, 0xD1, 0xE7, 0xFF}}},
	{{{-4, -3, -3},0, {2100, 32},{0xE3, 0xE9, 0x86, 0xFF}}},
};

Gfx yoshi_shin_L_mesh_layer_1_tri_0[] = {
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 6, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 216, 0, 300, 48),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 6, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 216, 0, 300, 48),
	gsSPVertex(yoshi_shin_L_mesh_layer_1_vtx_0 + 0, 7, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
	gsSP2Triangles(3, 0, 4, 0, 4, 0, 5, 0),
	gsSP1Triangle(1, 6, 2, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_foot_L_mesh_layer_1_vtx_0[20] = {
	{{{-14, 21, -6},0, {3420, 16},{0x99, 0x32, 0xC9, 0xFF}}},
	{{{14, -13, -6},0, {3908, 272},{0x5F, 0xC1, 0xC7, 0xFF}}},
	{{{-4, -17, -5},0, {3908, 16},{0xC6, 0x9F, 0xC6, 0xFF}}},
	{{{8, 25, -6},0, {3420, 272},{0x4B, 0x58, 0xCC, 0xFF}}},
	{{{5, -13, 9},0, {3466, 542},{0x15, 0xAD, 0x5E, 0xFF}}},
	{{{-11, -6, 9},0, {3466, 542},{0x88, 0xDC, 0x18, 0xFF}}},
	{{{-7, -5, 7},0, {3466, 542},{0x91, 0xD4, 0xD4, 0xFF}}},
	{{{15, 0, 9},0, {3466, 542},{0x7C, 0x12, 0x17, 0xFF}}},
	{{{11, -1, 7},0, {3466, 542},{0x79, 0x8, 0xD9, 0xFF}}},
	{{{-1, 12, 9},0, {3466, 542},{0xE6, 0x7B, 0x15, 0xFF}}},
	{{{0, 7, 6},0, {3466, 542},{0xEA, 0x68, 0x46, 0xFF}}},
	{{{-4, -17, -5},0, {3928, 344},{0xC6, 0x9F, 0xC6, 0xFF}}},
	{{{14, -13, -6},0, {3928, 344},{0x5F, 0xC1, 0xC7, 0xFF}}},
	{{{5, -13, 9},0, {3928, 546},{0x15, 0xAD, 0x5E, 0xFF}}},
	{{{11, -1, 7},0, {3632, 536},{0x79, 0x8, 0xD9, 0xFF}}},
	{{{8, 25, -6},0, {3392, 344},{0x4B, 0x58, 0xCC, 0xFF}}},
	{{{-4, 25, 7},0, {3512, 440},{0xEB, 0x59, 0x58, 0xFF}}},
	{{{-14, 21, -6},0, {3392, 344},{0x99, 0x32, 0xC9, 0xFF}}},
	{{{-7, -5, 7},0, {3632, 536},{0x91, 0xD4, 0xD4, 0xFF}}},
	{{{0, 7, 6},0, {3632, 536},{0xEA, 0x68, 0x46, 0xFF}}},
};

Gfx yoshi_foot_L_mesh_layer_1_tri_0[] = {
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 5, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 420, 0, 492, 72),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 5, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 420, 0, 492, 72),
	gsSPVertex(yoshi_foot_L_mesh_layer_1_vtx_0 + 0, 20, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 7, 5, 0),
	gsSP2Triangles(4, 8, 7, 0, 7, 8, 9, 0),
	gsSP2Triangles(10, 9, 8, 0, 5, 9, 10, 0),
	gsSP2Triangles(6, 5, 10, 0, 7, 9, 5, 0),
	gsSP2Triangles(11, 12, 13, 0, 13, 12, 14, 0),
	gsSP2Triangles(14, 12, 15, 0, 14, 15, 16, 0),
	gsSP2Triangles(17, 16, 15, 0, 18, 16, 17, 0),
	gsSP2Triangles(17, 11, 18, 0, 18, 11, 13, 0),
	gsSP2Triangles(19, 16, 18, 0, 14, 16, 19, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_hip_L_skinned_mesh_layer_1_vtx_0[6] = {
	{{{-10, 10, 4},0, {2384, 336},{0x93, 0x3F, 0x13, 0xFF}}},
	{{{-4, -3, -3},0, {2100, 32},{0xE3, 0xE9, 0x86, 0xFF}}},
	{{{4, -4, 1},0, {1902, 32},{0x73, 0xD1, 0xE7, 0xFF}}},
	{{{8, 6, 1},0, {1880, 376},{0x7D, 0xFE, 0xE8, 0xFF}}},
	{{{8, 6, 1},0, {1772, 356},{0x7D, 0xFE, 0xE8, 0xFF}}},
	{{{2, 6, 10},0, {2058, 314},{0x20, 0x14, 0x79, 0xFF}}},
};

Gfx yoshi_hip_L_skinned_mesh_layer_1_tri_0[] = {
	gsSPVertex(yoshi_hip_L_skinned_mesh_layer_1_vtx_0 + 0, 6, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_hip_L_mesh_layer_1_vtx_0[3] = {
	{{{-1, 2, -6},0, {2060, 312},{0xF6, 0x2E, 0x8A, 0xFF}}},
	{{{5, 7, 3},0, {1912, 414},{0x3A, 0x71, 0x9, 0xFF}}},
	{{{-1, 2, -6},0, {1880, 376},{0xF6, 0x2E, 0x8A, 0xFF}}},
};

Gfx yoshi_hip_L_mesh_layer_1_tri_0[] = {
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 6, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 216, 0, 300, 52),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 6, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 216, 0, 300, 52),
	gsSPVertex(yoshi_hip_L_mesh_layer_1_vtx_0 + 0, 3, 6),
	gsSP2Triangles(0, 6, 1, 0, 1, 6, 2, 0),
	gsSP2Triangles(4, 2, 6, 0, 0, 7, 8, 0),
	gsSP2Triangles(5, 7, 0, 0, 5, 3, 7, 0),
	gsSP1Triangle(8, 7, 3, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_hip_L_mesh_layer_1_vtx_1[13] = {
	{{{3, 8, 11},0, {2058, 314},{0x25, 0x6, 0x79, 0xFF}}},
	{{{2, -2, 10},0, {2078, 346},{0x1A, 0xEF, 0x7B, 0xFF}}},
	{{{8, 0, 1},0, {1772, 356},{0x7D, 0x8, 0xEA, 0xFF}}},
	{{{-12, 8, 5},0, {2384, 336},{0x85, 0x15, 0x18, 0xFF}}},
	{{{-11, 0, 4},0, {2384, 336},{0x85, 0xED, 0x18, 0xFF}}},
	{{{-2, 2, -6},0, {2060, 312},{0xF9, 0x15, 0x83, 0xFF}}},
	{{{-2, 15, -3},0, {1880, 376},{0xEF, 0x3A, 0x90, 0xFF}}},
	{{{-2, 2, -6},0, {1880, 376},{0xF9, 0x15, 0x83, 0xFF}}},
	{{{-12, 8, 5},0, {1880, 376},{0x85, 0x15, 0x18, 0xFF}}},
	{{{8, 0, 1},0, {1880, 376},{0x7D, 0x8, 0xEA, 0xFF}}},
	{{{7, 19, 5},0, {1880, 376},{0x67, 0x49, 0xC, 0xFF}}},
	{{{-2, 23, 6},0, {1880, 376},{0xE8, 0x7A, 0x1A, 0xFF}}},
	{{{3, 8, 11},0, {1880, 376},{0x25, 0x6, 0x79, 0xFF}}},
};

Gfx yoshi_hip_L_mesh_layer_1_tri_1[] = {
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 6, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 216, 32, 300, 48),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 6, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 216, 32, 300, 48),
	gsSPVertex(yoshi_hip_L_mesh_layer_1_vtx_1 + 0, 13, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(1, 3, 4, 0, 3, 5, 4, 0),
	gsSP2Triangles(6, 7, 8, 0, 6, 9, 7, 0),
	gsSP2Triangles(9, 6, 10, 0, 6, 11, 10, 0),
	gsSP2Triangles(6, 8, 11, 0, 11, 8, 12, 0),
	gsSP2Triangles(10, 11, 12, 0, 10, 12, 9, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_shin_R_mesh_layer_1_vtx_0[7] = {
	{{{0, -4, -7},0, {2090, 32},{0xF, 0xED, 0x83, 0xFF}}},
	{{{-9, -2, -2},0, {2328, 32},{0x84, 0x2, 0xE3, 0xFF}}},
	{{{-9, 9, -1},0, {2384, 336},{0x91, 0x3D, 0xF9, 0xFF}}},
	{{{-2, -3, 5},0, {2100, 32},{0xF2, 0xE8, 0x7C, 0xFF}}},
	{{{2, 6, -9},0, {2058, 314},{0x11, 0x15, 0x84, 0xFF}}},
	{{{9, 6, 0},0, {1772, 356},{0x7F, 0x0, 0x9, 0xFF}}},
	{{{6, -4, -1},0, {1902, 32},{0x76, 0xD3, 0xC, 0xFF}}},
};

Gfx yoshi_shin_R_mesh_layer_1_tri_0[] = {
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 6, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 216, 0, 300, 48),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 6, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 216, 0, 300, 48),
	gsSPVertex(yoshi_shin_R_mesh_layer_1_vtx_0 + 0, 7, 0),
	gsSP2Triangles(0, 1, 2, 0, 2, 1, 3, 0),
	gsSP2Triangles(4, 0, 2, 0, 5, 0, 4, 0),
	gsSP1Triangle(5, 6, 0, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_foot_R_mesh_layer_1_vtx_0[20] = {
	{{{-9, 26, -6},0, {3420, 272},{0xAE, 0x52, 0xCB, 0xFF}}},
	{{{14, 24, -5},0, {3420, 16},{0x63, 0x3C, 0xCC, 0xFF}}},
	{{{-12, -12, -6},0, {3908, 272},{0xA9, 0xB9, 0xC5, 0xFF}}},
	{{{7, -15, -5},0, {3908, 16},{0x44, 0xA5, 0xC7, 0xFF}}},
	{{{-2, -12, 9},0, {3466, 542},{0xF1, 0xAA, 0x5D, 0xFF}}},
	{{{9, -3, 7},0, {3466, 542},{0x73, 0xDE, 0xD6, 0xFF}}},
	{{{13, -3, 9},0, {3466, 542},{0x7A, 0xE7, 0x1A, 0xFF}}},
	{{{1, 9, 7},0, {3466, 542},{0xC, 0x68, 0x48, 0xFF}}},
	{{{2, 14, 9},0, {3466, 542},{0xF, 0x7C, 0x17, 0xFF}}},
	{{{-9, 0, 6},0, {3466, 542},{0x88, 0xFF, 0xD7, 0xFF}}},
	{{{-13, 0, 9},0, {3466, 542},{0x83, 0x7, 0x15, 0xFF}}},
	{{{7, -15, -5},0, {3928, 344},{0x44, 0xA5, 0xC7, 0xFF}}},
	{{{-2, -12, 9},0, {3928, 546},{0xF1, 0xAA, 0x5D, 0xFF}}},
	{{{-12, -12, -6},0, {3928, 344},{0xA9, 0xB9, 0xC5, 0xFF}}},
	{{{9, -3, 7},0, {3632, 536},{0x73, 0xDE, 0xD6, 0xFF}}},
	{{{14, 24, -5},0, {3392, 344},{0x63, 0x3C, 0xCC, 0xFF}}},
	{{{3, 27, 7},0, {3512, 440},{0xB, 0x5A, 0x59, 0xFF}}},
	{{{-9, 26, -6},0, {3392, 344},{0xAE, 0x52, 0xCB, 0xFF}}},
	{{{-9, 0, 6},0, {3632, 536},{0x88, 0xFF, 0xD7, 0xFF}}},
	{{{1, 9, 7},0, {3632, 536},{0xC, 0x68, 0x48, 0xFF}}},
};

Gfx yoshi_foot_R_mesh_layer_1_tri_0[] = {
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 5, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 420, 0, 492, 72),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 5, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 420, 0, 492, 72),
	gsSPVertex(yoshi_foot_R_mesh_layer_1_vtx_0 + 0, 20, 0),
	gsSP2Triangles(0, 1, 2, 0, 2, 1, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 6, 5, 7, 0),
	gsSP2Triangles(6, 7, 8, 0, 8, 7, 9, 0),
	gsSP2Triangles(8, 9, 10, 0, 10, 9, 4, 0),
	gsSP2Triangles(4, 6, 10, 0, 10, 6, 8, 0),
	gsSP2Triangles(11, 12, 13, 0, 11, 14, 12, 0),
	gsSP2Triangles(15, 14, 11, 0, 16, 14, 15, 0),
	gsSP2Triangles(15, 17, 16, 0, 17, 18, 16, 0),
	gsSP2Triangles(13, 18, 17, 0, 13, 12, 18, 0),
	gsSP2Triangles(18, 19, 16, 0, 19, 14, 16, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_hip_R_skinned_mesh_layer_1_vtx_0[6] = {
	{{{-9, 9, -1},0, {2384, 336},{0x91, 0x3D, 0xF9, 0xFF}}},
	{{{-2, -3, 5},0, {2100, 32},{0xF2, 0xE8, 0x7C, 0xFF}}},
	{{{6, -4, -1},0, {1902, 32},{0x76, 0xD3, 0xC, 0xFF}}},
	{{{9, 6, 0},0, {1772, 356},{0x7F, 0x0, 0x9, 0xFF}}},
	{{{9, 6, 0},0, {1972, 374},{0x7F, 0x0, 0x9, 0xFF}}},
	{{{2, 6, -9},0, {2058, 314},{0x11, 0x15, 0x84, 0xFF}}},
};

Gfx yoshi_hip_R_skinned_mesh_layer_1_tri_0[] = {
	gsSPVertex(yoshi_hip_R_skinned_mesh_layer_1_vtx_0 + 0, 6, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_hip_R_mesh_layer_1_vtx_0[3] = {
	{{{1, 2, 7},0, {2060, 312},{0x2, 0x2E, 0x76, 0xFF}}},
	{{{6, 8, -2},0, {2066, 380},{0x37, 0x71, 0xF0, 0xFF}}},
	{{{1, 2, 7},0, {1972, 374},{0x2, 0x2E, 0x76, 0xFF}}},
};

Gfx yoshi_hip_R_mesh_layer_1_tri_0[] = {
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 6, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 216, 0, 300, 48),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 6, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 216, 0, 300, 48),
	gsSPVertex(yoshi_hip_R_mesh_layer_1_vtx_0 + 0, 3, 6),
	gsSP2Triangles(0, 1, 6, 0, 6, 1, 2, 0),
	gsSP2Triangles(6, 2, 3, 0, 7, 0, 8, 0),
	gsSP2Triangles(5, 0, 7, 0, 5, 7, 4, 0),
	gsSP1Triangle(7, 8, 4, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_hip_R_mesh_layer_1_vtx_1[13] = {
	{{{3, 9, -10},0, {2058, 314},{0x17, 0x6, 0x83, 0xFF}}},
	{{{10, 1, -1},0, {1772, 356},{0x7E, 0xB, 0x7, 0xFF}}},
	{{{2, -1, -9},0, {2078, 346},{0xC, 0xF0, 0x83, 0xFF}}},
	{{{-11, 8, -2},0, {2384, 336},{0x83, 0x12, 0xF6, 0xFF}}},
	{{{-9, -1, -1},0, {2384, 336},{0x83, 0xEA, 0xF7, 0xFF}}},
	{{{1, 2, 7},0, {2060, 312},{0x6, 0x15, 0x7D, 0xFF}}},
	{{{10, 1, -1},0, {1972, 374},{0x7E, 0xB, 0x7, 0xFF}}},
	{{{-1, 15, 5},0, {1972, 374},{0xFB, 0x3A, 0x71, 0xFF}}},
	{{{1, 2, 7},0, {1972, 374},{0x6, 0x15, 0x7D, 0xFF}}},
	{{{8, 19, -5},0, {1972, 374},{0x63, 0x4C, 0xE8, 0xFF}}},
	{{{3, 9, -10},0, {1972, 374},{0x17, 0x6, 0x83, 0xFF}}},
	{{{-1, 23, -4},0, {1972, 374},{0xE2, 0x79, 0xE9, 0xFF}}},
	{{{-11, 8, -2},0, {1972, 374},{0x83, 0x12, 0xF6, 0xFF}}},
};

Gfx yoshi_hip_R_mesh_layer_1_tri_1[] = {
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 6, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 216, 32, 300, 48),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 6, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 216, 32, 300, 48),
	gsSPVertex(yoshi_hip_R_mesh_layer_1_vtx_1 + 0, 13, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(3, 2, 4, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 8, 0, 6, 9, 7, 0),
	gsSP2Triangles(10, 9, 6, 0, 11, 9, 10, 0),
	gsSP2Triangles(11, 10, 12, 0, 7, 11, 12, 0),
	gsSP2Triangles(8, 7, 12, 0, 7, 9, 11, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_spine_mesh_layer_1_vtx_0[26] = {
	{{{7, -17, 18},0, {910, 106},{0x1E, 0xAC, 0x5A, 0xFF}}},
	{{{24, -11, -1},0, {72, 322},{0x74, 0xCC, 0xFE, 0xFF}}},
	{{{18, -2, 17},0, {526, 428},{0x58, 0xF8, 0x5C, 0xFF}}},
	{{{4, -24, -1},0, {726, 0},{0x10, 0x82, 0x0, 0xFF}}},
	{{{-17, -13, 14},0, {1540, 32},{0xC3, 0xC7, 0x60, 0xFF}}},
	{{{-4, 1, 22},0, {1494, 430},{0xE2, 0xB, 0x7B, 0xFF}}},
	{{{15, 15, 15},0, {466, 916},{0x4D, 0x30, 0x59, 0xFF}}},
	{{{7, -17, -19},0, {910, 106},{0x1B, 0xAC, 0xA5, 0xFF}}},
	{{{-20, -13, -14},0, {1540, 32},{0xBE, 0xCC, 0xA1, 0xFF}}},
	{{{-5, 1, -23},0, {1494, 430},{0xDE, 0xB, 0x86, 0xFF}}},
	{{{17, -2, -19},0, {526, 428},{0x54, 0xF8, 0xA1, 0xFF}}},
	{{{15, 15, -17},0, {466, 916},{0x4A, 0x30, 0xA4, 0xFF}}},
	{{{-5, 1, -23},0, {2824, 1496},{0xDE, 0xB, 0x86, 0xFF}}},
	{{{-20, -13, -14},0, {2888, 1186},{0xBE, 0xCC, 0xA1, 0xFF}}},
	{{{-29, -1, 0},0, {4080, 1238},{0xEF, 0x7E, 0x0, 0xFF}}},
	{{{-40, 4, 0},0, {3834, 1554},{0x9D, 0x50, 0x3, 0xFF}}},
	{{{-17, -13, 14},0, {2612, 1120},{0xC3, 0xC7, 0x60, 0xFF}}},
	{{{-29, -1, 0},0, {3228, 1554},{0xEF, 0x7E, 0x0, 0xFF}}},
	{{{-20, -13, -14},0, {2612, 1120},{0xBE, 0xCC, 0xA1, 0xFF}}},
	{{{-4, 1, 22},0, {2824, 1496},{0xE2, 0xB, 0x7B, 0xFF}}},
	{{{-17, -13, 14},0, {2888, 1186},{0xC3, 0xC7, 0x60, 0xFF}}},
	{{{4, -24, -1},0, {110, 1252},{0x10, 0x82, 0x0, 0xFF}}},
	{{{-17, -13, 14},0, {688, 1264},{0xC3, 0xC7, 0x60, 0xFF}}},
	{{{-26, -18, -1},0, {372, 1052},{0xB4, 0x9A, 0x1, 0xFF}}},
	{{{-40, 4, 0},0, {870, 764},{0x9D, 0x50, 0x3, 0xFF}}},
	{{{-20, -13, -14},0, {688, 1264},{0xBE, 0xCC, 0xA1, 0xFF}}},
};

Gfx yoshi_spine_mesh_layer_1_tri_0[] = {
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 4, 0, 196, 116),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 13, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 4, 0, 196, 116),
	gsSPVertex(yoshi_spine_mesh_layer_1_vtx_0 + 0, 12, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(0, 4, 3, 0, 5, 4, 0, 0),
	gsSP2Triangles(0, 2, 5, 0, 5, 2, 6, 0),
	gsSP2Triangles(1, 3, 7, 0, 7, 3, 8, 0),
	gsSP2Triangles(9, 7, 8, 0, 7, 9, 10, 0),
	gsSP2Triangles(11, 10, 9, 0, 1, 7, 10, 0),
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 12, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 320, 136, 508, 196),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 12, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 320, 136, 508, 196),
	gsSPVertex(yoshi_spine_mesh_layer_1_vtx_0 + 12, 9, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(3, 5, 6, 0, 7, 2, 8, 0),
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 7, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 8, 88, 112, 160),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 7, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 8, 88, 112, 160),
	gsSPVertex(yoshi_spine_mesh_layer_1_vtx_0 + 21, 5, 0),
	gsSP2Triangles(0, 1, 2, 0, 2, 1, 3, 0),
	gsSP2Triangles(2, 3, 4, 0, 4, 0, 2, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_back_skinned_mesh_layer_1_vtx_0[14] = {
	{{{18, -2, 17},0, {526, 428},{0x58, 0xF8, 0x5C, 0xFF}}},
	{{{24, -11, -1},0, {626, 422},{0x74, 0xCC, 0xFE, 0xFF}}},
	{{{17, -2, -19},0, {526, 428},{0x54, 0xF8, 0xA1, 0xFF}}},
	{{{15, 15, -17},0, {466, 916},{0x4A, 0x30, 0xA4, 0xFF}}},
	{{{15, 15, 15},0, {334, 1124},{0x4D, 0x30, 0x59, 0xFF}}},
	{{{15, 15, -17},0, {334, 1124},{0x4A, 0x30, 0xA4, 0xFF}}},
	{{{15, 15, 15},0, {466, 916},{0x4D, 0x30, 0x59, 0xFF}}},
	{{{-5, 1, -23},0, {1494, 430},{0xDE, 0xB, 0x86, 0xFF}}},
	{{{-29, -1, 0},0, {4080, 1238},{0xEF, 0x7E, 0x0, 0xFF}}},
	{{{15, 15, -17},0, {278, 1120},{0x4A, 0x30, 0xA4, 0xFF}}},
	{{{-5, 1, -23},0, {2824, 1496},{0xDE, 0xB, 0x86, 0xFF}}},
	{{{-4, 1, 22},0, {1494, 430},{0xE2, 0xB, 0x7B, 0xFF}}},
	{{{-4, 1, 22},0, {2824, 1496},{0xE2, 0xB, 0x7B, 0xFF}}},
	{{{15, 15, 15},0, {278, 1120},{0x4D, 0x30, 0x59, 0xFF}}},
};

Gfx yoshi_back_skinned_mesh_layer_1_tri_0[] = {
	gsSPVertex(yoshi_back_skinned_mesh_layer_1_vtx_0 + 0, 14, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_back_mesh_layer_1_vtx_0[10] = {
	{{{-1, 20, -13},0, {938, 1060},{0xEF, 0x62, 0xB0, 0xFF}}},
	{{{0, 20, 12},0, {938, 1060},{0xF2, 0x61, 0x51, 0xFF}}},
	{{{21, 7, -1},0, {480, 986},{0x73, 0x37, 0xFE, 0xFF}}},
	{{{21, 7, -1},0, {172, 1092},{0x73, 0x37, 0xFE, 0xFF}}},
	{{{8, 21, -1},0, {630, 1556},{0x39, 0x72, 0xFF, 0xFF}}},
	{{{-1, 20, -13},0, {304, 1680},{0xEF, 0x62, 0xB0, 0xFF}}},
	{{{0, 20, 12},0, {304, 1680},{0xF2, 0x61, 0x51, 0xFF}}},
	{{{-1, 20, -13},0, {3448, 2032},{0xEF, 0x62, 0xB0, 0xFF}}},
	{{{-6, 20, -1},0, {4080, 2032},{0xBA, 0x6A, 0x1, 0xFF}}},
	{{{0, 20, 12},0, {3448, 2032},{0xF2, 0x61, 0x51, 0xFF}}},
};

Gfx yoshi_back_mesh_layer_1_tri_0[] = {
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 11, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 16, 48, 188, 212),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 11, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 16, 48, 188, 212),
	gsSPVertex(yoshi_back_mesh_layer_1_vtx_0 + 0, 7, 14),
	gsSP2Triangles(3, 7, 14, 0, 11, 6, 15, 0),
	gsSP2Triangles(16, 2, 3, 0, 16, 1, 2, 0),
	gsSP2Triangles(0, 1, 16, 0, 16, 6, 0, 0),
	gsSP2Triangles(4, 17, 18, 0, 18, 17, 5, 0),
	gsSP2Triangles(19, 18, 9, 0, 20, 13, 18, 0),
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 11, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 348, 148, 508, 252),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 11, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 348, 148, 508, 252),
	gsSPVertex(yoshi_back_mesh_layer_1_vtx_0 + 7, 3, 14),
	gsSP2Triangles(8, 14, 10, 0, 8, 15, 14, 0),
	gsSP2Triangles(16, 15, 8, 0, 12, 16, 8, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_back_mesh_layer_1_vtx_1[4] = {
	{{{-6, 20, -1},0, {630, 1902},{0xBA, 0x6A, 0x1, 0xFF}}},
	{{{8, 21, -1},0, {630, 1556},{0x39, 0x72, 0xFF, 0xFF}}},
	{{{-1, 20, -13},0, {304, 1680},{0xEF, 0x62, 0xB0, 0xFF}}},
	{{{0, 20, 12},0, {304, 1680},{0xF2, 0x61, 0x51, 0xFF}}},
};

Gfx yoshi_back_mesh_layer_1_tri_1[] = {
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 32, 188, 80, 240),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 32, 188, 80, 240),
	gsSPVertex(yoshi_back_mesh_layer_1_vtx_1 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_head_mesh_layer_1_vtx_0[126] = {
	{{{23, 5, -1},0, {2646, 28},{0xF2, 0x82, 0x1, 0xFF}}},
	{{{16, 15, 13},0, {2666, 42},{0xB, 0xC0, 0x6D, 0xFF}}},
	{{{17, 7, -1},0, {2656, 30},{0x6, 0x81, 0x3, 0xFF}}},
	{{{17, 7, -1},0, {2656, 32},{0x6, 0x81, 0x3, 0xFF}}},
	{{{15, 14, -17},0, {2666, 42},{0xD, 0xC3, 0x91, 0xFF}}},
	{{{-3, 7, 21},0, {3112, 740},{0xD, 0xB1, 0x63, 0xFF}}},
	{{{17, 7, -1},0, {3112, 740},{0x6, 0x81, 0x3, 0xFF}}},
	{{{16, 15, 13},0, {3112, 740},{0xB, 0xC0, 0x6D, 0xFF}}},
	{{{-2, 22, 25},0, {3112, 740},{0x11, 0x13, 0x7C, 0xFF}}},
	{{{-15, 14, 21},0, {3112, 740},{0xB7, 0xDC, 0x61, 0xFF}}},
	{{{-10, 0, 8},0, {3112, 740},{0xD2, 0x92, 0x2D, 0xFF}}},
	{{{44, 34, 14},0, {3314, 144},{0x51, 0x2D, 0x57, 0xFF}}},
	{{{43, 43, -2},0, {2994, 304},{0x4D, 0x65, 0xFF, 0xFF}}},
	{{{27, 41, 14},0, {3314, 432},{0xFF, 0x5B, 0x59, 0xFF}}},
	{{{51, 26, -2},0, {2994, 16},{0x7F, 0xFB, 0xFE, 0xFF}}},
	{{{43, 34, -17},0, {3314, 144},{0x4E, 0x2D, 0xA6, 0xFF}}},
	{{{26, 41, -17},0, {3314, 432},{0xFC, 0x5B, 0xA7, 0xFF}}},
	{{{43, 43, -2},0, {2640, 496},{0x4D, 0x65, 0xFF, 0xFF}}},
	{{{25, 48, -1},0, {2640, 496},{0xF1, 0x7E, 0x0, 0xFF}}},
	{{{27, 41, 14},0, {2640, 496},{0xFF, 0x5B, 0x59, 0xFF}}},
	{{{26, 41, -17},0, {2640, 496},{0xFC, 0x5B, 0xA7, 0xFF}}},
	{{{25, 11, -17},0, {2640, 60},{0x1, 0xA5, 0xA7, 0xFF}}},
	{{{15, 14, -17},0, {2664, 44},{0xD, 0xC3, 0x91, 0xFF}}},
	{{{41, 9, -1},0, {2616, 32},{0x49, 0x98, 0x1, 0xFF}}},
	{{{42, 19, -17},0, {2612, 56},{0x49, 0xCD, 0xA6, 0xFF}}},
	{{{25, 28, -22},0, {2638, 68},{0xF6, 0x8, 0x82, 0xFF}}},
	{{{15, 14, -17},0, {2666, 46},{0xD, 0xC3, 0x91, 0xFF}}},
	{{{7, 36, -12},0, {2672, 72},{0x27, 0x36, 0x94, 0xFF}}},
	{{{26, 41, -17},0, {2636, 74},{0xFC, 0x5B, 0xA7, 0xFF}}},
	{{{25, 48, -1},0, {2658, 90},{0xF1, 0x7E, 0x0, 0xFF}}},
	{{{10, 39, -1},0, {2680, 78},{0x2F, 0x76, 0x0, 0xFF}}},
	{{{8, 36, 11},0, {2672, 72},{0x2C, 0x33, 0x6C, 0xFF}}},
	{{{8, 36, 11},0, {2672, 72},{0x2C, 0x33, 0x6C, 0xFF}}},
	{{{27, 41, 14},0, {2636, 74},{0xFF, 0x5B, 0x59, 0xFF}}},
	{{{25, 48, -1},0, {2658, 90},{0xF1, 0x7E, 0x0, 0xFF}}},
	{{{26, 28, 20},0, {2638, 68},{0xF7, 0x5, 0x7F, 0xFF}}},
	{{{16, 15, 13},0, {2664, 44},{0xB, 0xC0, 0x6D, 0xFF}}},
	{{{25, 11, 14},0, {2640, 60},{0xFC, 0xA7, 0x5B, 0xFF}}},
	{{{23, 5, -1},0, {2646, 28},{0xF2, 0x82, 0x1, 0xFF}}},
	{{{41, 9, -1},0, {2616, 32},{0x49, 0x98, 0x1, 0xFF}}},
	{{{42, 19, 14},0, {2612, 56},{0x4D, 0xCE, 0x58, 0xFF}}},
	{{{51, 26, -2},0, {2594, 54},{0x7F, 0xFB, 0xFE, 0xFF}}},
	{{{42, 19, -17},0, {2612, 56},{0x49, 0xCD, 0xA6, 0xFF}}},
	{{{43, 34, -17},0, {2608, 74},{0x4E, 0x2D, 0xA6, 0xFF}}},
	{{{25, 28, -22},0, {2638, 68},{0xF6, 0x8, 0x82, 0xFF}}},
	{{{26, 41, -17},0, {2636, 74},{0xFC, 0x5B, 0xA7, 0xFF}}},
	{{{44, 34, 14},0, {2608, 74},{0x51, 0x2D, 0x57, 0xFF}}},
	{{{-10, 40, -10},0, {2942, 82},{0x9A, 0x33, 0xC7, 0xFF}}},
	{{{-7, 53, -16},0, {2798, 156},{0xBF, 0x2E, 0x9D, 0xFF}}},
	{{{1, 37, -16},0, {2942, 164},{0x14, 0x26, 0x88, 0xFF}}},
	{{{-8, 56, -1},0, {2760, -16},{0x9D, 0x50, 0x1, 0xFF}}},
	{{{-10, 40, 9},0, {2942, -114},{0x9D, 0x33, 0x3D, 0xFF}}},
	{{{-18, 35, 0},0, {2760, -16},{0x9D, 0x50, 0x1, 0xFF}}},
	{{{-4, 60, -8},0, {2720, 72},{0xE4, 0x7A, 0xEC, 0xFF}}},
	{{{7, 56, -1},0, {2720, 72},{0x5D, 0x57, 0xFF, 0xFF}}},
	{{{-4, 60, 7},0, {2720, 72},{0xE5, 0x7A, 0x15, 0xFF}}},
	{{{-6, 53, 15},0, {2798, 156},{0xC3, 0x2E, 0x66, 0xFF}}},
	{{{-10, 40, 9},0, {2942, 82},{0x9D, 0x33, 0x3D, 0xFF}}},
	{{{2, 37, 15},0, {2942, 164},{0x19, 0x26, 0x77, 0xFF}}},
	{{{-4, 7, -22},0, {3112, 740},{0x7, 0xB0, 0x9D, 0xFF}}},
	{{{15, 14, -17},0, {3112, 740},{0xD, 0xC3, 0x91, 0xFF}}},
	{{{17, 7, -1},0, {3112, 740},{0x6, 0x81, 0x3, 0xFF}}},
	{{{-3, 22, -26},0, {3112, 740},{0x9, 0x14, 0x83, 0xFF}}},
	{{{-16, 14, -21},0, {3112, 740},{0xB3, 0xDC, 0xA1, 0xFF}}},
	{{{-23, 13, 0},0, {3388, 716},{0x85, 0xDF, 0x2, 0xFF}}},
	{{{-34, 20, 0},0, {3388, 716},{0x8A, 0xD2, 0x2, 0xFF}}},
	{{{-23, 23, -4},0, {3388, 716},{0xE8, 0x4, 0x83, 0xFF}}},
	{{{-23, 23, 3},0, {3388, 716},{0xED, 0x4, 0x7E, 0xFF}}},
	{{{-33, 29, 0},0, {3388, 716},{0xA5, 0x59, 0x1, 0xFF}}},
	{{{-20, 31, 0},0, {3388, 716},{0x83, 0xF0, 0xF, 0xFF}}},
	{{{-27, 39, 0},0, {3388, 716},{0x82, 0xB, 0x3, 0xFF}}},
	{{{-16, 35, -4},0, {3388, 716},{0xEC, 0x9, 0x83, 0xFF}}},
	{{{-14, 35, 3},0, {3388, 716},{0xF5, 0xD, 0x7E, 0xFF}}},
	{{{-21, 46, 0},0, {3388, 716},{0xDA, 0x79, 0x1, 0xFF}}},
	{{{-8, 41, -1},0, {3388, 716},{0x2E, 0x76, 0x7, 0xFF}}},
	{{{-30, 3, 0},0, {3388, 716},{0x82, 0xF2, 0x2, 0xFF}}},
	{{{-18, 6, 2},0, {3388, 716},{0xF7, 0xF2, 0x7E, 0xFF}}},
	{{{-23, -5, 0},0, {3388, 716},{0xDD, 0x86, 0x0, 0xFF}}},
	{{{-18, 6, -3},0, {3388, 716},{0xF2, 0xF2, 0x83, 0xFF}}},
	{{{-10, 0, -1},0, {3388, 716},{0x2E, 0x8A, 0x0, 0xFF}}},
	{{{-10, 0, 8},0, {1208, 1470},{0xD2, 0x92, 0x2D, 0xFF}}},
	{{{-21, 16, 14},0, {1436, 1672},{0x91, 0xED, 0x3B, 0xFF}}},
	{{{-22, 7, 0},0, {962, 1646},{0x96, 0xB9, 0x2, 0xFF}}},
	{{{-10, 0, -9},0, {1208, 1470},{0xD1, 0x92, 0xD5, 0xFF}}},
	{{{-21, 16, -14},0, {1436, 1672},{0x8F, 0xED, 0xC9, 0xFF}}},
	{{{8, 36, 11},0, {1394, 1912},{0x2C, 0x33, 0x6C, 0xFF}}},
	{{{-2, 22, 25},0, {1396, 1342},{0x11, 0x13, 0x7C, 0xFF}}},
	{{{16, 15, 13},0, {1846, 1594},{0xB, 0xC0, 0x6D, 0xFF}}},
	{{{2, 37, 15},0, {1690, 2006},{0x19, 0x26, 0x77, 0xFF}}},
	{{{-13, 28, 19},0, {2058, 1688},{0xBB, 0x39, 0x5A, 0xFF}}},
	{{{-10, 40, 9},0, {2058, 2032},{0x9D, 0x33, 0x3D, 0xFF}}},
	{{{-18, 35, 0},0, {2624, 1914},{0x9D, 0x50, 0x1, 0xFF}}},
	{{{-25, 22, 0},0, {2620, 1670},{0x83, 0x19, 0x2, 0xFF}}},
	{{{-14, 28, -20},0, {2058, 1688},{0xB8, 0x39, 0xA8, 0xFF}}},
	{{{-10, 40, -10},0, {2058, 2032},{0x9A, 0x33, 0xC7, 0xFF}}},
	{{{1, 37, -16},0, {1690, 2006},{0x14, 0x26, 0x88, 0xFF}}},
	{{{-3, 22, -26},0, {1396, 1342},{0x9, 0x14, 0x83, 0xFF}}},
	{{{7, 36, -12},0, {1394, 1912},{0x27, 0x36, 0x94, 0xFF}}},
	{{{15, 14, -17},0, {1846, 1594},{0xD, 0xC3, 0x91, 0xFF}}},
	{{{-16, 14, -21},0, {1396, 1344},{0xB3, 0xDC, 0xA1, 0xFF}}},
	{{{-21, 16, -14},0, {2378, 1450},{0x8F, 0xED, 0xC9, 0xFF}}},
	{{{-21, 16, 14},0, {2378, 1450},{0x91, 0xED, 0x3B, 0xFF}}},
	{{{-15, 14, 21},0, {1396, 1344},{0xB7, 0xDC, 0x61, 0xFF}}},
	{{{-10, 0, 8},0, {1322, 1322},{0xD2, 0x92, 0x2D, 0xFF}}},
	{{{0, -4, -1},0, {1114, 1310},{0x1C, 0x84, 0x0, 0xFF}}},
	{{{-3, 7, 21},0, {1606, 1348},{0xD, 0xB1, 0x63, 0xFF}}},
	{{{17, 7, -1},0, {1606, 1348},{0x6, 0x81, 0x3, 0xFF}}},
	{{{-4, 7, -22},0, {1606, 1348},{0x7, 0xB0, 0x9D, 0xFF}}},
	{{{-10, 0, -9},0, {1322, 1322},{0xD1, 0x92, 0xD5, 0xFF}}},
	{{{0, -4, -1},0, {244, 2030},{0x1C, 0x84, 0x0, 0xFF}}},
	{{{-10, 0, 8},0, {152, 2312},{0xD2, 0x92, 0x2D, 0xFF}}},
	{{{-10, 0, -9},0, {152, 1750},{0xD1, 0x92, 0xD5, 0xFF}}},
	{{{-22, 7, 0},0, {1760, 2064},{0x96, 0xB9, 0x2, 0xFF}}},
	{{{-25, 22, 0},0, {1954, 2064},{0x83, 0x19, 0x2, 0xFF}}},
	{{{-21, 16, -14},0, {1880, 1714},{0x8F, 0xED, 0xC9, 0xFF}}},
	{{{-21, 16, 14},0, {1880, 1714},{0x91, 0xED, 0x3B, 0xFF}}},
	{{{-10, 0, -9},0, {152, 1750},{0xD1, 0x92, 0xD5, 0xFF}}},
	{{{-10, 0, 8},0, {152, 2312},{0xD2, 0x92, 0x2D, 0xFF}}},
	{{{-22, 7, 0},0, {-108, 2030},{0x96, 0xB9, 0x2, 0xFF}}},
	{{{-10, 0, 8},0, {2462, 1176},{0xD2, 0x92, 0x2D, 0xFF}}},
	{{{-15, 14, 21},0, {1396, 1344},{0xB7, 0xDC, 0x61, 0xFF}}},
	{{{-21, 16, 14},0, {2378, 1450},{0x91, 0xED, 0x3B, 0xFF}}},
	{{{-10, 0, -9},0, {2462, 1176},{0xD1, 0x92, 0xD5, 0xFF}}},
	{{{-21, 16, -14},0, {2378, 1450},{0x8F, 0xED, 0xC9, 0xFF}}},
	{{{-16, 14, -21},0, {1396, 1344},{0xB3, 0xDC, 0xA1, 0xFF}}},
	{{{-4, 7, -22},0, {1932, 1272},{0x7, 0xB0, 0x9D, 0xFF}}},
};

Gfx yoshi_head_mesh_layer_1_tri_0[] = {
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 7, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 320, 0, 424, 96),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 7, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 320, 0, 424, 96),
	gsSPVertex(yoshi_head_mesh_layer_1_vtx_0 + 0, 32, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 0, 0),
	gsSP2Triangles(5, 6, 7, 0, 5, 7, 8, 0),
	gsSP2Triangles(9, 5, 8, 0, 10, 5, 9, 0),
	gsSP2Triangles(11, 12, 13, 0, 12, 11, 14, 0),
	gsSP2Triangles(12, 14, 15, 0, 12, 15, 16, 0),
	gsSP2Triangles(17, 18, 19, 0, 17, 20, 18, 0),
	gsSP2Triangles(21, 0, 22, 0, 0, 21, 23, 0),
	gsSP2Triangles(24, 23, 21, 0, 24, 21, 25, 0),
	gsSP2Triangles(25, 21, 26, 0, 25, 26, 27, 0),
	gsSP2Triangles(25, 27, 28, 0, 28, 27, 29, 0),
	gsSP2Triangles(29, 27, 30, 0, 30, 31, 29, 0),
	gsSPVertex(yoshi_head_mesh_layer_1_vtx_0 + 32, 32, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(4, 3, 0, 0, 5, 3, 4, 0),
	gsSP2Triangles(6, 5, 4, 0, 7, 5, 6, 0),
	gsSP2Triangles(7, 8, 5, 0, 9, 8, 7, 0),
	gsSP2Triangles(9, 7, 10, 0, 11, 9, 10, 0),
	gsSP2Triangles(12, 11, 10, 0, 13, 11, 12, 0),
	gsSP2Triangles(14, 8, 9, 0, 14, 3, 8, 0),
	gsSP2Triangles(1, 3, 14, 0, 8, 3, 5, 0),
	gsSP2Triangles(15, 16, 17, 0, 16, 15, 18, 0),
	gsSP2Triangles(19, 18, 15, 0, 15, 20, 19, 0),
	gsSP2Triangles(18, 21, 16, 0, 18, 22, 21, 0),
	gsSP2Triangles(23, 22, 18, 0, 24, 23, 18, 0),
	gsSP2Triangles(24, 18, 25, 0, 24, 25, 26, 0),
	gsSP2Triangles(27, 28, 29, 0, 27, 30, 28, 0),
	gsSP1Triangle(31, 30, 27, 0),
	gsSPVertex(yoshi_head_mesh_layer_1_vtx_0 + 64, 16, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(1, 3, 4, 0, 4, 3, 5, 0),
	gsSP2Triangles(4, 5, 2, 0, 2, 1, 4, 0),
	gsSP2Triangles(5, 6, 7, 0, 5, 8, 6, 0),
	gsSP2Triangles(6, 8, 9, 0, 9, 8, 10, 0),
	gsSP2Triangles(9, 10, 7, 0, 7, 6, 9, 0),
	gsSP2Triangles(11, 12, 0, 0, 13, 12, 11, 0),
	gsSP2Triangles(13, 11, 14, 0, 11, 0, 14, 0),
	gsSP2Triangles(15, 13, 14, 0, 12, 13, 15, 0),
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 12, 156, 328, 252),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 12, 156, 328, 252),
	gsSPVertex(yoshi_head_mesh_layer_1_vtx_0 + 80, 32, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 2, 4, 0),
	gsSP2Triangles(5, 6, 7, 0, 8, 6, 5, 0),
	gsSP2Triangles(9, 6, 8, 0, 10, 9, 8, 0),
	gsSP2Triangles(11, 9, 10, 0, 11, 12, 9, 0),
	gsSP2Triangles(13, 12, 11, 0, 11, 14, 13, 0),
	gsSP2Triangles(13, 14, 15, 0, 13, 15, 16, 0),
	gsSP2Triangles(16, 15, 17, 0, 16, 17, 18, 0),
	gsSP2Triangles(13, 16, 19, 0, 19, 20, 13, 0),
	gsSP2Triangles(13, 20, 12, 0, 12, 21, 9, 0),
	gsSP2Triangles(9, 21, 22, 0, 9, 22, 6, 0),
	gsSP2Triangles(23, 24, 25, 0, 25, 24, 26, 0),
	gsSP2Triangles(27, 26, 24, 0, 28, 27, 24, 0),
	gsSP1Triangle(29, 30, 31, 0),
	gsSPVertex(yoshi_head_mesh_layer_1_vtx_0 + 112, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 212, 20, 252),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 0, 212, 20, 252),
	gsSPVertex(yoshi_head_mesh_layer_1_vtx_0 + 116, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 9, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 168, 140, 308, 184),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 9, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 168, 140, 308, 184),
	gsSPVertex(yoshi_head_mesh_layer_1_vtx_0 + 119, 7, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP1Triangle(3, 5, 6, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_head_mesh_layer_1_vtx_1[13] = {
	{{{7, 56, -1},0, {404, 796},{0x5D, 0x57, 0xFF, 0xFF}}},
	{{{-4, 60, 7},0, {354, 996},{0xE5, 0x7A, 0x15, 0xFF}}},
	{{{7, 52, 12},0, {108, 706},{0x56, 0x35, 0x4D, 0xFF}}},
	{{{-6, 53, 15},0, {-64, 896},{0xC3, 0x2E, 0x66, 0xFF}}},
	{{{2, 37, 15},0, {-10, 216},{0x19, 0x26, 0x77, 0xFF}}},
	{{{8, 36, 11},0, {116, -6},{0x2C, 0x33, 0x6C, 0xFF}}},
	{{{10, 39, -1},0, {492, 110},{0x2F, 0x76, 0x0, 0xFF}}},
	{{{7, 56, -1},0, {496, 796},{0x5D, 0x57, 0xFF, 0xFF}}},
	{{{6, 52, -13},0, {108, 706},{0x53, 0x35, 0xAF, 0xFF}}},
	{{{7, 36, -12},0, {116, -6},{0x27, 0x36, 0x94, 0xFF}}},
	{{{1, 37, -16},0, {-10, 216},{0x14, 0x26, 0x88, 0xFF}}},
	{{{-7, 53, -16},0, {-64, 896},{0xBF, 0x2E, 0x9D, 0xFF}}},
	{{{-4, 60, -8},0, {354, 996},{0xE4, 0x7A, 0xEC, 0xFF}}},
};

Gfx yoshi_head_mesh_layer_1_tri_1[] = {
	gsSPVertex(yoshi_head_mesh_layer_1_vtx_1 + 0, 13, 0),
	gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
	gsSP2Triangles(2, 3, 4, 0, 4, 5, 2, 0),
	gsSP2Triangles(2, 5, 6, 0, 2, 6, 7, 0),
	gsSP2Triangles(7, 6, 8, 0, 9, 8, 6, 0),
	gsSP2Triangles(10, 8, 9, 0, 11, 8, 10, 0),
	gsSP2Triangles(12, 8, 11, 0, 8, 12, 0, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_shoulder_L_mesh_layer_1_vtx_0[6] = {
	{{{-8, 12, -3},0, {2640, 496},{0x86, 0xE9, 0xE6, 0xFF}}},
	{{{-5, -2, -4},0, {2640, 496},{0x96, 0xC7, 0xD9, 0xFF}}},
	{{{0, 12, 4},0, {2640, 496},{0xF, 0xFD, 0x7E, 0xFF}}},
	{{{3, -1, 4},0, {2640, 496},{0x1F, 0xDE, 0x76, 0xFF}}},
	{{{2, -7, -1},0, {2640, 496},{0x12, 0x83, 0x11, 0xFF}}},
	{{{7, 0, -7},0, {2640, 496},{0x5F, 0xE5, 0xB0, 0xFF}}},
};

Gfx yoshi_shoulder_L_mesh_layer_1_tri_0[] = {
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 324, 56, 332, 64),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 324, 56, 332, 64),
	gsSPVertex(yoshi_shoulder_L_mesh_layer_1_vtx_0 + 0, 6, 0),
	gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
	gsSP2Triangles(1, 4, 3, 0, 5, 4, 1, 0),
	gsSP1Triangle(3, 4, 5, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_arm_L_skinned_mesh_layer_1_vtx_0[5] = {
	{{{3, -1, 4},0, {2640, 496},{0x1F, 0xDE, 0x76, 0xFF}}},
	{{{7, 0, -7},0, {2640, 496},{0x5F, 0xE5, 0xB0, 0xFF}}},
	{{{-5, -2, -4},0, {2640, 496},{0x96, 0xC7, 0xD9, 0xFF}}},
	{{{-8, 12, -3},0, {2640, 496},{0x86, 0xE9, 0xE6, 0xFF}}},
	{{{0, 12, 4},0, {2640, 496},{0xF, 0xFD, 0x7E, 0xFF}}},
};

Gfx yoshi_arm_L_skinned_mesh_layer_1_tri_0[] = {
	gsSPVertex(yoshi_arm_L_skinned_mesh_layer_1_vtx_0 + 0, 5, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_arm_L_mesh_layer_1_vtx_0[1] = {
	{{{3, 4, -5},0, {2640, 496},{0x31, 0x5A, 0xB4, 0xFF}}},
};

Gfx yoshi_arm_L_mesh_layer_1_tri_0[] = {
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 324, 56, 332, 64),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 324, 56, 332, 64),
	gsSPVertex(yoshi_arm_L_mesh_layer_1_vtx_0 + 0, 1, 5),
	gsSP2Triangles(5, 2, 3, 0, 5, 1, 2, 0),
	gsSP2Triangles(0, 1, 5, 0, 4, 0, 5, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_arm_L_mesh_layer_1_vtx_1[7] = {
	{{{-8, 0, -1},0, {2640, 496},{0x84, 0xE3, 0x1, 0xFF}}},
	{{{-5, -6, -2},0, {2640, 496},{0xCF, 0x8E, 0xE4, 0xFF}}},
	{{{1, -1, 4},0, {2640, 496},{0x30, 0xC5, 0x66, 0xFF}}},
	{{{4, -1, -6},0, {2640, 496},{0x48, 0xC7, 0xA9, 0xFF}}},
	{{{6, 14, -7},0, {2640, 496},{0x51, 0x2B, 0xA8, 0xFF}}},
	{{{-8, 14, 0},0, {2640, 496},{0x8E, 0x37, 0x6, 0xFF}}},
	{{{3, 14, 5},0, {2640, 496},{0x34, 0x38, 0x65, 0xFF}}},
};

Gfx yoshi_arm_L_mesh_layer_1_tri_1[] = {
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 324, 56, 332, 64),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 324, 56, 332, 64),
	gsSPVertex(yoshi_arm_L_mesh_layer_1_vtx_1 + 0, 7, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(0, 4, 3, 0, 5, 4, 0, 0),
	gsSP2Triangles(5, 0, 2, 0, 6, 5, 2, 0),
	gsSP2Triangles(2, 3, 6, 0, 2, 1, 3, 0),
	gsSP1Triangle(6, 3, 4, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_hand_L_skinned_mesh_layer_1_vtx_0[3] = {
	{{{3, 14, 5},0, {2640, 496},{0x34, 0x38, 0x65, 0xFF}}},
	{{{6, 14, -7},0, {2640, 496},{0x51, 0x2B, 0xA8, 0xFF}}},
	{{{-8, 14, 0},0, {2640, 496},{0x8E, 0x37, 0x6, 0xFF}}},
};

Gfx yoshi_hand_L_skinned_mesh_layer_1_tri_0[] = {
	gsSPVertex(yoshi_hand_L_skinned_mesh_layer_1_vtx_0 + 0, 3, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_hand_L_mesh_layer_1_vtx_0[1] = {
	{{{-2, 5, -2},0, {2640, 496},{0xD8, 0x76, 0xE6, 0xFF}}},
};

Gfx yoshi_hand_L_mesh_layer_1_tri_0[] = {
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 324, 56, 332, 64),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 324, 56, 332, 64),
	gsSPVertex(yoshi_hand_L_mesh_layer_1_vtx_0 + 0, 1, 3),
	gsSP2Triangles(0, 1, 3, 0, 3, 1, 2, 0),
	gsSP1Triangle(3, 2, 0, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_hand_L_mesh_layer_1_vtx_1[18] = {
	{{{-7, 19, 9},0, {2448, 594},{0xDB, 0x43, 0x66, 0xFF}}},
	{{{-12, 18, -1},0, {2432, 370},{0x91, 0x38, 0xE4, 0xFF}}},
	{{{-8, 1, 0},0, {2008, 382},{0xA6, 0xA6, 0x4, 0xFF}}},
	{{{5, 0, -8},0, {2640, 496},{0x27, 0x9C, 0xBB, 0xFF}}},
	{{{3, 1, 4},0, {2640, 496},{0x31, 0xAC, 0x52, 0xFF}}},
	{{{-8, 1, 0},0, {2640, 496},{0xA6, 0xA6, 0x4, 0xFF}}},
	{{{-8, 1, 0},0, {1784, 1024},{0xA6, 0xA6, 0x4, 0xFF}}},
	{{{3, 1, 4},0, {1632, 1024},{0x31, 0xAC, 0x52, 0xFF}}},
	{{{-7, 19, 9},0, {1756, 880},{0xDB, 0x43, 0x66, 0xFF}}},
	{{{14, 20, -4},0, {1512, 884},{0x6B, 0x44, 0x6, 0xFF}}},
	{{{5, 0, -8},0, {1510, 1024},{0x27, 0x9C, 0xBB, 0xFF}}},
	{{{-8, 1, 0},0, {2448, 960},{0xA6, 0xA6, 0x4, 0xFF}}},
	{{{-12, 18, -1},0, {2008, 994},{0x91, 0x38, 0xE4, 0xFF}}},
	{{{5, 0, -8},0, {2444, 700},{0x27, 0x9C, 0xBB, 0xFF}}},
	{{{3, 17, -16},0, {2008, 696},{0x0, 0x2B, 0x88, 0xFF}}},
	{{{14, 20, -4},0, {1794, 682},{0x6B, 0x44, 0x6, 0xFF}}},
	{{{-7, 19, 9},0, {1784, 1004},{0xDB, 0x43, 0x66, 0xFF}}},
	{{{14, 20, -4},0, {1996, 430},{0x6B, 0x44, 0x6, 0xFF}}},
};

Gfx yoshi_hand_L_mesh_layer_1_tri_1[] = {
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 10, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 184, 40, 332, 128),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 10, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 184, 40, 332, 128),
	gsSPVertex(yoshi_hand_L_mesh_layer_1_vtx_1 + 0, 18, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 8, 0, 8, 7, 9, 0),
	gsSP2Triangles(10, 9, 7, 0, 11, 12, 13, 0),
	gsSP2Triangles(13, 12, 14, 0, 14, 12, 15, 0),
	gsSP2Triangles(15, 12, 16, 0, 14, 17, 13, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_shoulder_R_mesh_layer_1_vtx_0[6] = {
	{{{-5, -1, 3},0, {2640, 496},{0x94, 0xC6, 0x22, 0xFF}}},
	{{{-7, 13, 1},0, {2640, 496},{0x85, 0xE8, 0x12, 0xFF}}},
	{{{1, 13, -5},0, {2640, 496},{0x16, 0xFC, 0x83, 0xFF}}},
	{{{4, 0, -5},0, {2640, 496},{0x26, 0xDE, 0x8C, 0xFF}}},
	{{{3, -6, 0},0, {2640, 496},{0x13, 0x83, 0xF1, 0xFF}}},
	{{{8, 1, 6},0, {2640, 496},{0x5A, 0xE6, 0x56, 0xFF}}},
};

Gfx yoshi_shoulder_R_mesh_layer_1_tri_0[] = {
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 324, 56, 332, 64),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 324, 56, 332, 64),
	gsSPVertex(yoshi_shoulder_R_mesh_layer_1_vtx_0 + 0, 6, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(0, 3, 4, 0, 4, 3, 5, 0),
	gsSP1Triangle(4, 5, 0, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_arm_R_skinned_mesh_layer_1_vtx_0[5] = {
	{{{-5, -1, 3},0, {2640, 496},{0x94, 0xC6, 0x22, 0xFF}}},
	{{{8, 1, 6},0, {2640, 496},{0x5A, 0xE6, 0x56, 0xFF}}},
	{{{-7, 13, 1},0, {2640, 496},{0x85, 0xE8, 0x12, 0xFF}}},
	{{{1, 13, -5},0, {2640, 496},{0x16, 0xFC, 0x83, 0xFF}}},
	{{{4, 0, -5},0, {2640, 496},{0x26, 0xDE, 0x8C, 0xFF}}},
};

Gfx yoshi_arm_R_skinned_mesh_layer_1_tri_0[] = {
	gsSPVertex(yoshi_arm_R_skinned_mesh_layer_1_vtx_0 + 0, 5, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_arm_R_mesh_layer_1_vtx_0[1] = {
	{{{3, 5, 5},0, {2640, 496},{0x2E, 0x5A, 0x4E, 0xFF}}},
};

Gfx yoshi_arm_R_mesh_layer_1_tri_0[] = {
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 324, 56, 332, 64),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 324, 56, 332, 64),
	gsSPVertex(yoshi_arm_R_mesh_layer_1_vtx_0 + 0, 1, 5),
	gsSP2Triangles(0, 5, 2, 0, 0, 1, 5, 0),
	gsSP2Triangles(4, 5, 1, 0, 3, 5, 4, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_arm_R_mesh_layer_1_vtx_1[7] = {
	{{{-8, 1, -1},0, {2640, 496},{0x85, 0xE2, 0xF9, 0xFF}}},
	{{{2, 0, -5},0, {2640, 496},{0x35, 0xC5, 0x9D, 0xFF}}},
	{{{-4, -5, 1},0, {2640, 496},{0xCE, 0x8E, 0x1A, 0xFF}}},
	{{{-8, 15, -1},0, {2640, 496},{0x8E, 0x37, 0xF4, 0xFF}}},
	{{{6, 15, 6},0, {2640, 496},{0x4C, 0x2C, 0x5B, 0xFF}}},
	{{{4, 0, 5},0, {2640, 496},{0x44, 0xC8, 0x5B, 0xFF}}},
	{{{3, 16, -6},0, {2640, 496},{0x39, 0x38, 0x9E, 0xFF}}},
};

Gfx yoshi_arm_R_mesh_layer_1_tri_1[] = {
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 324, 56, 332, 64),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 324, 56, 332, 64),
	gsSPVertex(yoshi_arm_R_mesh_layer_1_vtx_1 + 0, 7, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
	gsSP2Triangles(0, 4, 3, 0, 0, 5, 4, 0),
	gsSP2Triangles(2, 5, 0, 0, 2, 1, 5, 0),
	gsSP2Triangles(5, 1, 6, 0, 6, 1, 3, 0),
	gsSP1Triangle(6, 4, 5, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_hand_R_skinned_mesh_layer_1_vtx_0[3] = {
	{{{-8, 15, -1},0, {2640, 496},{0x8E, 0x37, 0xF4, 0xFF}}},
	{{{6, 15, 6},0, {2640, 496},{0x4C, 0x2C, 0x5B, 0xFF}}},
	{{{3, 16, -6},0, {2640, 496},{0x39, 0x38, 0x9E, 0xFF}}},
};

Gfx yoshi_hand_R_skinned_mesh_layer_1_tri_0[] = {
	gsSPVertex(yoshi_hand_R_skinned_mesh_layer_1_vtx_0 + 0, 3, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_hand_R_mesh_layer_1_vtx_0[1] = {
	{{{-2, 5, 1},0, {2640, 496},{0xD7, 0x76, 0x18, 0xFF}}},
};

Gfx yoshi_hand_R_mesh_layer_1_tri_0[] = {
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 324, 56, 332, 64),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 324, 56, 332, 64),
	gsSPVertex(yoshi_hand_R_mesh_layer_1_vtx_0 + 0, 1, 3),
	gsSP2Triangles(0, 1, 3, 0, 2, 3, 1, 0),
	gsSP1Triangle(0, 3, 2, 0),
	gsSPEndDisplayList(),
};

Vtx yoshi_hand_R_mesh_layer_1_vtx_1[18] = {
	{{{5, 1, 7},0, {2640, 496},{0x25, 0x9E, 0x48, 0xFF}}},
	{{{-8, 1, -2},0, {2640, 496},{0xA8, 0xA5, 0xFA, 0xFF}}},
	{{{4, 2, -5},0, {2640, 496},{0x35, 0xAC, 0xB1, 0xFF}}},
	{{{-6, 20, -11},0, {2448, 594},{0xDF, 0x41, 0x98, 0xFF}}},
	{{{-8, 1, -2},0, {2008, 382},{0xA8, 0xA5, 0xFA, 0xFF}}},
	{{{-11, 18, -1},0, {2432, 370},{0x90, 0x37, 0x17, 0xFF}}},
	{{{-8, 1, -2},0, {1784, 1024},{0xA8, 0xA5, 0xFA, 0xFF}}},
	{{{-6, 20, -11},0, {1756, 880},{0xDF, 0x41, 0x98, 0xFF}}},
	{{{4, 2, -5},0, {1632, 1024},{0x35, 0xAC, 0xB1, 0xFF}}},
	{{{14, 21, 3},0, {1512, 884},{0x6B, 0x44, 0xFF, 0xFF}}},
	{{{5, 1, 7},0, {1510, 1024},{0x25, 0x9E, 0x48, 0xFF}}},
	{{{-8, 1, -2},0, {2448, 960},{0xA8, 0xA5, 0xFA, 0xFF}}},
	{{{5, 1, 7},0, {2444, 700},{0x25, 0x9E, 0x48, 0xFF}}},
	{{{-11, 18, -1},0, {2008, 994},{0x90, 0x37, 0x17, 0xFF}}},
	{{{3, 18, 14},0, {2008, 696},{0xFA, 0x2B, 0x77, 0xFF}}},
	{{{14, 21, 3},0, {1996, 430},{0x6B, 0x44, 0xFF, 0xFF}}},
	{{{14, 21, 3},0, {1794, 682},{0x6B, 0x44, 0xFF, 0xFF}}},
	{{{-6, 20, -11},0, {1784, 1004},{0xDF, 0x41, 0x98, 0xFF}}},
};

Gfx yoshi_hand_R_mesh_layer_1_tri_1[] = {
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, yoshi_yoshi_body_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 10, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 184, 40, 332, 128),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 10, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 184, 40, 332, 128),
	gsSPVertex(yoshi_hand_R_mesh_layer_1_vtx_1 + 0, 18, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 8, 0, 8, 7, 9, 0),
	gsSP2Triangles(8, 9, 10, 0, 11, 12, 13, 0),
	gsSP2Triangles(13, 12, 14, 0, 14, 12, 15, 0),
	gsSP2Triangles(14, 16, 13, 0, 13, 16, 17, 0),
	gsSPEndDisplayList(),
};


Gfx mat_yoshi_yoshi_body_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(yoshi_yoshi_body_f3d_lights),
	gsSPEndDisplayList(),
};

Gfx mat_yoshi_yoshi_eyes_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureLUT(G_TT_RGBA16),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, yoshi_yoshi_eyes_ci4_pal_rgba16),
	gsDPTileSync(),
	gsDPSetTile(0, 0, 0, 256, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTLUTCmd(7, 13),
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, yoshi_yoshi_eyes_ci4),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 127, 2048),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 1, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPSetTileSize(0, 0, 0, 60, 124),
	gsSPSetLights1(yoshi_yoshi_eyes_f3d_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_yoshi_yoshi_eyes_f3d[] = {
	gsDPPipeSync(),
	gsDPSetTextureLUT(G_TT_NONE),
	gsSPEndDisplayList(),
};

Gfx yoshi_shin_L_mesh_layer_1[] = {
	gsSPDisplayList(mat_yoshi_yoshi_body_f3d),
	gsSPDisplayList(yoshi_shin_L_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx yoshi_foot_L_mesh_layer_1[] = {
	gsSPDisplayList(mat_yoshi_yoshi_body_f3d),
	gsSPDisplayList(yoshi_foot_L_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx yoshi_hip_L_skinned_mesh_layer_1[] = {
	gsSPDisplayList(mat_yoshi_yoshi_body_f3d),
	gsSPDisplayList(yoshi_hip_L_skinned_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx yoshi_hip_L_mesh_layer_1[] = {
	gsSPDisplayList(mat_yoshi_yoshi_body_f3d),
	gsSPDisplayList(yoshi_hip_L_mesh_layer_1_tri_0),
	gsSPDisplayList(yoshi_hip_L_mesh_layer_1_tri_1),
	gsSPEndDisplayList(),
};

Gfx yoshi_shin_R_mesh_layer_1[] = {
	gsSPDisplayList(mat_yoshi_yoshi_body_f3d),
	gsSPDisplayList(yoshi_shin_R_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx yoshi_foot_R_mesh_layer_1[] = {
	gsSPDisplayList(mat_yoshi_yoshi_body_f3d),
	gsSPDisplayList(yoshi_foot_R_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx yoshi_hip_R_skinned_mesh_layer_1[] = {
	gsSPDisplayList(mat_yoshi_yoshi_body_f3d),
	gsSPDisplayList(yoshi_hip_R_skinned_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx yoshi_hip_R_mesh_layer_1[] = {
	gsSPDisplayList(mat_yoshi_yoshi_body_f3d),
	gsSPDisplayList(yoshi_hip_R_mesh_layer_1_tri_0),
	gsSPDisplayList(yoshi_hip_R_mesh_layer_1_tri_1),
	gsSPEndDisplayList(),
};

Gfx yoshi_spine_mesh_layer_1[] = {
	gsSPDisplayList(mat_yoshi_yoshi_body_f3d),
	gsSPDisplayList(yoshi_spine_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx yoshi_back_skinned_mesh_layer_1[] = {
	gsSPDisplayList(mat_yoshi_yoshi_body_f3d),
	gsSPDisplayList(yoshi_back_skinned_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx yoshi_back_mesh_layer_1[] = {
	gsSPDisplayList(mat_yoshi_yoshi_body_f3d),
	gsSPDisplayList(yoshi_back_mesh_layer_1_tri_0),
	gsSPDisplayList(yoshi_back_mesh_layer_1_tri_1),
	gsSPEndDisplayList(),
};

Gfx yoshi_head_mesh_layer_1[] = {
	gsSPDisplayList(mat_yoshi_yoshi_body_f3d),
	gsSPDisplayList(yoshi_head_mesh_layer_1_tri_0),
	gsSPDisplayList(mat_yoshi_yoshi_eyes_f3d),
	gsSPDisplayList(yoshi_head_mesh_layer_1_tri_1),
	gsSPDisplayList(mat_revert_yoshi_yoshi_eyes_f3d),
	gsSPEndDisplayList(),
};

Gfx yoshi_shoulder_L_mesh_layer_1[] = {
	gsSPDisplayList(mat_yoshi_yoshi_body_f3d),
	gsSPDisplayList(yoshi_shoulder_L_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx yoshi_arm_L_skinned_mesh_layer_1[] = {
	gsSPDisplayList(mat_yoshi_yoshi_body_f3d),
	gsSPDisplayList(yoshi_arm_L_skinned_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx yoshi_arm_L_mesh_layer_1[] = {
	gsSPDisplayList(mat_yoshi_yoshi_body_f3d),
	gsSPDisplayList(yoshi_arm_L_mesh_layer_1_tri_0),
	gsSPDisplayList(yoshi_arm_L_mesh_layer_1_tri_1),
	gsSPEndDisplayList(),
};

Gfx yoshi_hand_L_skinned_mesh_layer_1[] = {
	gsSPDisplayList(mat_yoshi_yoshi_body_f3d),
	gsSPDisplayList(yoshi_hand_L_skinned_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx yoshi_hand_L_mesh_layer_1[] = {
	gsSPDisplayList(mat_yoshi_yoshi_body_f3d),
	gsSPDisplayList(yoshi_hand_L_mesh_layer_1_tri_0),
	gsSPDisplayList(yoshi_hand_L_mesh_layer_1_tri_1),
	gsSPEndDisplayList(),
};

Gfx yoshi_shoulder_R_mesh_layer_1[] = {
	gsSPDisplayList(mat_yoshi_yoshi_body_f3d),
	gsSPDisplayList(yoshi_shoulder_R_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx yoshi_arm_R_skinned_mesh_layer_1[] = {
	gsSPDisplayList(mat_yoshi_yoshi_body_f3d),
	gsSPDisplayList(yoshi_arm_R_skinned_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx yoshi_arm_R_mesh_layer_1[] = {
	gsSPDisplayList(mat_yoshi_yoshi_body_f3d),
	gsSPDisplayList(yoshi_arm_R_mesh_layer_1_tri_0),
	gsSPDisplayList(yoshi_arm_R_mesh_layer_1_tri_1),
	gsSPEndDisplayList(),
};

Gfx yoshi_hand_R_skinned_mesh_layer_1[] = {
	gsSPDisplayList(mat_yoshi_yoshi_body_f3d),
	gsSPDisplayList(yoshi_hand_R_skinned_mesh_layer_1_tri_0),
	gsSPEndDisplayList(),
};

Gfx yoshi_hand_R_mesh_layer_1[] = {
	gsSPDisplayList(mat_yoshi_yoshi_body_f3d),
	gsSPDisplayList(yoshi_hand_R_mesh_layer_1_tri_0),
	gsSPDisplayList(yoshi_hand_R_mesh_layer_1_tri_1),
	gsSPEndDisplayList(),
};

Gfx yoshi_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

