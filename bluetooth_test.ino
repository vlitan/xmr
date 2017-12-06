#include <SoftwareSerial.h>

char data = 0;            //Variable for storing received data
SoftwareSerial BLT(3,4);

void setup()
{
    Serial.begin(9600);   //Sets the baud for serial data transmission  
    BLT.begin(9600);                             
    //pinMode(13, OUTPUT);  //Sets digital pin 13 as output pin
}
void loop()
{
   if(BLT.available() > 0)      // Send data only when you receive data:
   {
      data = BLT.read();        //Read the incoming data & store into data
      Serial.print(data);          //Print Value inside data in Serial monitor
      Serial.print("\n");        
   }
}
