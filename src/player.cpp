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

const float CAR_STEPDIST = 10.0f;
const float CAR_COLHEIGHT = 10.0f;
const float CAR_WIDTH = 30.0f;
const float CAR_LENGTH = 50.0f;

const float FRICTION_ENERGYLOSS = 0.01f;
const float CAR_FRONT_THRESHOLD = 0.75f;

const float CAR_RECOVERY_SPEEDTHRESHOLD = 100.0f;
const float CAR_RECOVERY_TURNTHRESHOLD = 5.0f;
const float CAR_RECOVERY_DIRECTIONTHRESHOLD = 0.999f;

const float CAR_RECOVERY_LR_ENERGYLOSS_GRASS = 0.005f;
const float CAR_RECOVERY_FB_ENERGYLOSS_GRASS = 0.005f;
const float CAR_RECOVERY_LR_ENERGYLOSS_ROAD = 0.06f;
const float CAR_RECOVERY_FB_ENERGYLOSS_ROAD = 0.002f;

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

    initCollider(TAG_PLAYER, TAG_PLAYER, TAG_PLAYER, 1);
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
    TCollCast collFaces[PLAYER_COLLISIONCHECK_COUNT];

    mGroundFace = nullptr;
    float yDiff;
    
    int cnt = TCollision::castRadius(mPosition + (mUp * CAR_STEPDIST * 2.0f), CAR_LENGTH, collFaces, PLAYER_COLLISIONCHECK_COUNT, false);

    TVec3F carFront = mPosition + (mForward * CAR_LENGTH);

    bool pushed = false;
    for (int i = 0; i < cnt; i++){
        //Set ground face to whatever ground face is closest
        if (collFaces[i].face->isGround()){
            float yD;

            if (!collFaces[i].face->isXZInside(mPosition.xz())){
                continue;
            }

            if (mGroundFace == nullptr || (yD = TMath<f32>::abs(collFaces[i].face->calcYAt(mPosition.xz()) - mPosition.y())) < yDiff){
                mGroundFace = collFaces[i].face;
                yDiff = yD;
            }
            
            continue;
        }

        TVec3F closestPoint = collFaces[i].closestPoint;
        float distSqr = collFaces[i].distSqr;
        if (pushed){
            collFaces[i].face->calcClosestPt(mPosition + (mUp * CAR_STEPDIST * 2.0f), &closestPoint);
            distSqr = TVec3F::distSqr(mPosition + (mUp * CAR_STEPDIST * 2.0f), collFaces[i].closestPoint);
        }

        //Ignore face if its low enough to drive over or car has been pushed away from it by a previous face
        if (closestPoint.y() < mPosition.y() + CAR_STEPDIST || distSqr > CAR_LENGTH * CAR_LENGTH)
            continue;

        TVec3F nrm = collFaces[i].intersectionNrm;

        float energy = -mForward.dot(nrm);
        float friction = FRICTION_ENERGYLOSS;

        float steerDot = mRight.dot(nrm);

        if (energy > CAR_FRONT_THRESHOLD){
            //Turn car towards wall
            friction = 1.0f;

            mDriveDirection -= (int)(steerDot * steerDot * mSpeed * CAR_LENGTH + 0.99f);
        }
        else{
            //Turn car along wall
            mDriveDirection += (int)(energy * mSpeed + 0.99f) * (steerDot >= 0.0f ? 1 : -1);
            showFriction(collFaces[i].closestPoint,  energy * friction * mSpeed);
        }

        //Slow down from collision
        mSpeed -= TMath<f32>::clamp(energy * friction * mSpeed, 0.0f, mSpeed);
        showCollision(collFaces[i].closestPoint, energy * mSpeed);

        mVelocity += nrm * mVelocity.dot(nrm);

        //Push away from wall
        mPosition = collFaces[i].closestPoint + nrm * CAR_LENGTH - (mUp * CAR_STEPDIST * 2.0f);

        //Optimization so that we don't need to calculate closest point if the car hasn't moved
        pushed = true;
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

    if (!mOutOfControl){
        aButton = true;
    }

    TVec2F right = TVec2F(TSine::ssin(mDriveDirection + TSine::fromDeg(90)), TSine::scos(mDriveDirection + TSine::fromDeg(90)));

    TVec2F diff = mCurrentAITarget.xz() - mPosition.xz();
    diff.normalize();

    if (mOutOfControl){
        TVec3F temp = mVelocity;
        temp.normalize();
        diff = temp.xz();
    }

    float amtRight = -diff.dot(right);

    steer = TMath<f32>::clamp(amtRight * 4.0f, -1.0f, 1.0f);
    if (mSpeed < 0)
        steer = -steer;

    if (!inGrass && !mOutOfControl){
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

    mVelocity += mCollideEnergy;
    TVec3F velNrm = mVelocity;
    velNrm.y() = 0.0f;
    velNrm.normalize();
    mCollideEnergy = {0.0f, 0.0f, 0.0f};

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

    //Recover from being out of control if you are facing towards your velocity
    if (mOutOfControl){
        if (TMath<s16>::abs(mTurnRate) < TSine::fromDeg(CAR_RECOVERY_TURNTHRESHOLD)){
            if (mForward.dot(velNrm) >= CAR_RECOVERY_DIRECTIONTHRESHOLD){
                mOutOfControl = false;
            }
        }
        else if (mVelocity.getLength() < CAR_RECOVERY_SPEEDTHRESHOLD && !aButton)
            mOutOfControl = false;
    }
    else{
        /* go out of control if you are moving left or right too much */
        float oocSpeed = mVelocity.getLength();
        mOutOfControl = mVelocity.getLength() >= CAR_RECOVERY_SPEEDTHRESHOLD && mForward.dot(velNrm) < CAR_RECOVERY_DIRECTIONTHRESHOLD;
    }
    mOutOfControl |= (bButton && aButton);

    /* Convert out of control speed to vehicle speed */
    if (!mOutOfControl){
        float colF = mForward.dot(mVelocity);
        float colU = mUp.dot(mVelocity);
        mSpeed += colF;
        mYSpeed += colU;
        mVelocity -= (mForward * colF) + (mUp * colU);
    }

    /* Ground check */
    TVec3F pt = getPosition() + TVec3F(0.0f, CAR_STEPDIST, 0.0f);
    TVec3F front = pt + (mForward * CAR_LENGTH);
    if (mGroundFace == nullptr) //Only do check if collision from last frame could not find the ground
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

    switch (mState){
        // idle. c'mon let's get a move on...
        case playerstate_t::PLAYERSTATE_DRIVING:{
            float turn = steer;

            if (mOnGround && mGroundFace->surf == SURFACE_GRASS){        //Grass slowdown
                mVelocity *= CAR_RECOVERY_LR_ENERGYLOSS_GRASS;
                mSpeed *= 0.985f;
            }
            
            if (!aButton && !bButton){
                //Slow down when not pressing any button
                mSpeed *= mCarStats.getDrift(mSpeed);
            }
            else if (mOnGround && mOutOfControl){    
                if (mGroundFace->surf == SURFACE_GRASS){
                    //Slip on grass
                    mVelocity -= mForward * mVelocity.dot(mForward) * CAR_RECOVERY_FB_ENERGYLOSS_GRASS;
                    mVelocity -= mRight * mVelocity.dot(mRight) * CAR_RECOVERY_LR_ENERGYLOSS_GRASS;
                }
                else{
                    //Drift on road                           
                    float lr = mVelocity.dot(mRight) * CAR_RECOVERY_LR_ENERGYLOSS_ROAD;
                    float dot = mVelocity.dot(mForward);
                    mVelocity -= mForward * dot * CAR_RECOVERY_FB_ENERGYLOSS_ROAD;  //Slow down front/back
                    mVelocity -= mRight * lr;                                       //Slow down left/right
                }
            }
            else if (mOnGround){
                //Slow down when pressing a button
                mVelocity *= CAR_RECOVERY_LR_ENERGYLOSS_ROAD;
            }

            //Get real up direction
            if (mOnGround){
                mUp = mGroundFace->nrm.xyz();

                //Apply gravity
                mVelocity.y() -= PLAYER_GRAVITY * 50.0f * kInterval;
                mVelocity -= mUp * mUp.dot(mVelocity);
            }
            else
                mUp = TVec3F(0.0f, 1.0f, 0.0f);

            //Get real forward direction
            calculateForwardDirection();

            //acceleration and deceleration
            if (mOnGround){
                if (aButton) {
                    mSpeed += mCarStats.getAcceleration(mSpeed) * kInterval;
                }
                if (bButton && !mOutOfControl) {
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
                if (mOutOfControl){
                    mTurnRate *= 0.98f;
                    mTurnRate += turn * kInterval * TSine::fromDeg(120.0f);
                    mDriveDirection -= (s16)(mTurnRate * kInterval);
                }
                else{
                    mTurnRate = (s16)(turn * mSpeed * mCarStats.getTurn(mSpeed)) / kInterval;
                    mDriveDirection -= mTurnRate * kInterval;

                    f32 amtTurn = TMath<f32>::abs(turn);
                    f32 conversionLoss = (amtTurn * mCarStats.getTurnConversion(mSpeed)) + (1.0f - amtTurn);
                    mSpeed *= conversionLoss;
                }
            }

            //snap camera behind player
            bool cameraMode = (mSpeed > PLAYER_CAMERA_TRAIL_MINSPEED || mSpeed < -PLAYER_CAMERA_TRAIL_MINSPEED) || mOutOfControl;
            if (mCamera != nullptr){
                mCamera->setMode(cameraMode);
                if (cameraMode){
                    if (mOutOfControl){
                        mCamera->setPosition(mPosition - (velNrm * PLAYER_CAMERA_TRAIL_DISTANCE) + TVec3F(0.0f, PLAYER_CAMERA_TRAIL_HEIGHT, 0.0f));
                    }
                    else{
                        mCamera->setPosition(mPosition - (mForward * PLAYER_CAMERA_TRAIL_DISTANCE * (mSpeed >= 0 ? 1.0f : -1.0f)) + TVec3F(0.0f, PLAYER_CAMERA_TRAIL_HEIGHT, 0.0f));
                    }
                }
                mCameraTarget = mPosition;
            }
        }
        break;
    }

    if (mOutOfControl){
        mVelocity += mForward * mSpeed;
        mSpeed = 0.0f;
    }

    //Apply forward momentum
    mPosition += mForward * mSpeed * kInterval + (mVelocity * kInterval);

    //World collision (Also sets ground collision for the next frame for optimization purposes)
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

    TMtx44 rot;
    rot.rotateAxis(mUp, TSine::fromDeg(90));
    mRight = rot.mul(mForward);
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

void TPlayer::addCollision(
    const TVec3F& energy, float torque
) {
    mCollideEnergy += energy;
    float turnAmt = energy.getLength() * torque / 100.0f;
    mDriveDirection += (s16)turnAmt;
    mTurnRate += turnAmt;
}

//Called whenever the player crashes
void TPlayer::showCollision(const TVec3F& p, float energy){

}

//Called whenever the player scrapes a wall
void TPlayer::showFriction(const TVec3F& p, float energy){

}

// -------------------------------------------------------------------------- //

void TPlayer::onCollide(
    TCollider * const other
) {
    if (other->getCollideTag() == TAG_PLAYER){
        TPlayer* otherPlayer = (TPlayer*)other;
        TVec3F diff = mPosition - otherPlayer->getPosition();

        TMtx44 rot;
        rot.rotateAxis(mUp, TSine::fromDeg(90));
        
        //Get current object distance
        float dist = diff.getLength();
        diff.normalize();

        //Check how head on the collision was
        float colDot = mForward.dot(diff);
        float colDot2 = otherPlayer->mForward.dot(diff);

        //Check if collision is valid with an oval hitbox
        float aCD = TMath<f32>::abs(colDot);
        float aCD2 = TMath<f32>::abs(colDot2);
        float maxDist = (aCD * CAR_LENGTH) + ((1.0f - aCD) * CAR_WIDTH);
        maxDist += (aCD2 * CAR_LENGTH) + ((1.0f - aCD2) * CAR_WIDTH);
        
        if (dist > maxDist){
            return;
        }

        //Calculate how much to push this car
        dist = TMath<f32>::clamp(maxDist - dist, 0.0f, maxDist) / 2.0f;

        //Calculate the relative velocity of the collision
        TVec3F vel = otherPlayer->getVelocity() - getVelocity();
        float force = diff.dot(vel);

        if (force <= 0.0f)
            return;

        //Calculate energy transfer and torque
        float torque = rot.mul(diff).dot(vel);
        float energyTX = force / 2.0f;
        vel.normalize();
        addCollision(vel * energyTX, torque);

        //Apply a small speed decrease to simulate energy loss
        mSpeed -= mSpeed * 0.05 * diff.dot(vel);

        //Treat head-on and side collisions differently
        if (TMath<f32>::abs(colDot) > CAR_FRONT_THRESHOLD){
            //Don't slide to the side
            mPosition -= mForward * dist * (colDot > 0.0f ? -1.0f : 1.0f);
        }
        else{
            mPosition += diff * dist;
        }

        TVec3F colPos = mPosition + (diff / 2.0f);
        showCollision(colPos, vel.getLength());
    }
}