#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int dir1pin, int dir2pin, int spd_pin)
{
  pinMode(dir1pin, OUTPUT); 
  pinMode(dir2pin, OUTPUT); 
  pinMode(spd_pin, OUTPUT);  
  
  stop_Stop();
}
void Motor::forward(int speed)
{
  digitalWrite(dir1pin,HIGH);
  digitalWrite(dir2pin,LOW);
  digitalWrite(spd_pin,speed);
}

void Motor::backward(int speed)
{
  digitalWrite(dir1pin,LOW);
  digitalWrite(dir2pin,HIGH);
  digitalWrite(spd_pin,speed);
}

void Motor::stop()
{
  analogWrite(spd_pin,0);
}
