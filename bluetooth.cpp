#include <SoftwareSerial.h>
#include "pinConfig.h"
#include "bluetooth.h"
#include "motors.h"
#include "sysConfig.h"

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
          case 'F': drive(speed); break; //go forward
          case 'B': drive(-speed); break; //backward
          case 'L': turn(-speed); break; //left
          case 'R': turn(speed); break; //right
          case 'G': go(speed/2,speed); break; //forward left
          case 'I': go(speed,speed/2); break; //forward right
          case 'H': go(-speed/2,-speed); break; //back left
          case 'J': go(-speed, -speed/2); break; //back right
          case 'S': stop(); break; //stop
          case 'D': stop(); break; //stop all  
          case 'V': digitalWrite(buzzerPin,HIGH); break;
          case 'v': digitalWrite(buzzerPin,LOW); break; 
          default: if(lastData>='0' && lastData <='9'){
                        speed=map(lastData-'0',0,9,minSpeed,maxSpeed);
                    }
                   break;
          
        }
      }
   }
}

