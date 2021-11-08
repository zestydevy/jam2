#include <nusys.h>

#include "player.hpp"
#include "math.hpp"
#include "animator.hpp"
#include "util.hpp"
#include "segment.h"
#include <nusys.h>
#include <nualstl_n.h>
#include "audio.hpp"
#include "collision.h"

#include "../models/static/shadow/shadow.h"

//TODO: convert to variables
const float PLAYER_GRAVITY = 980.0f * kInterval;
const float PLAYER_BOUNCE_SCALE = 1.5f;
const float PLAYER_MIN_BOUNCE_SPEED = 50.0f;

const float PLAYER_BRAKE_MIN_SPEED = 20.0f;

const float PLAYER_CAMERA_TRAIL_MINSPEED = 20.0f;
const float PLAYER_CAMERA_TRAIL_DISTANCE = 200.0f;
const float PLAYER_CAMERA_TRAIL_HEIGHT = 100.0f;

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
    //setAnimation(1, ANIM_IDLE);

    // shadow
    mShadow = new TShadow(mDynList);
    mShadow->init();
    mShadow->setParent(this);
    mShadow->setPosition({0.0f,0.0f,0.0f});
    mShadow->setScale(mScale);

    initCollider(TAG_PLAYER, TAG_PLAYER, 0, 1);
    setCollideRadius(PLAYER_RADIUS);
    setCollideCenter(mPosition);

    mCameraTarget = mPosition;

    //Car stats
    mCarStats.importStats(sTestCar);

    mGameState = gameplaystate_t::PLAYERGAMESTATE_NORMAL;

    startDriving();
}

void TPlayer::setAnimation(int length, playeranim_t anim, bool loop, float timescale){
}

void TPlayer::startDriving(){
    mState = PLAYERSTATE_DRIVING;
}

void TPlayer::startCrashing(){
    mState = PLAYERSTATE_STUNNED;
}

