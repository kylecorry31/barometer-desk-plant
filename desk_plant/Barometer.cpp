#include "Barometer.h"

void Barometer::begin(){
    while(!barometer_.begin(0x76));
}

long Barometer::getPressure(){
    return (long)round(barometer_.readPressure());
}