#include "select.hpp"
#include "carstats.hpp"

#include "segment.h"
#include "../models/static/bigsley/model_bigsley.h"
#include "../models/static/ollie/model_otter.h"
#include "../models/ovl/sprites/sprite_menubg.h"
#include "../models/static/sprites/white_sprite.h"
#include "../models/static/sprites/sprite_meter.h"
#include "../models/static/floor/model_floor.h"
#include "../models/static/car/model_car.h"
#include "../models/static/sprites/sprite_choose.h"
#include "../models/static/sprites/sprite_arrow.h"
#include "../models/static/sprites/sprite_arrowl.h"
#include "../models/ovl/sprites/sprite_maraca.h"
#include "../models/ovl/sprites/sprite_bigsley.h"
#include "../models/ovl/sprites/sprite_ollie.h"
#include "../data/tire.h"

// -------------------------------------------------------------------------- //

template<typename T>
T Lerp(T p0, T p1, float mu) {
  return (T)((float)p0 * (1.0F - mu) + (float)p1 * mu);
}

// -------------------------------------------------------------------------- //

template<typename T>
T Sinerp(T p0, T p1, float mu) {
  float a = TSine::fromDeg(mu * 90.0F);
  return Lerp<T>(p0, p1, TSine::ssin(a));
}

// -------------------------------------------------------------------------- //

template<typename T>
T Coserp(T p0, T p1, float mu) {
  float a = TSine::fromDeg(mu * 90.0F);
  return Lerp<T>(p0, p1, (1.0F - TSine::scos(a)));
}

// -------------------------------------------------------------------------- //

template<typename T>
T Lagrange(T p0, T p1, T p2, float mu) {
  float t0 = ((1.0F - mu) * (1.0F - mu));
  float t1 = (2.0F * (1.0F - mu) * mu);
  float t2 = (mu * mu);

  return (T)((float)p0 * t0 + (float)p1 * t1 + (float)p2 * t2);
}

// -------------------------------------------------------------------------- //

f32 sStatsTest[3][3] =
{
    {1.5f, 1.0f, 1.9f},
    {1.2f, 0.6f, 1.3f},
    {1.2f, 1.4f, 1.9f},
};

TSelectModelDef sSelectModels[3] =
{
    {player00_Cube1_008_mesh, car_body_Cube3_mesh, wheel_Cube1_sep23_mesh},
    {bigsley_b_head_mesh, bigsley_b_car_mesh, bigsley_b_tire_mesh},
    {otter_o_head_mesh, otter_o_body_mesh, wheel_Cube1_sep23_mesh},
};

Sprite * sSelectSprites[3] = 
{
    &maraca_sprite,
    &BIGSLEY_sprite,
    &OLIVER_sprite
};

s32 sTestIndex;

