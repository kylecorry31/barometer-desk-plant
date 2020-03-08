#include "TriColorLED.h"

TriColorLED::TriColorLED(int r_pin, int g_pin, int b_pin){
  r_ = r_pin;
  g_ = g_pin;
  b_ = b_pin; 

  pinMode(r_, OUTPUT);
  pinMode(g_, OUTPUT);
  pinMode(b_, OUTPUT);
}

void TriColorLED::on(int r, int g, int b){
  analogWrite(r_, r);
  analogWrite(g_, g);
  analogWrite(b_, b);  
}

void TriColorLED::off(){
  on(0, 0, 0);  
}
