#include "carstats.hpp"

int TCarStats::calcGear(f32 speed, f32* speeds){
    for (int i = 0; i < 4; i++){
        if (speed < speeds[i])
            return i;
    }
    return 3;
}
f32 TCarStats::calcStat(f32 speed, f32* speeds, f32* stat){
    if (speed < 0.0f)
        speed = 0.0f;

    int gear = calcGear(speed, speeds);
    int nextGear = gear + 1;
    if (gear >= 3)
        return stat[3];
    
    float low = 0.0f;
    float high = speeds[gear];
    if (gear >= 1)
        low = speeds[gear - 1];

    float diff = (speed - low) / (high - low);

    return ((1.0f - diff) * stat[gear]) + (diff * stat[nextGear]);
}

const t_carstatdata testCar{
    100.0f,                 400.0f,                 800.0f,                 1000.0f,    //Gear Speeds
    100.0f,                 500.0f,                 200.0f,                 0.0f,       //Accelerations
    0.99f,                  0.99f,                  0.9925f,                0.995f,     //Drift Rates
    0.97f,                  0.97f,                  0.96f,                  0.96f,      //Brake Rates
    1.0f,                   1.0f,                   0.5f,                   0.005f,     //Turn Rates
    1.0f,                   1.0f,                   1.0f,                   0.99f       //Turn Energy Conversion Rates
};