
#include <nusys.h>

#include "audio.hpp"
#include "collision.h"
#include "graphic.h"
#include "heap.hpp"
#include "scene.hpp"
#include "scenedata.h"
#include "segment.h"
#include "sprite.hpp"
#include "staticobj.hpp"
#include "util.hpp"
#include "math.hpp"
#include "game.hpp"
#include "title.hpp"
#include "emitter.hpp"
#include "joint.hpp"

#include "../scene/object_info.h"
#include "../models/ovl/sprites/sp_logo1.h"
#include "../models/ovl/sprites/sp_logo2.h"
#include "../models/static/floor/model_floor.h"
#include "../models/static/ptcl00/sprite_ptcl00.h"
#include "../models/static/yoshi/model_yoshi.h"
#include "../data/ptcl_test.h"

// -------------------------------------------------------------------------- //

extern Gfx rdpinit_spr_dl[];
extern Gfx rdpinit_dl[];
extern Gfx rspinit_dl[];

TJoint * sYoshiJoint;

// -------------------------------------------------------------------------- //

Lights2 litc2 = gdSPDefLights2(
    0x5, 0x5, 0x5, /* ambient color */
    100, 100, 0,   /* light color */
    -32, -64, -32, /* normal */
    50, 50, 0,     /* light color */
    15, 30, 120    /* normal */
);

