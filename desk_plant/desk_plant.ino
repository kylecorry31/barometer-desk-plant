#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "TriColorLED.h"
#include "LightSensor.h"

Adafruit_BME280 barometer{};
TriColorLED led{2, 3, 4};
LightSensor light_sensor{A0};

long min_pressure = 99000L;
long max_pressure = 101000L;

void setup() {
  Serial.begin(9600);

  while(!barometer.begin(0x76));
}

void loop() {
  long pressure = (long)round(barometer.readPressure());
  min_pressure = min(pressure, min_pressure);
  max_pressure = max(pressure, max_pressure);

  Serial.print(min_pressure);
  Serial.print(',');
  Serial.println(max_pressure);
  
  if (light_sensor.IsDark()){
    led.Off();  
  } else {
    int pressure_amount = (int)map(pressure, min_pressure, max_pressure, 0, 255);
    SetColor(pressure_amount);
  }
}

void SetColor(int amount){
  int r = min(255, 255 - amount + 125);
  int g = amount;
  led.On(r, g, 0);  
}
