#ifndef sp_choose_h
#define sp_choose_h

#include <PR/sp.h>

#define chooseTRUEIMAGEH	17
#define chooseTRUEIMAGEW	200
#define chooseIMAGEH	32
#define chooseIMAGEW	224
#define chooseBLOCKSIZEW	32
#define chooseBLOCKSIZEH	32
#define chooseSCALEX	1.0
#define chooseSCALEY	1.0
#define chooseMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap choose_bitmaps[];
extern Gfx choose_dl[];

#define NUM_choose_BMS  (sizeof(choose_bitmaps)/sizeof(Bitmap))

extern Sprite choose_sprite;

#endif 

#if 0	/* Image preview */
+------------------------------------------------+
| .r... r  rr rr....... r .....  .   .  r.....  .|
|RR.RRRRbRRRrrRRRRr RR.R RRRrRRrrRRrRRrR rRrRRr R|
+------------------------------------------------+
#endif

