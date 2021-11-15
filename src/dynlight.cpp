#include "dynlight.hpp"    

bool TDynLight::checkInRadius(TVec3F const & position){
    return (position - mPosition).getSqrLength() <= mRadiusSqr;
}

bool TDynLight::lerpBetween(TDynLightInfo const & envLight, TVec3F const & objPosition, TDynLightInfo * lightOut){
    u8 envColor[3] = {envLight.color[0], envLight.color[1], envLight.color[2]};
    TVec3F envLightPoint = envLight.point;

    TVec3F relPos = (mPosition - objPosition);
    float sqrLen = relPos.getSqrLength();
    if (sqrLen > mRadiusSqr){
        lightOut->color[0] = envColor[0];
        lightOut->color[1] = envColor[1];
        lightOut->color[2] = envColor[2];
        lightOut->point = envLightPoint;
        return false;
    }

    float len = TMath<f32>::sqrt(sqrLen);

    lightOut->point = relPos;

    if (len <= mTransitionPoint){
        lightOut->color[0] = mR;
        lightOut->color[1] = mG;
        lightOut->color[2] = mB;
        return true;
    }

    float t = (mRadius - len) / (mRadius - mTransitionPoint);
    float ti = 1.0f - t;

    lightOut->color[0] = (u8)((ti * mR) + (t * envColor[0]));
    lightOut->color[1] = (u8)((ti * mG) + (t * envColor[1]));
    lightOut->color[2] = (u8)((ti * mB) + (t * envColor[2]));
    lightOut->point.lerp(envLightPoint, ti);
    return true;
}