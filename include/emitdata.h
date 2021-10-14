#pragma once
#include <ultra64.h>

enum EPtclType
{
    EMIT2D = 0b00000001,
    EMIT3D = 0b00000010,
    EMITBILLBOARD = 0b00000100,
    EMITCOLLISION = 0b00001000,
    EMITLOCAL = 0b00010000,
    EMITWORLD = 0b00100000,
};

enum EPtclShape
{
    SHAPESPHERE,
    SHAPECONE,
    SHAPEMODEL,    // 'tis but a dream
    SHAPEPLANE,
};

typedef struct
{
    u8 type;             // emission type
    u8 shape;           // shape of emission
    float radius;       // radius of emission
    u8 loop;                  // repeat emission after duration?
    f32 lifeSpan;               // emission lifetime
    f32 rate;                   // particles emitted per second
    float scale[3];               // base scale for particle
    float scaleOverTime[3];       // scale for particle at end of duration
    float velocity[3];            // base velocity range for particles
    float acceleration[3];        // base acceleration range for particles
    float force[3];               // force of particles
    s16 color[3];               // color of particles
    s16 colorOverTime[3];       // color for particles at end of duration
    u8 alpha;                   // alpha
    u8 alphaOverTime;           // alpha at end of duration
    Gfx * mesh2d;               // display list of particles if type EMIT_2D
    Gfx * mesh3d;               // display list of particles if type EMIT_3D
} TEmitData;