#ifndef sp_p3_h
#define sp_p3_h

#include <PR/sp.h>

#define p3TRUEIMAGEH	16
#define p3TRUEIMAGEW	32
#define p3IMAGEH	32
#define p3IMAGEW	32
#define p3BLOCKSIZEW	32
#define p3BLOCKSIZEH	32
#define p3SCALEX	1.0
#define p3SCALEY	1.0
#define p3MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap p3_bitmaps[];
extern Gfx p3_dl[];

#define NUM_p3_BMS  (sizeof(p3_bitmaps)/sizeof(Bitmap))

extern Sprite p3_sprite;

#endif 

#if 0	/* Image preview */
+--------------------------------+
|      rrrrrrrr        rrrrrr    |
|      rrrrrrrr        rrrrrr    |
|    rrYYYYYYYYrr    rrYYYYYYrr  |
|    rrYYrrrrrrYYrr    rrrrrrYYrr|
|  rrYYrrrrrrrrYYrr    rrYYYYrr  |
|  rrYYYYYYYYYYrr  rr    rrYYrr  |
|  rrYYYYYYYYYYrr  rr    rrYYrr  |
|rrYYrrrrrrrrrr  rrYYrrrrrrYYrr  |
|rrYYrr            rrYYYYYYrr    |
|rrrr                rrrrrr      |
+--------------------------------+
#endif

