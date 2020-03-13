#include "Arduino.h"
#include "MotorPID.h"
#include <FastPID.h>

#define KP 254
#define KI 10
#define KD 20

motorPID::motorPID(int dirPin1,int dirPin2,int spdPin,int encoderAPin,int encoderBpin)
{

  this.dirPin1     = dirPin1    ;
  this.dirPin2     = dirPin2    ;
  this.spdPin      = spdPin     ;
  this.encoderAPin = encoderAPin;
  this.encoderBpin = encoderBpin;
    //settup pins
  pinMode(this.dirPin1,OUTPUT);
  pinMode(this.dirPin2,OUTPUT);
  pinMode(this.spdPin,OUTPUT);
  pinMode(this.encoderAPin,INPUT);
  pinMode(this.encoderBpin,INPUT);
  
  //register encoder interupt
  attachInterrupt(digitalPinToInterrupt(this.encoderAPin), +[](int this.encoderAPin){ motorEncoderISR(encoderAPin); }, CHANGE);


  //settup PID controller
  FastPID myPID(KP, KI, KD, 10, 8, true);
  
  if (myPID.err()) 
    Serial1.println("There is a configuration error!");

  encoderCounter = 0;
}

void motorEncoderISR(int pin)
{
  if(digitalRead(rightB) == digitalRead(rightA))
    {
      encoderRightCounter --;
    }
    else
    {
      encoderRightCounter ++;
    }
}