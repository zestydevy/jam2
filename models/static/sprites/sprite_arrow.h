#ifndef sp_choose_arrow_h
#define sp_choose_arrow_h

#include <PR/sp.h>

#define choose_arrowTRUEIMAGEH	38
#define choose_arrowTRUEIMAGEW	32
#define choose_arrowIMAGEH	64
#define choose_arrowIMAGEW	32
#define choose_arrowBLOCKSIZEW	32
#define choose_arrowBLOCKSIZEH	32
#define choose_arrowSCALEX	1.0
#define choose_arrowSCALEY	1.0
#define choose_arrowMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap choose_arrow_bitmaps[];
extern Gfx choose_arrow_dl[];

#define NUM_choose_arrow_BMS  (sizeof(choose_arrow_bitmaps)/sizeof(Bitmap))

extern Sprite choose_arrow_sprite;

#endif 

#if 0	/* Image preview */
+--------------------------------+
|                                |
|                                |
|     rIRRrr                     |
|     r@@@RRrr                   |
|    r@@@@@@@@YRrr.              |
|   rR@@@@@@@@@@@RRrr            |
|  rR@@YYYYYYYYYYYYYYRRrr        |
|  r@@YYYYYYYYYYYYYYYYYRRr.      |
|  rrrRRYYYYYYYYYYYYYYYYRrrr     |
|   rrrrRRYYYYYYYYYYYYYYRrrr.    |
|     brrrrrrRRRRRRRRRRRRrrrbb   |
|      .brrrrRRRRRRRRRRRRrrrbb.  |
|     .rRR@@RRRRRRRRRRRRrrrrbb.  |
|   rrRI@RRRRRRRRRRRRRRRrrrrbb.  |
|  r@RRRRRRRRRRRRRRRRRRRrrrrbb.  |
|  rRRRRRRRRRRRRRRRRRRrrrrrrbb.  |
|   rRRRRRRRRRRRRrrrrrrrrrrrbb.  |
|   .rRRRRRRRRRrrrrrrrrrrrrbbb.  |
|    .rRRRRrrrrrrrrrrrbbbbbbbb.  |
|     rRRrrrrrrrrrrrbbbbbbbbb.   |
|      rrrrrrrrrbbbbbbbb..       |
|       rrrrrrbbbbbbbb.          |
|         .bbbbbbb.              |
|          .bbb..                |
|                                |
+--------------------------------+
#endif

