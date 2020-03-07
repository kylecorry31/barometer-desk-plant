#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "TriColorLED.h"
#include "LightSensor.h"

Adafruit_BME280 barometer{};
TriColorLED led{2, 3, 4};
LightSensor light_sensor{A0};

long min_pressure;
long max_pressure;

void setup() {
  while(!barometer.begin(0x76));

  long pressure = GetPressure();
  min_pressure = pressure - 100L;
  max_pressure = pressure + 100L;
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
  int r = min(255, 255 - amount + 125);
  int g = amount;
  led.On(r, g, 0);  
}
