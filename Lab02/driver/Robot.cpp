#include "Arduino.h"
#include "Robot.h"
#include "Motor.h"


Robot::Robot(int dirFL1pin, int dirFL2pin, int spdFLpin, int dirFR1pin, int dirFR2pin, int spdFRpin, 
                int dirRL1pin, int dirRL2pin, int spdRLpin, int dirRR1pin, int dirRR2pin, int spdRRpin):
                motor_FL(dirFL1pin, dirFL2pin, spdFLpin),
                motor_FR(dirFR1pin, dirFR2pin, spdFRpin),
                motor_RL(dirRL1pin, dirRL2pin, spdRLpin),
                motor_RR(dirRR1pin, dirRR2pin, spdRRpin)
{
  
}
void Robot::forward(int speed)
{
  motor_FL.forward(speed);
  motor_FR.forward(speed);
  motor_RR.forward(speed);
  motor_RL.forward(speed);
}

void Robot::backward(int speed)
{
  motor_FL.backward(speed);
  motor_FR.backward(speed);
  motor_RR.backward(speed);
  motor_RL.backward(speed);
}

void Robot::slideRight(int speed)
{
  
}

void Robot::slideLeft(int speed)
{

}

/*
void rotateCCW(int speed)
{
  motor_FL.backward(speed);
  motor_FR.forward(speed);
  motor_RR.forward(speed);
  motor_RL.backward(speed);
}

void rotateCW(int speed)
{
  motor_FL.forward(speed);
  motor_FR.backward(speed);
  motor_RR.backward(speed);
  motor_RL.forward(speed);
}
*/
void Robot::stop()
{
  motor_FL.stop();
  motor_FR.stop();
  motor_RR.stop();
  motor_RL.stop();
}
