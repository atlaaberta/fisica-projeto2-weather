#include "ESP8266WiFi.h"
#include <aREST.h>
#include <WiFiClientSecure.h>
#include "DHT.h"
// DHT11 sensor pins
#define DHTPIN D5
#define DHTTYPE DHT11
// Create aREST instance
aREST rest = aREST();
// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE, 15);
// WiFi parameters
const char* ssid = "Torre Stark";
const char* password = "abacate15";
// The port to listen for incoming TCP connections
#define LISTEN_PORT 80
// Create an instance of the server
WiFiServer server(LISTEN_PORT);
// Variables to be exposed to the API
float temperature;
float humidity;
String apiKey = "39YJM4SS4Q8ZCZT0";
const char* server2 = "api.thingspeak.com";
WiFiClientSecure client;

void setup(void)
{
// Start Serial
Serial.begin(115200);
// Init DHT
dht.begin();
// Init variables and expose them to REST API
rest.variable("temperature",&temperature);
rest.variable("humidity",&humidity);
// Give name and ID to device
rest.set_id("1");
rest.set_name("esp8266");
// Connect to WiFi
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
// Start the server
server.begin();
Serial.println("Server started");
// Print the IP address
Serial.println(WiFi.localIP());
}

void loop() {
  //rest.glow_led();
  // Reading temperature and humidity
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  
  if (client.connect(server2,80)) {
    String postStr = apiKey;
    postStr +="&field1=";
    postStr += String(temperature);
    postStr +="&field2=";
    postStr += String(humidity);
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
  }
  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);
}
