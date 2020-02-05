#include "Arduino.h"
#include "Robot.h"
#include "Motor.h"



#define SPEED 140
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


void square()
{
  robot.forward(80);
  delay(2500);
  
  robot.stop();
  delay(1000);

  robot.right_turn(70);
  delay(1000);

  robot.stop();
  delay(1000);

  robot.forward(80);
  delay(2500);

  robot.right_turn(80);
  delay(1000);
  
  robot.stop();
  delay(1000);
  
  robot.forward(80);
  delay(2500);
  
  robot.stop();
  delay(1000);

  robot.right_turn(70);
  delay(1000);
  
  robot.stop();
  delay(1000);
  
  robot.forward(80);
  delay(2500);

  robot.right_turn(80);
  delay(1000);

  robot.stop();
  delay(1000);
}

void setup() {
  
}

void loop() {
    
  square();
  
  
}
