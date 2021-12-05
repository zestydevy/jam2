#pragma once

#include <nusys.h>

#include "scene.hpp"
#include "kartobject.hpp"

struct TSelectModelDef
{
    Gfx * head;
    Gfx * body;
    Gfx * tire;
};

enum EKartMenu : s32
{
    KMENU_IN = 0,
    KMENU_SELECTING,
};

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
    virtual void draw2DBG() override;
    virtual TScene * exit() override;

    private:

    EKartMenu mMenuState{KMENU_IN};
    s32 mPlayerCount{1};

    TObject * mFloors[4]{};
    TObject * mPlayers[4]{};
    TObject * mKarts[4]{};
    TKartObject * mWheels[4][4]{};
    TPad * mPads[4]{};
    TCamera * mCamera{nullptr};

    TSprite mFade;
    TSprite mBg;
    TSprite mChPlayerSpr;
    TSprite mArrowL;
    TSprite mArrowR;
    TSprite mAva1;
    TSprite mStatsBg;
    TSprite mStats[3];
    s16 mChooseSin{50};
    TTimer mTimers1[4];
    TTimer mTimers2[4];
    TTimer mArrowTimers[4];

    TVec3F mViewOrigin{};

    f32 mTimer{0};
};

