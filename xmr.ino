#include "pinConfig.h"
#include "motors.h"
#include "sysConfig.h"
#include <Servo.h>
#include <NewPing.h>
#include "bluetooth.h"

Servo servo;
NewPing sonar(triggerPin, echoPin, maxDistance);

void setup() {
  setupMotors();
  servo.attach(servoPin);
  Serial.begin(115200);
  setupBLT();

}
int i = 2;
int inc = 1;

void loop() {
    /*drive(255);
    if ((i <= 1) || (i >= 179)){
      inc *= -1;
    }
    i += inc;
    servo.write(i);
    Serial.println(sonar.ping_cm());
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


