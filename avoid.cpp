#include <NewPing.h>
#include <Servo.h>
#include "avoid.h"
#include "pinConfig.h"
#include "sysConfig.h" 
#include "motors.h"

#define GO_FRONT  0
#define GO_LEFT   1
#define GO_RIGHT  2
#define TURN      3
#define NOTHING   4

extern NewPing sonar;
extern Servo servo;

void setupAvoid(){
  servo.write(lookFront);
}

int getDistance(int angle){
    servo.write(angle);
    delay(100);
    int dist1=sonar.ping_cm();
    dist1=dist1==0?100:dist1;
    int dist2=sonar.ping_cm();
    dist2=dist2==0?100:dist2;
    int dist3=sonar.ping_cm();
    dist3=dist3==0?100:dist3;
    int dist=(dist1+dist2+dist3)/3;
    return dist==0?100:dist;
}
int i1,i2;
int decision;
void loopAvoid(){
 // Serial.println("check front");
  decision = NOTHING;
  if(getDistance(lookFront)<minDist){
      stop();
      delay(1000);
      if(getDistance(lookLeft)<minDist){
        if(getDistance(lookRight)<minDist){
          decision = TURN;
        }
        else{
          decision = GO_RIGHT;
        }
    }
    else{
      decision = GO_LEFT;
    }
  }
  switch (decision){
    case GO_RIGHT:
             // Serial.println("go right");
              turn(avoidSpeed,turnDelay);    
            break;
    case GO_LEFT:
             // Serial.println("go left");
              turn(-avoidSpeed,turnDelay);     
            break;
    case TURN:
            //  Serial.println("turn around");
              turn(avoidSpeed,turnDelay*2);
            break;        
    case NOTHING:  
              stop();   
            break;
  }
 drive(avoidSpeed);
}

