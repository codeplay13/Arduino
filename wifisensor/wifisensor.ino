#include <SoftwareSerial.h>
#include <Stdlib.h>
#include <dht.h>
#define DHT11_PIN 7
dht DHT;
String apiKey = "1SZQIQ3PY1XVLZOJ";
SoftwareSerial ser(10,11);
void setup() {
  // put your setup code here, to run once:
ser.begin(115200);
Serial.begin(115200);
ser.println("AT+RST");
}

void loop() {
  // put your main code here, to run repeatedly:
          DHT.read11(DHT11_PIN);
          Serial.print("Temperature= ");
          Serial.println(DHT.temperature);
          Serial.print("Humidity= ");
          Serial.println(DHT.humidity);
          
          String cmd="AT+CIPSTART=\"TCP\",\"";
          cmd+="184.106.153.149";
          cmd+="\",80";
          ser.println(cmd);
            if(ser.find("Error"))
            {
              Serial.println("AT+CIPSTART error");
              return;
            }

          
          String getStr ="GET /update?api_key=";
          
          getStr +=apiKey;
          getStr +="&field1=";
          getStr +=String(DHT.temperature);
          getStr +="&field2=";
          getStr +=String(DHT.humidity);
          getStr +="\r\n\r\n";


          cmd ="AT+CIPSEND=";
          cmd +=String(getStr.length());
          ser.println(cmd);
          if(ser.find(">"))
          {
              ser.print(getStr);
          }
       
          else
          {
              ser.println("AT+CIPCLOSE");
              Serial.println("AT+CIPCLOSE");
          }
    delay(16000);
}

