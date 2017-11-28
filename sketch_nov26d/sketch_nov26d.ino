/*
 *  HTTP over TLS (HTTPS) example sketch
 *
 *  This example demonstrates how to use
 *  WiFiClientSecure class to access HTTPS API.
 *  We fetch and display the status of
 *  esp8266/Arduino project continuous integration
 *  build.
 *
 *  Created by Ivan Grokhotkov, 2015.
 *  This example is in public domain.
 */

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <DHT.h>

const char* ssid = "Torre Stark1";
const char* password = "abacate15";

String apiKey = "I4CNQBYEG6HGFMEV";
const char* host = "api.thingspeak.com";
const int httpsPort = 443;

#define DHTPIN D5 // what pin we’re connected to

DHT dht(DHTPIN, DHT11,15);

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    return;
  }
  
  
  Serial.print("Temperature:      ");
  Serial.print(t);
  Serial.print(" degrees Celcius ");
  Serial.println();
  
  Serial.print("Humidity:         ");
  Serial.print(h);
  Serial.print("%");
  Serial.println();
  
  //--- extra---- you can measure dew point with the temperature and the humidity
  
  double gamma = log(h/100) + ((17.62*t) / (243.5+t));
  double dp = 243.5*gamma / (17.62-gamma);
  
  Serial.print("Dew point:        ");
  Serial.print(dp);
  Serial.print(" degrees Celcius ");
  Serial.println();
  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  String url = "/update";
  url += "?api_key=";
  url += apiKey;
  url +="&field1=";
  url += String(t);
  url +="&field2=";
  url += String(h);
  url +="&field3=";
  url += String(dp);
  
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");
  delay(20000);
}
