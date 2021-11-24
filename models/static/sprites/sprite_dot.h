#ifndef sp_dot_h
#define sp_dot_h

#include <PR/sp.h>

#define dotTRUEIMAGEH	8
#define dotTRUEIMAGEW	8
#define dotIMAGEH	32
#define dotIMAGEW	32
#define dotBLOCKSIZEW	32
#define dotBLOCKSIZEH	32
#define dotSCALEX	1.0
#define dotSCALEY	1.0
#define dotMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap dot_bitmaps[];
extern Gfx dot_dl[];

#define NUM_dot_BMS  (sizeof(dot_bitmaps)/sizeof(Bitmap))

extern Sprite dot_sprite;

#endif 

#if 0	/* Image preview */
+--------+
|        |
|  BBBB  |
| BBBBBB |
| BBBBBB |
|  BBBB  |
+--------+
#endif

