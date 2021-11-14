#include <ultra64.h>

#include "scenedata.h"

/* */
const struct TSceneEntry scene_test00[] = {
	{23},
	{ OBJECT_PLAYERSTART, 225.00000f, 281.00000f, 2401.00000f, 90.00000f, -90.00000f, 0.00000f, 1.00000f, 1.00000f, 1.00000f, { 3, 270, 0, 0 } }, 
	{ OBJECT_PLAYERSTART, 475.00000f, 281.00000f, 2151.00000f, 90.00000f, -90.00000f, 0.00000f, 1.00000f, 1.00000f, 1.00000f, { 2, 270, 0, 0 } }, 
	{ OBJECT_PLAYERSTART, 725.00000f, 281.00000f, 1901.00000f, 90.00000f, -90.00000f, 0.00000f, 1.00000f, 1.00000f, 1.00000f, { 1, 270, 0, 0 } }, 
	{ OBJECT_PLAYERSTART, 975.00000f, 281.00000f, 1651.00000f, 90.00000f, -90.00000f, 0.00000f, 1.00000f, 1.00000f, 1.00000f, { 0, 270, 0, 0 } }, 
	{ OBJECT_CHECKPOINT, -18.00000f, 620.00000f, 2714.00000f, 90.00000f, 0.00000f, 0.00000f, 1.00000f, 1.00000f, 1.00000f, { -18, 1303, 0, 1 } }, 
	{ OBJECT_CHECKPOINT, -4728.00000f, 620.00000f, 2714.00000f, 90.00000f, 0.00000f, 0.00000f, 1.00000f, 1.00000f, 1.00000f, { -4728, 1303, 1, 2 } }, 
	{ OBJECT_CHECKPOINT, -6057.00000f, 620.00000f, 2180.00000f, 90.00000f, -45.00000f, 0.00000f, 1.00000f, 1.00000f, 1.00000f, { -5059, 1182, 2, 3 } }, 
	{ OBJECT_CHECKPOINT, -6308.00000f, 620.00000f, 1143.00000f, 90.00000f, -90.00000f, 0.00000f, 1.00000f, 1.00000f, 1.00000f, { -5256, 1143, 3, 4 } }, 
	{ OBJECT_CHECKPOINT, -6229.00000f, 620.00000f, -1161.00000f, 90.00000f, -90.00000f, 0.00000f, 1.00000f, 1.00000f, 1.00000f, { -5189, -1161, 4, 5 } }, 
	{ OBJECT_CHECKPOINT, -6031.00000f, 620.00000f, -2501.00000f, 90.00000f, -135.00000f, 0.00000f, 1.00000f, 1.00000f, 1.00000f, { -5112, -1553, 5, 6 } }, 
	{ OBJECT_CHECKPOINT, -4964.00000f, 620.00000f, -2917.00000f, 90.00000f, -180.00000f, 0.00000f, 1.00000f, 1.00000f, 1.00000f, { -4964, -1713, 6, 7 } }, 
	{ OBJECT_CHECKPOINT, -2596.00000f, 620.00000f, -2550.00000f, 90.00000f, -200.00000f, 0.00000f, 1.00000f, 1.00000f, 1.00000f, { -2987, -1683, 7, 8 } }, 
	{ OBJECT_CHECKPOINT, -943.99990f, 620.00000f, -1171.00000f, 90.00000f, -200.00000f, 0.00000f, 1.00000f, 1.00000f, 1.00000f, { -1296, -306, 8, 9 } }, 
	{ OBJECT_CHECKPOINT, 450.00000f, 620.00000f, -1096.00000f, 90.00000f, -180.00000f, 0.00000f, 1.00000f, 1.00000f, 1.00000f, { 450, -166, 9, 10 } }, 
	{ OBJECT_CHECKPOINT, 887.00000f, 620.00000f, -1152.00000f, 90.00000f, -135.00000f, 0.00000f, 1.00000f, 1.00000f, 1.00000f, { 1519, -470, 10, 11 } }, 
	{ OBJECT_CHECKPOINT, 1540.00000f, 620.00000f, -1999.00000f, 90.00000f, -135.00000f, 0.00000f, 1.00000f, 1.00000f, 1.00000f, { 2240, -1385, 11, 12 } }, 
	{ OBJECT_CHECKPOINT, 2718.00000f, 620.00000f, -2778.00000f, 90.00000f, -180.00000f, 0.00000f, 1.00000f, 1.00000f, 1.00000f, { 2718, -1806, 12, 13 } }, 
	{ OBJECT_CHECKPOINT, 4520.00000f, 620.00000f, -2890.00000f, 90.00000f, -180.00000f, 0.00000f, 1.00000f, 1.00000f, 1.00000f, { 4520, -1479, 13, 14 } }, 
	{ OBJECT_CHECKPOINT, 5960.00000f, 620.00000f, -2444.00000f, 90.00000f, -225.00000f, 0.00000f, 1.00000f, 1.00000f, 1.00000f, { 4962, -1446, 14, 15 } }, 
	{ OBJECT_CHECKPOINT, 6381.00000f, 620.00000f, -1352.00000f, 90.00000f, -270.00000f, 0.00000f, 1.00000f, 1.00000f, 1.00000f, { 4970, -1352, 15, 16 } }, 
	{ OBJECT_CHECKPOINT, 6457.00000f, 620.00000f, 620.00000f, 90.00000f, -270.00000f, 0.00000f, 1.00000f, 1.00000f, 1.00000f, { 5046, 620, 16, 17 } }, 
	{ OBJECT_CHECKPOINT, 6008.00000f, 620.00000f, 2152.00000f, 90.00000f, -315.00000f, 0.00000f, 1.00000f, 1.00000f, 1.00000f, { 5010, 1154, 17, 18 } }, 
	{ OBJECT_CHECKPOINT, 4894.00000f, 620.00000f, 2566.00000f, 90.00000f, 0.00000f, 0.00000f, 1.00000f, 1.00000f, 1.00000f, { 4894, 1155, 18, 0 } }, 
};
