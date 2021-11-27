#include "select.hpp"
#include "carstats.hpp"

#include "../models/static/floor/model_floor.h"
#include "../models/static/car/model_car.h"
#include "../data/tire.h"

void TSelectKartScene::init()
{
    mStatus = ESceneState::RUNNING;

    for (s32 i = 0; i < 4; ++i)
    {
        // initialize floors
        mFloors[i] = new TObject(mDynList);
        mFloors[i]->setPosition(TVec3F{0,-8,0});
        mFloors[i]->setScale(TVec3F{0.5f, 0.5f, 0.5f});
        mFloors[i]->setMesh(floor_Plane_mesh);

        //initialize karts
        mPlayers[i] = new TObject(mDynList);
        mPlayers[i]->setPosition(TVec3F{0,0,0});
        mPlayers[i]->setScale(TVec3F{0.4f, 0.4f, 0.4f});
        mPlayers[i]->setMesh(player00_Cube1_008_mesh);
        mPlayers[i]->setParent(mFloors[i]);
        mKarts[i] = new TObject(mDynList);
        mKarts[i]->setPosition(TVec3F{0,0,0});
        mKarts[i]->setScale(TVec3F{0.4f, 0.4f, 0.4f});
        mKarts[i]->setMesh(car_body_Cube3_mesh);
        mKarts[i]->setParent(mFloors[i]);

        // initialize tires
        for (s32 j = 0; j < 4; ++j) {
            mWheels[j][i] = new TKartObject(mDynList);
            mWheels[j][i]->setPosition(TVec3F{0,0,0});
            mWheels[j][i]->setMesh(car_body_Cube3_mesh);
            mWheels[j][i]->setParent(mKarts[i]);
        }

        auto config = reinterpret_cast<TTireConfig const &>(sTireConfig00);
        TTireConfig::loadConfig(&mWheels[0][i], const_cast<TTireConfig &>(config));

        //initialize pads
        mPads[i] = new TPad(i);
    }

    mCamera = new TCamera(mDynList);
    mCamera->setPad(mPads[0]);      // assign pad one to camera
    mCamera->setTarget(&mViewOrigin);
}

void TSelectKartScene::update()
{
    mCamera->update();

    for (s32 i = 0; i < mPlayerCount; ++i)
    {
        mFloors[i]->update();
        mPlayers[i]->update();  
        mPads[i]->read();
        mKarts[i]->update();

        for (s32 j = 0; j < 4; ++j) {
            mWheels[j][i]->update();
        }

    }
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
            mWheels[j][i]->draw();
        }
    }
    //gSPDisplayList(mDynList->pushDL(), letters_setup_dl);
}

void TSelectKartScene::draw2D()
{
    //mChPlayerSpr.init(mDynList)
}

TScene * TSelectKartScene::exit()
{
    return new TSelectKartScene { "fuck", mDynList };
}