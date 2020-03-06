#ifndef Light_Sensor_H
#define Light_Sensor_H

#include <Arduino.h>

class LightSensor {

  private:
    int pin_;
  
  public:
    LightSensor(int pin);
    bool IsLight();
    bool IsDark();
    int GetLight();
  
};

#endif
