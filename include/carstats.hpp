#pragma once

#include <nusys.h>
#include "util.hpp"

#define NUM_GEARS 4
#define NUM_STATS 5

typedef const f32 t_carstatdata[NUM_GEARS * (1 + NUM_STATS)];

class TCarStats {
    public:
    TCarStats( ){
    };
    TCarStats(  t_carstatdata data ){
        int i = 0;

        mGearSpeeds[0] = data[i++];
        mGearSpeeds[1] = data[i++];
        mGearSpeeds[2] = data[i++];
        mGearSpeeds[3] = data[i++];

        mAcceleration[0] = data[i++];
        mAcceleration[1] = data[i++];
        mAcceleration[2] = data[i++];
        mAcceleration[3] = data[i++];

        mDriftRate[0] = data[i++];
        mDriftRate[1] = data[i++];
        mDriftRate[2] = data[i++];
        mDriftRate[3] = data[i++];

        mBrakeRate[0] = data[i++];
        mBrakeRate[1] = data[i++];
        mBrakeRate[2] = data[i++];
        mBrakeRate[3] = data[i++];

        mTurnRate[0] = data[i++];
        mTurnRate[1] = data[i++];
        mTurnRate[2] = data[i++];
        mTurnRate[3] = data[i++];

        mTurnEnergyConversion[0] = data[i++];
        mTurnEnergyConversion[1] = data[i++];
        mTurnEnergyConversion[2] = data[i++];
        mTurnEnergyConversion[3] = data[i++];
    };

    inline int getGear(f32 speed){
        return calcGear(speed, mGearSpeeds);
    };
    inline f32 getAcceleration(f32 speed){
        return calcStat(speed, mGearSpeeds, mAcceleration);
    };
    inline f32 getDrift(f32 speed){
        return calcStat(speed, mGearSpeeds, mDriftRate);
    };
    inline f32 getBrake(f32 speed){
        return calcStat(speed, mGearSpeeds, mBrakeRate);
    };
    inline f32 getTurn(f32 speed){
        return calcStat(speed, mGearSpeeds, mTurnRate);
    };
    inline f32 getTurnConversion(f32 speed){
        return calcStat(speed, mGearSpeeds, mTurnEnergyConversion);
    };

    private:
    f32 mGearSpeeds[NUM_GEARS];                     //Speed of each gear
    f32 mAcceleration[NUM_GEARS];               //acceration
    f32 mDriftRate[NUM_GEARS];                  //slow down when no button pressed
    f32 mBrakeRate[NUM_GEARS];                  //slow down when brake pressed
    f32 mTurnRate[NUM_GEARS];                   //turn rate per unit travelled
    f32 mTurnEnergyConversion[NUM_GEARS];       //turn rate per unit travelled

    int calcGear(f32 speed, f32* speeds);
    f32 calcStat(f32 speed, f32* speeds, f32* stat);
};

extern t_carstatdata testCar;