#include <SoftwareSerial.h>
#define DEBUG true

SoftwareSerial esp8266(5, 6);   // rx, tx 


String sendData(String command, const int timeout, boolean debug){
    String response = "";
    esp8266.print(command);

    long int time = millis();
    while((time+timeout) > millis()){
      while(esp8266.available()){
        char c = esp8266.read(); // read the next character
        response += c;
      }
    }
    if(debug){
      Serial.print(response);
    }
    return response;
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  esp8266.begin(115200);

  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);

  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  sendData("AT+RST\r\n",1000,DEBUG); //reset module
  sendData("AT+CWMODE=3\r\n",1000,DEBUG);
  sendData("AT+CIFSR\r\n",1000,DEBUG); //get IP address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); //configure for multiplexing
  sendData("AT+CIPSERVER=1,8080\r\n",1000,DEBUG); //turn on server
}

void loop() {
  // put your main code here, to run repeatedly:
  if(esp8266.available()){
    if(esp8266.find("+IPD,")){
      delay(1000); //wait for the serial buffer to fill up 
      //get the connection id so that we can then disconnect 
      int connectionId = esp8266.read()-48;
      esp8266.find("pin="); //advance cursor to "pin="

       int pinNumber = (esp8266.read()-48)*10; //because data is sent bit by bit 
       pinNumber += (esp8266.read()-48);  //1 represents 49, 2 -> 50 and so on..

       digitalWrite(pinNumber, !digitalRead(pinNumber)); //toggle i.e. on if off and vice versa

       //make close command
       String closeCommand = "AT+CIPCLOSE=";
       closeCommand += connectionId; //append connection id
       closeCommand += "\r\n";

       sendData(closeCommand, 1000, DEBUG);
    }
  }
}
