#include <SoftwareSerial.h>
SoftwareSerial BTserial(11, 10); // RX | TX
char c = ' ';
void setup() 
{
Serial.begin(9600);
Serial.println("Arduino is ready");

// HC-05 default serial speed for commincation mode is 9600
BTserial.begin(9600);  
}

void loop()
{
if (BTserial.available() > 0)
{  
    c = BTserial.read();
      Serial.write(c);
}

// Keep reading from Arduino Serial Monitor and send to HC-05
if (Serial.available() > 0)
{
    c =  Serial.read();
    BTserial.write(c);  
}

}
