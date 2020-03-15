#include "Barometer.h"

Barometer::Barometer(float altitudeMeters){
    altitudeMeters_ = altitudeMeters;
}

void Barometer::begin(){
    #ifndef Arduino_BLE
    while(!barometer_.begin(0x76));
    #endif
    
    #ifdef Arduino_BLE
    BARO.begin();
    #endif
}

long Barometer::getPressure(){

    #ifndef Arduino_BLE
    float pressure = barometer_.readPressure() / 100.0;;
    #endif
    
    #ifdef Arduino_BLE
    float pressure = BARO.readPressure() * 10.0;
    #endif

    float seaLevelPressure = seaLevelForAltitude(altitudeMeters_, pressure);

    return (long)round(seaLevelPressure * 100);
}

float Barometer::seaLevelForAltitude(float altitude, float pressure){
    // Taken from https://github.com/adafruit/Adafruit_BME280_Library/blob/master/Adafruit_BME280.cpp
    return pressure / pow(1.0 - (altitude / 44330.0), 5.255);
}
