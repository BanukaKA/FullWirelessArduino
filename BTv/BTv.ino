
#include <AFMotor.h> //Adafruit Motor Shield Library. First you must download and install AFMotor library
#include <Servo.h>   //Servo library. This is standard library. (Sketch -> Include Library -> Servo)

#define trigPin 28 
#define echoPin 30 

String val;

AF_DCMotor motor1 (1, MOTOR12_64KHZ); //create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor motor2 (2, MOTOR12_8KHZ); //create motor #2 using M2 output on Motor Drive Shield, set to 1kHz PWM frequency
Servo myServo; //define servo name



void setup()
{
  Serial.begin(9600); //start serial communication
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(36,OUTPUT);
  pinMode(50, OUTPUT);
  pinMode(48, OUTPUT);
   
  myServo.attach(10); //define our servo pin (the motor shield servo1 input = digital pin 10)
  myServo.write(90);  //servo position is 90 degrees
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(2000);

}

void loop() 
{

  long duration, distance; 
   digitalWrite(trigPin, LOW);  
   delayMicroseconds(2); 
   digitalWrite(trigPin, HIGH);

   delayMicroseconds(10); 
   digitalWrite(trigPin, LOW);
   duration = pulseIn(echoPin, HIGH);
   distance = (duration/2) / 29.1;
   
  if(Serial.available() > 0){ //Check if there is an available byte to read
     
   val = Serial.read(); //Conduct a serial read
    
  
switch(val)
{  
    case"*forward": motor1.run(FORWARD);
             motor2.run(FORWARD);
             
             break;
      
    case"*backward": motor1.run(BACKWARD);
             motor2.run(BACKWARD);
             digitalWrite(36, HIGH);
             
             break;
      
    case"*turn right": myServo.write(0);
              delay(500);
              myServo.write(90);
              delay(500);
              motor1.run(RELEASE);
              motor1.setSpeed(170);
              motor2.run(FORWARD);
              motor2.setSpeed(170);
     
              break;
              
    case"*turn left" : myServo.write(180);
              delay(500);
              myServo.write(90);
              delay(500); 
              motor1.run(RELEASE);
              motor1.setSpeed(170);
              motor2.run(BACKWARD);
              motor2.setSpeed(170);
              
              break;
    
      
    case"*stop" : motor1.run(RELEASE);
              motor2.run(RELEASE);
              digitalWrite(36, HIGH);
              delay(1000);
              digitalWrite(36, LOW);
              break;
              
    case"*back lights on": digitalWrite(36, HIGH);

             break;

    case"*back lights off": digitalWrite(36, LOW);

             break;

    case"*front lights on": digitalWrite(50, HIGH);

             break;

   case"*front lights off": digitalWrite(50, LOW);

             break;

   case"*horn on": digitalWrite(48, HIGH);

            break;

   case"*horn off": digitalWrite(48, LOW);
    
  }
    
  Serial.println(val);

}
delay(50);
}
