#include "TriColorLED.h"
#include "LightSensor.h"
#include "Barometer.h"

// The light will only be on when it is light out
const int MODE_LIGHT_ON = 0;

// The light will only be on when it is dark out
const int MODE_DARK_ON = 1;

// The light will always be on
const int MODE_ALWAYS_ON = 2;


// ----- CONFIGURATION -----

// Change this value to adjust how long it will take for the plant to adapt to the local pressure
const long adaptedThreshold = 800L; // 8 hPa

// Change these values to adjust the default high and low pressures
const long defaultMinPressure = 100500L; // 1005 hPa
const long defaultMaxPressure = 101800L; // 1018 hPa

// Change this to control when the plant's light will be on
const byte onStrategy = MODE_LIGHT_ON;

// The altitude of the plant in meters
const float altitudeMeters = 30.48;

// ----- END CONFIGURATION -----


TriColorLED led{5, 3, 2};
LightSensor lightSensor{A0};
Barometer barometer{altitudeMeters};

// The min/max seen pressures
long minPressure = 1000000L;
long maxPressure = 0L;

void setup() {  
  Serial.begin(9600);
  barometer.begin();
  long pressure = barometer.getPressure();
  adaptToPressure(pressure);
}

void loop() {
  long pressure = barometer.getPressure();
  adaptToPressure(pressure);

  Serial.println(pressure / 100.0f);

  long actualMinPressure = min(minPressure, defaultMinPressure);
  long actualMaxPressure = max(maxPressure, defaultMaxPressure);

  if (isAdapted()){
    actualMinPressure = minPressure;
    actualMaxPressure = maxPressure;  
  }
  
  if (shouldBeOff()){
    led.off();  
  } else {
    int pressureAmount = (int)map(pressure, actualMinPressure, actualMaxPressure, 0, 255);
    setColor(pressureAmount);
  }
}

bool shouldBeOff(){
  switch (onStrategy){
    case MODE_DARK_ON:
      return lightSensor.isLight();
    case MODE_LIGHT_ON:
      return lightSensor.isDark();
    default:
      return false;
  }
}

void adaptToPressure(long pressure){
  minPressure = min(pressure, minPressure);
  maxPressure = max(pressure, maxPressure);
}

bool isAdapted(){
  return maxPressure - minPressure >= adaptedThreshold;
}

void setColor(int amount){
  int r = 255 - amount;
  int g = amount;
  led.on(r, g, 0);  
}
