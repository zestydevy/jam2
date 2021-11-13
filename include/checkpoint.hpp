#pragma once

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

typedef struct t_ranking
{
    int racerID;

    int ranking;

    int lastCheckpoint;

    float curLapProgress;
    float totalProgress;
    int lap;
} TRanking;

class TCheckpointTracker
{
    public:
    TCheckpointTracker()
    {
    }

    ~TCheckpointTracker() = default;

    bool clearCheckpoints();
    bool loadCheckpoint(const TSceneEntry & data);
    bool postLoadCheckpoints();
    f32 getDistance(const TVec3F & position, s16 index);
    s16 getNextCheckpoint(s16 index);
    TVec3F getCheckpointCenter(s16 index);
    TVec3F getRandomCheckpointPosition(s16 index);
    TVec3F getClosestCheckpointPosition(const TVec3F & position, s16 index);

    f32 updateRaceProgress(s16 racerID, const TVec3F & position, s16 index);
    s16 getRaceRanking(s16 racerID);
    f32 getDistFromFront(s16 racerID);

    s16 registerRacer();
    void updateRankings();

    private:

    s16 mCheckpointCount {0};
    TCheckpoint mCheckpoints[32];

    s16 mNumRacers{0};
    s16 mLeader{-1};
    TRanking mRankings[8];
};

extern TCheckpointTracker* gCurrentRace;