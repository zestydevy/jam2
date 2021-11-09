#pragma once

#include <nusys.h>

#include "animator.hpp"
#include "camera.hpp"
#include "collider.hpp"
#include "collision.hpp"
#include "dynlist.hpp"
#include "math.hpp"
#include "pad.hpp"
#include "staticobj.hpp"

#include "carstats.hpp"

enum playerstate_t : u16 {
    PLAYERSTATE_STUNNED,    //Falling
    PLAYERSTATE_DRIVING,       //Driving
};

enum gameplaystate_t : u16 {
    PLAYERGAMESTATE_NORMAL,
    PLAYERGAMESTATE_ITEM,
    PLAYERGAMESTATE_HACK,
    PLAYERGAMESTATE_TRANSITION
};

enum playeranim_t : u16 {
    ANIM_IDLE,
    ANIM_WALK,
    ANIM_RUN,
    ANIM_COUNT
};

enum playeraistate_t : u16 {
    AISTATE_DRIVETOTARGET,
    AISTATE_RETURNTOTRACK,
    AISTATE_FINISH
};

enum playeraitype_t : u16 {
    AI_BAD,
    AI_RANDOM,
    AI_GOOD
};

// -------------------------------------------------------------------------- //

class TPlayer;

extern TPlayer * gPlayers[4];

// -------------------------------------------------------------------------- //

class TPlayer :
    public TObject,
    public TSphereCollider
{

    public:

    TPlayer(TDynList2 * dl) :
        TObject { dl }
    {
    }

    virtual ~TPlayer() = default;

    void setPad(TPad * pad) {
        mPad = pad;
    }

    void setCamera(TCamera * camera) {
        mCamera = camera;
        mCamera->setTarget(&mCameraTarget);
        resetCamera();
    }

    void setDriveDirection(s16 rotation){
        mDriveDirection = rotation;
    }

    TCollFace const * getGroundFace() const {
        return mGroundFace;
    }

    TVec3F getVelocity() {
        return mDirection * mSpeed;
    }

    void setAIType(playeraitype_t ai) { mAIType = ai; }

    void snapToGround();

    virtual void updateMtx() override;

    virtual void init() override;
    virtual void update() override;
    virtual void draw() override;
    virtual void drawShadow();

    void resetCamera();

    void aiUpdate(bool& aButton, bool& bButton, f32& steer);
    void aiCalcNextTarget();

    void setAnimation(int length, playeranim_t anim, bool loop = true, float timescale = 0.25f);

    inline void setShadowMesh(Gfx * mesh, Gfx * initializer = nullptr) { mShadow->setMesh(mesh, initializer); }

    protected:
    void startDriving();
    void startCrashing();
    void checkLateralCollision();
    void checkMeshCollision(const TCollFace * face, float radius);

    TAnimator * mAnim{nullptr};
    TPad * mPad{nullptr};

    TShadow * mShadow{nullptr};

    TCamera * mCamera {nullptr};
    TVec3<f32> mCameraTarget{};

    f32 mSpeed{0.0f};
    f32 mYSpeed{0.0f};
    TVec3<f32> mDirection{};
    TVec3F mCenter{};

    s16 mDriveDirection{0};
    TVec3F mForward{0.0f, 0.0f, 1.0f};
    TVec3F mUp{0.0f,1.0f,0.0f};

    s16 mLastCheckpoint;
    TCarStats mCarStats{TCarStats()};

    bool mOnGround {false};
    TCollFace const * mGroundFace { nullptr };
    const TCollFace * mClosestFace;

    /* AI */
    playeraitype_t mAIType { AI_RANDOM };
    playeraistate_t mAIState { AISTATE_DRIVETOTARGET };
    TVec3F mCurrentAITarget {0.0f, 0.0f, 0.0f};

    playerstate_t mState{playerstate_t::PLAYERSTATE_DRIVING};
    gameplaystate_t mGameState{gameplaystate_t::PLAYERGAMESTATE_NORMAL};

    virtual void onCollide(TCollider *) override;
};

// -------------------------------------------------------------------------- //