void TPlayer::checkLateralCollision(){
    TVec3F nrmm = mDirection;
    nrmm.normalize();
    nrmm *= (PLAYER_RADIUS / 2.0f);

    mGroundFace = TCollision::findGroundBelow(mPosition + nrmm, PLAYER_RADIUS);  //recalc ground pos

    //if (mGroundFace != nullptr){
    //    float yPos = mGroundFace->calcYAt((mPosition + nrmm).xz()) + PLAYER_RADIUS;
    //    mPosition.y() = yPos;
    //}

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

    /* Ground check */
    TVec3F pt = getPosition() + TVec3F(0.0f, PLAYER_RADIUS, 0.0f);
    mGroundFace = TCollision::findGroundBelow(pt, PLAYER_RADIUS);
    float groundY = -1000.0f;
    if (mGroundFace != nullptr) groundY = mGroundFace->calcYAt(pt.xz());
    else{ 
        mGroundFace = TCollision::findGroundBelow(pt + (mForward * PLAYER_RADIUS), PLAYER_RADIUS);
        if (mGroundFace != nullptr) groundY = mGroundFace->calcYAt(pt.xz());
    }

    TVec3F vel = mForward * mSpeed + (mYSpeed * TVec3F(0.0f, 1.0f, 0.0f));

    /* Collision check */
    mClosestFace = TCollision::findClosest(mPosition, PLAYER_RADIUS);

    if (mGroundFace != nullptr && mPosition.y() <= groundY + 0.001f && vel.dot(mGroundFace->nrm) < 0.05f) {
        mPosition.y() = groundY;

        if (mYSpeed < PLAYER_MIN_BOUNCE_SPEED)
            mYSpeed = 0.0f;
        else
            mYSpeed = -mYSpeed / PLAYER_BOUNCE_SCALE;

        mOnGround = true;
    }
    else {
        if (mOnGround)
            mYSpeed = vel.y();

        mYSpeed -= PLAYER_GRAVITY;
        mPosition.y() += mYSpeed * kInterval;

        mForward = TVec3F(0.0f, 1.0f, 0.0f) * mYSpeed;

        mOnGround = false;
    }

    //Debug show rpm
    //mScale.y() = (0.1f + mCarStats.getGearTransition(mSpeed)) * mScale.x();

    switch (mState){
        // idle. c'mon let's get a move on...
        case playerstate_t::PLAYERSTATE_DRIVING:{
            //checkLateralCollision();

            float turn = TMath<f32>::clamp((float)mPad->getAnalogX() / 160.0f, -1.0f, 1.0f);

            if (mOnGround && mGroundFace->surf == SURFACE_GRASS)        //Grass slowdown
                mSpeed *= 0.985f;
            if (!mOnGround || (!mPad->isHeld(A) && !mPad->isHeld(B)))   //Air resistance
                mSpeed *= mCarStats.getDrift(mSpeed);

            //Get real up direction
            if (mOnGround)
                mUp = mGroundFace->nrm.xyz();
            else
                mUp = TVec3F(0.0f, 1.0f, 0.0f);

            //Get real forward direction
            TVec3F forward = TVec3F(TSine::ssin(mDriveDirection), 0.0f, TSine::scos(mDriveDirection));
            TVec3F proj = forward.dot(mUp) * mUp;
            mForward = forward - proj;

            //Apply gravity to speed
            mSpeed -= (mForward.dot(TVec3F(0.0f, 1.0f, 0.0f)) * PLAYER_GRAVITY * 50.0f) * kInterval;

            //acceleration and deceleration
            if (mOnGround){
                if (mPad->isHeld(A)) {
                    mSpeed += mCarStats.getAcceleration(mSpeed) * kInterval;
                }
                if (mPad->isHeld(B)) {
                    if (mSpeed >= PLAYER_BRAKE_MIN_SPEED)
                        mSpeed *= mCarStats.getBrake(mSpeed);
                    else
                        mSpeed -= mCarStats.getAcceleration(0.0f) * kInterval;
                    if (mSpeed < -200.0f)
                        mSpeed = -200.0f;
                }
            }

            //apply turn rate
            if (mOnGround && turn != 0.0f)
            {
                mDriveDirection -= (int)(turn * mSpeed * mCarStats.getTurn(mSpeed) + 0.99f);

                f32 amtTurn = TMath<f32>::abs(turn);
                f32 conversionLoss = (amtTurn * mCarStats.getTurnConversion(mSpeed)) + (1.0f - amtTurn);
                mSpeed *= conversionLoss;
            }

            //snap camera behind player
            bool cameraMode = mSpeed > PLAYER_CAMERA_TRAIL_MINSPEED || mSpeed < -PLAYER_CAMERA_TRAIL_MINSPEED;
            mCamera->setMode(cameraMode);
            if (cameraMode)
                mCamera->setPosition(mPosition - (mForward * PLAYER_CAMERA_TRAIL_DISTANCE * (mSpeed >= 0 ? 1.0f : -1.0f)) + TVec3F(0.0f, PLAYER_CAMERA_TRAIL_HEIGHT, 0.0f));
            mCameraTarget = mPosition;
        }
        break;
    }

    //Apply forward momentum
    mPosition += mForward * mSpeed * kInterval;

    //Mesh collision
    //if (mClosestFace != nullptr)
    //    checkMeshCollision(mClosestFace, PLAYER_RADIUS);

    //Object collision
    setCollideCenter(mPosition);

    // set shadow position and rotation to floor
    if (mGroundFace != nullptr) {
        s16 rotX = mRotation.x();
        s16 rotZ = mRotation.z();
        rotX = TMath<s16>::lerp(rotX, (s16)TSine::atan2(mGroundFace->nrm.z(), mGroundFace->nrm.y()), kInterval * 4.0f);
        rotZ = TMath<s16>::lerp(rotZ, (s16)-TSine::atan2(mGroundFace->nrm.x(), mGroundFace->nrm.y()), kInterval * 4.0f);
        setRotation(TVec3<s16>(rotX, (s16)0, rotZ));

        pt = getPosition();
        pt.y() = mGroundFace->calcYAt(pt.xz());
        mShadow->setPosition(pt);
        mShadow->setRotation(TVec3<s16>((s16)TSine::atan2(mGroundFace->nrm.z(), mGroundFace->nrm.y()), (s16)0, (s16)-TSine::atan2(mGroundFace->nrm.x(), mGroundFace->nrm.y())));
    }

    mCameraTarget = mPosition;

    updateBlkMap();
}

void TPlayer::updateMtx()
{
    TMtx44 temp1, temp2, temp3, mPosMtx, mScaleMtx;
    
    mPosMtx.translate(mPosition);
    temp1.rotateAxisX(mRotation.x());
    temp2.rotateAxisY(mRotation.y());
    temp3.rotateAxisZ(mRotation.z());
    TMtx44::concat(temp2, temp1, mRotMtx);
    TMtx44::concat(mRotMtx, temp3, mRotMtx);
    temp2.rotateAxisY(mDriveDirection);
    TMtx44::concat(mRotMtx, temp2, mRotMtx);
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
    //mAnim->draw();

    updateMtx();
    TObject::draw();

    if (mGroundFace != nullptr) {
        mShadow->draw();
    }
}

void TPlayer::drawShadow()
{
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