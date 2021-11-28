#include "select.hpp"
#include "carstats.hpp"

#include "../models/static/floor/model_floor.h"
#include "../models/static/car/model_car.h"
#include "../models/static/sprites/sprite_choose.h"
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


void TSelectKartScene::init()
{
    mStatus = ESceneState::RUNNING;

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
        mPlayers[i]->setMesh(player00_Cube1_008_mesh);
        mPlayers[i]->setParent(mFloors[i]);
        mKarts[i] = new TObject(mDynList);
        mKarts[i]->setPosition(TVec3F{0,0,0});
        mKarts[i]->setScale(TVec3F{0.6f, 0.6f, 0.6f});
        mKarts[i]->setMesh(car_body_Cube3_mesh);
        mKarts[i]->setParent(mFloors[i]);

        // initialize tires
        for (s32 j = 0; j < 4; ++j) {
            mWheels[i][j] = new TKartObject(mDynList);
            mWheels[i][j]->init();
            mWheels[i][j]->setPosition(TVec3F{0.0f,0.0f,0.0f});
            mWheels[i][j]->setMesh(wheel_Cube1_sep23_mesh);
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

    // choose player sprite
    mChPlayerSpr.load(choose_sprite);
    mChPlayerSpr.setPosition(TVec2S{15, 0});

    mChooseTimer.start(1.5f);
}

void TSelectKartScene::update()
{
    mCamera->update();
    mChooseTimer.update();

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

    s16 y = Lagrange<s16>(20, 50, 10, mChooseTimer.get());
    mChPlayerSpr.setPosition(TVec2S{(s16)15, y});

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
    //mChPlayerSpr.init(mDynList)
    mChPlayerSpr.draw();
}

TScene * TSelectKartScene::exit()
{
    return new TSelectKartScene { "fuck", mDynList };
}