#include "modeSelector.h"
#include "pinConfig.h"
#include <Arduino.h>

void setupModeSelector(){
  pinMode(switch1, INPUT_PULLUP);
  pinMode(switch2, INPUT_PULLUP);
}

mode_t  getMode(){
  char num = digitalRead(switch1) << 1 | digitalRead(switch2);
  switch (num){
    case 0 : return hardwareTest;
    case 1 : return bluetooth;
    case 2 : return obstacleAvoid;
    case 3 : return mapRoom;
  }
  return 0;
}

