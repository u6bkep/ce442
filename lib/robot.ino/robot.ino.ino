#include <FastPID.h>
// define all io
#define rightA              20
#define rightB              34
#define leftA               21
#define leftB               32

#define Echo_PIN            31 // Ultrasonic Echo pin connect to A5
#define Trig_PIN            30  // Ultrasonic Trig pin connect to A4

#define frontRightdirpin1   22
#define frontRightdirpin2   24
#define frontRightspdpin    9

#define frontLeftdirpin1    26
#define frontLeftdirpin2    1
#define frontLeftspdpin     10

#define rearRightdirpin1    5
#define rearRightdirpin2    6
#define rearRightspdpin     11

#define rearLeftdirpin1     7
#define rearLeftdirpin2     8
#define rearLeftspdpin      12


//timer constants
#define PID_UPDATE_FREQ 5
//#define TIMER3_INTERUPT_COUNT (16000000*(1/PID_UPDATE_FREQ))/16
#define TIMER3_INTERUPT_COUNT 50000
//PID constants
//#define Kp 10
//#define Ki 50
//#define Kd 10

#define Kp 40
#define Ki 0
#define Kd 0

//define global variables
FastPID myPID(Kp, Ki, Kd, PID_UPDATE_FREQ, 8, true);

//globals for ISR
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

//volatile int motorFeedback = 0;
volatile int motorSetpoint = 20;
//10Hz timer interupt ISR
ISR(TIMER3_COMPA_vect)
{
 
 //float motorFeedback = (encoderRightCounter/40.0)*255.0;
  uint8_t output = myPID.step(motorSetpoint, encoderRightCounter);

  Serial1.print(motorSetpoint);
  Serial1.print("    ");
  Serial1.print(output);
  Serial1.print("    ");
  Serial1.println(encoderRightCounter);
  if (myPID.err()) 
    Serial1.println("There is a configuration error!");
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
  
}

void motorPidControlInit(int dirPin1,int dirPin2,int spdPin,int encoderAPin,int encoderBpin)
{
  //settup pins
  pinMode(dirPin1,OUTPUT);
  pinMode(dirPin2,OUTPUT);
  pinMode(spdPin,OUTPUT);
  pinMode(encoderAPin,INPUT);
  pinMode(encoderBpin,INPUT);
  
  //register encoder interupt
  attachInterrupt(digitalPinToInterrupt(encoderAPin), +[](int encoderAPin){ motorEncoderISR(encoderAPin); }, CHANGE);


  //settup PID controller
  
  if (myPID.err()) 
    Serial1.println("There is a configuration error!");

  //settup timer for PID loop
  // initialize Timer3
  cli();          // disable global interrupts
  TCCR3A = 0;     // set entire TCCR3A register to 0
  TCCR3B = 0;     // same for TCCR3B

  // set compare match register to desired timer count: 10Hz
  //OCR3A = 50000;
  OCR3A = TIMER3_INTERUPT_COUNT;
  // turn on CTC mode:
  TCCR3B |= (1 << WGM12);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR3B |= (1 << CS01) | (1 << CS00);
  // enable timer compare interrupt:
  TIMSK3 |= (1 << OCIE3A);
  // enable global interrupts:
  sei();
}

void setup() 
{
  //configure io
  pinMode (Trig_PIN,OUTPUT);
  pinMode (Echo_PIN,INPUT);

  //start serial
  Serial.begin(9600);
  Serial1.begin(9600);

  // initialize motor pwm controller
  motorPidControlInit(frontRightdirpin1, frontRightdirpin2, frontRightspdpin, rightA, rightB);

}

void loop() 
{
  // put your main code here, to run repeatedly:
  

}
