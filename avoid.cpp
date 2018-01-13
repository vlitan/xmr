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

//angle -> the direction where the servo should point at
//return value: the average distance after several (nrReads) readings of the ultrasonic 
int getDistance(int angle){
    servo.write(angle); // turn the servo
    delay(500);         // wait for servo to get in the desired position. 
    long dist=0;        
    int i,disti;
    for(i = 0; i < nrReads; i++){
      disti = sonar.ping_cm();            //read value
      disti = (disti == 0) ? 100 : disti; //if 0 (got not response) the distance is assumed as far-away
      dist += disti;                      //add to sum
    }
    return dist / nrReads;                //return average
}

int decision;
//returns true if there is something in a certain direction, compares with minDist
bool isBlocked(int lookingDirection){
  return getDistance(lookingDirection)<minDist;
}
//given the direction and the strategy used returns if the bot should go a certain direction or not
bool shouldGo(int direction, int strategy){
  return (!isBlocked(direction) != !(strategy != AVOID));
}
//returns the decision (turn, go forward, do nothing etc) based on the employed strategy and sensor readings
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
  decision = getDecision(strategy); // get the decision
  
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
  if (strategy == FOLLOW && decision == NOTHING){ //if following and nothing is seen it should wait
    stop();
  }
  else{
    drive(avoidSpeed);
  };
}





