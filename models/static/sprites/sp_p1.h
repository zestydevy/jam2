#ifndef sp_p1_h
#define sp_p1_h

#include <PR/sp.h>

#define p1TRUEIMAGEH	16
#define p1TRUEIMAGEW	32
#define p1IMAGEH	32
#define p1IMAGEW	32
#define p1BLOCKSIZEW	32
#define p1BLOCKSIZEH	32
#define p1SCALEX	1.0
#define p1SCALEY	1.0
#define p1MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap p1_bitmaps[];
extern Gfx p1_dl[];

#define NUM_p1_BMS  (sizeof(p1_bitmaps)/sizeof(Bitmap))

extern Sprite p1_sprite;

#endif 

#if 0	/* Image preview */
+--------------------------------+
|      rrrrrrrr              rrrr|
|      rrrrrrrr              rrrr|
|    rrMMMMMMMMrr        rrrrMMrr|
|    rrRRrrrrrrRRrr    rrRRRRRRrr|
|  rrRRrrrrrrrrRRrr      rrRRrr  |
|  rrYYYYYYYYYYrr        rrYYrr  |
|  rrYYYYYYYYYYrr        rrYYrr  |
|rrYYrrrrrrrrrr        rrYYrr    |
|rr@@rr                rr@@rr    |
|rrrr                    rr      |
+--------------------------------+
#endif

