#import "motorPID.h"


#define frontRightdirpin1   22
#define frontRightdirpin2   24
#define frontRightspdpin    9
#define rightA              20
#define rightB              34

motorPID motorFrontRight(frontRightdirpin1,frontRightdirpin2,frontRightspdpin,
            rightA, rightB, 0);
void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial1.println(motorFrontRight.encoderCounter);
  delay(300);

}
