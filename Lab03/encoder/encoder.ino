/*
 * How to test encoder with Arduino
 * url: http://osoyoo.com/?p=30267
 */
 #define rightA 20
 #define rightB 34
 #define leftA 21
 #define leftB 32
 int counter = 0; 
 int aState;
 int aLastState;  
 volatile int encoderRightCounter = 0;
 volatile int encoderLeftCounter = 0;

 void EncoderRightISR()
 {
    if(digitalRead(rightB))
    {
      encoderRightCounter --;
    }
    else
    {
      encoderRightCounter ++;
    }
 }

 void EncoderLeftISR()
 {
   if(digitalRead(leftB))
    {
      encoderLeftCounter ++;
    }
    else
    {
      encoderLeftCounter --;
    }
 }
 
 void setup() { 
   pinMode (rightA,INPUT);
   pinMode (rightB,INPUT);
   pinMode (leftA,INPUT);
   pinMode (leftB,INPUT);

   attachInterrupt(digitalPinToInterrupt(rightA), EncoderRightISR, RISING);
   attachInterrupt(digitalPinToInterrupt(leftA), EncoderLeftISR, RISING);
 
   Serial.begin(9600);
 
 } 
 void loop() { 
   
     Serial.print("Position left: ");
     Serial.print(encoderLeftCounter, HEX);
     Serial.print(",  Position right: ");
     Serial.println(encoderRightCounter, HEX);
     delay(1000);
 }
