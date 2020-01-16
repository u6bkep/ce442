

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int red =  13;      // the number of the LED pin
const int yellow = 12;
const int green = 11;
int sensor = A0;
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(sensor);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:
  analogWrite(green, outputValue);
  
}
