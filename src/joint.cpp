#include "joint.hpp"
#include "exception.hpp"
#include "heap.hpp"

// -------------------------------------------------------------------------- //

TJoint::TJoint(s32 jointCount)
{
    auto heap = THeap::getCurrentHeap();
    mMtxList.setHeap(heap);
    mMtxFList.setHeap(heap);
    mPosList.setHeap(heap);

    mJointCount = jointCount;
    mNames = new char * [mJointCount];

    if (jointCount == 0) {
        TException::fault("allocating 0 joints?? no thanks");
    }

    for (s32 i = 0; i < jointCount; ++i) {
        TMtx44 * mtx = new TMtx44;
        Mtx * mtxF = new Mtx;
        mMtxList.push(mtx);
        mMtxFList.push(mtxF);
        mPosList.push(TVec3F{0.0f, 0.0f, 0.0f});
    }
}

// -------------------------------------------------------------------------- //

void TJoint::attachJoint(char * const name, Gfx * dl, TVec3F const & offset)
{
    mNames[mJointIdx] = name;
    mPosList[mJointIdx] = offset;

    TMtx44 temp1, temp2, temp3, mPosMtx, mScaleMtx, mRotMtx;
    
    mPosMtx.translate(mPosList[mJointIdx]);
    temp1.rotateAxisX(0);
    temp2.rotateAxisY(0);
    temp3.rotateAxisZ(0);
    TMtx44::concat(temp2, temp1, mRotMtx);
    TMtx44::concat(mRotMtx, temp3, mRotMtx);
    mScaleMtx.scale(TVec3F{1.0f, 1.0f, 1.0f});

    //Combine mtx
    TMtx44::concat(mPosMtx, mRotMtx, temp1);
    TMtx44::concat(temp1, mScaleMtx, temp2);

    TMtx44::floatToFixed(temp2, reinterpret_cast<Mtx &>(*mMtxFList[mJointIdx]));
    
    gSPMatrix(mDl->pushDL(), OS_K0_TO_PHYSICAL(mMtxFList[mJointIdx]),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);

    gSPDisplayList(mDl->pushDL(), dl);

    ++mJointIdx;
}

// -------------------------------------------------------------------------- //

TMtx44 & TJoint::getJoint(char * const name)
{
    for (s32 i = 0; i < mJointCount; ++i) {
        if (mNames[i] == name) {
            return reinterpret_cast<TMtx44 &>(*mMtxList[i]);
        }
    }

    // just return the first joint if not found
    return reinterpret_cast<TMtx44 &>(*mMtxList[0]);
}

// -------------------------------------------------------------------------- //

TVec3F & TJoint::getJointPosition(char * const name)
{
    for (s32 i = 0; i < mJointCount; ++i) {
        if (mNames[i] == name) {
            return mPosList[i];
        }
    }

    // just return the first joint position if not found
    return mPosList[0];
}

// -------------------------------------------------------------------------- //