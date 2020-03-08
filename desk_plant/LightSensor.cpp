#include "LightSensor.h"

LightSensor::LightSensor(int pin){
  pin_ = pin;
  pinMode(pin_, INPUT);  
}

bool LightSensor::isDark(){
  return getLight() < 400;  
}

bool LightSensor::isLight(){
  return !isDark();  
}

int LightSensor::getLight(){
  return analogRead(pin_);  
}
