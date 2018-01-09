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
    delay(500);
    long dist=0;
    int i,disti;
    for(i = 0; i < nrReads; i++){
      disti = sonar.ping_cm();
      disti = (disti == 0) ? 100 : disti;
      dist += disti;
    }
    return dist / nrReads;
}

int decision;

bool isBlocked(int lookingDirection){
  return getDistance(lookingDirection)<minDist;
}

bool shouldGo(int direction, int strategy){
  return (!isBlocked(direction) != !(strategy != AVOID));
}

int getDecision(int strategy){
  int decision = NOTHING;
  if(shouldGo(lookFront, strategy)){
      stop();
      if(shouldGo(lookLeft, strategy)){
  
        if(shouldGo(lookRight, strategy)){
          if (strategy == AVOID){
            decision = TURN;
          }
          else{
            decision = NOTHING;
          }
        }
        else{
          decision = GO_RIGHT;
        }
    }
    else{
      decision = GO_LEFT;
    }
  }
  else{
    decision =  GO_FRONT;
  }
  return (decision);
}

void loopAvoid(int strategy){
  decision = getDecision(strategy);
  
  switch (decision){
    case GO_RIGHT:
              turn(avoidSpeed,turnDelay);    
            break;
    case GO_LEFT:
              turn(-avoidSpeed,turnDelay);     
            break;
    case TURN:
              turn(avoidSpeed,turnDelay*2);
            break;       
    case NOTHING:  
              stop();   
            break;
  }
  if (strategy == FOLLOW && decision == NOTHING){
    stop();
  }
  else{
    drive(avoidSpeed);
  };
}





