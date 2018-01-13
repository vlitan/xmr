#include "pinConfig.h"
#include "motors.h"
#include "sysConfig.h"
#include <Servo.h>
#include <NewPing.h>
#include "modeSelector.h"
#include "bluetooth.h"
#include "avoid.h"

Servo servo;
NewPing sonar(triggerPin, echoPin, maxDistance);

void setup() {
  setupMotors();
  setupModeSelector();
  servo.attach(servoPin);
 // Serial.begin(9600);
  setupBLT();
  setupAvoid();
}


void loop() {
  switch(getMode()){
    case bluetooth:       loopBLT();  break;
    case hardwareTest:    loopTest();  break;
    case obstacleAvoid:   loopAvoid(AVOID); break;
    case obstacleFollow:  loopAvoid(FOLLOW); break;
  }
}

void loopTest(){
    static int i = 2;
    static int inc = 1;
    drive(255);
    if ((i <= 1) || (i >= 179)){
      inc *= -1;
    }
    i += inc;
    servo.write(i);
    Serial.println(sonar.ping_cm());
    delay(5);
    stop();
}
