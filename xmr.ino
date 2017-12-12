#include <Servo.h>
#include <NewPing.h>
#include "TimerOne.h"
// Pins of motor 1
#define mpin00 5
#define mpin01 6
// Pins of motor 2
#define mpin10 3
#define mpin11 11
//ultrasonic sensor
#define TRIGGER_PIN  13
#define ECHO_PIN     12

Servo srv;
NewPing sonar(TRIGGER_PIN,ECHO_PIN);

void setup() {
   // configuration of motor pins as output, initially 0
   digitalWrite(mpin00, 0);
   digitalWrite(mpin01, 0);
   digitalWrite(mpin10, 0);
   digitalWrite(mpin11, 0);
   pinMode (mpin00, OUTPUT);
   pinMode (mpin01, OUTPUT);
   pinMode (mpin10, OUTPUT);
   pinMode (mpin11, OUTPUT);
   // LED pin
   pinMode(13, OUTPUT);
   pinMode(A0,INPUT);
   Serial.begin(9600);
   //timer_ms(100,ultraDetectAvoid);
   Timer1.initialize(1000000);
   //Timer1.attachInterrupt(ultraDetectAvoid);
}

// Function to control a motor
// Input: pins m1 and m2, direction and speed
void StartMotor (int m1, int m2, int forward, int speed)
{
   if (speed==0) // stop
   {
      digitalWrite(m1, 0); 
      digitalWrite(m2, 0);
   }
   else
   {
     if (forward)
     {
       digitalWrite(m2, 0);
       analogWrite (m1, speed); // use PWM
     }
     else
     {
       digitalWrite(m1, 0);
       analogWrite(m2, speed);
     }
   }
}

// Safety function
// Commands motors to stop, then delays
void delayStopped(int ms)
{
   StartMotor (mpin00, mpin01, 0, 0);
   StartMotor (mpin10, mpin11, 0, 0);
   delay(ms);
}

// Use of servo
// Set three angles
// When finished, the servo remains in the middle (90 degrees)
void playWithServo(int pin)
{
   srv.attach(pin);
   for(int i = 0;i<180;i+=1){
    srv.write(i);
    delay(10);
   }
   for(int i = 180;i>0;i-=1){
    srv.write(i);
    delay(10);
   }
   /*
   srv.write(0);
   delay(1000);
   srv.write(180);
   delay(1000);
   srv.write(90);
   delay(1000);
   */
   srv.detach();
}

void loop() { 
  delay(50);
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm());
  Serial.println("cm");
  ultraDetectAvoid();
     // Warning code
   // Slow blink
   /*for (int i=0; i<10; i++)
   {
     digitalWrite(13, 1);
     delay(200);
     digitalWrite(13, 0);
     delay(200);
   }
   // Fast blink. Remove the USB cable!!!!
   for (int i=0; i<10; i++)
   {
     digitalWrite(13, 1);
     delay(100);
     digitalWrite(13, 0);
     delay(100);
   }
   digitalWrite(13, 1);*/
   // Start the servo motor
   //int val=analogRead(A0);
   
   /*int sped=100;
   StartMotor (mpin00, mpin01, 0, sped-(6*sped/100));
   StartMotor (mpin10, mpin11, 0, sped);
   delay(1000);
   delayStopped(1000);
   turnLeft();
   //delay(1000);
   StartMotor (mpin00, mpin01, 0, sped-(6*sped/100));
   StartMotor (mpin10, mpin11, 0, sped);
   delay(1000);
   delayStopped(1000);
   turnRight();*/
   
   //delay(1000);
   //playWithServo(8);
   // Now start the DC motors
  /* StartMotor (mpin00, mpin01, 0, 128);
   StartMotor (mpin10, mpin11, 0, 128);
  
   delay (500); // How long the motors are on
   delayStopped(500); // How long the motors are off
  
   StartMotor (mpin00, mpin01, 1, 128);
   StartMotor (mpin10, mpin11, 1, 128);
  
   delay (500);
   delayStopped(500);
   StartMotor (mpin00, mpin01, 0, 128);
   StartMotor (mpin10, mpin11, 1, 128);
  
   delay (500);
   delayStopped(500);
  
   StartMotor (mpin00, mpin01, 1, 128); 
   StartMotor (mpin10, mpin11, 0, 128);
  
   delay (500);
   delayStopped(500);*/
} 

void turnLeft(){
    StartMotor (mpin10, mpin11, 0, 128);
    delay (580);
    delayStopped(1000);
}

void turnRight(){
    StartMotor (mpin00, mpin01, 0, 115);
    delay (580);
    delayStopped(1000);
}

void ultraDetectAvoid(){
  digitalWrite(13,1);
  int dist=sonar.ping_cm();
  Serial.println(dist);
  int sped=100;
  if(dist<20 && dist!=0){
    digitalWrite(13,0);
    delayStopped(100);
    turnLeft();
    StartMotor (mpin00, mpin01, 0, sped-(6*sped/100));
    StartMotor (mpin10, mpin11, 0, sped);
  }
}


