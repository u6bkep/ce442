#include "Arduino.h"

#ifndef Motor_h
#define Motor_h



class Motor
{
  public:
    Motor(int pin, int pin2, int spd_pin);
    void forward (int speed);
    void backward(int speed);
    void stop();

  private:
    int _pin;
    int _pin2;
    int _spd_pin;
    
};

#endif
