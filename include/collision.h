#ifndef __collision_h__
#define __collision_h__
#ifdef _cplusplus
extern "C"{
#endif

// Surface Types
#define SURFACE_DEFAULT                    0x00000000 // Environment default
#define SURFACE_GRASS                      0x00000001 // Environment default
#define SURFACE_WATER                      0x00000002
#define SURFACE_BORDER                     0x00000003

typedef struct t_collisionface{
    float vtx1[3];
    float vtx2[3];
    float vtx3[3];

    float nrm[3];

    u32 surf;

    float d;
} CollisionFace;

#ifdef _cplusplus
}
#endif
#endif