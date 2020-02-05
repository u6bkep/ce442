#include "Arduino.h"
#include "Robot.h"
#include "Motor.h"



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

//2500 for 80
//1200 for 80

//3000 for 50
//1400 for 50

void square()
{
  //FIRST SIDE
  robot.forward(SPEED);
  delay(3000);
  robot.stop();
  delay(1000);

  robot.right_turn(SPEED);
  delay(1400);
  robot.stop();
  delay(1000);

//SECOND SIDE
  robot.forward(SPEED);
  delay(3000);
  robot.stop();
  delay(1000);

  robot.right_turn(SPEED);
  delay(1400);
  robot.stop();
  delay(1000);

//THIRD SIDE
  robot.forward(SPEED);
  delay(3000);
  robot.stop();
  delay(1000);

  robot.right_turn(SPEED);
  delay(1400);
  robot.stop();
  delay(1000);

//FOURTH SIDE
  robot.forward(SPEED);
  delay(3000);
  robot.stop();
  delay(1000);
  
  robot.right_turn(SPEED);
  delay(1400);
  robot.stop();
  delay(1000);
}

void figure8()
{
  robot.rotateCW(SPEED);
  delay(3000);
  robot.stop();
  delay(1000);
}

void setup() {
  
}

void loop() {
    
  square();
  
  
}
