#pragma once
#include <ultra64.h>

#include "math.hpp"
#include "array.hpp"
#include "util.hpp"
#include "dynlist.hpp"
#include "linklist.hpp"

class TParticle;

constexpr s32 kMaxCallbacks = 16;

// -------------------------------------------------------------------------- //

enum EEmitType : s8
{
    EMIT_2D = 0b0000'0001,
    EMIT_3D = 0b0000'0010,
    EMIT_BILLBOARD = 0b0000'0100,
    EMIT_COLLISION = 0b0000'1000,
    EMIT_LOCAL = 0b0001'0000,
    EMIT_WORLD = 0b0010'0000,
};

// -------------------------------------------------------------------------- //

enum EEmitShape : s8
{
    SHAPE_SPHERE,
    SHAPE_CONE,
    SHAPE_MODEL,    // 'tis but a dream
    SHAPE_PLANE,
};

// -------------------------------------------------------------------------- //

struct TEmitConfig
{
    EEmitType type;             // emission type
    EEmitShape shape;           // shape of emission
    float radius;               // radius of emission
    bool loop;                  // repeat emission after duration?
    f32 lifeSpan;               // emission lifetime
    f32 rate;                   // particles emitted per second
    TVec3F scale;               // base scale for particle
    TVec3F scaleOverTime;       // scale for particle at end of duration
    TVec3F velocity;            // base velocity range for particles
    TVec3F acceleration;        // base acceleration range for particles
    TVec3F force;               // force of particles
    TVec3S color;               // color of particles
    TVec3S colorOverTime;       // color for particles at end of duration
    u8 alpha;                   // alpha color for particles
    u8 alphaOverTime;           // alpha color at end of duration
    Gfx * mesh2d;               // display list of particles if type EMIT_2D
    Gfx * mesh3d;               // display list of particles if type EMIT_3D
};

// -------------------------------------------------------------------------- //

class TEmitter
{
    public:

    TEmitter() = default;
    TEmitter(TVec3<f32> const & position, TEmitConfig const & config, TDynList2 * dl);
    TEmitter(TVec3<f32> const & position, EEmitType const type);
    ~TEmitter() = delete;

    void setGlbDl(TDynList2 * dl){mDl = dl;}
    void attachCallback(void(*)());
    void emit();
    void draw();
    void destroy();

    private:

    EEmitType mType{EMIT_2D};
    TVec3F mPosition{};
    TEmitConfig * mConfig{nullptr};
    TArray<TParticle *> mPtclList;
    TArray<void(*)()> mCallbacks;
    TDynList2 * mDl{nullptr};
    TTimer mRateTimer;
    f32 rate{0.0f};
};

// -------------------------------------------------------------------------- //