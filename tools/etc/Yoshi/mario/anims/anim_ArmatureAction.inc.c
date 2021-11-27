static const s16 mario_anim_ArmatureAction_values[] = {
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFF11, 0xFC91, 0xF8E9, 0xF48A, 
	0xEFEE, 0xEB90, 0xE7E8, 0xE567, 0xE479, 0x0000, 0x0000, 
};

static const u16 mario_anim_ArmatureAction_indices[] = {
	0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0002, 0x000B, 0x0003, 0x0001, 
	0x000E, 0x0001, 0x000F, 
};

static const struct Animation mario_anim_ArmatureAction = {
	0,
	0,
	0,
	1,
	10,
	ANIMINDEX_NUMPARTS(mario_anim_ArmatureAction_indices),
	mario_anim_ArmatureAction_values,
	mario_anim_ArmatureAction_indices,
	0,
};

