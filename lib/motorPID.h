#include "Arduino.h"
#include <FastPID.h>

#ifndef Motor_h
#define Motor_h

class motorPID
{
  public:
    motorPID(int dirPin1,int dirPin2,int spdPin,
            int encoderAPin,int encoderBpin);
    void drive(int speed);

  private:
    const int dirPin1;
    const int dirPin2;
    const int spdPin;
    const int encoderAPin;
    const int encoderBpin;
    volatile int encoderCounter;
    FastPID myPID;

}


#endif