#ifndef sp_BIGSLEY_h
#define sp_BIGSLEY_h

#include <PR/sp.h>

#define BIGSLEYTRUEIMAGEH	80
#define BIGSLEYTRUEIMAGEW	80
#define BIGSLEYIMAGEH	96
#define BIGSLEYIMAGEW	96
#define BIGSLEYBLOCKSIZEW	32
#define BIGSLEYBLOCKSIZEH	32
#define BIGSLEYSCALEX	1.0
#define BIGSLEYSCALEY	1.0
#define BIGSLEYMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap BIGSLEY_bitmaps[];
extern Gfx BIGSLEY_dl[];

#define NUM_BIGSLEY_BMS  (sizeof(BIGSLEY_bitmaps)/sizeof(Bitmap))

extern Sprite BIGSLEY_sprite;

#endif 

#if 0	/* Image preview */
+------------------------------------------------+
|                                                |
|        . .         ...               .         |
|  .iiiibbbbiiiiiiiiiiiiiiiiiiiibbbbbbiiiiiiiii. |
|  .iIibbbbbbimmmmmmmmmmmmmmmmIiBBbbbbbimmmmmIii |
|  .iibBBBBBBiimmmmmmmmmmmmmmmmbBBBBBBBBBimmmMii |
|  .ibBBBBBBBBbmmmmmmmmmmmmmmmiBBBBBBBBBBBmmmBii |
|  .bbBBBBBBBBBbbmmmmmmmmmmmmmiBBBBBBBBBBBmmmBbb |
|  ibbBBBBBBBBBBibmmmmmmmmmmmmbBBBBBBBBBBimmmBbb |
|  .bbBBBBBBBBBBBBibbbiirrrrrrrriiiiiiiBbimMMBbb |
|  bibBBBBBBBBBRiirrrrrrrrrrrrrrrrrrrrrribMMMMbb.|
|  bbiiBBBBbrrrrrRrrrrrrrrrr .rrrrrrrrrr.mMMMMbb |
|  bBMMMBiRrrrrrriiiiirrrrRi@@@@IrrrrrrrrmMMMBbb |
|  bbBMBirrrrrrrI@@@@@@IiBi@@@@@@@iirrrrrmiBBibb |
|  .bBMMirrrrrri@@@@@@@@IBi@@@@@@@@IiBBRBBBBiBbb |
|  bBMMirrrrrii@@@@@@@iIibBiiiIii@@@iBBBBBbrRRbb |
|  bBMrrrrrrrBbI@@@@@iII.bBii@@@I@@@IBBBBBBRriii |
|  .rRrriiimbBb@@@@@@@@@IbBBii@@@@@@iBBBBBBBBbbb |
|  .rRRibBBBBBBi@@@@@@@IiBBBBiI@@@@@iBBBBBBBBbbb |
|  .rRRRRiBBBBBbII@@@@IiBbiiiibiiiiiBBBBBBBBBbbi.|
|  .rRRrriBBBBBBiiiIIiibBi    .BBbBBBBBBBBBBBbb. |
|  rrriBBBBBBBBiBBBBBBBBBBBiiiBBBBBBBbibBBBBBbb. |
|  ribbBBBBBBBBbBBBBBBBBBBBBbiBBBBBBBBiBBBBBBbbb |
|  .iiBBBBBBBBBbiBBBBBBBBi.rrrrrriiiiBBBBBBBBibb |
|  .ibmmbiBBBBBBBiiiii..rrrrrrrrriBBBBBBbBBBbMii |
|  .bBmmmmbBBBBBBBBBBrrrrrrrrrr.iBBBBbBmmiimiMii.|
|  .bBmmmiBBBBBBBBBBBirrrrrrrriBBBBBbmmmmmmmmMbi.|
|  ibBmmmiiimmmbbibBBBiirrrrrmBBBBbimmmmmmmmmMbi.|
|  ibMmmmmmmmmmbimmiBBBBiiiRBBBBBBimmmmmmmmmmMbr |
|  .bBmmmmmmmmmmmmmiiBBBBBBBBBBBBBBmimmmmmmmmmbb.|
|  .ibmmmmmmmmmmmmiibBBBBBBBBBBBBBBBbiimmmmmmMbi.|
|   .iiiiiiiiiiiiibbbbbbbbbbbbbbbbbbbbbiiiiiiiii |
|     ......ii............ ...b......     .....  |
+------------------------------------------------+
#endif

