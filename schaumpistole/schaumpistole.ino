
#include <Servo.h> 
 
Servo myservo;                
 
//const int buttonPin = 5;     // the number of the pushbutton pin
const int servoPin =  9;      // the number of the servo pin
const int pottiPin = A0;

// set debug to true if you want to monitor the angle on the serial output, set debug to false otherwise
const boolean debug = false;

const int ServoOpen = 5;
const int ServoClosed = 107;

// variables will change:
int pottiState = 0;
int angle= ServoClosed;
   
void setup() 
{ 
  
  myservo.attach(servoPin);  
  pinMode(pottiPin, INPUT); 
  
  myservo.write(ServoOpen);
  
  if (debug){
    Serial.begin(9600);
    while (!Serial) {
      ; 
    }
  }
}
void loop() 
{ 
  pottiState= analogRead(pottiPin);
  angle = map(pottiState, 0, 1023, ServoOpen, ServoClosed);
  myservo.write(angle);
  if (debug){
    Serial.println(angle);
  }
  delay(200);  
}
