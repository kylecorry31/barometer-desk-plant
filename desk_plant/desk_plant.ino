#include "TriColorLED.h"
#include "LightSensor.h"
#include "Barometer.h"

// ----- CONFIGURATION -----

// Change these values to adjust the default high and low pressures
const long minPressure = -300L; // -3 hPa / 3 hr
const long maxPressure = 300L; // 3 hPa / 3 hr

// The maximum brightness when it is dark out
const int maxNightBrightness = 0;

// The maximum brightness when it is light out
const int maxDayBrightness = 255;

const long updateInterval = 60L * 1000L;
const int historyLength = 180;

// ----- END CONFIGURATION -----

long history[historyLength];
int historySize = 0;
int historyIdx = 0;

long lastTime = 0;

TriColorLED led{5, 3, 6};
LightSensor lightSensor{A0};
Barometer barometer{};

void setup() {  
  Serial.begin(9600);
  barometer.begin();
  history[0] = barometer.getPressure();
  historySize = 1;
  historyIdx = 0;
  lastTime = millis();
}

void loop() {
  long pressure = barometer.getPressure();

  int maxBrightness = 0;

  if (lightSensor.isLight()){
    maxBrightness = maxDayBrightness;
  } else {
    maxBrightness = maxNightBrightness;
  }

  long first;
  
  if (historySize == historyLength){
    // Already full
    first = history[(historyIdx + 1) % historyLength];
  } else {
    first = history[0];
  }

  if (millis() - lastTime >= updateInterval){
    historySize++;
    historySize = min(historySize, historyLength); 
    historyIdx++;
    historyIdx %= historyLength;
    history[historyIdx] = pressure;
    lastTime = millis();
  }

  long tendency = pressure - first;

  Serial.println(tendency);
  
  int pressureAmount = min(maxBrightness, max(0, (int)map(tendency, minPressure, maxPressure, 0, maxBrightness)));
  setColor(pressureAmount, maxBrightness);  
}



void setColor(int amount, int maxBrightness){
  int r = maxBrightness - amount;
  int g = amount;
  led.on(r, g, 0);  
}
