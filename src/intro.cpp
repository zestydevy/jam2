#include "intro.hpp"

#include "../models/static/n64/model_n64.h"

#include "segment.h"

// -------------------------------------------------------------------------- //

void TIntroScene::init()
{
    mStatus = ESceneState::RUNNING;

    TUtil::toMemory(
        reinterpret_cast<void *>(_codeSegmentBssEnd), 
        _menu_ovlSegmentRomStart, 
        _menu_ovlSegmentRomEnd-_menu_ovlSegmentRomStart
    );

    mPad = new TPad(0);
    mCamera = new TCamera(mDynList);
    mCamera->setPad(mPad);

    mLogo = new TObject(mDynList);
    mLogo->init();
    mLogo->setMesh(n64_n64_N_mesh_mesh_mesh);
    mLogo->setPosition(TVec3F{0.0f, 0.0f, 0.0f});
    mLogo->setScale(TVec3F{1.0f, 1.0f, 1.0f});

    mCamera->setTarget(&mOrigin);
    mCamera->jumpToTarget();
}

// -------------------------------------------------------------------------- //

void TIntroScene::update()
{
    mCamera->update();
    mLogo->update();
}

// -------------------------------------------------------------------------- //

void TIntroScene::draw()
{
    TScene::beginDraw();

    mCamera->render();
    mLogo->draw();
}

// -------------------------------------------------------------------------- //

void TIntroScene::draw2D()
{   
}

// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //

void TIntroScene::draw2DBG()
{   
}

// -------------------------------------------------------------------------- //

TScene * TIntroScene::exit()
{
    return nullptr;
}

// -------------------------------------------------------------------------- //