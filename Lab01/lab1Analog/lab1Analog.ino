

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int red =  13;      // the number of the LED pin
const int yellow = 12;
const int green = 11;
int sensor = A0;
int sensorValue = 0;

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
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  sensorValue = analogRead(sensor);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    digitalWrite(green, HIGH); // turn on LED
    delay(10 * sensorValue); // waits for a second
    digitalWrite(green, LOW); // turn off LED
    //delay(500); // waits for a second
    
    digitalWrite(yellow, HIGH); // turn on LED
    delay(1000); // waits for a second
    digitalWrite(yellow, LOW); // turn off LED
    //delay(500); // waits for a second
    
    digitalWrite(red, HIGH); // turn on LED
    delay(sensorValue * 10); // waits for a second
    digitalWrite(red, LOW); // turn off LED
    //delay(1000); // waits for a second
  
}
