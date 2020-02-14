/*
 * How to test encoder with Arduino
 * url: http://osoyoo.com/?p=30267
 */

#include "Robot.h"
#include <Servo.h>
Servo servo;
 
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
 int left, center, right;
 int distance;
 int sensors = 0;

//sonar pin config
 #define Echo_PIN    31 // Ultrasonic Echo pin connect to A5
 #define Trig_PIN    30  // Ultrasonic Trig pin connect to A4

//robot driving parameters
#define SPEED 40
#define TURN_SPEED 30

//robot control pin config
//Front right
#define frontRightdirpin1  22
#define frontRightdirpin2  24
#define frontRightspdpin 9

//Front Left
#define frontLeftdirpin1  26
#define frontLeftdirpin2  28
#define frontLeftspdpin  10

//Rear right
#define rearRightdirpin1  5
#define rearRightdirpin2  6
#define rearRightspdpin  11

//Rear left
#define rearLeftdirpin1  7
#define rearLeftdirpin2  8
#define rearLeftspdpin  12

//constants for the light sensor
#define LIGHT_SENSOR_LEFT A10
#define LIGHT_SENSOR_CENTER A9
#define LIGHT_SENSOR_RIGHT A8

float THRESHOLD_LEFT;
float THRESHOLD_CENTER;
float THRESHOLD_RIGHT;
int x = 1000;
int i = 0;

//initialise the robot control library
Robot robot(frontLeftdirpin1, frontLeftdirpin2, frontLeftspdpin, frontRightdirpin1, frontRightdirpin2, frontRightspdpin,
            rearLeftdirpin1, rearLeftdirpin2, rearLeftspdpin, rearRightdirpin1, rearRightdirpin2, rearRightspdpin);
            
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

int sensorCheck()
{
  int result = 0;

  left = analogRead(LIGHT_SENSOR_LEFT);
  center = analogRead(LIGHT_SENSOR_CENTER);
  right = analogRead(LIGHT_SENSOR_RIGHT);

  if(left > THRESHOLD_LEFT)
  {
    result = result + 100;
  }
  if(center > THRESHOLD_CENTER)
  {
    result = result + 10;
  }
  if(right > THRESHOLD_RIGHT)
  {
    result = result + 1;
  }
  return result;
}


  void cal()
  {
    Serial.print("IN CAL");
    left = 0;
    center = 0;
    right = 0;
    Serial.println("######");
    Serial.println(i);
    Serial.println(x);
    Serial.println("######");
    for(i = 0; i<= x ; i++)
    {
      left = analogRead(LIGHT_SENSOR_LEFT);
      center = analogRead(LIGHT_SENSOR_CENTER);
      right = analogRead(LIGHT_SENSOR_RIGHT);
      THRESHOLD_LEFT = THRESHOLD_LEFT + left;
      THRESHOLD_CENTER = THRESHOLD_CENTER + center;
      THRESHOLD_RIGHT = THRESHOLD_RIGHT + right;
      Serial.println(left);
      Serial.println(center);
      Serial.println(right);
    }
    
    THRESHOLD_LEFT = THRESHOLD_LEFT / x;
    THRESHOLD_CENTER = THRESHOLD_CENTER / x;
    THRESHOLD_RIGHT = THRESHOLD_RIGHT / x;
    Serial.println(THRESHOLD_LEFT);
    Serial.println(THRESHOLD_CENTER);
    Serial.println(THRESHOLD_RIGHT);
  }
  


void centerWhite()
{
  Serial.println("##########CENTERWHITE STARTED ###########");
  if(left > THRESHOLD_LEFT)//LEFT BLACK
  {
    while(left > THRESHOLD_LEFT) //Black Detected
    {
      do
      {
      robot.rotateCCW(TURN_SPEED);
      delay(50);
      left = analogRead(LIGHT_SENSOR_LEFT);
      center = analogRead(LIGHT_SENSOR_CENTER);
      right = analogRead(LIGHT_SENSOR_RIGHT);
      }while(center < THRESHOLD_CENTER);//Center is white

      if(center > THRESHOLD_CENTER)//Center black again
      {
        Serial.println("##########CENTERWHITE ENDED ###########");
        return;
      }//CENTER BLACK AGAIN
    }
    do
      {
      robot.rotateCCW(TURN_SPEED);
      delay(50);
      left = analogRead(LIGHT_SENSOR_LEFT);
      center = analogRead(LIGHT_SENSOR_CENTER);
      right = analogRead(LIGHT_SENSOR_RIGHT);
      }while(center < THRESHOLD_CENTER);//Center is white

      if(center > THRESHOLD_CENTER)//Center black again
      {
        Serial.println("##########CENTERWHITE ENDED ###########");
        return;
      }//CENTER BLACK AGAIN
  }//END OF LEFT BLACK

  
  if(right > THRESHOLD_RIGHT)//BLACK
  {
    while(right > THRESHOLD_RIGHT) //Black Detected
    {
      do
      {
      robot.rotateCCW(TURN_SPEED);
      delay(50);
      left = analogRead(LIGHT_SENSOR_LEFT);
      center = analogRead(LIGHT_SENSOR_CENTER);
      right = analogRead(LIGHT_SENSOR_RIGHT);
      }while(center < THRESHOLD_CENTER);//Center is white

      if(center > THRESHOLD_CENTER)//Center black again
      {
        Serial.println("##########CENTERWHITE ENDED ###########");
        return;
      }//CENTER BLACK AGAIN
    }//END OF BLACK RIGHT
          do
      {
      robot.rotateCCW(TURN_SPEED);
      delay(50);
      left = analogRead(LIGHT_SENSOR_LEFT);
      center = analogRead(LIGHT_SENSOR_CENTER);
      right = analogRead(LIGHT_SENSOR_RIGHT);
      }while(center < THRESHOLD_CENTER);//Center is white
      
      if(center > THRESHOLD_CENTER)//Center black again
      {
        Serial.println("##########CENTERWHITE ENDED ###########");
        return;
      }//CENTER BLACK AGAIN
  }//END OF RIGHT BLACK
  Serial.println("##########CENTERWHITE ENDED ###########");
  return;
}

