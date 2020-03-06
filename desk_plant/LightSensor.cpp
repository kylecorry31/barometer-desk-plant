#include "LightSensor.h"

LightSensor::LightSensor(int pin){
  pin_ = pin;
  pinMode(pin_, INPUT);  
}

bool LightSensor::IsDark(){
  return GetLight() < 500;  
}

bool LightSensor::IsLight(){
  return !IsDark();  
}

int LightSensor::GetLight(){
  return analogRead(pin_);  
}
