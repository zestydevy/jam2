#ifndef sp_maraca_h
#define sp_maraca_h

#include <PR/sp.h>

#define maracaTRUEIMAGEH	80
#define maracaTRUEIMAGEW	80
#define maracaIMAGEH	96
#define maracaIMAGEW	96
#define maracaBLOCKSIZEW	32
#define maracaBLOCKSIZEH	32
#define maracaSCALEX	1.0
#define maracaSCALEY	1.0
#define maracaMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap maraca_bitmaps[];
extern Gfx maraca_dl[];

#define NUM_maraca_BMS  (sizeof(maraca_bitmaps)/sizeof(Bitmap))

extern Sprite maraca_sprite;

#endif 

#if 0	/* Image preview */
+------------------------------------------------+
|                                                |
|                                                |
|   bbbbbbbbbbbbbbbbbbrrrrrrrrrrrrrrrrrrbbbbbii. |
|   bbBBBBBBBBBBBBBBBbRRRRRRRRrrRRrrRRriBCCcCGgg |
|  .bBCCCCCCCCCCCCCCCbrrrrrrrrrrrrrrrBBCccgggggg |
|  .bbCCCCCCCCCCCCCCCmrrrrrrrrrrrrriBCccgggggGg. |
|  .bbCCCCCCCCCCCCCCCrrrrrrrrrrrrmCCccgggggggGgg |
|  .bbCCCCCCCCCCCCCCcrrrrrrrrrriMCccgggggggggggg |
|  .bbCCCCCCCCCCCCCCirrrrrrrrmBCccgggggggggggggg |
|  biicCCCCCCCCCCCCcrrrrrrrriBgggggggggggggggGg. |
|  .bbBbbccCCCCCCCCirrrrrr.cgggggggggggggggggGgg |
|  .bbbbbbbbbCCCCCCirrrrrccgggggggcgccccccgggggg |
|  bbBbbbbbbbbbbbcCccCCcCcCCCcC@@@ccCCCCCCCCCCbi |
|  bbBbbbbbbbbbbbbcIIIccCCCCcc@@@@@@cCCCCCCCCCbb |
|  .bbBbbbbbbbbbc@@@@@@@IcCCc@@@@@@@IcCCCCCCCCbb |
|  .bbBbbbbbbbbc@@@@@@@@@cCCc@@@@@@@@cCCccCCCCbb.|
|  .bbBbbbbbBCCC@@@@@@@@cccCcI.@@@@@@ccCCCcCCCbb.|
|   ibCcbRBCCCCI@@@@@@@@cccCcI.C@@@@@ccCCCCCCCbb |
|   bbrRRrcCCCCc@@@@@@@@iccCGCC@@@@@CcCCCCCcCCbb |
|   irrRRcCCCCCc@@@@@@@@@cYYYYYcIYcccCCCCCcCCCbb |
|   rrrRRcCCCCCCccI@@@CcyYYYYYYYYYYYYYIcCCCCCCbb |
|  .rrrRRcCCCCCCCCCC@IYYYYYYYYYYYYYYYYYcCCCCCBbb |
|   rriCCCcCCCCCCCCCcYYYYYYYYYYYYYYYYYYYcCCCCCgb |
|   irCCCCCccCCCCCCCcYYYYYYYYYYYYYYYYYYYccCCCCgg |
|  .bBCCCCCCCCcccCCCCcYYYYYYYYYYYYYYYYYYcCCCCCgg |
|  .gGCCCCCCCCCCCccccCccYYYYYYYYYYYYYYYYCCCCCCgg |
|  .gGCCCCCCCCCCCCcCCCCCCcccIGYYYYYYYYYcCCCCCCgg |
|  .gGCCCCCCCCCCCCcCCCCCCCCCCCCcCcCccccCCCCCCCgg |
|   ggCCCCCCCCCCCCCCCCCCCccCCCCCCCCCCCCCCCCCCCgg |
|   ggCCCCCCCCCCcciCCCCCcCCccccCCCCCcccCCCCCCCgg.|
|   ggggggggggggbbbbbbbbbbbbbbggggggbbbggggggggg |
|    ..g..ggg..............b......  ........g.   |
+------------------------------------------------+
#endif

