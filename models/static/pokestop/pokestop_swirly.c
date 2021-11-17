#include <ultra64.h>

Vtx pokestop_swirly_pokestop_swirly_mesh_vtx_cull[8] = {
	{{{-94, 80, 3},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-94, 80, 3},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-94, 133, 3},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-94, 133, 3},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{51, 80, 3},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{51, 80, 3},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{51, 133, 3},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{51, 133, 3},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
};

Vtx pokestop_swirly_pokestop_swirly_mesh_vtx_0[14] = {
	{{{-38, 102, 3},0, {169, 922},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-71, 80, 3},0, {110, 882},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-51, 123, 3},0, {146, 979},{0x0, 0x0, 0x81, 0xFF}}},
	{{{0, 133, 3},0, {240, 998},{0x0, 0x0, 0x81, 0xFF}}},
	{{{51, 123, 3},0, {334, 979},{0x0, 0x0, 0x81, 0xFF}}},
	{{{0, 109, 3},0, {240, 936},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-94, 94, 3},0, {66, 926},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-51, 123, 3},0, {146, 979},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-71, 80, 3},0, {110, 882},{0x0, 0x0, 0x81, 0xFF}}},
	{{{51, 123, 3},0, {334, 979},{0x0, 0x0, 0x81, 0xFF}}},
	{{{38, 102, 3},0, {311, 922},{0x0, 0x0, 0x81, 0xFF}}},
	{{{0, 109, 3},0, {240, 936},{0x0, 0x0, 0x81, 0xFF}}},
	{{{0, 133, 3},0, {240, 998},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-38, 102, 3},0, {169, 922},{0x0, 0x0, 0x81, 0xFF}}},
};

Gfx pokestop_swirly_pokestop_swirly_mesh_tri_0[] = {
	gsSPVertex(pokestop_swirly_pokestop_swirly_mesh_vtx_0 + 0, 14, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 8, 0, 9, 10, 11, 0),
	gsSP2Triangles(7, 12, 13, 0, 13, 12, 11, 0),
	gsSPEndDisplayList(),
};

Gfx pokestop_swirly_pokestop_swirly_mesh[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(pokestop_swirly_pokestop_swirly_mesh_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(pokestop_swirly_pokestop_swirly_mesh_tri_0),
	gsSPEndDisplayList(),
};

