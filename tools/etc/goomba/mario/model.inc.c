Lights1 mario_Material_f3d_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Vtx mario_Cube_mesh_vtx_cull[8] = {
	{{{-100, -100, -100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-100, -100, 100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-100, 100, 100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-100, 100, -100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{100, -100, -100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{100, -100, 100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{100, 100, 100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{100, 100, -100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
};

Vtx mario_Cube_mesh_vtx_0[24] = {
	{{{100, 100, -100},0, {624, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-100, 100, -100},0, {880, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-100, 100, 100},0, {880, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{100, 100, 100},0, {624, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{100, -100, 100},0, {368, 240},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{100, 100, 100},0, {624, 240},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-100, 100, 100},0, {624, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-100, -100, 100},0, {368, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-100, -100, 100},0, {368, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-100, 100, 100},0, {624, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-100, 100, -100},0, {624, 752},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-100, -100, -100},0, {368, 752},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-100, -100, -100},0, {112, 496},{0x0, 0x81, 0x0, 0xFF}}},
	{{{100, -100, -100},0, {368, 496},{0x0, 0x81, 0x0, 0xFF}}},
	{{{100, -100, 100},0, {368, 240},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-100, -100, 100},0, {112, 240},{0x0, 0x81, 0x0, 0xFF}}},
	{{{100, -100, -100},0, {368, 496},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{100, 100, -100},0, {624, 496},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{100, 100, 100},0, {624, 240},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{100, -100, 100},0, {368, 240},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{-100, -100, -100},0, {368, 752},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-100, 100, -100},0, {624, 752},{0x0, 0x0, 0x81, 0xFF}}},
	{{{100, 100, -100},0, {624, 496},{0x0, 0x0, 0x81, 0xFF}}},
	{{{100, -100, -100},0, {368, 496},{0x0, 0x0, 0x81, 0xFF}}},
};

Gfx mario_Cube_mesh_tri_0[] = {
	gsSPVertex(mario_Cube_mesh_vtx_0 + 0, 24, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
	gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
	gsSPEndDisplayList(),
};

Gfx mat_mario_Material_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(NOISE, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, NOISE, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(mario_Material_f3d_lights),
	gsSPEndDisplayList(),
};

Gfx mario_Cube_mesh[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(mario_Cube_mesh_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_mario_Material_f3d),
	gsSPDisplayList(mario_Cube_mesh_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

