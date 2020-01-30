#include "Arduino.h"

#ifndef Motor_h
#define Motor_h



class motor
{
  public:
    motor(int pin, int pin2, int spd_pin);
    void forward (int speed);
    void backward(int speed);
    void stop();

  private:
    int_pin;
    int_pin2;
    int_spd_pin;
    
};

#endif
