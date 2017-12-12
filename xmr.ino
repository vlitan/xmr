#include "pinConfig.h"
#include "motors.h"
#include "sysConfig.h"
#include <Servo.h>
#include <NewPing.h>
#include "modeSelector.h"
#include "bluetooth.h"

Servo servo;
NewPing sonar(triggerPin, echoPin, maxDistance);

void setup() {
  setupMotors();
  setupModeSelector();
  servo.attach(servoPin);
  Serial.begin(115200);
  setupBLT();

}
int i = 2;
int inc = 1;

void loop() {
  switch(getMode()){
    case bluetooth:     Serial.println("blue"); break;
    case hardwareTest:  Serial.println("hard"); break;
    case obstacleAvoid: Serial.println("avoi"); break;
    case mapRoom:       Serial.println("mapr"); break;
  }
}


void testLoop(){
    /*drive(255);
    if ((i <= 1) || (i >= 179)){
      inc *= -1;
    }
    i += inc;
    servo.write(i);
    Serial.println(sonar.ping_cm());
<<<<<<< HEAD
    delay(5);
}
    delay(5);*/
    loopBLT();
 }


void ultraDetectAvoid(){
  digitalWrite(13,1);
  int dist=sonar.ping_cm();
  Serial.println(dist);
  int sped=100;
  drive(100);
  if(dist<20 && dist!=0){
    digitalWrite(13,0);
    stop();
    delay(100);
    turn(100);
    delay(100);
  }
}


