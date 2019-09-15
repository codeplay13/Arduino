#include"SoftwareSerial.h"

SoftwareSerial BT(10, 11);  //TX, RX
String st;
void setup() {
  // put your setup code here, to run once:
  BT.begin(9600);
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(BT.available()){
    delay(100);
    char c = BT.read();
    st += c;
  }
    if(st.length() > 0){
      Serial.println(st);

      if(st == "on"){
        digitalWrite(13, HIGH);
        //digitalWrite(8, HIGH);
      }
      else if(st == "fuck off"){
        digitalWrite(13, LOW);
        //digitalWrite(8, LOW);
      }
      st = "";    //Reset the variable
    }
  }

