#include "Barometer.h"

Barometer::Barometer(float altitudeMeters){
    altitudeMeters_ = altitudeMeters;
}

void Barometer::begin(){
    while(!barometer_.begin(0x76));
}

long Barometer::getPressure(){

    float pressure = barometer_.readPressure() / 100.0;
    float seaLevelPressure = barometer_.seaLevelForAltitude(altitudeMeters_, pressure);

    return (long)round(seaLevelPressure * 100);
}