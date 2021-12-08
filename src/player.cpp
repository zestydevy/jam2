#include <nusys.h>

#include "player.hpp"
#include "kartobject.hpp"
#include "math.hpp"
#include "animator.hpp"
#include "util.hpp"
#include "segment.h"
#include <nusys.h>
#include <nualstl_n.h>
#include "audio.hpp"
#include "collision.h"
#include "checkpoint.hpp"
#include "trail.hpp"

#include "../models/static/car/model_car.h"
#include "../data/ptcl_test.h"
#include "../data/tire.h"
#include "../models/static/shadow/shadow.h"

constexpr s32 kMaxWheels = 4;

const bool PLAYER_DOUBLESIDEDCOL = true;
const int PLAYER_COLLISIONCHECK_COUNT = 8;

//TODO: convert to variables
const float PLAYER_GRAVITY = 980.0f * kInterval;
const float PLAYER_BOUNCE_SCALE = 1.5f;
const float PLAYER_MIN_BOUNCE_SPEED = 50.0f;

const float PLAYER_BRAKE_MIN_SPEED = 20.0f;

const float PLAYER_CAMERA_TRAIL_MINSPEED = 20.0f;
const float PLAYER_CAMERA_TRAIL_DISTANCE = 200.0f;
const float PLAYER_CAMERA_TRAIL_HEIGHT = 150.0f;
const float PLAYER_CAMERA_TARGET_HEIGHT = 75.0f;

const float CAR_STEPDIST = 10.0f;
const float CAR_COLHEIGHT = 10.0f;
const float CAR_WIDTH = 30.0f;
const float CAR_LENGTH = 50.0f;

const float CAR_GRASS_ENERGYLOSS = 0.004f;

const float FRICTION_ENERGYLOSS = 0.01f;
const float CAR_FRONT_THRESHOLD = 0.75f;

const float CAR_RECOVERY_SPEEDTHRESHOLD = 100.0f;
const float CAR_RECOVERY_TURNTHRESHOLD = 0.4f;
const float CAR_RECOVERY_DIRECTIONTHRESHOLD = 0.98f;

const float CAR_RECOVERY_LR_ENERGYLOSS_GRASS = 0.005f;
const float CAR_RECOVERY_FB_ENERGYLOSS_GRASS = 0.004f;
const float CAR_RECOVERY_LR_ENERGYLOSS_ROAD = 0.06f;
const float CAR_RECOVERY_FB_ENERGYLOSS_ROAD = 0.002f;

// -------------------------------------------------------------------------- //

TPlayer * gPlayers[4] { nullptr, nullptr, nullptr, nullptr };

Gfx _mat_tire_tread_align_[] = {gsSPEndDisplayList()};
Gfx mat_tire_tread[] = {
	gsDPPipeSync(),
	gsDPSetRenderMode(G_RM_AA_ZB_XLU_DECAL, G_RM_AA_ZB_XLU_DECAL2),
    gsDPSetCombineLERP(0, 0, 0, 0, 0, 0, 0, SHADE, 0, 0, 0, 0, 0, 0, 0, SHADE),
    gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPClearGeometryMode(G_LIGHTING | G_SHADING_SMOOTH | G_CULL_BOTH),
    gsSPSetGeometryMode(G_SHADE),
    gsSPEndDisplayList(),
};

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

    initCollider(TAG_PLAYER, TAG_PLAYER | TAG_POKESTOP | TAG_PROJECTILE, TAG_PLAYER | TAG_PROJECTILE, 1);
    setCollideRadius(CAR_LENGTH);
    setCollideCenter(mPosition);

    mCameraTarget = mPosition;

    // initialize treads
    for (int i = 0; i < 4; i++){
        mTireTreads[i].init(mDynList, 16);
        mTireTreads[i].setTexture(mat_tire_tread);
    }

    //Car stats
    mCarStats.importStats(sTestCar);

    mGameState = gameplaystate_t::PLAYERGAMESTATE_NORMAL;

    mLastCheckpoint = 0;
    if (mPad == nullptr)
        aiCalcNextTarget();

    mRacerID = gCurrentRace->registerRacer();

    mTireConfig = reinterpret_cast<TTireConfig const &>(sTireConfig00);

    startDriving();
}

