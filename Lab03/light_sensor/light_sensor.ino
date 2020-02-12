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

//sonar pin config
 #define Echo_PIN    31 // Ultrasonic Echo pin connect to A5
 #define Trig_PIN    30  // Ultrasonic Trig pin connect to A4

//robot driving parameters
#define SPEED 100
#define TURN_SPEED 90

//robot control pin config
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

//constants for the light sensor
#define LIGHT_SENSOR_LEFT A10
#define LIGHT_SENSOR_CENTER A9
#define LIGHT_SENSOR_RIGHT A8

#define THRESHOLD_LEFT 850
#define THRESHOLD_CENTER 900
#define THRESHOLD_RIGHT 900

//initialise the robot control library
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
    //Serial1.println((int)echo_distance);
    return round(echo_distance);
}
 
 void setup() { 
   pinMode (rightA,INPUT);
   pinMode (rightB,INPUT);
   pinMode (leftA,INPUT);
   pinMode (leftB,INPUT);

  pinMode (Trig_PIN,OUTPUT);
  pinMode (Echo_PIN,INPUT);

  pinMode(LIGHT_SENSOR_LEFT, INPUT);
  pinMode(LIGHT_SENSOR_CENTER, INPUT);
  pinMode(LIGHT_SENSOR_RIGHT, INPUT);
   
   Serial1.begin(9600);
   attachInterrupt(digitalPinToInterrupt(rightA), EncoderRightISR, CHANGE);
   attachInterrupt(digitalPinToInterrupt(leftA), EncoderLeftISR, CHANGE);

 } 
 
 void loop() 
 { 
  Serial1.print("Left: ");
  int left = analogRead(LIGHT_SENSOR_LEFT);
  Serial1.print(left);
  if(left > THRESHOLD_LEFT)
    Serial1.print(", 1");
    else
    Serial1.print(", 0");

  Serial1.print(" Center: ");
  int center = analogRead(LIGHT_SENSOR_CENTER);
  Serial1.print(center);
  if(center > THRESHOLD_CENTER)
    Serial1.print(", 1");
    else
    Serial1.print(", 0");

  Serial1.print(" Right: ");
  int right = analogRead(LIGHT_SENSOR_RIGHT);
  Serial1.print(right);
  if(right > THRESHOLD_RIGHT)
    Serial1.println(", 1");
    else
    Serial1.println(", 0");

  delay(2000);
 }




 
