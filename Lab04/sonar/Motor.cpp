#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int dir1pin, int dir2pin, int spd_pin)
{
  pinMode(dir1pin, OUTPUT); 
  pinMode(dir2pin, OUTPUT); 
  pinMode(spd_pin, OUTPUT);  
  _pin = dir1pin;
  _pin2 = dir2pin;
  _spd_pin = spd_pin;
  
}
void Motor::forward(int speed)
{
  speed = map(speed,0,100,0,255);
  digitalWrite(_pin,HIGH);
  digitalWrite(_pin2,LOW);
  analogWrite(_spd_pin,speed);
}

void Motor::backward(int speed)
{
  speed = map(speed,0,100,0,255);
  digitalWrite(_pin,LOW);
  digitalWrite(_pin2,HIGH);
  analogWrite(_spd_pin,speed);
}

void Motor::stop()
{
  analogWrite(_spd_pin,0);
}
