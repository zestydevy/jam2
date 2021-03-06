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
#include "emitter.hpp"

class TKartObject : public TObject
{
    public:

    TKartObject(TDynList2 * dl) :
        TObject { dl }
    {
    }

    virtual ~TKartObject() = default;

    virtual void updateMtx() override;

    virtual void init() override;
    virtual void update() override;
    virtual void draw() override;

    void rotateX(s16 rate){mRotation.x() += rate; mMtxNeedsUpdate = true;}
    void rotateY(s16 rate){mRotation.y() += rate; mMtxNeedsUpdate = true;}
    void rotateZ(s16 rate){mRotation.z() += rate; mMtxNeedsUpdate = true;}

    void setDirection(s16 const direction){mTurnDirection = direction; mMtxNeedsUpdate = true; }
    void setDirectionLerp(s16 const direction, f32 const multiplier){mTurnDirection = TMath<s16>::lerp(mTurnDirection, direction, multiplier); mMtxNeedsUpdate = true; }
    void setLeanAngle(s16 const angle, f32 const multiplier){ mLeanAngle = TMath<s16>::lerp(mLeanAngle, angle, multiplier); mMtxNeedsUpdate = true; }

    void setSuper(TObject * parent){mSuperParent = parent;}

    Mtx const & getTransformationMtx() { return mFMtx; }
    Gfx * getShadowMesh(){return mShadowMesh;}
    void setShadowMesh(Gfx * mesh) {mShadowMesh = mesh;}

    protected:
    Gfx * mShadowMesh;
    TObject * mSuperParent{nullptr};

    s16 mLeanAngle{0};
    s16 mTurnDirection{0};
};