#pragma once
#include <ultra64.h>

#include "emitter.hpp"
#include "math.hpp"
#include "staticobj.hpp"
#include "util.hpp"

// -------------------------------------------------------------------------- //

class TParticle : public TObject
{
    public:
    
    TParticle(TDynList2 * dl, TEmitConfig const & config) :
        TObject { dl }
    {
        setConfig(config);
    }

    virtual ~TParticle() = default;

    virtual void updateMtx() override;

    virtual void init() override;
    virtual void update() override;
    virtual void draw() override;

    bool isExpired() {return mIsExpired;}
    void setDirection(TVec3F const & direction) {mDirection = direction;}

    private:

    void setConfig(TEmitConfig const &);

    TEmitConfig * mConfig{nullptr};
    float mLifeSpan{0.0f};
    TVec3F mVelocity{};
    TVec3F mAcceleration{};
    TVec3F mDirection{};
    TVec3<u8> mInitColor{};
    u8 mAlpha{0};
    TTimer mLifeTimer;
    f32 mFrame{0};
    bool mIsExpired{false};

};

// -------------------------------------------------------------------------- //