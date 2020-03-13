#include <FastPID.h>

#define KP 254
#define KI 10
#define KD 20

#define frontRightdirpin1   22
#define frontRightdirpin2   24
#define frontRightspdpin    9
#define rightA              20
#define rightB              34



volatile int encoderRightCounter = 0;

void motorEncoderISR(int pin)
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

FastPID myPID(KP, KI, KD, 10, 8, true);
void setup() {
  // put your setup code here, to run once:

  pinMode(frontRightdirpin1,OUTPUT);
  pinMode(frontRightdirpin2,OUTPUT);
  pinMode(frontRightspdpin,OUTPUT);
  pinMode(rightA,INPUT);
  pinMode(rightB,INPUT);

  attachInterrupt(digitalPinToInterrupt(rightA), +[](int encoderAPin){ motorEncoderISR(rightA); }, CHANGE);

  Serial.begin(9600);
  Serial1.begin(9600);

  
  //FastPID myPID(100, 0, 0, 10, 8, true);
  if (myPID.err()) 
    Serial1.println("There is a configuration error!");

}

int motorSetpoint = 20;
void loop() {
  // put your main code here, to run repeatedly:

  uint8_t output = myPID.step(motorSetpoint, encoderRightCounter);

  Serial1.print(motorSetpoint);
  Serial1.print("    ");
  Serial1.print(output);
  Serial1.print("    ");
  Serial1.println(encoderRightCounter);
  encoderRightCounter = 0;

  if(output >= 0)
  {
    digitalWrite(frontRightdirpin1,HIGH);
    digitalWrite(frontRightdirpin2,LOW);
  }
  else
  {
    digitalWrite(frontRightdirpin1,LOW);
    digitalWrite(frontRightdirpin2,HIGH);
    //convert the negative speed to a positive speed
    output = (~output) - 1;
  }
  
  analogWrite(frontRightspdpin,output);
  
  delay(100);

}
