#ifndef Tri_Color_LED_H
#define Tri_Color_LED_H

#include <Arduino.h>

class TriColorLED {

  private:
    int r_;
    int g_;
    int b_;

  public:
    TriColorLED(int r_pin, int g_pin, int b_pin);
    void on(int r, int g, int b);
    void off();
};

#endif
