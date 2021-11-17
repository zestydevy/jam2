#include <ultra64.h>

Lights1 pokestop_base_pokestop_lights = gdSPDefLights1(
	0x27, 0x5F, 0x67,
	0x4E, 0xBF, 0xCF, 0x28, 0x28, 0x28);

Vtx pokestop_base_pokestop_base_mesh_vtx_cull[8] = {
	{{{-100, 2, -100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-100, 2, 100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-100, 322, 100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-100, 322, -100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{100, 2, -100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{100, 2, 100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{100, 322, 100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{100, 322, -100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
};

Vtx pokestop_base_pokestop_base_mesh_vtx_0[38] = {
	{{{5, 322, -5},0, {624, 496},{0x5A, 0x4, 0xA6, 0xFF}}},
	{{{-5, 322, -5},0, {880, 496},{0xA6, 0x4, 0xA6, 0xFF}}},
	{{{-5, 322, 5},0, {880, 240},{0xA6, 0x4, 0x5A, 0xFF}}},
	{{{5, 322, 5},0, {624, 240},{0x5A, 0x4, 0x5A, 0xFF}}},
	{{{5, 122, -5},0, {368, 496},{0x5A, 0xFC, 0xA6, 0xFF}}},
	{{{5, 122, 5},0, {368, 240},{0x5A, 0xFC, 0x5A, 0xFF}}},
	{{{-5, 322, 5},0, {624, -16},{0xA6, 0x4, 0x5A, 0xFF}}},
	{{{-5, 122, 5},0, {368, -16},{0xA6, 0xFC, 0x5A, 0xFF}}},
	{{{-5, 122, -5},0, {112, 496},{0xA6, 0xFC, 0xA6, 0xFF}}},
	{{{-5, 122, 5},0, {112, 240},{0xA6, 0xFC, 0x5A, 0xFF}}},
	{{{-5, 122, 5},0, {368, 1008},{0xA6, 0xFC, 0x5A, 0xFF}}},
	{{{-5, 322, 5},0, {624, 1008},{0xA6, 0x4, 0x5A, 0xFF}}},
	{{{-5, 322, -5},0, {624, 752},{0xA6, 0x4, 0xA6, 0xFF}}},
	{{{-5, 122, -5},0, {368, 752},{0xA6, 0xFC, 0xA6, 0xFF}}},
	{{{100, 22, -100},0, {624, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-100, 22, -100},0, {880, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-100, 22, 100},0, {880, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{100, 22, 100},0, {624, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{100, 2, 100},0, {368, 240},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{100, 22, 100},0, {624, 240},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-100, 22, 100},0, {624, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-100, 2, 100},0, {368, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-100, 2, 100},0, {368, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-100, 22, 100},0, {624, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-100, 22, -100},0, {624, 752},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-100, 2, -100},0, {368, 752},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-100, 2, -100},0, {112, 496},{0x0, 0x81, 0x0, 0xFF}}},
	{{{100, 2, -100},0, {368, 496},{0x0, 0x81, 0x0, 0xFF}}},
	{{{100, 2, 100},0, {368, 240},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-100, 2, 100},0, {112, 240},{0x0, 0x81, 0x0, 0xFF}}},
	{{{100, 2, -100},0, {368, 496},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{100, 22, -100},0, {624, 496},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{100, 22, 100},0, {624, 240},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{100, 2, 100},0, {368, 240},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{-100, 2, -100},0, {368, 752},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-100, 22, -100},0, {624, 752},{0x0, 0x0, 0x81, 0xFF}}},
	{{{100, 22, -100},0, {624, 496},{0x0, 0x0, 0x81, 0xFF}}},
	{{{100, 2, -100},0, {368, 496},{0x0, 0x0, 0x81, 0xFF}}},
};

Gfx pokestop_base_pokestop_base_mesh_tri_0[] = {
	gsSPVertex(pokestop_base_pokestop_base_mesh_vtx_0 + 0, 30, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 0, 3, 0, 4, 3, 5, 0),
	gsSP2Triangles(5, 3, 6, 0, 5, 6, 7, 0),
	gsSP2Triangles(8, 4, 5, 0, 8, 5, 9, 0),
	gsSP2Triangles(10, 11, 12, 0, 10, 12, 13, 0),
	gsSP2Triangles(13, 12, 0, 0, 13, 0, 4, 0),
	gsSP2Triangles(14, 15, 16, 0, 14, 16, 17, 0),
	gsSP2Triangles(18, 19, 20, 0, 18, 20, 21, 0),
	gsSP2Triangles(22, 23, 24, 0, 22, 24, 25, 0),
	gsSP2Triangles(26, 27, 28, 0, 26, 28, 29, 0),
	gsSPVertex(pokestop_base_pokestop_base_mesh_vtx_0 + 30, 8, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSPEndDisplayList(),
};

Gfx mat_pokestop_base_pokestop[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(pokestop_base_pokestop_lights),
	gsSPEndDisplayList(),
};

Gfx pokestop_base_pokestop_base_mesh[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(pokestop_base_pokestop_base_mesh_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_pokestop_base_pokestop),
	gsSPDisplayList(pokestop_base_pokestop_base_mesh_tri_0),
	gsSPEndDisplayList(),
};