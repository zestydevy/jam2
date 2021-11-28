#include "kartobject.hpp"

void TKartObject::init() {
    TObject::init();
}

void TKartObject::update() { }

void TKartObject::updateMtx()
{
    if (mMtxNeedsUpdate){
        TMtx44 temp1, temp2, temp3, temp4, mPosMtx, mScaleMtx;
        
        mPosMtx.translate(mPosition);
        temp1.rotateAxisX(mRotation.x());
        temp2.rotateAxisY(mRotation.y());
        temp3.rotateAxisZ(mRotation.z());
        TMtx44::concat(temp2, temp1, mRotMtx);
        TMtx44::concat(mRotMtx, temp3, mRotMtx);
        temp2.rotateAxisY(mTurnDirection);
        temp4.rotateAxis(TVec3F{0.0f, 0.0f, 1.0f}, mLeanAngle);
        TMtx44::concat(mRotMtx, temp2, mRotMtx);
        TMtx44::concat(mRotMtx, temp4, mRotMtx);
        mScaleMtx.scale(mScale);

        //Combine mtx
        TMtx44::concat(mPosMtx, mRotMtx, temp1);
        TMtx44::concat(temp1, mScaleMtx, temp2);

        TMtx44::floatToFixed(temp2, mFMtx);
        TMtx44::floatToFixed(mRotMtx, mFRotMtx);

        mMtxNeedsUpdate = false;
    }
}

void TKartObject::draw()
{
    if (!mInCamera)
        return;

    updateMtx();

    if (mSuperParent != nullptr) {
        gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mSuperParent->getDrawMtx()),
            G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);
    }
    
    // kart object matrix
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFMtx),
        G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);

    bool lod = mLODMesh != nullptr && !TCamera::checkDistance(mPosition, mLODDistanceSquared);
        
    if (mMesh != nullptr) {
        if (lod){
            gSPDisplayList(mDynList->pushDL(), mLODMesh);
        }
        else{
            gSPDisplayList(mDynList->pushDL(), mMesh);
        }
    }

    if (mSuperParent != nullptr) gSPPopMatrix(mDynList->pushDL(), G_MTX_MODELVIEW);
    gSPPopMatrix(mDynList->pushDL(), G_MTX_MODELVIEW);
}