#ifndef Barometer_H
#define Barometer_H

#include <Arduino.h>

#include <Adafruit_BME280.h>

class Barometer {
    public:
        Barometer(float altitudeMeters);
        void begin();
        long getPressure();
    private:
        Adafruit_BME280 barometer_{};
        float altitudeMeters_;
};

#endif
