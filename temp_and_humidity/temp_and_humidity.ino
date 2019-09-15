#include<dht.h>
#define dht11 7
dht abc;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
int x = 1;
void loop() {
  // put your main code here, to run repeatedly:
  abc.read11(dht11);
  while(x){
    Serial.println("Temperature: ");
    Serial.println(abc.temperature);
    Serial.println("Humidity : ");
    Serial.println(abc.humidity);
    x = 0;
  }
}