void TPlayer::setAnimation(int length, playeranim_t anim, bool loop, float timescale){
}

void TPlayer::setCharacter(ECharacter const character)
{
    TKartObject * charObj = new TKartObject(mDynList);
    charObj->init();
    charObj->setPosition({0.0f, 0.0f, 0.0f});
    charObj->setScale(TVec3F{1.0f,1.0f,1.0f});
    mPlayerMesh = charObj;

    switch(character)
    {
        case ECharacter::CHAR_PARROT:
            charObj->setMesh(player00_Cube1_008_mesh);
            charObj->setShadowMesh(player00_shadow_008_mesh);
            break;
        default:
            // just default to the parrot
            charObj->setMesh(player00_Cube1_008_mesh);
            charObj->setShadowMesh(player00_shadow_008_mesh);
            break;
    }
}

void TPlayer::initWheels()
{
    for (s32 i = 0; i < 4; ++i) {
        mWheels[i] = new TKartObject(mDynList);
        mWheels[i]->init();
        mWheels[i]->setParent(this);
        mWheels[i]->setMesh(wheel_Cube1_sep23_mesh);
        mWheels[i]->setShadowMesh(wheel_shadow_sep23_mesh);
    }
    
    mWheels[3]->setRotation(TVec3F{0.0f, TSine::toDeg(580.0f), 0.0f});
    mWheels[2]->setRotation(TVec3F{0.0f, TSine::toDeg(580.0f), 0.0f});
    
    TTireConfig::loadConfig(mWheels, const_cast<TTireConfig &>(mTireConfig));
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
    
    int cnt = TCollision::castRadius(mPosition + (mUp * CAR_STEPDIST * 2.0f), CAR_LENGTH, collFaces, PLAYER_COLLISIONCHECK_COUNT, true);

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

        mVelocity += nrm * -mVelocity.dot(nrm);

        //Push away from wall
        mPosition = collFaces[i].closestPoint + (nrm * CAR_LENGTH) - (mUp * CAR_STEPDIST * 2.0f);

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

void TPlayer::aiUpdate(bool& aButton, bool& bButton, f32& steer, const TVec3F & velNrm){
    bool inGrass = false;
    if (mGroundFace != nullptr && mGroundFace->surf == SURFACE_GRASS)
        inGrass = true;

    aButton = true;

    float vel = mSpeed;

    TVec2F forward = mForward.xz();
    forward.normalize();
    TVec2F right = mRight.xz();
    right.normalize();

    TVec2F diff = mCurrentAITarget.xz() - mPosition.xz();
    diff.normalize();

    bool drifting = false;

    if (mOutOfControl){
        vel = mVelocity.getLength();
        if (vel < 200.0f){
            diff = velNrm.xz();
            aButton = false;
        }
        else{
            drifting = true;
        }
    }

    float amtRight = -diff.dot(right);
    steer = TMath<f32>::clamp(amtRight * 4.0f, -1.0f, 1.0f);
    if (mSpeed < 0){
        steer = -steer;
    }
    if (mOutOfControl){
        f32 targetTurnRate = steer * 200.0f * 0.8f / kInterval;
        if (inGrass){
            aButton = false;
            targetTurnRate = 0.0f;
        }

        steer = (targetTurnRate - mTurnRate);
        steer = TMath<f32>::clamp(steer, -1.0f, 1.0f);
    }

    if (!inGrass && !mOutOfControl){
        if (drifting){
            aButton = true;
            bButton = false;
        }
        else if (mCarStats.getGear(mSpeed) > 2){
            //if (TMath<f32>::abs(amtRight) > 0.3f && mAIType == AI_GOOD){
            //    aButton = true;
            //    bButton = true;

                //Force turn towards closest point
            //    mCurrentAITarget = gCurrentRace->getClosestCheckpointPosition(mPosition, gCurrentRace->getNextCheckpoint(mLastCheckpoint));
            //}
        }
        else{
            if (TMath<f32>::abs(amtRight) > 0.7f && mSpeed > 10.0f){
                aButton = false;
            }
            if (TMath<f32>::abs(amtRight) > 0.90f){
                bButton = true;
            }
        }
    }
}

void TPlayer::aiCalcNextTarget(){
    switch (mAIType){
        case AI_BAD:
            mCurrentAITarget = gCurrentRace->getClosestCheckpointPosition(mPosition, gCurrentRace->getNextCheckpoint(mLastCheckpoint), 0);
            break;
        case AI_RANDOM:
            mCurrentAITarget = gCurrentRace->getRandomCheckpointPosition(gCurrentRace->getNextCheckpoint(mLastCheckpoint));
            break;
        case AI_GOOD:{
             mCurrentAITarget = gCurrentRace->getClosestCheckpointPosition(mPosition, gCurrentRace->getNextCheckpoint(mLastCheckpoint), 2);
            }
            break;
    }
}

void TPlayer::updateWheels() {
    if (mUsingLOD){
        return;
    }

    for (s32 i = 0; i < 4; ++i) {
        mWheels[i]->update();
    }
}

void TPlayer::update()
{
    TObject::update();

    float aiCheatSpeedModifier = 1.0f;
    float aiCheatSteerModifier = 1.0f;

    mVelocity += mCollideEnergy;

    TVec3F velNrm = mVelocity;
    velNrm.y() = 0.0f;
    velNrm.normalize();

    TVec3F fwdXZ = mForward;
    fwdXZ.y() = 0.0f;
    fwdXZ.normalize();

    mCollideEnergy = {0.0f, 0.0f, 0.0f};

    if (mPlayerMesh != nullptr && !mUsingLOD) {
        mPlayerMesh->update();
    }

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
        aiUpdate(aButton, bButton, steer, velNrm);
        aiCheatSpeedModifier += (gCurrentRace->getDistFromFront(mRacerID) * 0.05f) + 0.05f;
        aiCheatSteerModifier += (gCurrentRace->getDistFromFront(mRacerID) * 0.1f) + 0.1f;
    }

    //Recover from being out of control if you are facing towards your velocity
    if (mOutOfControl){
        if (TMath<s16>::abs(mTurnRate) < TSine::fromDeg(CAR_RECOVERY_TURNTHRESHOLD)){
            
            fwdXZ.normalize();

            if (fwdXZ.dot(velNrm) >= CAR_RECOVERY_DIRECTIONTHRESHOLD){
                mOutOfControl = false;
            }
        }
        else if (mVelocity.getLength() < CAR_RECOVERY_SPEEDTHRESHOLD && !aButton)
            mOutOfControl = false;
    }
    else{
        /* go out of control if you are moving left or right too much */
        float oocSpeed = mVelocity.getLength();
        mOutOfControl = mVelocity.getLength() >= CAR_RECOVERY_SPEEDTHRESHOLD && fwdXZ.dot(velNrm) < CAR_RECOVERY_DIRECTIONTHRESHOLD;
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

    bool inGrass = mGroundFace->surf == SURFACE_GRASS;

    switch (mState){
        // idle. c'mon let's get a move on...
        case playerstate_t::PLAYERSTATE_DRIVING:{
            float turn = steer;

            if (mOnGround){
                if (inGrass && !mOutOfControl){        //Grass slowdown
                    mSpeed -= mSpeed * CAR_GRASS_ENERGYLOSS;
                }
                
                if (mOutOfControl){    
                    if (inGrass){
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
                else if (!aButton && !bButton){
                    //Slow down when not pressing any button
                    mSpeed *= mCarStats.getDrift(mSpeed);
                }
                else{
                    //Slow down when pressing a button
                    mVelocity *= CAR_RECOVERY_LR_ENERGYLOSS_ROAD;
                }
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
                    mSpeed += mCarStats.getAcceleration(mSpeed) * kInterval * (bButton ? 0.333f : 1.0f) * aiCheatSpeedModifier;
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
            if (mOnGround)
            {
                if (mOutOfControl){
                    mTurnRate *= 0.99f;
                    mTurnRate += turn * kInterval * TSine::fromDeg(120.0f) * velNrm.dot(mForward);
                    mDriveDirection -= (s16)(mTurnRate * kInterval);
                }
                else if (turn != 0.0f) {
                    mTurnRate = (s16)(turn * mSpeed * mCarStats.getTurn(mSpeed) * aiCheatSteerModifier / kInterval);
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
                        TVec3F fwd = mForward;
                        fwd.y() = 0.0f;
                        fwd.normalize();
                        mCamera->setPosition(mPosition - (fwd * PLAYER_CAMERA_TRAIL_DISTANCE * (mSpeed >= 0 ? 1.0f : -1.0f)) + (mUp * PLAYER_CAMERA_TRAIL_HEIGHT));
                    }
                }
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

        if (mPlayerMesh != nullptr) {
            mPlayerMesh->setLeanAngle(steer * 5000.0f, kInterval * 4.0f);
            mWheels[1]->setDirectionLerp(-steer * 9000.0f, kInterval * 1.5f);
            mWheels[3]->setDirectionLerp(-steer * 9000.0f, kInterval * 1.5f);
        }
    }

    mCameraTarget = mPosition + (mUp * PLAYER_CAMERA_TARGET_HEIGHT);

    int nextcheckpoint = gCurrentRace->getNextCheckpoint(mLastCheckpoint);
    float checkPointDist = gCurrentRace->getDistance(mPosition, nextcheckpoint);
    float progress = gCurrentRace->updateRaceProgress(mRacerID, mPosition, mLastCheckpoint);
    
    if (checkPointDist < 50.0f){
        mLastCheckpoint = nextcheckpoint;

        if (mPad == nullptr)
            aiCalcNextTarget();
    }

    updateBlkMap();

    //update tire particles
    if (mTireEmitters[0] != nullptr){
        bool updateTires = mOnGround && (bButton || mOutOfControl);

        mTireEmitters[0]->setEnable(updateTires);
        mTireEmitters[1]->setEnable(updateTires);
        mTireEmitters[2]->setEnable(mOnGround && mOutOfControl);
        mTireEmitters[3]->setEnable(mOnGround && mOutOfControl);

        if (updateTires){
            f32 tireRate = getVelocity().getLength() / 100.0f * (1.0f - TMath<f32>::abs(mForward.dot(velNrm)));
            tireRate = TMath<f32>::clamp(tireRate, 0.1f, 1.0f);
            mTireEmitters[0]->setRateScale(aButton ? 1.0f : tireRate);
            mTireEmitters[1]->setRateScale(aButton ? 1.0f : tireRate);
            mTireEmitters[2]->setRateScale(tireRate);
            mTireEmitters[3]->setRateScale(tireRate);
        }
    }

    // update tires
    updateWheels();

    //update tire tread
    for (int i = 0; i < 4; i++){
        mTireTreads[i].update();
        if (!mOutOfControl){
            mTireTreads[i].Interval = TMath<f32>::max(mSpeed / 5.0f, 25.0f);
        }

        if (inGrass){
            mTireTreads[i].Color[0] = 90;
            mTireTreads[i].Color[1] = 55;
            mTireTreads[i].Color[2] = 44;
        }
        else{
            mTireTreads[i].Color[0] = 0;
            mTireTreads[i].Color[1] = 0;
            mTireTreads[i].Color[2] = 0;
        }
    }

    mTireTreads[0].Color[3] = mInCamera && mOutOfControl ? 128 : 0;
    mTireTreads[1].Color[3] = mInCamera && mOutOfControl ? 128 : 0;
    mTireTreads[2].Color[3] = mInCamera && mOutOfControl || bButton ? 128 : 0;
    mTireTreads[3].Color[3] = mInCamera && mOutOfControl || bButton ? 128 : 0;

    if ( mInCamera ){
        mTireTreads[0].extend(mPosition + (mRight * mTireConfig.position[0].x() * 100.0f * mScale.x()) + (mForward * mTireConfig.position[0].z() * 100.0f * mScale.x()), mUp, mUsingLOD);
        mTireTreads[1].extend(mPosition + (mRight * mTireConfig.position[1].x() * 100.0f * mScale.x()) + (mForward * mTireConfig.position[1].z() * 100.0f * mScale.x()), mUp, mUsingLOD);
        mTireTreads[2].extend(mPosition + (mRight * mTireConfig.position[2].x() * 100.0f * mScale.x()) + (mForward * mTireConfig.position[2].z() * 100.0f * mScale.x()), mUp, mUsingLOD);
        mTireTreads[3].extend(mPosition + (mRight * mTireConfig.position[3].x() * 100.0f * mScale.x()) + (mForward * mTireConfig.position[3].z() * 100.0f * mScale.x()), mUp, mUsingLOD);
    }
}

void TPlayer::calculateForwardDirection(){
    TVec3F forward = TVec3F(TSine::ssin(mDriveDirection), 0.0f, TSine::scos(mDriveDirection));
    TVec3F proj = forward.dot(mUp) * mUp;
    mForward = forward - proj;

    mRight = mForward.cross(mUp) * -1.0f;
    mRight.normalize();
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
    updateMtx();
    
    if (!mInCamera)
        return;

    if (mMtxNeedsUpdate)
        updateMtx();

    bool lod = mLODMesh != nullptr && !TCamera::checkDistance(mPosition, mLODDistanceSquared);

    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFMtx),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);
        
    if (mMesh != nullptr) {
        if (lod){
            gSPDisplayList(mDynList->pushDL(), mLODMesh);
        }
        else{
            gSPDisplayList(mDynList->pushDL(), mMesh);
        }
    }

    mPlayerMesh->draw();

    for (s32 i = 0; i < 4; ++i) {
        mWheels[i]->draw();
    }

    gSPPopMatrix(mDynList->pushDL(), G_MTX_MODELVIEW);
}

void TPlayer::drawShadow()
{
    if (mGroundFace != nullptr) {
        mShadow->draw();
        mShadow->drawChild(mPlayerMesh);
        for (int i = 0; i < 4; i++){
            mShadow->drawChild(mWheels[i]);
        }
    }
}

void TPlayer::drawTransparent()
{
    for (int i = 0; i < 4; i++){
        mTireTreads[i].draw();
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

void TPlayer::initParticles(TArray<TEmitter *> & emitList){
    mSmokeEmitter = new TEmitter(mPosition, reinterpret_cast<TEmitConfig const &>(sPtclSmoke), mDynList);
    mSmokeEmitter->attach(this, {-CAR_WIDTH / 2.0f, 6.0f, -CAR_LENGTH + 5.0f});
    mSmokeEmitter->setEnable(true);
    emitList.push(mSmokeEmitter);
    for (int i = 0; i < 4; i++){
        mTireEmitters[i] = new TEmitter(mPosition, reinterpret_cast<TEmitConfig const &>(sPtclTire), mDynList);
        mTireEmitters[i]->setEnable(false);
        mTireEmitters[i]->attach(this, mTireConfig.position[i] * mScale.x());
        emitList.push(mTireEmitters[i]);
    }

    mCollisionEmitter = new TEmitter(mPosition, reinterpret_cast<TEmitConfig const &>(sPtclSmoke), mDynList);
    mCollisionEmitter->setEnable(false);
    emitList.push(mCollisionEmitter);
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
        mSpeed -= mSpeed * 0.02 * diff.dot(vel) * mForward.dot(diff);

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