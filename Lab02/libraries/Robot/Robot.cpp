#include "Arduino.h"
#include "Robot.h"

Robot::Robot(int dirFL1pin, int dirFL2pin, int spdFLpin, int FR1pin, int dirFR2pin, int spdFRpin, 
                int dirRL1pin int dirRL2pin, int spdRLpin, int dirRR1pin, int dirRR2pin, int spdRRpin);
{
  Motor motor_FL(dirFL1pin, dirFL2pin, spdFLpin);
  Motor motor_FL(dirFR1pin, dirFR2pin, spdFRpin);
  Motor motor_FL(dirRL1pin, dirRL2pin, spdRLpin);
  Motor motor_FL(dirRR1pin, dirRR2pin, spdRRpin);
  
}
void Robot::forward(int speed)
{
  motor_FL.forward(speed);
  motor_FR.forward(speed);
  motor_RR.forward(speed);
  motor_RL.forword(speed);
}

void Robot::backward(int speed)
{
  motor_FL.backward(speed);
  motor_FR.backward(speed);
  motor_RR.backward(speed);
  motor_RL.backword(speed);
}

void Robot::slideRight(int speed)
{
  
}

void Robot::slideLeft(int speed)
{

}

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

void Robot::stop()
{
  analogWrite(spd_pin,0);
}
