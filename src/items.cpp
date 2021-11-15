#include "items.hpp"

#include "../models/static/pokestop/pokestop.h"

const float POKESTOP_HEADHEIGHT = 650.0f;
const float POKESTOP_PLATHEIGHT = 350.0f;

const float POKESTOP_HEADROTRATE = 30.0f;
const float POKESTOP_PLATROTRATE = 12.0f;
const float POKESTOP_SWIRLROTRATE = 75.0f;

void TPokeStop::init(){
    TObject::init();

    mRotation = TVec3<f32>(0.0f, 0.0f, 0.0f);

    mScale = {0.5f, 0.5f, 0.5f};

    initCollider(TAG_POKESTOP, TAG_UNKNOWN, TAG_PLAYER, 1);
    setCollideRadius(mRadius);
    setCollideCenter(mPosition);

    setMesh(pokestop_base_pokestop_base_mesh, mat_pokestop_base_pokestop);
    mHeadMesh = pokestop_head_pokestop_head_mesh;
    mPlatMesh = pokestop_plat_pokestop_plat_mesh;
    mSwirlMesh = pokestop_swirly_pokestop_swirly_mesh;
}

void TPokeStop::update(){
    mHeadRotation += TSine::fromDeg(POKESTOP_HEADROTRATE) * kInterval;
    mPlatRotation += TSine::fromDeg(POKESTOP_PLATROTRATE) * kInterval;
    mSwirlRotation += TSine::fromDeg(POKESTOP_SWIRLROTRATE) * kInterval;

    mInCamera = true;
    mMtxNeedsUpdate = true;
}

void TPokeStop::updateMtx()
{
    TObject::updateMtx();

    TMtx44 temp1, mHeadRotMtx, mPlatRotMtx, mSwirlRotMtx;
    
    temp1.translate({0.0f, POKESTOP_HEADHEIGHT, 0.0f});
    mHeadRotMtx.rotateAxisY(mHeadRotation);
    mSwirlRotMtx.rotateAxisZ(mSwirlRotation);
    TMtx44::concat(mHeadRotMtx, mSwirlRotMtx, mSwirlRotMtx);
    TMtx44::concat(temp1, mHeadRotMtx, mHeadRotMtx);
    TMtx44::concat(temp1, mSwirlRotMtx, mSwirlRotMtx);
    
    temp1.translate({0.0f, POKESTOP_PLATHEIGHT, 0.0f});
    mPlatRotMtx.rotateAxisY(mPlatRotation);
    TMtx44::concat(temp1, mPlatRotMtx, mPlatRotMtx);

    //Combine mtx
    TMtx44::floatToFixed(mHeadRotMtx, mFHeadMtx);
    TMtx44::floatToFixed(mPlatRotMtx, mFPlatMtx);
    TMtx44::floatToFixed(mSwirlRotMtx, mFSwirlMtx);
}

void TPokeStop::draw(){
    if (mMtxNeedsUpdate)
        updateMtx();

    //draw base
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFMtx),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);
    
    gSPDisplayList(mDynList->pushDL(), mInitializer);
    gSPDisplayList(mDynList->pushDL(), mMesh);

    //draw head
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFHeadMtx),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);
    
    gSPDisplayList(mDynList->pushDL(), mHeadMesh);

    gSPPopMatrix(mDynList->pushDL(), G_MTX_MODELVIEW);

    //draw swirl
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFSwirlMtx),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);
    
    gSPDisplayList(mDynList->pushDL(), mSwirlMesh);

    gSPPopMatrix(mDynList->pushDL(), G_MTX_MODELVIEW);

    //draw platform
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFPlatMtx),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);

    gSPDisplayList(mDynList->pushDL(), mPlatMesh);

    gSPPopMatrix(mDynList->pushDL(), G_MTX_MODELVIEW);
    gSPPopMatrix(mDynList->pushDL(), G_MTX_MODELVIEW);
}

void TPokeStop::onCollide(TCollider * other){
    if (other->getCollideTag() == TAG_PLAYER){
        //player is in pokestop range
    }
}