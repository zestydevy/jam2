#include "math.hpp"
#include "scenedata.h"

#include "collider.hpp"

typedef struct t_checkpoint
{
    TVec3F a;
    TVec3F b;

    s16 idx;
    s16 nextIdx;

    f32 distFromNext;
} TCheckpoint;

class TCheckpointTracker
{
    public:

    int mCheckpointCount {0};
    TCheckpoint mCheckpoints[32];

    TCheckpointTracker()
    {
    }

    ~TCheckpointTracker() = default;

    bool clearCheckpoints();
    bool loadCheckpoint(const TSceneEntry& data);
    bool postLoadCheckpoints();
    f32 getDistance(TVec3F& position, s16 index);
    s16 getNextCheckpoint(s16 index);
    TVec3F getCheckpointCenter(s16 index);
    TVec3F getRandomCheckpointPosition(s16 index);
    TVec3F getClosestCheckpointPosition(TVec3F& position, s16 index);
    f32 getRaceProgress(TVec3F& position, s16 index);
};

extern TCheckpointTracker* gCurrentRace;