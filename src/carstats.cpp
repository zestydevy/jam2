#include "math.hpp"
#include "carstats.hpp"

int TCarStats::calcGear(f32 speed, f32* speeds){
    for (int i = 0; i < 4; i++){
        if (speed < speeds[i])
            return i;
    }
    return NUM_GEARS;
}
f32 TCarStats::calcStatTransition(f32 speed, f32* speeds){
    if (speed < 0.0f)
        speed = 0.0f;

    int gear = calcGear(speed, speeds);

    if (gear <= 0)
        return 0.0f;
    if (gear >= NUM_GEARS)
        return 1.0f;
    
    float low = speeds[gear - 1];
    float high = speeds[gear];

    float t = (speed - low) / (high - low);

    return t;
}
f32 TCarStats::calcStat(f32 speed, f32* speeds, f32* stat){
    if (speed < 0.0f)
        speed = 0.0f;

    int gear = calcGear(speed, speeds);

    if (gear <= 0)
        return stat[0];
    if (gear >= NUM_GEARS)
        return stat[NUM_GEARS - 1];
    
    float low = speeds[gear - 1];
    float high = speeds[gear];

    float t = (speed - low) / (high - low);

    return ((1.0f - t) * stat[gear - 1]) + (t * stat[gear]);
}

t_carstatdata sTestCar{
    100.0f,                 200.0f,                 600.0f,                 1200.0f,     //Gear Speeds
    200.0f,                 120.0f,                 100.0f,                 0.0f,       //Accelerations
    0.992f,                 0.994f,                 0.996f,                 0.998f,      //Drift Rates
    0.96f,                  0.97f,                  0.99f,                  0.992f,      //Brake Rates
    1.0f,                   0.8f,                   0.18f,                  0.08f,       //Turn Rates
    0.999f,                 0.999f,                 0.999f,                 0.998f      //Turn Energy Conversion Rates
};