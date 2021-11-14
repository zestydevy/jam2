#include "scenedata.h"
#include "exception.hpp"

#include "checkpoint.hpp"

TCheckpointTracker* gCurrentRace;

bool TCheckpointTracker::clearCheckpoints(){
    for (int i = 0; i < 32; i++){
        mCheckpoints[i].idx = -1;
        mCheckpoints[i].nextIdx = -1;
    }
    mCheckpointCount = 0;

    for (int i = 0; i < 8; i++){
        mRankings[i].curLapProgress = 0.0f;
        mRankings[i].lap = 0;
        mRankings[i].totalProgress = 0.0f;
        mRankings[i].lastCheckpoint = -1;
        mRankings[i].racerID = -1;
        mRankings[i].ranking = -1;
    }

    mLeader = 0;
    mNumRacers = 0;
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

f32 TCheckpointTracker::getDistance(const TVec3F & position, s16 index){
    return TCollideUtil::distPtLine(mCheckpoints[index].a, mCheckpoints[index].b, TVec3F(position.x(), 0.0f, position.z()));
}

s16 TCheckpointTracker::getNextCheckpoint(s16 index){
    return mCheckpoints[index].nextIdx;
}

TVec3F TCheckpointTracker::getCheckpointCenter(s16 index){
    return (mCheckpoints[index].a + mCheckpoints[index].b) / 2.0f;
}

TVec3F TCheckpointTracker::getClosestCheckpointPosition(const TVec3F & position, s16 index, bool lookAhead){
    TVec3F pt;
    
    if (lookAhead){
        TCollideUtil::distPtLine(mCheckpoints[mCheckpoints[index].nextIdx].a, mCheckpoints[mCheckpoints[index].nextIdx].b, TVec3F(position.x(), 0.0f, position.z()), &pt);
        if (TCollideUtil::testLineLine2D(position.xz(), pt.xz(), mCheckpoints[index].a.xz(), mCheckpoints[index].b.xz())){
            return pt;
        }
    }

    TCollideUtil::distPtLine(mCheckpoints[index].a, mCheckpoints[index].b, TVec3F(position.x(), 0.0f, position.z()), &pt);
    return pt;
}

TVec3F TCheckpointTracker::getRandomCheckpointPosition(s16 index){
    float t = TMath<float>::clamp(TMath<float>::frandnorm(0.5f, 0.1f), 0.25f, 0.75f);
    TVec3F ab = mCheckpoints[index].b - mCheckpoints[index].a;
    TVec3F pt = mCheckpoints[index].a + (ab * t);
    return pt;
}

f32 TCheckpointTracker::updateRaceProgress(s16 racerID, const TVec3F & position, s16 index){
    float sigma = 1 / (f32)mCheckpointCount;
    float startProg = sigma * index;
    float progress = startProg + (sigma * getDistance(position, mCheckpoints[index].nextIdx) / mCheckpoints[index].distFromNext);

    if (index == 0 && mRankings[racerID].lastCheckpoint == mCheckpointCount - 1){
        mRankings[racerID].lap++;
    }
    else if (index == mCheckpointCount - 1 && mRankings[racerID].lastCheckpoint == 0){
        mRankings[racerID].lap--;
    }
    mRankings[racerID].lastCheckpoint = index;
    mRankings[racerID].curLapProgress = progress;
    mRankings[racerID].totalProgress = (f32)mRankings[racerID].lap + progress;

    return progress;
}

s16 TCheckpointTracker::getRaceRanking(s16 racerID){
    return mRankings[racerID].ranking;
}

f32 TCheckpointTracker::getDistFromFront(s16 racerID){
    return mRankings[mLeader].totalProgress - mRankings[racerID].totalProgress;
}

s16 TCheckpointTracker::registerRacer(){
    if (mNumRacers >= 8){
        TException::fault("Too many racers!");
    }
    mRankings[mNumRacers].ranking = mNumRacers + 1;
    mRankings[mNumRacers].racerID = mNumRacers;
    return mNumRacers++;
}

void TCheckpointTracker::updateRankings(){
    for (int i = 0; i < 8 || mRankings[i].racerID == -1; i++){
        for (int j = 0; j < 8 || mRankings[j].racerID == -1; j++){
            if (mRankings[i].totalProgress > mRankings[j].totalProgress && mRankings[i].ranking < mRankings[j].ranking){
                int t = mRankings[i].ranking;
                mRankings[i].ranking = mRankings[j].ranking;
                mRankings[j].ranking = t;

                if (mRankings[i].ranking == 1){
                    mLeader = i;
                }
            }
        }
    }
}