#pragma once

#include <nusys.h>

#include "math.hpp"

typedef struct t_dynlightinfo{
    u8 color[3];
    TVec3F point;
} TDynLightInfo;

class TDynLight
{
    public:
    TDynLight(){
    }

    ~TDynLight() = default;

    void setPosition(TVec3F const & position){
        mPosition = position;
    }

    void setColor(u8 r, u8 g, u8 b){
        mR = r;
        mG = g;
        mB = b;
    }
    void setColor(u8 * color){
        mR = color[0];
        mG = color[1];
        mB = color[2];
    }

    void setRadius(float r, float transitionSize = 250.0f){
        mRadius = r;
        mRadiusSqr = r * r;
        mTransitionPoint = mRadius - transitionSize;
    }

    bool checkInRadius(TVec3F const & position);
    bool lerpBetween(TDynLightInfo const & envLight, TVec3F const & objPosition, TDynLightInfo * lightOut);

    private:
    TVec3F mPosition;
    u8 mR,mG,mB;
    float mRadius, mRadiusSqr;
    float mTransitionPoint;
};