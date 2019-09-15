#include<SoftwareSerial.h>
#include<dht.h>
#include<Stdlib.h>

#define DHT11 7

dht abc;

String apikey = "V9ST1RDBCRCWA5YZ";
String tweetapi = "PN5PZNW03NBQ7JY8";

SoftwareSerial ser(10, 11);
void setup() {
  // put your setup code here, to run once:
  ser.begin(115200);
  Serial.begin(115200);
  ser.print("AT+RST");
  pinMode(8, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  abc.read11(DHT11);

  Serial.println("Temperature in Celsius: ");
  Serial.println(abc.temperature);
  Serial.println("Temperature in Fahrenheit:");
  Serial.println(((abc.temperature)*(1.8))+32);
  Serial.println("Humidity: ");
  Serial.println(abc.humidity);

  if(abc.humidity > 64){
    digitalWrite(8, HIGH);
  }
  else{
    digitalWrite(8, LOW);
  }

  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149";
  cmd += "\",80";  //80 is port number for HTTP connection
  ser.println(cmd);

  String command = "AT+CIPSTART=\"TCP\",\"";
  command += "184.106.153.149";
  command += "\",80";  //80 is port number for HTTP connection
  ser.println(command);

  if(ser.find("Error")){
    Serial.println("AT+START Error");
    return;
  }

  String str = "GET /update?api_key=";
  str += apikey;
  str += "&field1=";
  str += String(abc.temperature);
  str += "&field2=";
  str += String(((abc.temperature)*(9/5))+32);
  str += "&field3=";
  str += String(abc.humidity);
  str += "\n\n\n\n";

  String tsData = "api_key=" + tweetapi + "&status=" + "Temperature in Celsius: " + String(abc.temperature) + " Degree Celsius" + "\nTemperature in Fahrenheit: " + String(((abc.temperature)*(9/5))+32) + " Degree Fahrenheit" + "\nHumidity: " + String(abc.humidity) + " Percentage \n:-D";

  String str1 = "POST /apps/thingtweet/1/statuses/update HTTP/1.1\n";
  str1 += "Host: api.thingspeak.com\n";
  str1 += "Connection: close\n";
  str1 += "Content-Type: application/x-www-form-urlencoded\n";
  str1 += "Content-Length: ";
  str1 += tsData.length();
  str1 += "\n\n";
  str1 += tsData;

  cmd = "AT+CIPSEND=";
  cmd += String(str.length());
  ser.println(cmd);
  if(ser.find(">")){
    ser.print(str);
  }

  delay(1000);
  
  command = "AT+CIPSEND=";
  command += String(str1.length());
  ser.println(command);
  if(ser.find(">")){
    ser.print(str1);
  }
  else{
    ser.println("AT+CIPCLOSE");
    //alert user
    Serial.println("AT+CIPCLOSE");
  }
  delay(16000);
}