void TSelectKartScene::init()
{
    mStatus = ESceneState::RUNNING;

    TUtil::toMemory(
        reinterpret_cast<void *>(_codeSegmentBssEnd), 
        _menu_ovlSegmentRomStart, 
        _menu_ovlSegmentRomEnd-_menu_ovlSegmentRomStart
    );

    for (s32 i = 0; i < 4; ++i)
    {
        // initialize floors
        mFloors[i] = new TObject(mDynList);
        mFloors[i]->setPosition(TVec3F{0,-8,0});
        mFloors[i]->setScale(TVec3F{0.4f, 0.4f, 0.4f});
        mFloors[i]->setMesh(floor_Plane_mesh);

        //initialize karts
        mPlayers[i] = new TObject(mDynList);
        mPlayers[i]->setPosition(TVec3F{0,0,0});
        mPlayers[i]->setScale(TVec3F{0.6f, 0.6f, 0.6f});
        mPlayers[i]->setMesh(sSelectModels[0].head);
        mPlayers[i]->setParent(mFloors[i]);
        mKarts[i] = new TObject(mDynList);
        mKarts[i]->setPosition(TVec3F{0,0,0});
        mKarts[i]->setScale(TVec3F{0.6f, 0.6f, 0.6f});
        mKarts[i]->setMesh(sSelectModels[0].body);
        mKarts[i]->setParent(mFloors[i]);

        // initialize tires
        for (s32 j = 0; j < 4; ++j) {
            mWheels[i][j] = new TKartObject(mDynList);
            mWheels[i][j]->init();
            mWheels[i][j]->setPosition(TVec3F{0.0f,0.0f,0.0f});
            mWheels[i][j]->setMesh(sSelectModels[0].tire);
            mWheels[i][j]->setSuper(mFloors[i]);
            mWheels[i][j]->setParent(mKarts[i]);
        }

        auto config = reinterpret_cast<TTireConfig const &>(sTireConfig00);
        TTireConfig::loadConfig(&mWheels[i][0], const_cast<TTireConfig &>(config), 0.65f);

        //initialize pads
        mPads[i] = new TPad(i);
    }

    mCamera = new TCamera(mDynList);
    mCamera->setPad(mPads[0]);      // assign pad one to camera
    mCamera->setTarget(&mViewOrigin);

    // initial position for player 1
    mFloors[0]->setPosition(TVec3F{50.0f,-20.0f,0.0f});
    mKarts[0]->setPosition(TVec3F{20.0f, -10.0f, 0.0f});
    mPlayers[0]->setPosition(TVec3F{20.0f,-10.0f, 0.0f});

    mFade.load(white_sprite);
    mFade.setColor(TColor{0,0,0,255});
    mFade.setScale(TVec2F{320.0f, 240.0f});
    mFade.setAttributes(SP_TRANSPARENT);

    // bg
    mBg.load(menubg_sprite);
    mBg.setPosition(TVec2S{0, 0});
    mBg.setAttributes(SP_Z | SP_FASTCOPY);

    // choose player sprite
    mChPlayerSpr.load(choose_sprite);
    mChPlayerSpr.setPosition(TVec2S{15, -40});
    mChPlayerSpr.setAttributes(SP_TRANSPARENT | SP_FRACPOS);

    // arrow sprites sprite
    mArrowL.load(choose_arrowl_sprite);
    mArrowL.setPosition(TVec2S{(s16)140, (s16)240});
    mArrowL.setAttributes(SP_TRANSPARENT | SP_FRACPOS);
    mArrowR.load(choose_arrow_sprite);
    mArrowR.setPosition(TVec2S{(s16)(140/2), (s16)240});
    mArrowR.setScale(TVec2F{1.0f, 1.0f});
    mArrowR.setAttributes(SP_TRANSPARENT | SP_FRACPOS);

    mAva1.load(*sSelectSprites[0]);
    mAva1.setPosition(TVec2S{(s16)200, (s16)70});
    mAva1.setAttributes(SP_TRANSPARENT | SP_FRACPOS);

    mStatsBg.load(white_sprite);
    mStatsBg.setColor(TColor{0, 0, 0, 100});
    mStatsBg.setPosition(TVec2S{205, 150});
    mStatsBg.setScale(TVec2F{2.2f, 1.5f});
    mStatsBg.setAttributes(SP_TRANSPARENT | SP_FRACPOS);

    for (s32 i = 0; i < 3; ++i) {
        mStats[i].load(meter_sprite);
        mStats[i].setScale(TVec2F{0.01f, 0.3f});
        mStats[i].setAttributes(SP_FRACPOS | SP_TRANSPARENT);
    }

    mStats[0].setPosition(TVec2S{210, 155});
    mStats[0].setColor(TColor{19,3,252,255});
    mStats[1].setPosition(TVec2S{210, 170});
    mStats[1].setColor(TColor{252,252,3,255});
    mStats[2].setPosition(TVec2S{210, 185});
    mStats[2].setColor(TColor{252,3,3,255});

    mTimers1[0].start(1.0f);
    mTimers2[0].start(1.0f);
}

