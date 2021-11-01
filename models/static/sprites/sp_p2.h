#ifndef sp_p2_h
#define sp_p2_h

#include <PR/sp.h>

#define p2TRUEIMAGEH	16
#define p2TRUEIMAGEW	32
#define p2IMAGEH	32
#define p2IMAGEW	32
#define p2BLOCKSIZEW	32
#define p2BLOCKSIZEH	32
#define p2SCALEX	1.0
#define p2SCALEY	1.0
#define p2MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap p2_bitmaps[];
extern Gfx p2_dl[];

#define NUM_p2_BMS  (sizeof(p2_bitmaps)/sizeof(Bitmap))

extern Sprite p2_sprite;

#endif 

#if 0	/* Image preview */
+--------------------------------+
|      bbbbbbbb          bbbb    |
|      bbbbbbbb          bbbb    |
|    bbccccccccbb      bbccccbb  |
|    bbccbbbbbbccbb      bbbbccbb|
|  bbccbbbbbbbbccbb  bbbb  bbccbb|
|  bbggggggggggbb  bbggggbbggbb  |
|  bbggggggggggbb  bbggggbbggbb  |
|bbggbbbbbbbbbb  bbggbbbbggggbb  |
|bbCCbb            bbCCCCbbbbCCbb|
|bbbb                bbbb    bb  |
+--------------------------------+
#endif

