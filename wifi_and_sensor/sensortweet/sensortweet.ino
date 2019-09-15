#include<SoftwareSerial.h>
#include<Stdlib.h>
#include<dht.h>

#define DHT11_PIN 7

dht DHT;

String apikey ="T0FOCGHO90KNPO7X";
SoftwareSerial ser(10,11);  //rx, tx
void setup() {
  // put your setup code here, to run once:
  ser.begin(115200);
  Serial.begin(115200);
  ser.println("AT+RST");
}

void loop() {
  // put your main code here, to run repeatedly:
  DHT.read11(DHT11_PIN);

  Serial.println("Temperature: ");
  Serial.println(DHT.temperature);
  Serial.println("Humidity: ");
  Serial.println(DHT.humidity);

  //TCP connection
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149";
  cmd += "\",80";  //80 is port number for HTTP connection
  ser.println(cmd);

  if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }

  String tsData = "api_key=" + apikey + "&status=" + "Temperature: " + String(DHT.temperature) + " Degree Celsius" + "\nHumidity: " + String(DHT.humidity) + " Water Vapour per cm cube \n:-D";

  String str = "POST /apps/thingtweet/1/statuses/update HTTP/1.1\n";
  str += "Host: api.thingspeak.com\n";
  str += "Connection: close\n";
  str += "Content-Type: application/x-www-form-urlencoded\n";
  str += "Content-Length: ";
  str += tsData.length();
  str += "\n\n";
  str += tsData;
  
  /*String str = "GET /update?api_key=";
  str += apikey;
  str += "&field1=";
  str += String(DHT.temperature);
  str += "&field2=";
  str += String(DHT.humidity);
  str += "\n\n\n\n";
  */
  
  //send data length
  cmd = "AT+CIPSEND=";
  cmd += String(str.length());
  ser.println(cmd);
  if(ser.find(">")){
    ser.print(str);
  }
  else{
    ser.println("AT+CIPCLOSE");
    //alert user
    Serial.println("AT+CIPCLOSE");
  }
  delay(16000);
}
