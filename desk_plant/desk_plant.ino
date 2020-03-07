#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "TriColorLED.h"
#include "LightSensor.h"

Adafruit_BME280 barometer{};
TriColorLED led{5, 3, 2};
LightSensor light_sensor{A0};

#define ADAPTIVE_PRESSURE true

long min_pressure;
long max_pressure;

void setup() {  
  while(!barometer.begin(0x76));

  long pressure = GetPressure();
  if (ADAPTIVE_PRESSURE){
    min_pressure = pressure - 100L;
    max_pressure = pressure + 100L;
  } else {
    min_pressure = 99000L;
    max_pressure = 101000L;  
  }
}

void loop() {
  long pressure = GetPressure();
  min_pressure = min(pressure, min_pressure);
  max_pressure = max(pressure, max_pressure);
  
  if (light_sensor.IsDark()){
    led.Off();  
  } else {
    int pressure_amount = (int)map(pressure, min_pressure, max_pressure, 0, 255);
    SetColor(pressure_amount);
  }
}

long GetPressure(){
  return (long)round(barometer.readPressure());  
}

void SetColor(int amount){
  int r = 255 - amount;
  int g = amount;
  led.On(r, g, 0);  
}
