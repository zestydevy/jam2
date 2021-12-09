#pragma once

#include <ultra64.h>

#include "scene.hpp"

class TIntroScene final
    : public TScene
{
    public:

    TIntroScene(char const * name, TDynList2 * list)
        : TScene(name, list) {};

    virtual void init() override;
    virtual void update() override;
    virtual void draw() override;
    virtual void draw2D() override;
    virtual void draw2DBG() override;
    virtual TScene * exit() override;

    private:

    TVec3F mOrigin{};
    TCamera * mCamera{nullptr};
    TPad * mPad{nullptr};
    TObject * mLogo{nullptr};
};