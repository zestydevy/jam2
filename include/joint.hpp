#pragma once
#include <ultra64.h>

#include "math.hpp"
#include "dynlist.hpp"
#include "array.hpp"

// -------------------------------------------------------------------------- //

class TJoint
{
    public:

    TJoint() = default;
    TJoint(s32 jointCount);
    ~TJoint() = delete;

    void attachJoint(char * const name, Gfx * dl, TVec3F const & offset);
    TMtx44 & getJoint(char * const name);
    TVec3F & getJointPosition(char * const name);

    void reset() {mJointIdx = 0;}
    void setDl(TDynList2 * dl) {mDl = dl;}

    private:

    TArray<TMtx44 *> mMtxList;
    TArray<Mtx *> mMtxFList;
    TArray<TVec3F> mPosList;
    char ** mNames;
    s32 mJointIdx{0};
    s32 mJointCount{0};
    TDynList2 * mDl{nullptr};
};

// -------------------------------------------------------------------------- //