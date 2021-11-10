
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
#include "exception.hpp"
#include "hashmap.hpp"

#include "../scene/object_info.h"
#include "../models/ovl/sprites/sp_logo1.h"
#include "../models/ovl/sprites/sp_logo2.h"
#include "../models/static/floor/model_floor.h"
#include "../models/static/ptcl00/sprite_ptcl00.h"
#include "../models/static/yoshi/model_dino.h"
#include "../models/static/n64/model_n64.h"
#include "../models/static/test00/model_test00.h"
#include "../models/static/car/model_car.h"
#include "../models/static/sprites/black_sprite.h"
#include "../models/static/sprites/sp_p1.h"
#include "../models/static/sprites/sp_p2.h"
#include "../models/static/sprites/sp_p3.h"
#include "../models/static/sprites/sp_p4.h"
#include "../data/ptcl_test.h"
#include "../data/anim_test.h"

// -------------------------------------------------------------------------- //

extern Gfx rdpinit_spr_dl[];
extern Gfx rdpinit_dl[];
extern Gfx rspinit_dl[];

TJoint * sYoshiJoint;
TObject * sLogoObj;
TObject * sSkyObj;
f32 sLogoRot = 0.0f;
TSprite * sFadeSpr;
TSprite * sP1;
TSprite * sP2;
TSprite * sP3;
TSprite * sP4;
u8 sFadeAlpha = 255;

TCollision::TFace* sFaces;

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
                if (gPlayers[list[i].data[0]] != nullptr){
                    gPlayers[list[i].data[0]]->setPosition({list[i].positionX, list[i].positionY, list[i].positionZ});
                    gPlayers[list[i].data[0]]->setDriveDirection(TSine::fromDeg(list[i].data[1]));
                    gPlayers[list[i].data[0]]->snapToGround();
                }
                continue;
            case EObjType::CHECKPOINT:
                gCurrentRace->loadCheckpoint(list[i]);
                break;
            case EObjType::DEBUG_CUBE:
                obj = new TObject(mDynList);
                obj->setMesh(TObject::getMeshGfx(type));
                break;
            default: 
                break;
        }

        if (obj == nullptr)
            continue;

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

    mTestPad = new TPad(0);

    // turn on screen
    //nuGfxDisplayOn();

    // load logo into memory
    TUtil::toMemory(
        reinterpret_cast<void *>(_codeSegmentBssEnd), 
        _logo_ovlSegmentRomStart, 
        _logo_ovlSegmentRomEnd-_logo_ovlSegmentRomStart
    );

    TCollider::startup(nullptr, 10, 512.0F);

    sFaces = new TCollision::TFace[test00_layer1_count];

    //Load collision data
    TUtil::toMemory(
        reinterpret_cast<void *>(sFaces), 
        _col_ovlSegmentRomStart, 
        _col_ovlSegmentRomEnd-_col_ovlSegmentRomStart
    );

    if (!TCollision::startup(
        sFaces, test00_layer1_count, nullptr,
        (test00_layer1_count * 1.4f), 10, 4096.0F
    ))
        *(int*)0 = 0;

    mRacist.clearCheckpoints();
    gCurrentRace = &mRacist;

    for (int i = 0; i < 4; i++){
        mPlayers[i] = new TPlayer(mDynList);
        mPlayers[i]->setMesh(car_Cube1_mesh);
        gPlayers[i] = mPlayers[i];
    }

    loadObjects(scene_test00);

    gCurrentRace->postLoadCheckpoints();

    //TAudio::playMusic(EBgm::BGM_INTRO);

    mShowTimer = new TTimer;
    mFadeTimer = new TTimer;

    // scene start timer
    mShowTimer->start(1);

    // move logo off-screen
    mLogoX = 512;

    mLogoSpr = new TSprite;
    mLogoNinSpr = new TSprite;

    sTestEmitter = new TEmitter(sTestPos, reinterpret_cast<TEmitConfig const &>(sPtclSmoke), mDynList);
    mEmitterList.setHeap(THeap::getCurrentHeap());
    mEmitterList.push(sTestEmitter);

    mTestCamera = new TCamera(mDynList);
    mTestCamera->setPad(mTestPad);

    for (int i = 0; i < 4; i++){
        mPlayers[i]->setScale(TVec3F{0.4f, 0.4f, 0.4f});
        mPlayers[i]->init();
        mPlayers[i]->setShadowMesh(car_Cube1_mesh_shadow);
    }

    //Player 1
    mPlayers[0]->setCamera(mTestCamera);
    mPlayers[0]->setPad(mTestPad);

    //Player 2
    mPlayers[1]->setAIType(AI_BAD);

    //Player 3
    mPlayers[2]->setAIType(AI_RANDOM);

    //Player 4
    mPlayers[3]->setAIType(AI_GOOD);

    sTestEmitter->attach(mPlayers[0], TVec3F{0.0f, 0.0f, 0.0f});

    sLogoObj = new TObject(mDynList);
    sLogoObj->setMesh(n64_n64_N_mesh_mesh_mesh);
    sLogoObj->setPosition(TVec3F{0.0f, -20.0f, 0.0f});
    sLogoObj->setScale(TVec3F{0.6f, 0.6f, 0.6f});

    sSkyObj = new TObject(mDynList);
    sSkyObj->setMesh(sky_Track1_mesh);
    sSkyObj->setPosition(TVec3F{0.0f, 0.0f, 0.0f});
    sSkyObj->setScale(TVec3F{4.5f, 4.5f, 4.5f});

    mTestCamera->jumpToTarget();

    sFadeSpr = new TSprite();
    sFadeSpr->load(black_sprite);
    
    sP1 = new TSprite();
    sP1->load(p1_sprite);
    sP2 = new TSprite();
    sP2->load(p2_sprite);
    sP3 = new TSprite();
    sP3->load(p3_sprite);
    sP4 = new TSprite();
    sP4->load(p4_sprite);

    sYoshiJoint = new TJoint(32);
    sYoshiJoint->registerAnimation(reinterpret_cast<TJointAnimData const &>(dino_anim_ArmatureAction));
    sYoshiJoint->playAnimation();
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

    TCollider::frameBegin();

    for (int i = 0; i < 4; i++)
        mPlayers[i]->update();

    mTestCamera->update();
    sYoshiJoint->updateAnimation();
    sLogoObj->update();
    sSkyObj->mAlwaysDraw = true;
    sSkyObj->update();

    sLogoRot += 140.0f;
    sLogoObj->setRotation(TVec3F{0.0f, sLogoRot, 0.0f});

    sTestEmitter->setParentOffset(TVec3F{TMath<f32>::frand(-6.0f, 6.0f), 0.0f, 0.0f});

    TCollider::frameEnd();
}

