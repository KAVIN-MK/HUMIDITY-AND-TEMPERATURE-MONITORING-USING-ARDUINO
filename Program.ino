#include "DHT.h"
#include "SoftwareSerial.h"
#define DHTPIN 5                       // Digital Pin 5
#define DHTTYPE DHT11                  // We are Using DHT11
String apiKey = "H9B8TGMQ28B3VD3O";    // Edit this API key according to your Account
String Host_Name = "Kavin";         // Edit Host_Name
String Password = "987654321";          // Edit Password
SoftwareSerial ser(2, 3);              // RX, TX
int i=1;
DHT dht(DHTPIN, DHTTYPE);              // Initialising Pin and Type of DHT
void setup() {                
Serial.begin(115200);                  // enable software serial
ser.begin(9600);                     // reset ESP8266
ser.println("AT+RST");               // Resetting ESP8266
dht.begin();                        // Enabling DHT11
char inv ='"';
String cmd = "AT+CWJAP";
       cmd+= "=";
       cmd+= inv;
       cmd+= Host_Name;
       cmd+= inv;
       cmd+= ",";
       cmd+= inv;
       cmd+= Password;
       cmd+= inv;
  ser.println(cmd);                    // Connecting ESP8266 to your WiFi Router
  }

// the loop 
void loop() {
  int humidity =  dht.readHumidity();             // Reading Humidity Value
  int temperature = dht.readTemperature();        // Reading Temperature Value
  String state1=String(humidity);                 // Converting them to string 
  String state2=String(temperature);              // as to send it through URL
  String cmd = "AT+CIPSTART=\"TCP\",\"";          // Establishing TCP connection
  cmd += "184.106.153.149";                       // api.thingspeak.com
  cmd += "\",80";                                 // port 80
  ser.println(cmd);
  Serial.println(cmd);
 if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }
String getStr = "https://api.thingspeak.com/update?api_key=";         // prepare GET string
  getStr += apiKey;
  getStr +="&field1=";
  getStr += String(state1);                       // Humidity Data
  getStr +="&field2=";
  getStr += String(state2);                       // Temperature Data
  getStr += "\r\n\r\n";
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());                // Total Length of data
  ser.println(cmd);
  Serial.println(cmd);
  //Serial.print(getStr);
//if(ser.find(">")){
    ser.print(getStr);
    Serial.print(getStr);
 // }
//  else{
 //   ser.println("AT+CIPCLOSE");                  // closing connection
    // alert user
  //  Serial.println("AT+CIPCLOSE");
 // }
 delay(5000);                                  // Update after every 15 seconds
}