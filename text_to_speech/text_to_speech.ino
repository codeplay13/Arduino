#include<SoftwareSerial.h>
#include<dht.h>

#define DHT11 7

dht DHT;

SoftwareSerial BT(10, 11);  //TX, RX
void setup() {
  // put your setup code here, to run once:
  BT.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  DHT.read11(DHT11);
    BT.println("Temperature is ");
    BT.println(DHT.temperature);
    //BT.println("Degree Celsius");
    BT.println("Humidity is ");
    BT.println(DHT.humidity);
    //BT.println("percentage");
    delay(10000);    
}

