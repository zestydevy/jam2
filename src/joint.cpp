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
    mTransAnimList.setHeap(heap);
    mRotAnimList.setHeap(heap);

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

TJoint::~TJoint()
{
    for (s32 i = 0; i < mJointCount; ++i) {
        delete mMtxList[i];
        delete mMtxFList[i];
    }
    
    mMtxList.clear();
    mMtxFList.clear();
    mPosList.clear();

    delete[] mNames;
}

// -------------------------------------------------------------------------- //

void TJoint::attachJoint(char const * name, Gfx * dl, TVec3F const & offset)
{
    mNames[mJointIdx] = const_cast<char *>(name);
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

    if (dl != NULL) {
        gSPDisplayList(mDl->pushDL(), dl);
    }

    ++mJointIdx;
}

void TJoint::attachAnimatedJoint(char const * name, Gfx * dl, TVec3F const & offset)
{
    mNames[mJointIdx] = const_cast<char *>(name);
    mPosList[mJointIdx] = offset;

    TMtx44 temp1, temp2, temp3, mPosMtx, mScaleMtx, mRotMtx;
    
    if (mIsAnimOn) {
        TVec3F pos{0.0f, 0.0f, 0.0f};
        getAnimTransFrame(pos);
        mPosMtx.translate(pos);    
    } else {
        mPosMtx.translate(mPosList[mJointIdx]);
    }

    TVec3S rot{};
    if (mIsAnimOn && mAnimJntIdx > 0) {
        getAnimRotFrame(rot);
        rot.x() = static_cast<s16>((f32)(rot.x()) / 360.0F * 360.0);
        rot.y() = static_cast<s16>((f32)(rot.y()) / 360.0F * 360.0);
        rot.z() = static_cast<s16>((f32)(rot.z()) / 360.0F * 360.0);
    }
    temp1.rotateAxisX(rot.x());
    temp2.rotateAxisY(rot.y());
    temp3.rotateAxisZ(rot.z());
    TMtx44::concat(temp2, temp1, mRotMtx);
    TMtx44::concat(mRotMtx, temp3, mRotMtx);
    mScaleMtx.scale(TVec3F{1.0f, 1.0f, 1.0f});

    //Combine mtx
    TMtx44::concat(mPosMtx, mRotMtx, temp1);
    TMtx44::concat(temp1, mScaleMtx, temp2);

    TMtx44::floatToFixed(temp2, reinterpret_cast<Mtx &>(*mMtxFList[mJointIdx]));
    
    gSPMatrix(mDl->pushDL(), OS_K0_TO_PHYSICAL(mMtxFList[mJointIdx]),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);

    if (dl != NULL) {
        gSPDisplayList(mDl->pushDL(), dl);
    }

    ++mJointIdx;
    ++mAnimJntIdx;
}

void TJoint::attachJoint(char const * name, Gfx * dl, TVec3F const & offset, TVec3S const & rot)
{
    mNames[mJointIdx] = const_cast<char *>(name);
    mPosList[mJointIdx] = offset;

    TMtx44 temp1, temp2, temp3, mPosMtx, mScaleMtx, mRotMtx;
    
    mPosMtx.translate(mPosList[mJointIdx]);
    temp1.rotateAxisX(rot.x());
    temp2.rotateAxisY(rot.y());
    temp3.rotateAxisZ(rot.z());
    TMtx44::concat(temp2, temp1, mRotMtx);
    TMtx44::concat(mRotMtx, temp3, mRotMtx);
    mScaleMtx.scale(TVec3F{1.0f, 1.0f, 1.0f});

    //Combine mtx
    TMtx44::concat(mPosMtx, mRotMtx, temp1);
    TMtx44::concat(temp1, mScaleMtx, temp2);

    TMtx44::floatToFixed(temp2, reinterpret_cast<Mtx &>(*mMtxFList[mJointIdx]));
    
    gSPMatrix(mDl->pushDL(), OS_K0_TO_PHYSICAL(mMtxFList[mJointIdx]),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);

    if (dl != NULL) {
        gSPDisplayList(mDl->pushDL(), dl);
    }

    ++mJointIdx;
}

