
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
#include "checkpoint.hpp"
#include "items.hpp"

#include "../scene/object_info.h"
#include "../models/ovl/sprites/sp_logo1.h"
#include "../models/ovl/sprites/sp_logo2.h"
#include "../models/ovl/sprites/sprite_minimap.h"
#include "../models/static/sprites/sprite_dot.h"
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
TSprite * sMiniMap;
TSprite * sMapDot;
TSprite * sMapDot2;
TSprite * sMapDot3;
TSprite * sMapDot4;
u8 sFadeAlpha = 255;

TCollision::TFace* sFaces;

char sSceneErrorBuff[32];

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

// -------------------------------------------------------------------------- //

bool TScene::isInitialized()
{
    return (mStatus == ESceneState::RUNNING);
}

// -------------------------------------------------------------------------- //

void TScene::beginDraw()
{
    gSPDisplayList(mDynList->pushDL(), letters_setup_dl);
}

// -------------------------------------------------------------------------- //

void TScene::loadObjects(TSceneEntry const list[])
{
    s32 size = list[0].id;
    list = reinterpret_cast<const TSceneEntry *>(&list[1]);
    // mObjList.reserve((u32)size);

    for(int i = 0; i < size; ++i) {
        
        if (list[i].id >= EObjType::INVALID) {
            sprintf(sSceneErrorBuff, "INVALID OBJ ID %d", list[i].id);
            return;
        }

        TObject * obj = nullptr;
        TDynLight * light = nullptr;
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
            case EObjType::POKESTOP:
                obj = new TPokeStop(mDynList);
                ((TPokeStop*)obj)->setRadius(list[i].data[0]);
                break;
            case EObjType::DEBUG_CUBE:
                obj = new TObject(mDynList);
                obj->setMesh(TObject::getMeshGfx(type));
                break;
            case EObjType::DYNLIGHT:
                light = new TDynLight();
                light->setPosition({list[i].positionX, list[i].positionY, list[i].positionZ});
                light->setColor(list[i].data[0], list[i].data[1], list[i].data[2]);
                light->setRadius((f32)list[i].data[3]);
                mLightList.push(light);
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

    if (!TCollider::startup(nullptr, test00_block_count, test00_block_size))
        TException::fault("COLDR START ERROR");

    sFaces = new TCollision::TFace[test00_layer1_count];

    //Load collision data
    TUtil::toMemory(
        reinterpret_cast<void *>(sFaces), 
        _col_ovlSegmentRomStart, 
        _col_ovlSegmentRomEnd-_col_ovlSegmentRomStart
    );

    if (!TCollision::startup(
        sFaces, test00_layer1_count, nullptr,
        (test00_layer1_count * 1.5f), test00_block_count, test00_block_size
    ))
        TException::fault("COLSN START ERROR");

    mRacist.clearCheckpoints();
    gCurrentRace = &mRacist;

    for (int i = 0; i < 4; i++){
        mPlayers[i] = new TPlayer(mDynList);
        mPlayers[i]->setMesh(car_body_Cube3_mesh);
        mPlayers[i]->setCharacter(ECharacter::CHAR_PARROT);
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
    sMiniMap = new TSprite();
    sMapDot = new TSprite();
    sMapDot2 = new TSprite();
    sMapDot3 = new TSprite();
    sMapDot4 = new TSprite();

    mEmitterList.setHeap(THeap::getCurrentHeap());

    mTestCamera = new TCamera(mDynList);
    mTestCamera->setPad(mTestPad);
    mTestCamera2 = new TCamera(mDynList);
    mTestCamera2->setPad(mTestPad);

    for (int i = 0; i < 4; i++){
        mPlayers[i]->setScale(TVec3F{0.4f, 0.4f, 0.4f});
        mPlayers[i]->init();
        mPlayers[i]->setShadowMesh(car_body_shadow_mesh, mat_car_shadow_f3d, car_Cube1_mesh_shadow_lod);
        mPlayers[i]->setRelativeLightSource({100.0f, 1000.0f, 100.0f});
        mPlayers[i]->initParticles(mEmitterList);
        mPlayers[i]->initWheels();
    }

    //Player 1
    mPlayers[0]->setCamera(mTestCamera);
    mPlayers[0]->setPad(mTestPad);

    //Player 2
    mPlayers[1]->setCamera(mTestCamera2);
    mPlayers[1]->setAIType(AI_BAD);

    sLogoObj = new TObject(mDynList);
    sLogoObj->setMesh(n64_n64_N_mesh_mesh_mesh);
    sLogoObj->setPosition(TVec3F{0.0f, -20.0f, 0.0f});
    sLogoObj->setScale(TVec3F{0.6f, 0.6f, 0.6f});

    sSkyObj = new TObject(mDynList);
    sSkyObj->setMesh(sky_Track1_mesh);
    sSkyObj->setPosition(TVec3F{0.0f, 0.0f, 0.0f});
    sSkyObj->setScale(TVec3F{4.5f, 4.5f, 4.5f});

    mTestCamera->jumpToTarget();
    mTestCamera2->jumpToTarget();

    sFadeSpr = new TSprite();
    sFadeSpr->load(black_sprite);

    sYoshiJoint = new TJoint(32);
    sYoshiJoint->registerAnimation(reinterpret_cast<TJointAnimData const &>(dino_anim_ArmatureAction));
    sYoshiJoint->playAnimation();
}

// -------------------------------------------------------------------------- //

float sSceneTime = 0.0f;
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

    sSceneTime += kInterval;

    for (int i = 0; i < mObjList.capacity(); i++){
        mObjList[i]->update();
    }

    for (int i = 0; i < 4; i++){
        TDynLightInfo envLight = TDynLightInfo();
        envLight.point = {100.0f, 1000.0f, 100.0f};
        envLight.color[0] = 255;
        envLight.color[1] = 255;
        envLight.color[2] = 255;

        for (int j = 0; j < mLightList.capacity(); ++j){
            if (mLightList[j]->lerpBetween(envLight, mPlayers[i]->getPosition(), &envLight)){
            }
        }
        mPlayers[i]->update();
        mPlayers[i]->setRelativeLightSource(envLight.point);
    }
    gCurrentRace->updateRankings();

    mTestCamera->update();
    mTestCamera2->update();
    sYoshiJoint->updateAnimation();
    sLogoObj->update();
    sSkyObj->mAlwaysDraw = true;
    sSkyObj->update();

    sLogoRot += 140.0f;
    sLogoObj->setRotation(TVec3F{0.0f, sLogoRot, 0.0f});

    TCollider::frameEnd();
}

// -------------------------------------------------------------------------- //

void TLogoScene::draw()
{
    gSPDisplayList(mDynList->pushDL(), letters_setup_dl);
    //gSPDisplayList(mDynList->pushDL(), rdpinit_spr_dl);

    //gSPDisplayList(mDynList->pushDL(), rdpinit_dl);
    //gSPDisplayList(mDynList->pushDL(), rspinit_dl);

    gSPDisplayList(mDynList->pushDL(), TCamera::getPlayer1View());
    mTestCamera->render();
    sSkyObj->draw();
	sLogoObj->draw();

    for (int i = 0; i < mObjList.capacity(); i++){
        mObjList[i]->draw();
    }

    for (int i = 0; i < 4; i++){
        mPlayers[i]->draw();
    }

    gSPDisplayList(mDynList->pushDL(), grass_Track1_001_mesh);

    gSPDisplayList(mDynList->pushDL(), mat_car_shadow_f3d);

    for (int i = 0; i < 4; i++)
        mPlayers[i]->drawShadow();

    gSPDisplayList(mDynList->pushDL(), mat_car_shadow_f3d_revert);

    for (int i = 0; i < 4; i++){
        mPlayers[i]->drawTransparent();
    }

    for (int i = 0; i < mEmitterList.capacity(); ++i) {
        mEmitterList[i]->draw();
    }

    
    gSPDisplayList(mDynList->pushDL(), letters_setup_dl);
    gSPDisplayList(mDynList->pushDL(), TCamera::getPlayer2View());
    mTestCamera2->render();
	
    sSkyObj->draw();
	sLogoObj->draw();

    for (int i = 0; i < mObjList.capacity(); i++){
        mObjList[i]->draw();
    }

    for (int i = 0; i < 4; i++){
        mPlayers[i]->draw();
    }

    gSPDisplayList(mDynList->pushDL(), grass_Track1_001_mesh);

    gSPDisplayList(mDynList->pushDL(), mat_car_shadow_f3d);

    for (int i = 0; i < 4; i++)
        mPlayers[i]->drawShadow();

    gSPDisplayList(mDynList->pushDL(), mat_car_shadow_f3d_revert);

    for (int i = 0; i < 4; i++){
        mPlayers[i]->drawTransparent();
    }

    for (int i = 0; i < mEmitterList.capacity(); ++i) {
        mEmitterList[i]->draw();
    }

    /*

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

    sMiniMap->load(minimap_sprite);
    sMiniMap->setPosition(TVec2S{260, 150});
    sMiniMap->setScale(TVec2F{0.5f, 0.5f});
    sMiniMap->setColor(TColor{255,255,255,200});
    sMiniMap->setAttributes(SP_FRACPOS | SP_TRANSPARENT);
    sMiniMap->draw();

    sMapDot->load(dot_sprite);
    auto mapPos = (gPlayers[0]->getPosition().zx() / 175.0f) + TVec2F{-273.0f, 186.0f};
    sMapDot->setPosition(TVec2S{(s16)-mapPos.x(), (s16)mapPos.y()});
    sMapDot->setScale(TVec2F{0.5f, 0.5f});
    sMapDot->setColor(TColor{255,255,255,180});
    sMapDot->setAttributes(SP_FRACPOS | SP_TRANSPARENT);
    sMapDot->draw();

    sMapDot2->load(dot_sprite);
    mapPos = (gPlayers[1]->getPosition().zx() / 175.0f) + TVec2F{-273.0f, 186.0f};
    sMapDot2->setPosition(TVec2S{(s16)-mapPos.x(), (s16)mapPos.y()});
    sMapDot2->setScale(TVec2F{0.5f, 0.5f});
    sMapDot2->setColor(TColor{255,0,0,100});
    sMapDot2->setAttributes(SP_FRACPOS | SP_TRANSPARENT);
    sMapDot2->draw();

    sMapDot3->load(dot_sprite);
    mapPos = (gPlayers[2]->getPosition().zx() / 175.0f) + TVec2F{-273.0f, 186.0f};
    sMapDot3->setPosition(TVec2S{(s16)-mapPos.x(), (s16)mapPos.y()});
    sMapDot3->setScale(TVec2F{0.5f, 0.5f});
    sMapDot3->setColor(TColor{255,0,0,100});
    sMapDot3->setAttributes(SP_FRACPOS | SP_TRANSPARENT);
    sMapDot3->draw();

    sMapDot4->load(dot_sprite);
    mapPos = (gPlayers[3]->getPosition().zx() / 175.0f) + TVec2F{-273.0f, 186.0f};
    sMapDot4->setPosition(TVec2S{(s16)-mapPos.x(), (s16)mapPos.y()});
    sMapDot4->setScale(TVec2F{0.5f, 0.5f});
    sMapDot4->setColor(TColor{255,0,0,100});
    sMapDot4->setAttributes(SP_FRACPOS | SP_TRANSPARENT);
    sMapDot4->draw();

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

// -------------------------------------------------------------------------- //

void TLogoScene::draw2DBG()
{   
}

// -------------------------------------------------------------------------- //

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