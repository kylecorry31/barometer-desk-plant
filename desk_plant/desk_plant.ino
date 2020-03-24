#include "TriColorLED.h"
#include "LightSensor.h"
#include "Barometer.h"

// ----- CONFIGURATION -----

// Change these values to adjust the default high and low pressures
const long minPressure = -600L; // -6 hPa / 3 hr
const long maxPressure = 600L; // 6 hPa / 3 hr

// The maximum brightness when it is dark out
const int maxNightBrightness = 0;

// The maximum brightness when it is light out
const int maxDayBrightness = 255;

// ----- END CONFIGURATION -----

#define HISTORY_LENGTH 180

long history[HISTORY_LENGTH];
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
  historySize++;
  historyIdx++;
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

  if (millis() - lastTime >= 60000L){
    historySize++;
    historySize %= HISTORY_LENGTH; 
  }

  long first;
  
  if (historySize == HISTORY_LENGTH){
    // Already full
    first = history[(historyIdx + 1) % HISTORY_LENGTH];
  } else {
    first = history[0];
  }

  if (millis() - lastTime >= 60000L){
    historyIdx++;
    historyIdx %= HISTORY_LENGTH;
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
