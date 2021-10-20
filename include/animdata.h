#ifndef __H_ANIMDATA
#define __H_ANIMDATA

#include <ultra64.h>

#define ANIMINDEX_NUMPARTS(animindex) (sizeof(animindex) / sizeof(u16) / 6)

struct TAnimData
{
    s32 loopStart;
    s32 loopEnd;
    s8 numOfAnimatedJoints;
    s16 * values;
    u16 * indices;
};

#endif