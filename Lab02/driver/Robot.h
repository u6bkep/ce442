#ifndef Robot_h
#define Robot_h

#include "Arduino.h"
#include "Motor.h"

class Robot {
  public:
   // Robot(int dirFLpin1, dirFLpin2, int spdFLpin, int dirFRpin1, int dirFRpin2, int spdFRpin. dirRLpin1
    Robot(int dirFL1pin, int dirFL2pin, int spdFLpin, int FR1pin, int dirFR2pin, int spdFRpin, 
                int dirRL1pin, int dirRL2pin, int spdRLpin, int dirRR1pin, int dirRR2pin, int spdRRpin);
    void forward (int speed);
    void backward(int speed);
    void slideRight(int speed);
    void slideLeft(int speed);
    void rotateCCW(int speed);
    void rotateCW(int speed);
    void left_turn(int speed);
    void right_turn(int speed);
    
    void stop();

  private:
  Motor motor_FL;
  Motor motor_FR;
  Motor motor_RL;
  Motor motor_RR;
    
};

#endif
