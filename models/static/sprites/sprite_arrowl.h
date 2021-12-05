#ifndef sp_choose_arrowl_h
#define sp_choose_arrowl_h

#include <PR/sp.h>

#define choose_arrowlTRUEIMAGEH	38
#define choose_arrowlTRUEIMAGEW	32
#define choose_arrowlIMAGEH	64
#define choose_arrowlIMAGEW	32
#define choose_arrowlBLOCKSIZEW	32
#define choose_arrowlBLOCKSIZEH	32
#define choose_arrowlSCALEX	1.0
#define choose_arrowlSCALEY	1.0
#define choose_arrowlMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap choose_arrowl_bitmaps[];
extern Gfx choose_arrowl_dl[];

#define NUM_choose_arrowl_BMS  (sizeof(choose_arrowl_bitmaps)/sizeof(Bitmap))

extern Sprite choose_arrowl_sprite;

#endif 

#if 0	/* Image preview */
+--------------------------------+
|                                |
|                                |
|                     rrRRIr     |
|                   rrRR@@@r     |
|              .rrRY@@@@@@@@r    |
|            rrRR@@@@@@@@@@@Rr   |
|        rrRRYYYYYYYYYYYYYY@@Rr  |
|      .rRRYYYYYYYYYYYYYYYYY@@r  |
|     rrrRYYYYYYYYYYYYYYYYRRrrr  |
|    .rrrRYYYYYYYYYYYYYYRRrrrr   |
|   bbrrrRRRRRRRRRRRRrrrrrrb     |
|  .bbrrrRRRRRRRRRRRRrrrrb.      |
|  .bbrrrrRRRRRRRRRRRR@@RRr.     |
|  .bbrrrrRRRRRRRRRRRRRRR@IRrr   |
|  .bbrrrrRRRRRRRRRRRRRRRRRRR@r  |
|  .bbrrrrrrRRRRRRRRRRRRRRRRRRr  |
|  .bbrrrrrrrrrrrRRRRRRRRRRRRr   |
|  .bbbrrrrrrrrrrrrRRRRRRRRRr.   |
|  .bbbbbbbbrrrrrrrrrrrRRRRr.    |
|   .bbbbbbbbbrrrrrrrrrrrRRr     |
|       ..bbbbbbbbrrrrrrrrr      |
|          .bbbbbbbbrrrrrr       |
|              .bbbbbbb.         |
|                ..bbb.          |
|                                |
+--------------------------------+
#endif