void TJoint::registerAnimation(TJointAnimData const & anim)
{
    for (s32 i = 0; i < anim.numOfAnimatedJoints; ++i) {
        TBone * trans = new TBone;
        TBone * rot = new TBone;
        mTransAnimList.push(trans);
        mRotAnimList.push(rot);
    }

    // set all translation keyframes
    for (s32 i = 0; i < anim.numOfAnimatedJoints; ++i) {
        *mTransAnimList[i] = reinterpret_cast<TBone *>(&anim.indices[(i * 6)]);
    }

    // set all rotation keyframes
    for (s32 i = 1; i < anim.numOfAnimatedJoints; ++i) {
        *mRotAnimList[i] = reinterpret_cast<TBone *>(&anim.indices[i + (anim.numOfAnimatedJoints * 6) - 1]);
    }

    mAnim = const_cast<TJointAnimData *>(&anim);
}

void TJoint::updateAnimation()
{
    if (mFrame <= mAnim->loopEnd - 1) {
        ++mFrame;
    } else {
        mFrame = mAnim->loopStart - 1;
    }
}

void TJoint::detach()
{
    gSPPopMatrix(mDl->pushDL(), G_MTX_MODELVIEW);
}

// -------------------------------------------------------------------------- //

TMtx44 & TJoint::getJoint(char const * name)
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

TVec3F & TJoint::getJointPosition(char const * name)
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

TVec3F & TJoint::getJointPosition(s32 const index)
{
    return mPosList[index];
}

// -------------------------------------------------------------------------- //

void TJoint::getAnimTransFrame(TVec3F & dest)
{
    if (mFrame <= mTransAnimList[mAnimJntIdx]->x.frameCount) {
        mLastIdx.x() = mFrame;
        dest.x() = static_cast<f32>(mAnim->values[mTransAnimList[mAnimJntIdx]->x.index + mFrame]);
    } else {
        //dest.x() = static_cast<f32>(mAnim->values[mTransAnimList[mAnimJntIdx]->x.index + mLastIdx.x()]);
    }

    if (mFrame <= mTransAnimList[mAnimJntIdx]->y.frameCount) {
        mLastIdx.y() = mFrame;
        dest.y() = static_cast<f32>(mAnim->values[mTransAnimList[mAnimJntIdx]->y.index + mFrame]);
    } else {
        //dest.y() = static_cast<f32>(mAnim->values[mTransAnimList[mAnimJntIdx]->y.index + mLastIdx.y()]);
    }

    if (mFrame <= mTransAnimList[mAnimJntIdx]->z.frameCount) {
        mLastIdx.z() = mFrame;
        dest.z() = static_cast<f32>(mAnim->values[mTransAnimList[mAnimJntIdx]->z.index + mFrame]);
    } else { 
        //dest.z() = static_cast<f32>(mAnim->values[mTransAnimList[mAnimJntIdx]->z.index + mLastIdx.z()]);
    }
}

void TJoint::getAnimRotFrame(TVec3S & dest)
{
    if (mFrame <= mRotAnimList[mAnimJntIdx]->x.frameCount) {
        mLastRotIdx.x() = mFrame;
        dest.x() = (mAnim->values[mRotAnimList[mAnimJntIdx]->x.index + mFrame]);
    } else {
        dest.x() = (mAnim->values[mRotAnimList[mAnimJntIdx]->x.index + mLastRotIdx.x()]);
    }

    if (mFrame <= mRotAnimList[mAnimJntIdx]->y.frameCount) {
        mLastRotIdx.y() = mFrame;
        dest.y() = (mAnim->values[mRotAnimList[mAnimJntIdx]->y.index + mFrame]);
    } else {
        dest.y() = (mAnim->values[mRotAnimList[mAnimJntIdx]->y.index + mLastRotIdx.y()]);
    }

    if (mFrame <= mRotAnimList[mAnimJntIdx]->z.frameCount) {
        mLastRotIdx.z() = mFrame;
        dest.z() = (mAnim->values[mRotAnimList[mAnimJntIdx]->z.index + mFrame]);
    } else { 
        dest.z() = (mAnim->values[mRotAnimList[mAnimJntIdx]->z.index + mLastRotIdx.z()]);
    }
}