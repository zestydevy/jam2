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
#include "checkpoint.hpp"

#include "../models/static/shadow/shadow.h"

const bool PLAYER_DOUBLESIDEDCOL = true;
const int PLAYER_COLLISIONCHECK_COUNT = 8;

//TODO: convert to variables
const float PLAYER_GRAVITY = 980.0f * kInterval;
const float PLAYER_BOUNCE_SCALE = 1.5f;
const float PLAYER_MIN_BOUNCE_SPEED = 50.0f;

const float PLAYER_BRAKE_MIN_SPEED = 20.0f;

const float PLAYER_CAMERA_TRAIL_MINSPEED = 20.0f;
const float PLAYER_CAMERA_TRAIL_DISTANCE = 200.0f;
const float PLAYER_CAMERA_TRAIL_HEIGHT = 100.0f;

const float CAR_STEPDIST = 50.0f;
const float CAR_COLHEIGHT = 10.0f;
const float CAR_WIDTH = 50.0f;
const float CAR_LENGTH = 45.0f;

const float FRICTION_ENERGYLOSS = 0.01f;
const float CAR_FRONT_THRESHOLD = 0.75f;

// -------------------------------------------------------------------------- //

TPlayer * gPlayers[4] { nullptr, nullptr, nullptr, nullptr };

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
    setCollideRadius(CAR_LENGTH);
    setCollideCenter(mPosition);

    mCameraTarget = mPosition;

    //Car stats
    mCarStats.importStats(sTestCar);

    mGameState = gameplaystate_t::PLAYERGAMESTATE_NORMAL;

    mLastCheckpoint = 0;
    if (mPad == nullptr)
        aiCalcNextTarget();

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

s16 calcTriangleAngle(TVec3F& a, TVec3F& b, TVec3F& c){
    float ab = TVec3F::dist(a, b);
    float ac = TVec3F::dist(a, c);
    float bc = TVec3F::dist(b, c);
    float abc = ((ac * ac) + (ab * ab) - (bc * bc)) / (2 * ac * ab);
    return TSine::acos(abc);
}

void TPlayer::checkLateralCollision(){
    const TCollFace* collFaces[PLAYER_COLLISIONCHECK_COUNT];
    for (int i = 0; i < PLAYER_COLLISIONCHECK_COUNT; i++)
        collFaces[i] = nullptr;

    TCollision::checkRadius(mPosition, CAR_LENGTH, collFaces, PLAYER_COLLISIONCHECK_COUNT);

    TMtx44 rot;
    rot.rotateAxis(mUp, TSine::fromDeg(90));
    TVec3F carFront = mPosition + (mForward * CAR_LENGTH);
    TVec3F right = rot.mul(mForward);

    TVec3F p, cp;
    for (int i = 0; i < PLAYER_COLLISIONCHECK_COUNT; i++){
        if (collFaces[i] == nullptr)
            break;
        if (collFaces[i]->isGround())
            continue;

        TVec3F carCenter = mPosition + (mUp * CAR_STEPDIST);

        collFaces[i]->calcClosestPt(carCenter + (mUp * CAR_STEPDIST), &cp);

        //Ignore face if its low enough to drive over
        if (cp.y() < carCenter.y())
            continue;

        TVec3F nrm = collFaces[i]->nrm;

        collFaces[i]->project(mPosition, &p);

        //Flip normal if double sided collisions are enabled and we are on the wrong side
        if (PLAYER_DOUBLESIDEDCOL){
            float direction = nrm.dot(mPosition - p);
            if (direction < 0.0f)
                nrm = TVec3F(0.0f, 0.0f, 0.0f) - nrm;
        }

        float energy = -mForward.dot(nrm);
        float friction = FRICTION_ENERGYLOSS;

        float steerDot = right.dot(nrm);

        if (energy > CAR_FRONT_THRESHOLD){
            //Turn car towards wall
            friction = 1.0f;

            mDriveDirection -= (int)(steerDot * steerDot * mSpeed * CAR_LENGTH + 0.99f);
        }
        else{
            //Turn car along wall
            mDriveDirection += (int)(energy * mSpeed + 0.99f) * (steerDot >= 0.0f ? 1 : -1);
            showFriction(p,  energy * friction * mSpeed);
        }

        mSpeed -= TMath<f32>::clamp(energy * friction * mSpeed, 0.0f, mSpeed);
        showCollision(p, energy * mSpeed);

        mPosition = p + nrm * CAR_LENGTH;
    }
}

void TPlayer::checkMeshCollision(const TCollFace * face, float radius){
    TVec3F p;
    face->project(mPosition, &p);
    mPosition = p + face->nrm * radius;
}

void TPlayer::snapToGround(){
    TVec3F pt = getPosition() + TVec3F(0.0f, CAR_STEPDIST, 0.0f);
    auto face = TCollision::findGroundBelow(pt, CAR_STEPDIST);
    if (face != nullptr) mPosition.y() = face->calcYAt(pt.xz());
}

void TPlayer::resetCamera(){
    if (mCamera != nullptr){
        mCamera->setAngle(mDriveDirection);
        mCamera->setPosition(mPosition - (mForward * PLAYER_CAMERA_TRAIL_DISTANCE * (mSpeed >= 0 ? 1.0f : -1.0f)) + TVec3F(0.0f, PLAYER_CAMERA_TRAIL_HEIGHT, 0.0f));
        mCamera->jumpToTarget();
    }
}

