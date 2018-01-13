#pragma once
//this file holds all configuration constants
const int maxDistance = 100;  //max distance of an object 
const int maxSpeed = 255;     //maximum speed of the car
const int minSpeed = 50;      //minimum speed of the car
const int avoidSpeed = 100;   //the speed used in avoid strategies
const int constCompensate = 5;//compensation for motor speeds
const int lookLeft = 180;     //value for servo to turn left
const int lookRight = 0;      //value for servo to turn right
const int lookFront = 90;     //value for servo to look front
const int minDist = 20;       //threshold for object detection
const int turnDelay = 430;    //delay for turning at ~90 deg
const int nrReads = 10;       //nr of reads of the ultrasonic sensor
