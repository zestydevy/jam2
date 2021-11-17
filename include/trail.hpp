#pragma once

#include <nusys.h>

#include "math.hpp"
#include "dynlist.hpp"

class TTrail
{
    public:
    TTrail(){}

    ~TTrail() = default;

    void init(TDynList2 * list, int capacity);
    void setTexture(Gfx * initializer){mInitializer = initializer;};

    void update();
    void extend(TVec3F const & position, TVec3F const & up, bool lod = false);
    void clear();

    void draw();

    float Width{5.0f};
    float Interval{100.0f};
    u8 Color[4];

    private:
    s16 mCapacity{0};
    s16 mStart{0};
    s16 mEnd{0};

    TDynList2 * mDynList{nullptr};
    Gfx * mInitializer{nullptr};

    s16 mFrameTimer{0};

    TVec3F mLastPosition{0.0f, 0.0f, 0.0f};
    Vtx * mVertices;
};