#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "TriColorLED.h"
#include "LightSensor.h"

Adafruit_BME280 barometer{};
TriColorLED led{5, 3, 2};
LightSensor light_sensor{A0};

const long adapted_threshold = 800L; // 8 hPa

long default_min_pressure = 99500L; // 995 hPa
long default_max_pressure = 101800L; // 1018 hPa

long min_pressure;
long max_pressure;

void setup() {  
  while(!barometer.begin(0x76));

  long pressure = GetPressure();
  min_pressure = pressure;
  max_pressure = pressure;
}

void loop() {
  long pressure = GetPressure();
  min_pressure = min(pressure, min_pressure);
  max_pressure = max(pressure, max_pressure);

  long actual_min_pressure = min(min_pressure, default_min_pressure);
  long actual_max_pressure = max(max_pressure, default_max_pressure);

  if (max_pressure - min_pressure >= adapted_threshold){
    // Plant has adapted to environment
    actual_min_pressure = min_pressure;
    actual_max_pressure = max_pressure;  
  }
  
  if (light_sensor.IsDark()){
    led.Off();  
  } else {
    int pressure_amount = (int)map(pressure, actual_min_pressure, actual_max_pressure, 0, 255);
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
