#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


#define STEADY 2
#define DOWN 3
#define UP 4
#define MIN_CHANGE 0.1
#define MIN_PRESSURE 990
#define MAX_PRESSURE 1040

const unsigned long interval = 1000UL * 60UL * 2UL;
unsigned long previousMillis = 0;

Adafruit_BME280 _bme{};

float last_reading = -1;
int last_direction = -1;

void setup() {
  pinMode(STEADY, OUTPUT);
  pinMode(DOWN, OUTPUT);
  pinMode(UP, OUTPUT);
  pinMode(A0, INPUT);

  Serial.begin(9600);

  while(!_bme.begin(0x76));

  last_reading = _bme.readPressure() / 100.0F;
  digitalWrite(STEADY, HIGH);
  digitalWrite(UP, HIGH);
  digitalWrite(DOWN, HIGH);
}

void loop() {

  if (analogRead(A0) < 500)
  {
    digitalWrite(STEADY, LOW); 
    digitalWrite(UP, LOW); 
    digitalWrite(DOWN, LOW); 
  } else 
  {
    digitalWrite(last_direction, HIGH);
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    run();
  }
}


void run() {
  float pressure = _bme.readPressure() / 100.0F;

  int direction;

  float change = pressure - last_reading;

  if (change < -MIN_CHANGE){
    direction = DOWN;
  } else if (change > MIN_CHANGE){
    direction = UP;  
  } else {
    direction = STEADY;  
  }

  if (direction != last_direction)
  {
    digitalWrite(STEADY, LOW); 
    digitalWrite(UP, LOW); 
    digitalWrite(DOWN, LOW);  
  }

  last_reading = pressure;
  last_direction = direction; 
}
