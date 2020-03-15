#ifndef Barometer_H
#define Barometer_H

// Uncomment this line if using on the Arduino Nano BLE Sense
//#define Arduino_BLE

#include <Arduino.h>

#ifndef Arduino_BLE
#include <Adafruit_BME280.h>
#endif

#ifdef Arduino_BLE
#include <Arduino_LPS22HB.h>
#endif

class Barometer {
    public:
        Barometer(float altitudeMeters);
        void begin();
        long getPressure();
    private:
        #ifndef Arduino_BLE
        Adafruit_BME280 barometer_{};
        #endif        
        float altitudeMeters_;
        float seaLevelForAltitude(float altitude, float pressure);
};

#endif
