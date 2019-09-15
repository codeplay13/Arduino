#include<SoftwareSerial.h>

SoftwareSerial ss(5,6);

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  ss.read();
}
