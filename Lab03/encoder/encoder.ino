/*
 * How to test encoder with Arduino
 * url: http://osoyoo.com/?p=30267
 */

#include "Robot.h"
 
 #define rightA 20
 #define rightB 34
 #define leftA 21
 #define leftB 32
 int counter = 0; 
 int aState;
 int aLastState;  
 volatile int encoderRightCounter = 0;
 volatile int encoderLeftCounter = 0;

 #define SPEED 50
#define TURN_SPEED 160

#define frontRightdirpin1  22
#define frontRightdirpin2  24
#define frontRightspdpin 9

#define frontLeftdirpin1  26
#define frontLeftdirpin2  28
#define frontLeftspdpin  10

#define rearRightdirpin1  5
#define rearRightdirpin2  6
#define rearRightspdpin  11

#define rearLeftdirpin1  7
#define rearLeftdirpin2  8
#define rearLeftspdpin  12

Robot robot(frontLeftdirpin1, frontLeftdirpin2, frontLeftspdpin, frontRightdirpin1, frontRightdirpin2, frontRightspdpin,
            rearLeftdirpin1, rearLeftdirpin2, rearLeftspdpin, rearRightdirpin1, rearRightdirpin2, rearRightspdpin);

 void EncoderRightISR()
 {
    if(digitalRead(rightB))
    {
      encoderRightCounter --;
    }
    else
    {
      encoderRightCounter ++;
    }
    
 }

 void EncoderLeftISR()
 {
   if(digitalRead(leftB))
    {
      encoderLeftCounter ++;
    }
    else
    {
      encoderLeftCounter --;
    }
    
 }
 
 void setup() { 
   pinMode (rightA,INPUT);
   pinMode (rightB,INPUT);
   pinMode (leftA,INPUT);
   pinMode (leftB,INPUT);

   attachInterrupt(digitalPinToInterrupt(rightA), EncoderRightISR, RISING);
   attachInterrupt(digitalPinToInterrupt(leftA), EncoderLeftISR, RISING);
 
   Serial.begin(9600);

   //FIRST SIDE
  robot.forward(SPEED);
  delay(3000);
  robot.stop();
  delay(1000);

  robot.right_turn(SPEED);
  delay(1400);
  robot.stop();
  delay(1000); 
 } 
 void loop() { 
   
    Serial.print("Position left: ");
     Serial.print(encoderLeftCounter, HEX);
     Serial.print(",  Position right: ");
     Serial.println(encoderRightCounter, HEX);

     
     delay(1000);
 }