void TSelectKartScene::update()
{
    mCamera->update();
    mTimers1[0].update();
    mTimers2[0].update();
    mArrowTimers[0].update();
    mArrowTimers[1].update();

    for (s32 i = 0; i < mPlayerCount; ++i)
    {
        mFloors[i]->rotateY(TSine::fromDeg(1.0f));
        mFloors[i]->update();
        mPlayers[i]->update();
        mPads[i]->read();
        mKarts[i]->update();

        for (s32 j = 0; j < 4; ++j) {
            mWheels[i][j]->update();
        }
    }

    switch(mMenuState)
    {
        case KMENU_IN:

            s16 y = Lagrange<s16>(20, 50, -20, mTimers1[0].get());
            mChPlayerSpr.setPosition(TVec2S{(s16)15, y});

            y = Lagrange<s16>(90, 70, 290, mTimers1[0].get());
            mArrowR.setPosition(TVec2S{Lagrange<s16>(140, 160, 140, mArrowTimers[0].get()), y});
            mArrowL.setPosition(TVec2S{Lagrange<s16>(140/5, 140/5-20, 140/5, mArrowTimers[1].get()), y});

            for (s32 i = 0; i < 3; ++i) {
                mStats[i].setScale(TVec2F{Sinerp<f32>(sStatsTest[sTestIndex][i], 0.01f, mTimers2[0].get()), 0.3f});
            }

            // fade
            mFade.setColor(TColor{0,0,0, Lerp<u8>(0, 230, mTimers1[0].get())});
            
            //kart
            
            TVec3F kartScale{0.4f, 0.4f, 0.4f};
            kartScale.lerp(TVec3F{0.4f, 0.0f, 0.4f}, mTimers2[0].get());
            mFloors[0]->setScale(kartScale);
            
            // face
            mAva1.setPosition(TVec2S{Coserp<s16>(200, 350, mTimers2[0].get()), (s16)70});
            mAva1.setColor(TColor{255, 255, 255, Lagrange<u8>(255, 0, 0, mTimers2[0].get())});

            // brain damage
            for (s32 i = 0; i < 1; ++i) {
                if (mPads[i]->isPressed(EButton::RIGHT)) {
                    mTimers2[i].start(1.0f);
                    ++sTestIndex;
                    if (sTestIndex > 2) sTestIndex = 0;
                    mAva1.load(*sSelectSprites[sTestIndex]);
                    mAva1.setPosition(TVec2S{320,320});
                    mFloors[i]->setScale(TVec3F{0.4f, 0.0f, 0.4f});
                    mPlayers[i]->setMesh(sSelectModels[sTestIndex].head);
                    mKarts[i]->setMesh(sSelectModels[sTestIndex].body);
                    for (s32 j = 0; j < 4; ++j) {
                        mWheels[i][j]->setMesh(sSelectModels[sTestIndex].tire);
                    }
                    mArrowTimers[i].start(1.0f);
                }
                if (mPads[i]->isPressed(EButton::LEFT)) {
                    mTimers2[i].start(1.0f);
                    --sTestIndex;
                    if (sTestIndex < 0) sTestIndex = 2;
                    mAva1.load(*sSelectSprites[sTestIndex]);
                    mAva1.setPosition(TVec2S{320,320});
                    mFloors[i]->setScale(TVec3F{0.4f, 0.0f, 0.4f});
                    mPlayers[i]->setMesh(sSelectModels[sTestIndex].head);
                    mKarts[i]->setMesh(sSelectModels[sTestIndex].body);
                    for (s32 j = 0; j < 4; ++j) {
                        mWheels[i][j]->setMesh(sSelectModels[sTestIndex].tire);
                    }
                    mArrowTimers[i+1].start(1.0f);
                }
            }
        
            break;
    }

    mTimer += kInterval;
}

void TSelectKartScene::draw()
{
    beginDraw();
    
    mCamera->render();
    
    for (s32 i = 0; i < mPlayerCount; ++i) {
      mFloors[i]->draw();
      mPlayers[i]->draw();
      mKarts[i]->draw();

      for (s32 j = 0; j < 4; ++j) {
            mWheels[i][j]->draw();
        }
    }
    //gSPDisplayList(mDynList->pushDL(), letters_setup_dl);
}

void TSelectKartScene::draw2D()
{
    mChPlayerSpr.draw();
    mArrowL.draw();
    mArrowR.draw();
    mAva1.draw();

    mStatsBg.draw();
    for (s32 i = 0; i < 3; ++i) {
        mStats[i].draw();
    }

    mFade.draw();

}

// -------------------------------------------------------------------------- //

void TSelectKartScene::draw2DBG()
{
    mBg.draw();
}

// -------------------------------------------------------------------------- //

TScene * TSelectKartScene::exit()
{
    return new TSelectKartScene { "fuck", mDynList };
}