// -------------------------------------------------------------------------- //

void TLogoScene::draw()
{
    gSPDisplayList(mDynList->pushDL(), letters_setup_dl);
    //gSPDisplayList(mDynList->pushDL(), rdpinit_spr_dl);

    //gSPDisplayList(mDynList->pushDL(), rdpinit_dl);
    //gSPDisplayList(mDynList->pushDL(), rspinit_dl);

    //gSPDisplayList(mDynList->pushDL(), TCamera::getPlayer1View());
    mTestCamera->render();
    sSkyObj->draw();
	sLogoObj->draw();

    for (int i = 0; i < 4; i++)
        mPlayers[i]->draw();

    gSPDisplayList(mDynList->pushDL(), grass_Track1_001_mesh);

    for (int i = 0; i < 4; i++)
        mPlayers[i]->drawShadow();

    for (int i = 0; i < mEmitterList.capacity(); ++i) {
        mEmitterList[i]->draw();
    }

    /*
    gSPDisplayList(mDynList->pushDL(), letters_setup_dl);
    gSPDisplayList(mDynList->pushDL(), TCamera::getPlayer2View());
    mTestCamera2->render();
	sLogoObj->draw();
    for (int i = 0; i < mEmitterList.capacity(); ++i) {
        mEmitterList[i]->draw();
    }

    gSPDisplayList(mDynList->pushDL(), letters_setup_dl);
    gSPDisplayList(mDynList->pushDL(), TCamera::getPlayer3View());
    mTestCamera3->render();
	sLogoObj->draw();
    for (int i = 0; i < mEmitterList.capacity(); ++i) {
        mEmitterList[i]->draw();
    }

    gSPDisplayList(mDynList->pushDL(), letters_setup_dl);
    gSPDisplayList(mDynList->pushDL(), TCamera::getPlayer4View());
    mTestCamera4->render();
	sLogoObj->draw();
    for (int i = 0; i < mEmitterList.capacity(); ++i) {
        mEmitterList[i]->draw();
    }
    */

    //gSPDisplayList(mDynList->pushDL(), n64_n64_N_mesh_mesh_mesh);
}

void TLogoScene::draw2D()
{
    sFadeSpr->load(black_sprite);
    sFadeSpr->setScale(TVec2F{320.0f, 240.0f});
    sFadeAlpha = TMath<u8>::clamp(sFadeAlpha -= 2, 7, 255);
    sFadeSpr->setColor(TColor{255,255,255, sFadeAlpha});
    sFadeSpr->setAttributes(SP_FRACPOS | SP_TRANSPARENT);
    sFadeSpr->draw();

    /*
    sP1->setPosition(TVec2S{16, 16});
    sP1->setAttributes(SP_FRACPOS | SP_TRANSPARENT);
    sP1->draw();

    sP2->setPosition(TVec2S{320/2+16, 16});
    sP2->setAttributes(SP_FRACPOS | SP_TRANSPARENT);
    sP2->draw();

    sP3->setPosition(TVec2S{16, 240/2+16});
    sP3->setAttributes(SP_FRACPOS | SP_TRANSPARENT);
    sP3->draw();

    sP4->setPosition(TVec2S{320/2+16, 240/2+16});
    sP4->setAttributes(SP_FRACPOS | SP_TRANSPARENT);
    sP4->draw();
    */
    
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