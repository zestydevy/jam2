#ifndef sp_minimap_h
#define sp_minimap_h

#include <PR/sp.h>

#define minimapTRUEIMAGEH	150
#define minimapTRUEIMAGEW	64
#define minimapIMAGEH	160
#define minimapIMAGEW	64
#define minimapBLOCKSIZEW	32
#define minimapBLOCKSIZEH	32
#define minimapSCALEX	1.0
#define minimapSCALEY	1.0
#define minimapMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap minimap_bitmaps[];
extern Gfx minimap_dl[];

#define NUM_minimap_BMS  (sizeof(minimap_bitmaps)/sizeof(Bitmap))

extern Sprite minimap_sprite;

#endif 

#if 0	/* Image preview */
+------------------------------------------------+
|           ....gggggggg.... .                   |
|       ggiiiiiiiiiiiiiiiiiiiiiiiiiii.           |
|    .iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii      |
|   giiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii.     |
|  .iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii    |
| giiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii   |
| iiiiiiiiiiiiii........iiiiiiiiiiiiiiiiiiiiii.  |
| iiiiiiiii                           iiiiiiiii  |
|iiiiiiiiii                           iiiiiiiii  |
|iiiiiiiii.                           .iiiiiiii. |
|iiiiiiiii.                           .iiiiiiiii |
|iiiiiiiii.                           .iiiiiiiii |
|iiiiiiiii.                            iiiiiiiii |
|iiiiiiiii.                            iiiiiiiii |
|iiiiiiiii.                            iiiiiiiii |
|iiiiiiiii.                            iiiiiiiii |
|iiiiiiiiii                            iiiiiiiii |
|iiiiiiiiii                            iiiiiiiii |
|.iiiiiiiii                            iiiiiiiii |
|.iiiiiiiii                           iiiiiiiiii |
|.iiiiiiiii                          iiiiiiiiii  |
|.iiiiiiiii                         .iiiiiiiiii  |
|.iiiiiiiii                        iiiiiiiiiii   |
|.iiiiiiiii                       iiiiiiiiiiii   |
|.iiiiiiiii                     iiiiiiiiiiii.    |
|.iiiiiiiii                    iiiiiiiiiiii      |
|.iiiiiiiii                  iiiiiiiiiiiii       |
|.iiiiiiiii                 iiiiiiiiiiii         |
|.iiiiiiiii                iiiiiiiiiiii          |
|.iiiiiiiii               iiiiiiiiiii.           |
|.iiiiiiiii               iiiiiiiiii.            |
|.iiiiiiiii              iiiiiiiiii              |
|iiiiiiiiii              iiiiiiiii               |
|iiiiiiiiii              iiiiiiiii               |
|iiiiiiiiii              iiiiiiiii               |
|iiiiiiiiii              iiiiiiiii               |
|iiiiiiiiii              iiiiiiiii               |
|iiiiiiiiii              iiiiiiiii               |
|iiiiiiiiii              iiiiiiiii               |
|iiiiiiiiii              iiiiiiiii.              |
|iiiiiiiiii              iiiiiiiii.              |
|iiiiiiiiii              iiiiiiiiii              |
|iiiiiiiiii               iiiiiiiiiii            |
|iiiiiiiiii               .iiiiiiiiiii.          |
|iiiiiiiiii                iiiiiiiiiiiii         |
|iiiiiiiiii                 iiiiiiiiiiiiiii      |
|iiiiiiiiii                  iiiiiiiiiiiiiii     |
|iiiiiiiiii                    iiiiiiiiiiiiiii   |
|iiiiiiiiii                      iiiiiiiiiiiiii  |
|iiiiiiiiii                        iiiiiiiiiiii. |
|iiiiiiiiii                          iiiiiiiiiii |
|iiiiiiiiii                            iiiiiiiiii|
|iiiiiiiiii                             iiiiiiiii|
|iiiiiiiiii                             iiiiiiiii|
|iiiiiiiiii                             iiiiiiiii|
|iiiiiiiiii                             iiiiiiiii|
|iiiiiiiiii                             iiiiiiiii|
|iiiiiiiiii                             iiiiiiiii|
|iiiiiiiiii                             iiiiiiiii|
|iiiiiiiiii                             iiiiiiiii|
|iiiiiiiiii                             iiiiiiiii|
|iiiiiiiiii                             iiiiiiiii|
|iiiiiiiiii                             iiiiiiiii|
|iiiiiiiiii                             iiiiiiiii|
|iiiiiiiiii                             iiiiiiiii|
|.iiiiiiiii                             iiiiiiiii|
| iiiiiiiii                            iiiiiiiiii|
| iiiiiiiiii.                         iiiiiiiiiii|
| iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii |
|  .iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii. |
|   iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii   |
|    iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii   |
|     .iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii     |
|         iiiiiiiiiiiiiiiiiiiiiiiiiiiiiii        |
+------------------------------------------------+
#endif

