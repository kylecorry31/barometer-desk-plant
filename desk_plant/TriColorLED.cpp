#include "TriColorLED.h"

TriColorLED::TriColorLED(int r_pin, int g_pin, int b_pin){
  _r = r_pin;
  _g = g_pin;
  _b = b_pin; 

  pinMode(_r, OUTPUT);
  pinMode(_g, OUTPUT);
  pinMode(_b, OUTPUT);
}

void TriColorLED::On(int r, int g, int b){
  analogWrite(_r, r);
  analogWrite(_g, g);
  analogWrite(_b, b);  
}

void TriColorLED::Off(){
  On(0, 0, 0);  
}
