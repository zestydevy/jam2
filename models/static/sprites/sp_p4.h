#ifndef sp_p4_h
#define sp_p4_h

#include <PR/sp.h>

#define p4TRUEIMAGEH	16
#define p4TRUEIMAGEW	32
#define p4IMAGEH	32
#define p4IMAGEW	32
#define p4BLOCKSIZEW	32
#define p4BLOCKSIZEH	32
#define p4SCALEX	1.0
#define p4SCALEY	1.0
#define p4MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap p4_bitmaps[];
extern Gfx p4_dl[];

#define NUM_p4_BMS  (sizeof(p4_bitmaps)/sizeof(Bitmap))

extern Sprite p4_sprite;

#endif 

#if 0	/* Image preview */
+--------------------------------+
|      cccccccc              cc  |
|      cccccccc              cc  |
|    ccCCCCCCCCcc      cc  ccCCcc|
|    ccCCccccccCCcc  ccCCccccCCcc|
|  ccggccccccccggcc  ccggccggcc  |
|  ccggggggggggcc  ccggccccggcc  |
|  ccggggggggggcc  ccggccccggcc  |
|ccggcccccccccc    ccggggggggggcc|
|ccCCcc              ccccCCcccc  |
|cccc                    cc      |
+--------------------------------+
#endif

