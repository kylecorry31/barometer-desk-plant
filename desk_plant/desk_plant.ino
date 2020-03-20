#include "TriColorLED.h"
#include "LightSensor.h"
#include "Barometer.h"

// ----- CONFIGURATION -----

// Change these values to adjust the default high and low pressures
const long minPressure = 100900L; // 1009 hPa
const long maxPressure = 102200L; // 1022 hPa

// The altitude of the plant in meters
const float altitudeMeters = 126;//36;

// The maximum brightness when it is dark out
const int maxNightBrightness = 0;

// The maximum brightness when it is light out
const int maxDayBrightness = 255;

// ----- END CONFIGURATION -----


TriColorLED led{5, 3, 6};
LightSensor lightSensor{A0};
Barometer barometer{altitudeMeters};

void setup() {  
  Serial.begin(9600);
  barometer.begin();
}

void loop() {
  long pressure = barometer.getPressure();

  Serial.println(pressure / 100.0f);

  int maxBrightness = 0;

  if (lightSensor.isLight()){
    maxBrightness = maxDayBrightness;
  } else {
    maxBrightness = maxNightBrightness;
  }

  int pressureAmount = min(maxBrightness, max(0, (int)map(pressure, minPressure, maxPressure, 0, maxBrightness)));
  setColor(pressureAmount, maxBrightness);
}

void setColor(int amount, int maxBrightness){
  int r = maxBrightness - amount;
  int g = amount;
  led.on(r, g, 0);  
}
