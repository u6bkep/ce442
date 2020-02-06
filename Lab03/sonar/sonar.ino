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
 int flag = 0;

 #define Echo_PIN    31 // Ultrasonic Echo pin connect to A5
 #define Trig_PIN    30  // Ultrasonic Trig pin connect to A4

 #define SPEED 100
#define TURN_SPEED 90

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
  
    if(digitalRead(rightB) == digitalRead(rightA))
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
   if(digitalRead(leftB) == digitalRead(leftA))
    {
      encoderLeftCounter ++;
    }
    else
    {
      encoderLeftCounter --;
    }
    
 }

 int sonarDistance()
{
    long echo_distance;
    digitalWrite(Trig_PIN,LOW);
    delayMicroseconds(5);
    digitalWrite(Trig_PIN,HIGH);
    delayMicroseconds(15);
    digitalWrite(Trig_PIN,LOW);
    echo_distance=pulseIn(Echo_PIN,HIGH);
    echo_distance=echo_distance*0.01657; //how far away is the object in cm
    //Serial.println((int)echo_distance);
    return round(echo_distance);
}
 
 void setup() { 
   pinMode (rightA,INPUT);
   pinMode (rightB,INPUT);
   pinMode (leftA,INPUT);
   pinMode (leftB,INPUT);

  pinMode (Trig_PIN,OUTPUT);
  pinMode (Echo_PIN,INPUT);
   
   Serial.begin(9600);
   attachInterrupt(digitalPinToInterrupt(rightA), EncoderRightISR, CHANGE);
   attachInterrupt(digitalPinToInterrupt(leftA), EncoderLeftISR, CHANGE);

 } 
 void loop() { 
  /*
  Serial.print("Position left: ");
  Serial.print(encoderLeftCounter);
  Serial.print(",  Position right: ");
  Serial.println(encoderRightCounter);
  */
  //Serial.print("distance: ");
  //Serial.print(sonarDistance());
  //Serial.println("cm");
  //delay(1000);

  if(sonarDistance() < 24)
  {
    flag = random(0,2);
    if(flag)
    {
      //turn right
      robot.rotateCCW(TURN_SPEED);
      delay(1000);
    }
    else
    {
      //turn left
      robot.rotateCW(TURN_SPEED);
      delay(1000);
    }
  }
  else
  {
    robot.forward(SPEED);
  }
 }
