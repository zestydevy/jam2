#include <nusys.h>

#include "credits.hpp"

#include "scene.hpp"
#include "util.hpp"
#include "game.hpp"
#include "app.hpp"
#include "pad.hpp"
#include "audio.hpp"

#include "../models/ovl/sprites/sp_crash.h"
#include "../models/ovl/sprites/sp_credits.h"

#include "segment.h"

// -------------------------------------------------------------------------- //

void TCreditsScene::init()
{
    mStatus = ESceneState::RUNNING;

    
    if (mIsCredits) {
        TAudio::playSound(ESfxType::SFX_KARASU);
    }

    // load logo into memory
    
    mCreditsBg = new TSprite;
}

// -------------------------------------------------------------------------- //

void TCreditsScene::update()
{
    TAudio::update();
}

// -------------------------------------------------------------------------- //

void TCreditsScene::draw()
{
    // ...
}

// -------------------------------------------------------------------------- //

void TCreditsScene::draw2D()
{   
}

// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //

void TCreditsScene::draw2DBG()
{   
}

// -------------------------------------------------------------------------- //

TScene * TCreditsScene::exit()
{
    return nullptr;
}

// -------------------------------------------------------------------------- //