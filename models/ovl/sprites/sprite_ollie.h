#ifndef sp_OLIVER_h
#define sp_OLIVER_h

#include <PR/sp.h>

#define OLIVERTRUEIMAGEH	80
#define OLIVERTRUEIMAGEW	80
#define OLIVERIMAGEH	96
#define OLIVERIMAGEW	96
#define OLIVERBLOCKSIZEW	32
#define OLIVERBLOCKSIZEH	32
#define OLIVERSCALEX	1.0
#define OLIVERSCALEY	1.0
#define OLIVERMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap OLIVER_bitmaps[];
extern Gfx OLIVER_dl[];

#define NUM_OLIVER_BMS  (sizeof(OLIVER_bitmaps)/sizeof(Bitmap))

extern Sprite OLIVER_sprite;

#endif 

#if 0	/* Image preview */
+------------------------------------------------+
|                                                |
|                                                |
|    ....................................g....   |
|   ..gggggggggggggggrgrrrrrrrrrrrgrrrrrrrrrrr.  |
|   .rrrrrrrrrrrrrrrrirrrrrrrrrrrrrrrrrrrrrrrr.. |
|   rrrrrrrrrrrrrrrrrRRRrrrrrrrrrrrrrrrrrrrrrr.. |
|   rrrrrrrrrrrrrrrRRRRRRRRRrirrrrrrrrrrrrrrrrr. |
|   rrrrrrrrrrrrrrrRRRRRRRRRRRirrrrrrrrrrrrrrrr. |
|   rrrrrrrrrrrrrrrrRRRRRRRRRRRRrrrrrrrrrrrrrrr. |
|   rrirrrrrrrrrrrrrrRRRRRRRRRRRRrrrrrrrrrrrrrr. |
|  .rrRRRRrrrrrrrrrRRrrrrrrRRRRRRRRRrrrrrrrrrrr. |
|  .rrRRRRRRRrrRRRRRRRRRRRRRRRRRRRrrRrrrrrrrrrr. |
|  .rrRRRRRRRRRRrRRrrrRRRRRRRrIIrrRR.Rrrrrrrrrrr |
|  .rrRRRRRRRRRrrrI@@@rrRRRRiI@@@IirrRRrrrrrrrrr |
|   rrRRRRRrRrrrI@@@@@@@iRRr@@@@@@@@rRRRrrrrrrrr |
|   rirrrrrrrRRi@@@@@@@@iRRr@@@@@@@@rRRRrrrrrrrr |
|   rrrrrrrriRRI@@@@@@@@RRRrII@@@@@@@rRrrrrrrrr. |
|   rrrrrrrrrRRr@@@@@@I IrRRrrI@@@@@RrRrrrrrrrr. |
|  .rrrrrrrRrRRRiI@@@@Ii.RRRRri@@@@@RrRRrrrRrrrr |
|  .rrrRRRrrrRRRRrR@@@@IrRRRRRrI@@IIrRRRRRrrRrrr |
|  .rrrRRrRRRRRRRRRrrrRRrrrrrRRRRrRRRRRRRRRrRrr. |
|  .rrRRRrRRRRRRRRRRRRRRi     RRRRRRRRRRRRRrRrr. |
|  .rrRRRrRRRRRRRRRRRRRRRRrrRRRRRRRrRRRRRRrRRrr. |
|  .rrRRRRrRRRRRRRRRRRRRRRrrRRRRRRr.RRRRRRrRRrr. |
|  .rrRRRRriRRRRRRRRRrrrrrRRrrRRrrrRRRRRriRRRrr. |
|  .rrRRRRRRrRRRRRRRRRRRRRRRRRrrRRRRRRRrRRRRRRr. |
|  .rrRRRRRRRRRiRRRRRRRRRRRRRRRRRRRRrirRRRRRRrr. |
|  .rrRRRRRRRRRRRrrrrrrrrRRRRRRrr.rRRRRRRRRRRrr. |
|  .rrRRRRRRRRRRRRRRRRrrRRRRRRRirrrrrrrRRRRRRrr. |
|  .rrrrRRrrrrrrrrrrrrrrRRRRRRRrirrrrrrrrrrrrrr. |
|   .rrrrrrrrrrrrrrrrrrirrrrrrrrrrrrirrrrrrrrr.. |
|              .. . ..... ....    ....           |
+------------------------------------------------+
#endif

