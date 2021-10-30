#include <nusys.h>

#include "player.hpp"
#include "math.hpp"
#include "animator.hpp"
#include "util.hpp"
#include "segment.h"
#include <nusys.h>
#include <nualstl_n.h>
#include "audio.hpp"

#include "../models/static/shadow/shadow.h"

const float PLAYER_WALKSPEED = 1.2f * kInterval;
const float PLAYER_RUNSPEED = 1.2f * kInterval;
const float PLAYER_TURNSPEED = 1.2f * kInterval;

const float PLAYER_RADIUS = 10.0f;

// -------------------------------------------------------------------------- //

TPlayer * gPlayer { nullptr };

// -------------------------------------------------------------------------- //

void TPlayer::init()
{
    TObject::init();


    // set up to start in flight for testing:
    mDirection = TVec3<f32>(0.0f, 0.0f, 0.0f);
    mRotation = TVec3<f32>(0.0f, 0.0f, 0.0f);
    mSpeed = 1.0f;

    //Load model from ROM

    //Set up model animator
    setAnimation(1, ANIM_IDLE);

    // shadow
    /*mShadow = new TShadow(mDynList);
    mShadow->init();
    mShadow->setParent(this);
    mShadow->setPosition({0.0f,0.0f,0.0f});
    mShadow->setScale(mScale);
    mShadow->setMesh(mesh);
    */

    initCollider(TAG_PLAYER, TAG_PLAYER, 0, 1);
    setCollideRadius(PLAYER_RADIUS);
    setCollideCenter(mPosition);

    mCameraTarget = mPosition;

    mGameState = gameplaystate_t::PLAYERGAMESTATE_NORMAL;
}

void TPlayer::setAnimation(int length, playeranim_t anim, bool loop, float timescale){
}

void TPlayer::startIdle(){
    mState = PLAYERSTATE_IDLE;
}

void TPlayer::checkLateralCollision(){
    TVec3F nrmm = mDirection;
    nrmm.normalize();
    nrmm *= (PLAYER_RADIUS / 2.0f);

    mGroundFace = TCollision::findGroundBelow(mPosition + nrmm, PLAYER_RADIUS);  //recalc ground pos

    float yPos = mGroundFace->calcYAt((mPosition + nrmm).xz()) + PLAYER_RADIUS;
    mPosition.y() = yPos;

    mClosestFace = TCollision::findClosest(mPosition + nrmm , PLAYER_RADIUS / 2.0f); //use closest face in front of player
}

void TPlayer::checkMeshCollision(const TCollFace * face, float radius){
    TVec3F p;
    face->project(mPosition, &p);
    mPosition = p + face->nrm * radius;
}

void TPlayer::update()
{
    TObject::update();

    // ...
    //if (mPad->getAnalogX() != 0 || mPad->getAnalogY() != 0) {
    //    mAngle = TSine::atan2(-mPad->getAnalogX(), -mPad->getAnalogY());
    //}

    TMtx44 temp1, temp2, temp3;

    //find the camera
    s16 cameraAngle = mCamera->getAngle();
    TVec3<f32> up = TVec3<f32>(0.0f, 1.0f, 0.0f);   //Camera up
    TVec3<f32> forward = TVec3<f32>(TSine::ssin(cameraAngle), 0.0f, TSine::scos(cameraAngle));  //Camera forward
    TVec3<f32> right = TVec3<f32>(-forward.z(), 0.0f, forward.x()); //Camera right

    TVec3<f32> fright;  //Flight right
    TVec3<f32> fback;  //Flight back

    float animRate = 0.25f;

    TVec3<f32> move = TVec3<f32>(0.0f, 0.0f, 0.0f);

    /* Ground check */
    mGroundFace = TCollision::findGroundBelow(mPosition, PLAYER_RADIUS);

    /* Collision check */
    mClosestFace = TCollision::findClosest(mPosition, PLAYER_RADIUS);

    switch (mState){
        // idle. c'mon let's get a move on...
        case playerstate_t::PLAYERSTATE_IDLE:{
            checkLateralCollision();
            
            if (mPad->getAnalogX() != 0 || mPad->getAnalogY() != 0) {
                mState = playerstate_t::PLAYERSTATE_WALKING;
            }
        }
        break;

        // -------------------------------------------------------------------- //
        // walking on the ground
        case playerstate_t::PLAYERSTATE_WALKING:{
            checkLateralCollision();

            mCameraTarget = mPosition + (up * 35.00f) + (mDirection * mSpeed * 10.0f);  //Target slightly above player and slightly in front of player

            // played moved, change to walking state
            if (mPad->getAnalogX() == 0 && mPad->getAnalogY() == 0) {
                // back to idle
                mState = playerstate_t::PLAYERSTATE_IDLE;
            }

            mAnim->setTimescale(move.getLength() * 0.1f);
        }
        break;
    }

    //Mesh collision
    checkMeshCollision(mClosestFace, PLAYER_RADIUS);

    //Object collision
    setCollideCenter(mPosition);

    // set shadow position and rotation to floor
    if (getGroundFace() != nullptr) {
        TVec3F pt = getPosition();
        pt.y() = getGroundFace()->calcYAt(pt.xz()) + 1.0f;
        mShadow->setPosition(pt);
        mShadow->setRotation(TVec3<s16>((s16)TSine::atan2(mGroundFace->nrm.z(), mGroundFace->nrm.y()), (s16)0, (s16)-TSine::atan2(mGroundFace->nrm.x(), mGroundFace->nrm.y())));
    }
    else if (mPosition.y() < 0.0f){
        mPosition.y() = 0.0f;   //if they somehow got underground
    }

    mAnim->update();

    updateBlkMap();
}

void TPlayer::updateMtx()
{
    TMtx44 temp1, temp2, temp3, mPosMtx, mScaleMtx;
    
    mPosMtx.translate(mPosition);
    temp1.rotateAxis(TVec3<f32>(-TSine::scos(mRotation.y()), 0.0f, TSine::ssin(mRotation.y())), -mRotation.x());
    temp2.rotateAxisY(mRotation.y());
    TMtx44::concat(temp1, temp2, temp3);
    temp1.rotateAxis(temp3.mul(TVec3<f32>(0.0f, 0.0f, 1.0f)), mRotation.z());
    TMtx44::concat(temp1, temp3, mRotMtx);
    mScaleMtx.scale(mScale);

    //Combine mtx
    TMtx44::concat(mPosMtx, mRotMtx, temp1);
    TMtx44::concat(temp1, mScaleMtx, temp2);

    TMtx44::floatToFixed(temp2, mFMtx);
    TMtx44::floatToFixed(mRotMtx, mFRotMtx);

    mMtxNeedsUpdate = false;
}

void TPlayer::draw()
{
    mAnim->draw();

    //setMesh(mesh);
    
    updateMtx();
    TObject::draw();

    if (mGroundFace != nullptr) {
        mShadow->draw();
    }
}

// -------------------------------------------------------------------------- //

void TPlayer::onCollide(
    TCollider * const other
) {
    // TODO
}