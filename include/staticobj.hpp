#pragma once

#include <nusys.h>

#include "math.hpp"
#include "dynlist.hpp"

#include "../scene/object_info.h"

// -------------------------------------------------------------------------- //

enum EObjType : s16
{
    PLAYERSTART = -1,
    NONE = 0,
    DEBUG_CUBE,
    BALLOON,
    LUNCHTABLE,
    CHAIR,
    BASKET,
    BEER,
    NOODLE,
    MELON,
    APPLE,
    BALLOON_DEFLATED,
    BEEHIVE,
    BILLS,
    CARD,
    FLOWER,
    NECKLACE,
    RING,
    SOCCER,
    STICK,
    TABLE,
    CAT,
    CHICKEN,
    CRITIC,
    AVGN,
    WOMAN,
    CHILD,
    LOGO,
    STORE_E,
    STORE_B,
    STEPPINGSTONE,
    FENCE,
    TRUNK,
    LEAVES,
    BRANCH,
    ROOTS,
    MAILBOX,
    NEST,
    DEADTREE,
    BALDHOOKTREE,
    BALDTREE,
    TIRE,
    TOASTER,
    PLANK,
    TRASHCAN,
    TRASHCAN2,
    POT,
    BUSH,
    LAMP,
    CAR,
    CHECKPOINT,
    DYNLIGHT,
    POKESTOP,
    INVALID
};

enum EDrawLayer : s16
{
    PREWINDOW,
    POSTWINDOW,
    LAYERNONE
};

// -------------------------------------------------------------------------- //

class TObject
{
    public:

    TObject(TDynList2 * list)
        : mDynList{list} {}
    virtual ~TObject() = default;

    void setPosition(TVec3<f32> const & pos);
    void setRotation(TVec3<f32> const & rot);
    void setScale(TVec3<f32> const & scale);
    inline void setMesh(Gfx * mesh, Gfx * initializer = nullptr, Gfx * lod = nullptr) { mMesh = mesh; mInitializer = initializer; mLODMesh = lod; }
    void setParent(TObject * obj) {mParent = obj;}
    const Gfx * getGraphicsInitializer(){ return mInitializer; };

    TVec3<f32> const & getPosition() {return mPosition;}
    TVec3<s16> const & getRotation() {return mRotation;}
    TVec3<f32> const & getScale() {return mScale;}
    bool getInCamera() {return mInCamera;}
    bool getUsingDistantModel() {return mUsingLOD;}

    const Mtx & getDrawMtx() { return mFMtx; }
    const Mtx & getRotMtx() { return mFRotMtx; }

    const TMtx44 & getRotationMatrix() { return mRotMtx; }

    void rotateX(s16 rate){mRotation.x() += rate; mMtxNeedsUpdate = true;}
    void rotateY(s16 rate){mRotation.y() += rate; mMtxNeedsUpdate = true;}
    void rotateZ(s16 rate){mRotation.z() += rate; mMtxNeedsUpdate = true;}

    virtual void updateMtx();

    virtual void init();
    virtual void update();
    virtual void draw();
    virtual void drawRing();

    virtual void increaseRadius(float threshold);

    static Gfx * getMeshGfx(EObjType type);
    static const TObjectData & getNestObjectInfo(EObjType type);

    bool mAlwaysDraw{false};

    EDrawLayer mDrawLayer {EDrawLayer::PREWINDOW};

    protected:
    bool mInCamera{false};
    bool mMtxNeedsUpdate{true};
    bool mUsingLOD {false};

    TVec3<f32> mPosition{};
    TVec3<s16> mRotation{};
    TVec3<f32> mScale{};
    
    TMtx44 mRotMtx{};

    // 1 matrix push call per object.
    Mtx mFMtx{};
    Mtx mFRotMtx{}; //used by shadows and can be used for other math
    
    Gfx * mInitializer{nullptr};
    Gfx * mMesh{nullptr};
    Gfx * mLODMesh{nullptr};
    TDynList2 * mDynList{nullptr};

    float mLODDistanceSquared{1000000.0f};
    float mDrawDistanceSquared{100000000.0f};

    TObject * mParent {nullptr};
};

// -------------------------------------------------------------------------- //

class TKartObject;

class TShadow : public TObject
{
    public:

    TShadow(TDynList2 * dl) :
        TObject { dl }
    {
    }

    virtual ~TShadow() = default;

    virtual void updateMtx() override;

    virtual void init() override;
    virtual void update() override;
    virtual void draw() override;
    virtual void drawChild(TKartObject * child);

    void setParent(TObject * obj) {mParent = obj;}
    void setRelativeLightSource(TVec3F const & pos){ mRelativeLightSource = pos; mShadowNeedsUpdate = true; }

    protected:
    bool mShadowNeedsUpdate {false};
    bool mShadowVisible {false};
    bool mShadowUsingLOD {false};
    TVec3F mRelativeLightSource;

    Mtx mFScaleMtx1{};
    Mtx mFScaleMtx2{};

    Mtx mFAngleMtx{};

    TObject * mParent {nullptr};
};

// -------------------------------------------------------------------------- //