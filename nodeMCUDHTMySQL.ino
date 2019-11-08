/* This arduino code is sending data to mysql server every 30 seconds.
Created By Embedotronics Technologies, editted by Lemongrass IOT Technology*/

#include <DHT.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>


#define DHTPIN D2
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);

const char* ssid = "Your WiFi SSID";// 
const char* password = "Your WiFi Password";

char server[] = "your local host ip address";   //eg: 192.168.0.110


WiFiClient client;    


void setup()
{
  Serial.begin(115200);
  delay(10);
  dht.begin();
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 

  Serial.println("Server started");
  Serial.print(WiFi.localIP());
  delay(1000);
  Serial.println("connecting...");
 }
 
void loop()
{ 
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  Sending_To_phpmyadmindatabase(); 
  delay(30000); // interval
 }

 void Sending_To_phpmyadmindatabase()                         // connect to mysql server at localhost
 {
   if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    Serial.print("GET http://<type in your localhost ip> /dhttest/index.php?humidity=");  //example below
    client.print("GET http://192.168.0.110/dhttest/index.php?humidity=");  
    Serial.println(h);
    client.print(h);
    client.print("&temperature=");
    Serial.println("&temperature=");
    client.print(t);
    Serial.println(t);
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: Your Local IP");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
 }
