#include "scenedata.h"

#include "checkpoint.hpp"

TCheckpointTracker* gCurrentRace;

bool TCheckpointTracker::clearCheckpoints(){
    for (int i = 0; i < 32; i++){
        mCheckpoints[i].idx = -1;
        mCheckpoints[i].nextIdx = -1;
    }
    mCheckpointCount = 0;
    return true;
}

bool TCheckpointTracker::loadCheckpoint(const TSceneEntry& data){
    int idx = data.data[2];

    if (idx < 0 || idx >= 32)
        return false;

    mCheckpoints[idx].a = TVec3F(data.positionX, 0.0f, data.positionZ);
    mCheckpoints[idx].b = TVec3F((f32)data.data[0], 0.0f, (f32)data.data[1]);
    mCheckpoints[idx].idx = data.data[2];
    mCheckpoints[idx].nextIdx = data.data[3];

    if (mCheckpoints[idx].idx >= mCheckpointCount)
        mCheckpointCount = mCheckpoints[idx].idx + 1;

    return true;
}

bool TCheckpointTracker::postLoadCheckpoints(){
    if (mCheckpointCount < 0 || mCheckpointCount >= 32)
        return false;
    
    for (int i = 0; i < mCheckpointCount; i++){
        TVec3F center = getCheckpointCenter(i);
        TVec3F center2 = getCheckpointCenter((i + 1) % mCheckpointCount);

        mCheckpoints[i].distFromNext = TVec3F::dist(center2, center);
    }

    return true;
}

f32 TCheckpointTracker::getDistance(TVec3F& position, s16 index){
    return TCollideUtil::distPtLine(mCheckpoints[index].a, mCheckpoints[index].b, TVec3F(position.x(), 0.0f, position.z()));
}

s16 TCheckpointTracker::getNextCheckpoint(s16 index){
    return mCheckpoints[index].nextIdx;
}

TVec3F TCheckpointTracker::getCheckpointCenter(s16 index){
    return (mCheckpoints[index].a + mCheckpoints[index].b) / 2.0f;
}

TVec3F TCheckpointTracker::getRandomCheckpointPosition(s16 index){
    return (mCheckpoints[index].a + mCheckpoints[index].b) / 2.0f;
}

f32 TCheckpointTracker::getRaceProgress(TVec3F& position, s16 index){
    float sigma = 1 / (f32)mCheckpointCount;
    float startProg = sigma * index;
    return startProg + (sigma * getDistance(position, mCheckpoints[index].nextIdx) / mCheckpoints[index].distFromNext);
}