Gfx letters_setup_dl[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPSetGeometryMode(
        G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH |
        G_CULL_BACK | G_LIGHTING
    ), gsSPSetLights2(litc2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPEndDisplayList(),
};

TVec3F const sTestPos{0.0f,0.0f,0.0f};
TEmitter * sTestEmitter;

// -------------------------------------------------------------------------- //

bool TScene::isInitialized()
{
    return (mStatus == ESceneState::RUNNING);
}

// -------------------------------------------------------------------------- //

void TScene::loadObjects(TSceneEntry const list[])
{
    s32 size = list[0].id;
    list = reinterpret_cast<const TSceneEntry *>(&list[1]);
    // mObjList.reserve((u32)size);

    for(int i = 0; i < size; ++i) {
        
        if (list[i].id >= EObjType::INVALID) {
            // wtf kind of model are you tryin to load
            return;
        }

        TObject * obj = nullptr;
        auto type = (EObjType)list[i].id;

        switch(list[i].id) {
            case EObjType::PLAYERSTART:
                //gPlayer->setPosition({list[i].positionX, list[i].positionY, list[i].positionZ});
                break;
            case EObjType::DEBUG_CUBE:
                obj = new TObject(mDynList);
                obj->setMesh(TObject::getMeshGfx(type));
                break;
            default: 
                break;
        }

        if (obj == nullptr) {
            continue;
        }

        obj->setPosition({list[i].positionX, list[i].positionY, list[i].positionZ});
        obj->setRotation({TSine::fromDeg(list[i].rotationX), TSine::fromDeg(list[i].rotationY), TSine::fromDeg(list[i].rotationZ)});
        obj->setScale({list[i].scaleX, list[i].scaleY, list[i].scaleZ});
        obj->init();

        mObjList.push(obj);
    }
}

// -------------------------------------------------------------------------- //

void TLogoScene::init()
{
    mStatus = ESceneState::RUNNING;

    mTestCamera = new TCamera(mDynList);
    mTestPad = new TPad(0);
    mTestCamera->setPad(mTestPad);
    mTestCamera->setTarget(&sTestPos);
    mTestCamera->jumpToTarget();

    // turn on screen
    //nuGfxDisplayOn();

    // load logo into memory
    TUtil::toMemory(
        reinterpret_cast<void *>(_codeSegmentBssEnd), 
        _logo_ovlSegmentRomStart, 
        _logo_ovlSegmentRomEnd-_logo_ovlSegmentRomStart
    );

    TAudio::playMusic(EBgm::BGM_INTRO);

    mShowTimer = new TTimer;
    mFadeTimer = new TTimer;

    // scene start timer
    mShowTimer->start(1);

    // move logo off-screen
    mLogoX = 512;

    mLogoSpr = new TSprite;
    mLogoNinSpr = new TSprite;

    sTestEmitter = new TEmitter(sTestPos, reinterpret_cast<TEmitConfig const &>(sTestPtcl00), mDynList);
    mEmitterList.setHeap(THeap::getCurrentHeap());
    mEmitterList.push(sTestEmitter);

    sYoshiJoint = new TJoint(2);
}

// -------------------------------------------------------------------------- //

void TLogoScene::update()
{
    // wait two seconds to boot
    if (mShowTimer != nullptr) {
        runBootTimer();
    } else {
        runFadeLogo1();
    }
    mTestPad->read();

    for (int i = 0; i < mEmitterList.capacity(); ++i) {
        mEmitterList[i]->emit();
    }

    mTestCamera->update();
}

// -------------------------------------------------------------------------- //

void TLogoScene::draw()
{
    gSPDisplayList(mDynList->pushDL(), letters_setup_dl);
    //gSPDisplayList(mDynList->pushDL(), rdpinit_spr_dl);

    //gSPDisplayList(mDynList->pushDL(), rdpinit_dl);
    //gSPDisplayList(mDynList->pushDL(), rspinit_dl);

    mTestCamera->render();

    //gSPDisplayList(mDynList->pushDL(), yoshi_wrist_r1_001_mesh);
    
    sYoshiJoint->setDl(mDynList);
    sYoshiJoint->attachJoint("body", mario_Bone_mesh_layer_1, TVec3F{0.0f,0.0f,0.0f});
        gSPDisplayList(mDynList->pushDL(), mario_Bone_001_skinned_mesh_layer_1);
        sYoshiJoint->attachJoint("head", mario_Bone_001_mesh_layer_1, TVec3F{0.0f,49.0f,0.0f});
        sYoshiJoint->detach();
    sYoshiJoint->detach();
    sYoshiJoint->reset();
    
    //gDPSetPrimColor(mDynList->pushDL(), 0, 0, 254, 254, 254, 255)
    //gSPDisplayList(mDynList->pushDL(), ptcl00_Plane_mesh);
    //gSPDisplayList(mDynList->pushDL(), distant_Distant_mesh);

    for (int i = 0; i < mEmitterList.capacity(); ++i) {
        mEmitterList[i]->draw();
    }
}

void TLogoScene::draw2D()
{
    /*
    switch(mLogoState)
    {
        case 0:
        case 1:
            mLogoSpr->load(logo1_sprite);
            mLogoSpr->setPosition(TVec2S{mLogoX, mLogoY});
            mLogoSpr->setScale(TVec2F{1.0f, 1.0f});
            mLogoSpr->setColor({255,255,255,static_cast<u8>(mAlpha)});
            mLogoSpr->setAttributes(SP_FRACPOS | SP_TRANSPARENT);
            mLogoSpr->draw();
            break;
        case 2:
        case 3:
            mLogoSpr->load(logo2_sprite); 
            mLogoSpr->setPosition(TVec2S{mLogoX, mLogoY});
            mLogoSpr->setScale(TVec2F{1.0f, 1.0f});
            mLogoSpr->setColor({255,255,255,static_cast<u8>(mAlpha)});
            mLogoSpr->setAttributes(SP_FRACPOS | SP_TRANSPARENT);
            mLogoSpr->draw();
    }
*/

}

TScene * TLogoScene::exit()
{
    // turn off screen
    //nuGfxDisplayOff();

    delete mLogoSpr;
    delete mLogoNinSpr;
    delete mFadeTimer;
    return new TTitleScene { "title", mDynList };

}

// -------------------------------------------------------------------------- //

void TLogoScene::runBootTimer()
{
    if (mShowTimer->update()) {
        delete mShowTimer;
        mShowTimer = nullptr;
        mLogoX = 0;        // move logo on screen
        mFadeTimer->start(9999);
        //TAudio::playSound(ESfxType::SFX_CAW);
    }
}

// -------------------------------------------------------------------------- //

void TLogoScene::runLogoTimer()
{
    if (mTimer->update()) {
        mAlpha -= 4;
        if (mAlpha <= 4) {
            mAlpha = 0;

            delete mTimer;
            mTimer = nullptr;

            mStatus = ESceneState::EXITING;     // exit scene
        }
    }
}

// -------------------------------------------------------------------------- //

void TLogoScene::runFadeLogo1()
{
    const float delayList[5] = {999, 1.2f, 2, 99999.0f, 99999};
    auto game = TGame::getInstance();

    TPad * mMenuPad = new TPad(0);
    mMenuPad->read();
    if (mMenuPad->isPressed(EButton::A)) game->mCoarseList[game->mCurrentSample]++;
    if (mMenuPad->isPressed(EButton::B)) game->mCoarseList[game->mCurrentSample]--;
    if (mMenuPad->isPressed(EButton::R)) game->mCurrentSample++;
    if (mMenuPad->isPressed(EButton::L)) game->mCurrentSample--;
    if (mMenuPad->isPressed(EButton::START)){
        musHandle sndHandle = MusStartEffect(game->mCurrentSample);
		MusHandleSetFreqOffset(sndHandle, game->mCoarseList[game->mCurrentSample]);
    }
    delete mMenuPad;

    if (!mFadeTimer->update()) {
        switch(mLogoState)
        {
            case 0:
                mAlpha = TMath<s16>::clamp((mAlpha + 12), 0, 255);
                break;
            case 1:
                game->setClearColor(255,255,255,1);
                mAlpha = TMath<s16>::clamp((mAlpha - 7), 0, 255);
                break;
            case 2:
                mAlpha = TMath<s16>::clamp((mAlpha + 7), 0, 255);
                break;
            case 3:
                mAlpha = TMath<s16>::clamp((mAlpha - 7), 0, 255);
                break;
            case 4:
                mStatus = ESceneState::EXITING;
                break;
        }
    } else {
        ++mLogoState;
        mFadeTimer->start(delayList[mLogoState]);
    }
}