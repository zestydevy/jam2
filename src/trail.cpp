#include <ultra64.h>

#include "exception.hpp"
#include "trail.hpp"

void TTrail::init(TDynList2 * list, int capacity){
    mDynList = list;
    mCapacity = capacity;

    if (mCapacity > 16){
        TException::fault("trail too big!");
    }

    mVertices = new Vtx[32];
    for (int i = 1; i < mCapacity; i++){
        int idx = i * 2;
        mVertices[idx].v.ob[0] = 0;
        mVertices[idx].v.ob[1] = 0;
        mVertices[idx].v.ob[2] = 0;
        mVertices[idx].v.flag = mVertices[i - 2].v.flag;
        mVertices[idx].v.tc[0] = mVertices[i - 2].v.tc[0];
        mVertices[idx].v.tc[1] = i & 2 == 0 ? -16 : 1008;
        mVertices[idx].v.cn[0] = 0x00;
        mVertices[idx].v.cn[1] = 0x00;
        mVertices[idx].v.cn[2] = 0x00;
        mVertices[idx].v.cn[3] = 0xFF;

        idx++;
        mVertices[idx].v.ob[0] = 0;
        mVertices[idx].v.ob[1] = 0;
        mVertices[idx].v.ob[2] = 0;
        mVertices[idx].v.flag = mVertices[i - 2].v.flag;
        mVertices[idx].v.tc[0] = mVertices[i - 2].v.tc[0];
        mVertices[idx].v.tc[1] = i & 2 == 0 ? -16 : 1008;
        mVertices[idx].v.cn[0] = 0x00;
        mVertices[idx].v.cn[1] = 0x00;
        mVertices[idx].v.cn[2] = 0x00;
        mVertices[idx].v.cn[3] = 0xFF;
    }
}

void TTrail::extend(TVec3F const & position, TVec3F const & up){
    TVec3F dif = (position - mLastPosition);
    if (mEnd == 0){
        mLastPosition = position;
    }
    else if (dif.getSqrLength() > (Interval * Interval)){
        mLastPosition = position;
        mEnd++;
        if (mEnd - mStart >= mCapacity){
            mStart++;
        }
    }

    dif.normalize();
    TVec3F right = dif.cross(up);
    TVec3F pL = position - (right * Width);
    TVec3F pR = position + (right * Width);

    //Left vertex
    int idx = (mEnd * 2) % 32;
    mVertices[idx].v.ob[0] = (s16)pL.x();
    mVertices[idx].v.ob[1] = (s16)pL.y();
    mVertices[idx].v.ob[2] = (s16)pL.z();
    mVertices[idx].v.cn[3] = Color[0];
    mVertices[idx].v.cn[3] = Color[1];
    mVertices[idx].v.cn[3] = Color[2];
    mVertices[idx].v.cn[3] = Color[3];

    //Right vertex
    idx++;
    mVertices[idx].v.ob[0] = (s16)pR.x();
    mVertices[idx].v.ob[1] = (s16)pR.y();
    mVertices[idx].v.ob[2] = (s16)pR.z();
    mVertices[idx].v.cn[3] = Color[0];
    mVertices[idx].v.cn[3] = Color[1];
    mVertices[idx].v.cn[3] = Color[2];
    mVertices[idx].v.cn[3] = Color[3];

    if (mEnd == 0){
        mEnd++;
    }
}

void TTrail::update(){
    if (mFrameTimer++ % 2 != 0){
        return;
    }

    for (int i = mStart; i < mEnd; ++i){
        int l1 = i % mCapacity;
        int l2 = (i + 1) % mCapacity;
        int idx1 = l1 * 2;
        int idx2 = l2 * 2;

        if (mVertices[idx1].v.cn[3] != 0){
            mVertices[idx1].v.cn[3] -= 1;
            mVertices[idx1 + 1].v.cn[3] -= 1;
        }
        if (mVertices[idx2].v.cn[3] != 0){
            mVertices[idx2].v.cn[3] -= 1;
            mVertices[idx2 + 1].v.cn[3] -= 1;
        }
    }
}

void TTrail::clear(){
    mStart = mEnd = 0;
}

void TTrail::draw(){
    if (mEnd - mStart < 1){
        return;
    }

    gSPDisplayList(mDynList->pushDL(), mInitializer);

    gSPVertex(mDynList->pushDL(), mVertices, 32, 0);
    for (int i = mStart; i < mEnd; ++i){
        int l1 = i % mCapacity;
        int l2 = (i + 1) % mCapacity;

        int idx1 = l1 * 2;
        int idx2 = l2 * 2;

        gSP2Triangles(mDynList->pushDL(), idx1 + 1, idx1, idx2, 0, idx2 + 1, idx1 + 1, idx2, 0);
    }
}