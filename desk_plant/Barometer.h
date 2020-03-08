#ifndef Barometer_H
#define Barometer_H

#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

class Barometer {

    private:
        Adafruit_BME280 barometer_{};
    public:
        void begin();
        long getPressure();
};

#endif