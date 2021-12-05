#ifndef sp_meter_h
#define sp_meter_h

#include <PR/sp.h>

#define meterTRUEIMAGEH	32
#define meterTRUEIMAGEW	32
#define meterIMAGEH	32
#define meterIMAGEW	32
#define meterBLOCKSIZEW	32
#define meterBLOCKSIZEH	32
#define meterSCALEX	1.0
#define meterSCALEY	1.0
#define meterMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap meter_bitmaps[];
extern Gfx meter_dl[];

#define NUM_meter_BMS  (sizeof(meter_bitmaps)/sizeof(Bitmap))

extern Sprite meter_sprite;

#endif 

#if 0	/* Image preview */
+--------------------------------+
|iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii|
|iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii|
|IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII|
|IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII|
|IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII|
|IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII|
|IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII|
|IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII|
|IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII|
|IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII|
|IIIIIIIIIIIIIIIIIIIIIIIIIIIIIII@|
|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@|
|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@|
|IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII|
|IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII|
|IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII|
|IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII|
|IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII|
|IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII|
|iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii|
|iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii|
+--------------------------------+
#endif

