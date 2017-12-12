#include <SoftwareSerial.h>
#include "pinConfig.h"
#include "bluetooth.h"
#include "motors.h"

char data = 0, lastData = '.';            //Variable for storing received data
SoftwareSerial BLT(serialRX,serialTX); //to TX, to RX
int speed = 100;

void setupBLT()
{
    BLT.begin(9600);                             
}
void loopBLT()
{
   if(BLT.available() > 0)      // Send data only when you receive data:
   {
      data = BLT.read();        //Read the incoming data & store into data
      if(data!=lastData){
        lastData=data;
        switch(lastData){
          case 'F': drive(100); break; //go forward
          case 'B': drive(-100); break; //backward
          case 'L': turn(-100); break; //left
          case 'R': turn(100); break; //right
          case 'G': go(50,100); break; //forward left
          case 'I': go(100,50); break; //forward right
          case 'H': go(-50,-100); break; //back left
          case 'J': go(-100, -50); break; //back right
          case 'S': stop(); break; //stop
          case 'D': stop(); break; //stop all   
          //default: if char     
        }
      }
   }
}