void TPlayer::aiUpdate(bool& aButton, bool& bButton, f32& steer){
    bool inGrass = false;
    if (mGroundFace != nullptr && mGroundFace->surf == SURFACE_GRASS)
        inGrass = true;

    aButton = true;

    TVec2F right = TVec2F(TSine::ssin(mDriveDirection + TSine::fromDeg(90)), TSine::scos(mDriveDirection + TSine::fromDeg(90)));

    TVec2F diff = mCurrentAITarget.xz() - mPosition.xz();
    diff.normalize();

    float amtRight = -diff.dot(right);

    steer = TMath<f32>::clamp(amtRight * 4.0f, -1.0f, 1.0f);
    if (mSpeed < 0)
        steer = -steer;

    if (!inGrass){
        if (TMath<f32>::abs(amtRight) > 0.5f && mSpeed > 10.0f)
            aButton = false;
        if (TMath<f32>::abs(amtRight) > 0.75f && mSpeed > 10.0f)
            bButton = true;
        else if (TMath<f32>::abs(amtRight) > 0.9f)
            bButton = true;
    }
}

void TPlayer::aiCalcNextTarget(){
    switch (mAIType){
        case AI_BAD:
            mCurrentAITarget = gCurrentRace->getCheckpointCenter(gCurrentRace->getNextCheckpoint(mLastCheckpoint));
            break;
        case AI_RANDOM:
            mCurrentAITarget = gCurrentRace->getRandomCheckpointPosition(gCurrentRace->getNextCheckpoint(mLastCheckpoint));
            break;
        case AI_GOOD:
            mCurrentAITarget = gCurrentRace->getClosestCheckpointPosition(mPosition, gCurrentRace->getNextCheckpoint(mLastCheckpoint));
            break;
    }
}

void TPlayer::update()
{
    TObject::update();

    /* Get controller/ai inputs */
    bool aButton = false;
    bool bButton = false;
    float steer = 0.0f;

    if (mPad != nullptr){
        //Player controlled
        aButton = mPad->isHeld(A);
        bButton = mPad->isHeld(B);
        steer = TMath<f32>::clamp((float)mPad->getAnalogX() / 160.0f, -1.0f, 1.0f);
    }
    else{
        //AI
        aiUpdate(aButton, bButton, steer);
    }

    /* Ground check */
    TVec3F pt = getPosition() + TVec3F(0.0f, CAR_STEPDIST, 0.0f);
    TVec3F front = pt + (mForward * CAR_LENGTH);
    mGroundFace = TCollision::findGroundBelow(pt, CAR_STEPDIST);
    float groundY = -1000.0f;
    if (mGroundFace != nullptr)
        groundY = mGroundFace->calcYAt(pt.xz());
    TVec3F vel = mForward * mSpeed + (mYSpeed * TVec3F(0.0f, 1.0f, 0.0f));

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
            float turn = steer;

            if (mOnGround && mGroundFace->surf == SURFACE_GRASS)        //Grass slowdown
                mSpeed *= 0.985f;
            if (!mOnGround || (!aButton && !bButton))   //Air resistance
                mSpeed *= mCarStats.getDrift(mSpeed);

            //Get real up direction
            if (mOnGround)
                mUp = mGroundFace->nrm.xyz();
            else
                mUp = TVec3F(0.0f, 1.0f, 0.0f);

            //Get real forward direction
            calculateForwardDirection();

            //Apply gravity to speed
            mSpeed -= (mForward.dot(TVec3F(0.0f, 1.0f, 0.0f)) * PLAYER_GRAVITY * 50.0f) * kInterval;

            //acceleration and deceleration
            if (mOnGround){
                if (aButton) {
                    mSpeed += mCarStats.getAcceleration(mSpeed) * kInterval;
                }
                if (bButton) {
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
            if (mCamera != nullptr){
                mCamera->setMode(cameraMode);
                if (cameraMode)
                    mCamera->setPosition(mPosition - (mForward * PLAYER_CAMERA_TRAIL_DISTANCE * (mSpeed >= 0 ? 1.0f : -1.0f)) + TVec3F(0.0f, PLAYER_CAMERA_TRAIL_HEIGHT, 0.0f));
                mCameraTarget = mPosition;
            }
        }
        break;
    }

    //Apply forward momentum
    mPosition += mForward * mSpeed * kInterval;

    //World collision
    checkLateralCollision();

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

    int nextcheckpoint = gCurrentRace->getNextCheckpoint(mLastCheckpoint);
    float checkPointDist = gCurrentRace->getDistance(mPosition, nextcheckpoint);
    float progress = gCurrentRace->getRaceProgress(mPosition, mLastCheckpoint);
    
    if (checkPointDist < 50.0f){
        mLastCheckpoint = nextcheckpoint;

        if (mPad == nullptr)
            aiCalcNextTarget();
    }

    updateBlkMap();
}

void TPlayer::calculateForwardDirection(){
    TVec3F forward = TVec3F(TSine::ssin(mDriveDirection), 0.0f, TSine::scos(mDriveDirection));
    TVec3F proj = forward.dot(mUp) * mUp;
    mForward = forward - proj;
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
}

void TPlayer::drawShadow()
{
    if (mGroundFace != nullptr) {
        mShadow->draw();
    }
}

//Called whenever the player crashes
void TPlayer::showCollision(TVec3F& p, float energy){

}

//Called whenever the player scrapes a wall
void TPlayer::showFriction(TVec3F& p, float energy){

}

// -------------------------------------------------------------------------- //

void TPlayer::onCollide(
    TCollider * const other
) {
    // TODO
}