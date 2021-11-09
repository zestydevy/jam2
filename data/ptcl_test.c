#include <ultra64.h>

#include "emitdata.h"
#include "../models/static/ptcl00/sprite_ptcl00.h"


TEmitData const sTestPtcl00 =
{
    EMIT2D | EMITBILLBOARD,             // type
    SHAPESPHERE,                        // shape
    20.0f,                               // radius
    TRUE,                               // loop
    4.0f,                               // lifespan
    0.05f,                               // rate
    {2.0f, 2.0f, 2.0f},                 // scale
    {0.0f, 0.0f, 0.0f},                 // scale over time
    {0.0f, 0.0f, 0.0f},                 // velocity
    {0.0f, 0.02f, 0.0f},               // acceleration
    {0.0f, -0.80f, 0.0f},                // force
    {255, 255, 255},                    // color
    {255, 255, 255},                    // color over time
    255,                                // alpha
    0,                                  // alpha over time
    ptcl00_Plane_mesh,                  // 2D mesh
    NULL                                // 3D mesh
};

TEmitData const sPtclSmoke =
{
    EMIT2D | EMITBILLBOARD,             // type
    SHAPESPHERE,                        // shape
    20.0f,                               // radius
    TRUE,                               // loop
    2.0f,                               // lifespan
    0.02f,                               // rate
    {1.0f, 1.0f, 1.0f},                 // scale
    {3.0f, 3.0f, 3.0f},                 // scale over time
    {0.0f, 0.0f, 0.0f},                 // velocity
    {0.0f, 0.36f, 0.0f},               // acceleration
    {0.0f, 0.00f, 0.0f},                // force
    {108, 105, 105},                    // color
    {255, 255, 255},                    // color over time
    255,                                // alpha
    0,                                  // alpha over time
    ptcl_smoke_Plane_mesh,              // 2D mesh
    NULL                                // 3D mesh
};