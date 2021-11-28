#pragma once

#include <nusys.h>

#include "scene.hpp"
#include "kartobject.hpp"

class TSelectKartScene final
    : public TScene
{
    public:

    TSelectKartScene(char const * name, TDynList2 * list)
        : TScene(name, list) {};

    ~TSelectKartScene() = default;

    virtual void init() override;
    virtual void update() override;
    virtual void draw() override;
    virtual void draw2D() override;
    virtual TScene * exit() override;

    private:

    s32 mPlayerCount{1};

    TObject * mFloors[4]{};
    TObject * mPlayers[4]{};
    TObject * mKarts[4]{};
    TKartObject * mWheels[4][4]{};
    TPad * mPads[4]{};
    TCamera * mCamera{nullptr};

    TSprite mChPlayerSpr;
    TSprite mArrowL;
    TSprite mArrowR;
    s16 mChooseSin{50};
    TTimer mChooseTimer{};

    TVec3F mViewOrigin{};

    f32 mTimer{0};
};

