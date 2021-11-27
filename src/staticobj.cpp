#include <nusys.h>

#include "staticobj.hpp"
#include "camera.hpp"
#include "math.hpp"

#include "kartobject.hpp"

// -------------------------------------------------------------------------- //

static Gfx * gObjMeshList[] =
{
    nullptr,
};

// -------------------------------------------------------------------------- //

void TObject::setPosition(TVec3<f32> const & pos)
{
    mPosition = pos;
    mMtxNeedsUpdate = true;
}

void TObject::setRotation(TVec3<f32> const & rot)
{
    mRotation.set(rot.x(), rot.y(), rot.z());
    mMtxNeedsUpdate = true;
}

void TObject::setScale(TVec3<f32> const & scale)
{
    mScale = scale;
    mMtxNeedsUpdate = true;
}

void TObject::init()
{
    mInCamera = true;
    updateMtx();
    mMtxNeedsUpdate = true;
}

void TObject::increaseRadius(float threshold){

}

void TObject::updateMtx()
{
    if (!mInCamera){
        mMtxNeedsUpdate = true;
        return;
    }

    TMtx44 temp1, temp2, temp3, mPosMtx, mScaleMtx;
    
    mPosMtx.translate(mPosition);
    temp1.rotateAxisX(mRotation.x());
    temp2.rotateAxisY(mRotation.y());
    temp3.rotateAxisZ(mRotation.z());
    TMtx44::concat(temp2, temp1, mRotMtx);
    TMtx44::concat(mRotMtx, temp3, mRotMtx);
    mScaleMtx.scale(mScale);

    //Combine mtx
    TMtx44::concat(mPosMtx, mRotMtx, temp1);
    TMtx44::concat(temp1, mScaleMtx, temp2);

    TMtx44::floatToFixed(temp2, mFMtx);
    TMtx44::floatToFixed(mRotMtx, mFRotMtx);

    mMtxNeedsUpdate = false;
}

void TObject::update() {
    mInCamera = mAlwaysDraw || TCamera::checkVisible(mPosition, mDrawDistanceSquared);
    mUsingLOD = !mInCamera || !TCamera::checkDistance(mPosition, mLODDistanceSquared);
}

void TObject::draw()
{
    if (!mInCamera)
        return;

    if (mMtxNeedsUpdate)
        updateMtx();

    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFMtx),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);

    if (mParent != nullptr){
        gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mParent->getDrawMtx()),
            G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    }
        
    if (mMesh != nullptr) {
        if (mUsingLOD && mLODMesh != nullptr){
            gSPDisplayList(mDynList->pushDL(), mLODMesh);
        }
        else{
            gSPDisplayList(mDynList->pushDL(), mMesh);
        }
    }

    gSPPopMatrix(mDynList->pushDL(), G_MTX_MODELVIEW);
}

void TObject::drawRing()
{
}

// -------------------------------------------------------------------------- //

Gfx * TObject::getMeshGfx(
    EObjType const type
) {
    if (type >= EObjType::INVALID) {
        return nullptr;
    }

    return gObjMeshList[(u32)type];
}

const TObjectData & TObject::getNestObjectInfo(
    EObjType const type
) {
    if (type >= EObjType::INVALID) {
        return gObjectDataList[0];
    }

    return gObjectDataList[(u32)type];
}

// -------------------------------------------------------------------------- //

void TShadow::init() {
    TObject::init();
    mShadowNeedsUpdate = true;
}

void TShadow::update() {
    mInCamera = mParent->getInCamera();
}

void TShadow::updateMtx()
{
    if (!mInCamera){
        mMtxNeedsUpdate = true;
        return;
    }

    TMtx44 temp1, temp2, temp3, mPosMtx, mScaleMtx, mScaleMtx2, mAngleMtx;
    
    mPosMtx.translate(mPosition);
    temp1.rotateAxisX(mRotation.x());
    temp2.rotateAxisY(mRotation.y());
    temp3.rotateAxisZ(mRotation.z());
    TMtx44::concat(temp2, temp1, mRotMtx);
    TMtx44::concat(mRotMtx, temp3, mRotMtx);
    mScaleMtx.scale(mScale);

    if (mShadowNeedsUpdate){
        //Update dynamic shadow scale
        mScaleMtx2.scale({1.0f, 0.0f, 1.0f});

        float proj = -1.0f / mRelativeLightSource.y(); //Tx = x / (x * proj.x + 1) | Ty = y / (y * proj.y + 1)

        TVec2F shear = { TMath<f32>::sqrt(TMath<f32>::abs(mRelativeLightSource.x() / mRelativeLightSource.y())) * (mRelativeLightSource.x() >= 0.0f ? -1.0f : 1.0f), 
                         TMath<f32>::sqrt(TMath<f32>::abs(mRelativeLightSource.z() / mRelativeLightSource.y())) * (mRelativeLightSource.z() >= 0.0f ? -1.0f : 1.0f)};

        mAngleMtx.shear({0.0f, 0.0f}, shear, {0.0f, 0.0f});
        temp1.projective({0.0f, proj, 0.0f});
        TMtx44::concat(temp1, mAngleMtx, mAngleMtx);

        //Combine mtx
        TMtx44::floatToFixed(mAngleMtx, mFAngleMtx);
        TMtx44::floatToFixed(mScaleMtx2, mFScaleMtx2);

        mShadowVisible = proj > -0.05f && mRelativeLightSource.y() > 0.0f;

        mShadowNeedsUpdate = false;
    }

    //Combine mtx
    TMtx44::floatToFixed(mPosMtx, mFMtx);
    TMtx44::floatToFixed(mScaleMtx, mFScaleMtx1);
    TMtx44::floatToFixed(mRotMtx, mFRotMtx);

    mMtxNeedsUpdate = false;
}

void TShadow::draw() {
    if (!mInCamera){
        return;
    }

    if (mMtxNeedsUpdate){
        updateMtx();
    }

    if (!mShadowVisible){
        return;
    }

    mShadowUsingLOD = mLODMesh != nullptr && !TCamera::checkDistance(mPosition, mLODDistanceSquared);

    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFMtx),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFRotMtx),
            G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFScaleMtx2),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFAngleMtx),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    if (mParent != nullptr){
        gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mParent->getRotMtx()),
            G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    }
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFScaleMtx1),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
        
    if (mMesh != nullptr) {
        if (mShadowUsingLOD){
            gSPDisplayList(mDynList->pushDL(), mLODMesh);
        }
        else{
            gSPDisplayList(mDynList->pushDL(), mMesh);
        }
    }

    gSPPopMatrix(mDynList->pushDL(), G_MTX_MODELVIEW);
}

void TShadow::drawChild(TKartObject * child) {
    if (!mInCamera){
        return;
    }

    if (!mShadowVisible){
        return;
    }

    if (mShadowUsingLOD){
        return;
    }

    if (child->getShadowMesh() == nullptr){
        return;
    }

    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFMtx),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFRotMtx),
            G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFScaleMtx2),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFAngleMtx),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    if (mParent != nullptr){
        gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mParent->getRotMtx()),
            G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    }
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFScaleMtx1),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&child->getTransformationMtx()),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&child->getRotMtx()),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
        
    if (mMesh != nullptr) {
        gSPDisplayList(mDynList->pushDL(), child->getShadowMesh());
    }

    gSPPopMatrix(mDynList->pushDL(), G_MTX_MODELVIEW);
}