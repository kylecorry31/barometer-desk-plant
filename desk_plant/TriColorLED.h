#ifndef Tri_Color_LED_H
#define Tri_Color_LED_H

#include <Arduino.h>

class TriColorLED {

  private:
    int _r;
    int _g;
    int _b;

  public:
    TriColorLED(int r_pin, int g_pin, int b_pin);
    void On(int r, int g, int b);
    void Off();
};

#endif
