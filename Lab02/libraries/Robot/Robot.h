#include "Arduino.h"

#ifndef Robot_h
#define Robot_h


class Robot
{
  public:
    Robot(int dirFL1pin, int dirFL2pin, int spdFLpin, int FR1pin, int dirFR2pin, int spdFRpin, 
                int dirRL1pin int dirRL2pin, int spdRLpin, int dirRR1pin, int dirRR2pin, int spdRRpin);
    void forward (int speed);
    void backward(int speed);
    void slideRide(int speed);
    void slideLeft(int speed);
    void rotateCCW(int speed);
    void rotateCW(int speed);
    
    void stop();

  private:
    int_dirFL1pin;
    int_dirFL2pin;
    int_spdFLpin;

    int_dirRL1pin;
    int_dirRL2pin;
    int_spdRLpin;

    int_dirFR1pin;
    int_dirFR2pin;
    int_spdFRpin;

    int_dirRR1pin;
    int_dirRR2pin;
    int_spdRRpin;
    
};

#endif
