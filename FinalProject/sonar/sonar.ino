/*
 * How to test encoder with Arduino
 * url: http://osoyoo.com/?p=30267
 */

#include "Robot.h"
//#include <//servo.h>

////servo //servo;
 
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
int dir;
int firstTime = 1;
int distance = 0;

#define Echo_PIN    31 // Ultrasonic Echo pin connect to A5
#define Trig_PIN    30  // Ultrasonic Trig pin connect to A4

int SPEED = 80;
int TURN_SPEED = 60;
int kVar = 15;
int error = 0;

#define frontRightdirpin1  22
#define frontRightdirpin2  24
#define frontRightspdpin 9

#define frontLeftdirpin1  26
#define frontLeftdirpin2  2
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
   Serial1.begin(9600);
   attachInterrupt(digitalPinToInterrupt(rightA), EncoderRightISR, CHANGE);
   attachInterrupt(digitalPinToInterrupt(leftA), EncoderLeftISR, CHANGE);
   ////servo.attach(13);
   ////servo.write(0);
   delay(1000);
   ////servo.write(180);
   delay(1000);
   ////servo.write(90);
   delay(3000);

 } 

struct Cord
{
  int x;
  int y;
  int r; 
};

struct Cord getSerialString()
{
  Cord a;
  a.x = Serial.parseInt();
  a.y = Serial.parseInt();
  a.r = Serial.parseInt();
  Serial1.println(a.r);
  return a;
}
 
 void loop() { 

Cord distance;
int state = 0;

#define R_LOW 40
#define R_HIGH 50

while(true)
{
  
  distance = getSerialString();
  
  if((distance.r == 0) || (distance.r > R_LOW) && (distance.r < R_HIGH))
    state = 0;
  else if(distance.r >= R_HIGH)
    state = 1;
  else if(distance.r < R_LOW)
    state = 2;

  if((state != 0) && distance.x >250)
    state = 3;
  else if((state != 0) && distance.x < 100)
    state = 4;

  switch(state)
  {
    case 0:
    robot.stop();
    
    break;
    case 1:
      SPEED = (45 - distance.r)*kVar;
      robot.backward(SPEED);
      break;
    case 2:
      SPEED = (45 - distance.r)*kVar;
      robot.forward(SPEED);
      break;
    case 3:
      robot.rotateCW(25);
      break;
    case 4:
      robot.rotateCCW(25);
      break;
  }
}
  /*
  robot.forward(SPEED);

  //Serial.write('n');
  distance = getSerialString();
  error = 50-distance;
  SPEED = error*kVar;
  while(distance > 50)
  {
    robot.forward(SPEED);
    //Serial.write('n');
    distance = getSerialString();
    
    error = 50-distance;
    SPEED = error*kVar;
  }//To far
  while(distance < 50)
  {
    robot.backward(SPEED);
    //Serial.write('n');
    distance = getSerialString();
    error = 50-distance;
    SPEED = error*kVar;
  }//To close
  while(distance == 50)
  {
    robot.stop();
    //Serial.write('n');
    distance = getSerialString();
    error = 50-distance;
    SPEED = error*kVar;
  }*/
 }