void threeBlack()
{
  if(right > THRESHOLD_RIGHT && center > THRESHOLD_CENTER) //Black Detected
    {
      while( right > THRESHOLD_RIGHT) //Black Detected
      {
        robot.rotateCCW(TURN_SPEED);
        left = analogRead(LIGHT_SENSOR_LEFT);
        center = analogRead(LIGHT_SENSOR_CENTER);
        right = analogRead(LIGHT_SENSOR_RIGHT);
      }
      return;
    }
    else if(left > THRESHOLD_LEFT && center > THRESHOLD_CENTER) //Black Detected
    {
      while( left > THRESHOLD_LEFT) //Black Detected
      {
        robot.rotateCW(TURN_SPEED);
        left = analogRead(LIGHT_SENSOR_LEFT);
        center = analogRead(LIGHT_SENSOR_CENTER);
        right = analogRead(LIGHT_SENSOR_RIGHT);
      }
      return;
    }
 return;
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
   
   Serial.begin(9600);

   servo.attach(13);
   servo.write(0);
   delay(500);
   cal();
   
   delay(1000);
   servo.write(180);
   delay(100);
   servo.write(90);
   delay(1500);

 }//END OF SETUP

 
 void loop() 
{ 
/*
    Robots Left sensor reading and correction
*/
    left = analogRead(LIGHT_SENSOR_LEFT);
    center = analogRead(LIGHT_SENSOR_CENTER);
    right = analogRead(LIGHT_SENSOR_RIGHT);
 // Serial.print("Left: ");
 // Serial.print(left);

  /*while(sonarDistance < 20)
  {
    robot.stop();
  }
  */
  
  
    while(left > THRESHOLD_LEFT) //Black Detected
    {
      robot.rotateCCW(TURN_SPEED);
      left = analogRead(LIGHT_SENSOR_LEFT);
      center = analogRead(LIGHT_SENSOR_CENTER);
      right = analogRead(LIGHT_SENSOR_RIGHT);
      //robot.forward(SPEED);
      //delay(10);
    }//End of Black left
    if(left < THRESHOLD_LEFT)
    {
      Serial.print(", WHITE DETECTED ON LEFT");
    }

/*
    Center sensor reading and drive
*/

    left = analogRead(LIGHT_SENSOR_LEFT);
    center = analogRead(LIGHT_SENSOR_CENTER);
    right = analogRead(LIGHT_SENSOR_RIGHT);

  
  //Serial.print(center);
  //Serial.print(" Center: ");
  while(center > THRESHOLD_CENTER)//Black
  {
    /*
    distance = sonarDistance();
    while(distance < 20);
    {
      robot.stop();
      delay(1000);
      distance = sonarDistance();
    }
    */
    Serial.print(", BLACK DETECTED");
    robot.forward(SPEED);
    left = analogRead(LIGHT_SENSOR_LEFT);
    center = analogRead(LIGHT_SENSOR_CENTER);
    right = analogRead(LIGHT_SENSOR_RIGHT);
    while((center > THRESHOLD_CENTER) && (right > THRESHOLD_RIGHT) && (left > THRESHOLD_LEFT))
    {
      robot.stop();
      delay(50);
      robot.backward(SPEED);
      delay(50);
      
      threeBlack();
      
      robot.backward(SPEED);
      delay(50);
      
    }
    if((center > THRESHOLD_CENTER) && (left > THRESHOLD_LEFT) && (right > THRESHOLD_RIGHT))
    {
      robot.stop();
      delay(50);
      robot.backward(SPEED);
      delay(50);
      
      threeBlack();

      robot.backward(SPEED);
      delay(50);
    }
  }

  if (center < THRESHOLD_CENTER)//White
  {
    robot.stop();
    delay(100);
    centerWhite();
    left = analogRead(LIGHT_SENSOR_LEFT);
    center = analogRead(LIGHT_SENSOR_CENTER);
    right = analogRead(LIGHT_SENSOR_RIGHT);
  }
  
  else
    Serial.print(", WHITE DETECTED");

/*
    Robots Right sensor reading and correction
*/


    left = analogRead(LIGHT_SENSOR_LEFT);
    center = analogRead(LIGHT_SENSOR_CENTER);
    right = analogRead(LIGHT_SENSOR_RIGHT);
    
 // Serial.print(" Right: ");
 // Serial.print(right);
 
  if(right > THRESHOLD_RIGHT)//Black
  {
    Serial.println(", BLACK DETECTED");
    robot.stop();
    
    while(right > THRESHOLD_RIGHT)
    {
      robot.rotateCW(TURN_SPEED);
      left = analogRead(LIGHT_SENSOR_LEFT);
      center = analogRead(LIGHT_SENSOR_CENTER);
      right = analogRead(LIGHT_SENSOR_RIGHT);
      robot.forward(SPEED);
      delay(10);
    }
    robot.stop();
  }

  
  else
    Serial.println(", WHITE DETECTED");

  //delay(2000);
}//End of loop
