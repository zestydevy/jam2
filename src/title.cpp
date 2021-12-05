#include <nusys.h>

#include "title.hpp"
#include "scene.hpp"
#include "credits.hpp"
#include "util.hpp"
#include "game.hpp"
#include "app.hpp"
#include "pad.hpp"
#include "audio.hpp"

#include "segment.h"

#include "../models/ovl/sprites/sp_bg0.h"
#include "../models/ovl/sprites/sp_bg1.h"
#include "../models/ovl/sprites/sp_bg2.h"
#include "../models/ovl/sprites/sp_bg3.h"
#include "../models/ovl/sprites/sp_bg4.h"

extern "C" void bzero(void *, int);

static TTimer * sCrashTimer{nullptr};
static TTimer * sScrollTimer{nullptr};
static TTimer * sExitTimer{nullptr};
static bool sIsCredits{false};
static bool sIsLoop{false};
static EButton const sButtonCache[] = {UP, UP, DOWN, DOWN, LEFT, RIGHT, LEFT, RIGHT, B, A};

// -------------------------------------------------------------------------- //

void TTitleScene::init()
{
    mStatus = ESceneState::RUNNING;

    // turn on screen
    //nuGfxDisplayOn();

    auto game = TGame::getInstance();
    game->setClearColor(255,255,255,1);

    mMenuPad = new TPad(0);
    
    mBgStart = new TSprite;
    mBgLayer1 = new TSprite;
    mBgLayer2 = new TSprite;
    mBgLayer2Dup = new TSprite;
    mBgLayer3 = new TSprite;
    mBgLayer4 = new TSprite;

    mStartTimer = new TTimer;
    sCrashTimer = new TTimer;
    sScrollTimer = new TTimer;
    sExitTimer = new TTimer;
    mStartTimer->start(1);
    sExitTimer->start(110.0F);

    mCloud1X = 360 / 2;
    mCloud2X = -250 * -2;

    TAudio::playMusic(EBgm::BGM_INTRO);
    TAudio::fadeMusic(1.0F);

}

// -------------------------------------------------------------------------- //

void TTitleScene::update()
{
    mMenuPad->read();
    
    scrollCloudLayer();
    handleStart();
    waitForEnd();

    // can i press start now?
    if (mCanStart) {
        handleCheat();
        if (mMenuPad->isPressed(EButton::START)) {
            
            TAudio::fadeMusic(0.0f, 4.0f);
            auto handle = MusStartEffect(ESfxType::SFX_SELECT);
            MusHandleSetVolume(handle, 50);

            mStartState = 3;
            mStartAlpha = 0;
            mCanStart = false;
        }
    }

    TAudio::update();
}

// -------------------------------------------------------------------------- //

void TTitleScene::draw()
{
    // ...
}

// -------------------------------------------------------------------------- //

void TTitleScene::draw2D()
{   
    if (mStartState >= 4) return;
}

// -------------------------------------------------------------------------- //

void TTitleScene::draw2DBG()
{   
}

// -------------------------------------------------------------------------- //

TScene * TTitleScene::exit()
{
    delete sCrashTimer;
    delete sScrollTimer;
    delete sExitTimer;

    if (sIsLoop) {
        sIsLoop = false;
        sIsCredits = false;
        return new TLogoScene { nullptr, mDynList };
    } else {
        return new TCreditsScene { "credits", mDynList, sIsCredits };
    }
}

// -------------------------------------------------------------------------- //

void TTitleScene::scrollCloudLayer()
{
    if (!sScrollTimer->update()) {
        ++mCloud1X;
        ++mCloud2X;
    } else {
        sScrollTimer->start(0.04F);
    }

    if (mCloud1X >= 480) {
        mCloud1X = -250;
    }

    if (mCloud2X >= 480) {
        mCloud2X = -250;
    }
}

// -------------------------------------------------------------------------- //

void TTitleScene::handleStart()
{
    float const delayTimer[3] = {1, 1, 1};
    auto game = TGame::getInstance();

    if (!mStartTimer->update()) {
        switch(mStartState)
        {
            case 0:
                mAlpha = TMath<s16>::clamp((mAlpha + 7), 0, 255);
                break;
            case 1:
                mAlpha = TMath<s16>::clamp((mAlpha + 7), 0, 255);
                mStartAlpha = TMath<s16>::clamp((mStartAlpha + 8), 0, 255);
                break;
            case 2:
                mCanStart = true;
                mStartAlpha = TMath<s16>::clamp((mStartAlpha - 8), 0, 255);
                break;
            case 3:
                mStartTimer->start(99.0f);
                //game->setClearColor(0,0,0,255);
                mAlpha = TMath<s16>::clamp((mAlpha - 4), 0, 255);
                if (mAlpha == 0) mStartState = 4;
                break;
            case 4:
                mAlpha = TMath<s16>::clamp((mAlpha + 6), 0, 255);
                game->setClearColor(-mAlpha,-mAlpha,-mAlpha,255);
                sCrashTimer->start(4);
                mStartState = 5;
                break;
            case 5:
                game->setClearColor(-mAlpha,-mAlpha,-mAlpha,255); 
                mAlpha = TMath<s16>::clamp((mAlpha + 6), 0, 255);
                if (sCrashTimer->update()) {
                    mStatus = ESceneState::EXITING;
                }
                break;
        }
    } else {
        mStartTimer->start(delayTimer[mStartState]);
        ++mStartState;
        if (mStartState > 2) mStartState = 1;
    }
}

// -------------------------------------------------------------------------- //

void TTitleScene::handleCheat()
{
    if (mMenuPad->isPressed(sButtonCache[mCheatState])){
        mCheatState++;

        if (mCheatState == sizeof(sButtonCache) / sizeof(EButton)){
            sIsCredits = true;
            
            TAudio::fadeMusic(0.0f, 8.0f);
            TAudio::playSound(ESfxType::SFX_SELECT);

            mStartState = 3;
            mStartAlpha = 0;
            mCanStart = false;
        }
    }
    else if (mMenuPad->isPressed((EButton)(A | B | UP | LEFT | RIGHT | DOWN)))
        mCheatState = 0;
}

// -------------------------------------------------------------------------- //

void TTitleScene::waitForEnd()
{
    if (sExitTimer->update()) {
        mCanStart = false;
        if (!sIsLoop) {
            sIsLoop = true;
            mStartState = 2;
            mStartTimer->start(2);
        }
    }

    if (sIsLoop && mStartTimer->update()) {
        mStatus = ESceneState::EXITING;
    }
}

// -------------------------------------------------------------------------- //