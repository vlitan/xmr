#pragma once


void setupMotors();
//applies speeds to motors
void go(int speedLeft, int speedRight);


//drives in a straightline with a specified speed
//TODO if the robot is not going straight, adjust here
void drive(int speed);

void turn(int speed);
//stops motors
void stop();
