#pragma once
#include <ultra64.h>

#include "math.hpp"
#include "dynlist.hpp"
#include "array.hpp"

// -------------------------------------------------------------------------- //

struct TJointAnimData
{
    s32 loopStart;
    s32 loopEnd;
    s8 numOfAnimatedJoints;
    s16 * values;
    u16 * indices;
};

struct TBoneNode
{
    s16 frameCount{0};
    s16 index{0};
};

struct TBone
{
    TBoneNode x;
    TBoneNode y;
    TBoneNode z;

    TBone & operator=(TBone * other)
    {
        x.frameCount = other->x.frameCount;
        y.frameCount = other->y.frameCount;
        z.frameCount = other->z.frameCount;

        x.index = other->x.index;
        y.index = other->y.index;
        z.index = other->z.index;

        return *this;
    }
};

class TJoint
{
    public:

    TJoint() = default;
    TJoint(s32 jointCount);
    ~TJoint();

    void attachJoint(char const * name, Gfx * dl, TVec3F const & offset);
    void attachAnimatedJoint(char const * name, Gfx * dl, TVec3F const & offset);
    void attachJoint(char const * name, Gfx * dl, TVec3F const & offset, TVec3S const & rot);
    void registerAnimation(TJointAnimData const & anim);
    void playAnimation() {mIsAnimOn = true;}
    void updateAnimation();
    void detach();
    TMtx44 & getJoint(char const * name);
    TVec3F & getJointPosition(char const * name);
    TVec3F & getJointPosition(s32 const index);
    void getAnimTransFrame(TVec3F & dest);
    void getAnimRotFrame(TVec3S & dest);

    void reset() {mJointIdx = 0; mAnimJntIdx = 0;}
    void setDl(TDynList2 * dl) {mDl = dl;}

    private:

    TArray<TMtx44 *> mMtxList;
    TArray<Mtx *> mMtxFList;
    TArray<TVec3F> mPosList;
    TArray<TBone *> mTransAnimList;
    TArray<TBone *> mRotAnimList;
    char ** mNames;
    TJointAnimData * mAnim{nullptr};
    TVec3S mLastIdx;
    TVec3S mLastRotIdx;
    s32 mJointIdx{0};
    s32 mJointCount{0};
    s32 mAnimJntIdx{0};
    s32 mFrame{0};
    bool mIsAnimOn{false};
    TDynList2 * mDl{nullptr};
};

// -------------------------------------------------------------------------- //