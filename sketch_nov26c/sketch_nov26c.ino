// www.arduinesp.com
//
// Plot DTH11 data on thingspeak.com using an ESP8266
// April 11 2015
// Author: Jeroen Beemster
// Website: www.arduinesp.com

#include <DHT.h>
#include <ESP8266WiFi.h>

// replace with your channel’s thingspeak API key,
String apiKey = "I4CNQBYEG6HGFMEV";
const char* ssid = "Torre Stark1";
const char* password = "abacate15";

const char* server = "api.thingspeak.com";
#define DHTPIN D5 // SO CONNECT THE DHT11/22 SENSOR TO PIN D4 OF THE NODEMCU

DHT dht(DHTPIN, DHT11,15); //CHANGE DHT11 TO DHT22 IF YOU ARE USING DHT22
WiFiClient client;

void setup() {
Serial.begin(115200);
delay(10);
dht.begin();

WiFi.begin(ssid, password);

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

}

void loop() {

float h = dht.readHumidity();
float t = dht.readTemperature();
if (isnan(h) || isnan(t)) {
Serial.println("Failed to read from DHT sensor!");
return;
}

  //--- extra---- you can measure dew point with the temperature and the humidity

  double gamma = log(h/100) + ((17.62*t) / (243.5+t));
  double dp = 243.5*gamma / (17.62-gamma);

if (client.connect(server,443)) { // "184.106.153.149" or api.thingspeak.com
String postStr = apiKey;
postStr +="&field1=";
postStr += String(t);
postStr +="&field2=";
postStr += String(h);
postStr +="&field3=";
postStr += String(dp);
postStr += "\r\n\r\n";

client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(postStr.length());
client.print("\n\n");
client.print(postStr);

Serial.print("Temperature: ");
Serial.print(t);
Serial.print(" degrees Celcius Humidity: ");
Serial.print(h);
Serial.print(" degrees Celcius dew point: ");
Serial.print(dp);
Serial.println("% send to Thingspeak");
}
client.stop();

Serial.println("Waiting...");
// thingspeak needs minimum 15 sec delay between updates
delay(20000);
}
