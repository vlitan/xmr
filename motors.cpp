#include "pinConfig.h"
#include <Arduino.h>
#include "motors.h"
#include "sysConfig.h"

void setupMotors(){
  pinMode(leftMotorPinA, OUTPUT);
  pinMode(leftMotorPinB, OUTPUT);
  pinMode(rightMotorPinA, OUTPUT);
  pinMode(rightMotorPinB, OUTPUT);
  stop();
}

//applies speeds to motors
void go(int speedLeft, int speedRight){
    if (speedLeft > 0) {
      analogWrite(leftMotorPinA, speedLeft);
      analogWrite(leftMotorPinB, 0);
    } 
    else {
      analogWrite(leftMotorPinA, 0);
      analogWrite(leftMotorPinB, -speedLeft);
    }
   
    if (speedRight > 0) {
      analogWrite(rightMotorPinA, speedRight);
      analogWrite(rightMotorPinB, 0);
    }else {
      analogWrite(rightMotorPinA, 0);
      analogWrite(rightMotorPinB, -speedRight);
    }
}

//drives in a straightline with a specified speed
//TODO if the robot is not going straight, adjust here
void drive(int speed){
  go(speed - constCompensate, speed);//TODO compensate
}

void turn(int speed){
  go(speed, -speed);
}
//stops motors
void stop(){
  go(0, 0);
}
