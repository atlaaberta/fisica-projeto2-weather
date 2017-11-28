
/*


This sketch is a combination of two other sketches:
1.
Plot DTH11 data on thingspeak.com using an ESP8266
April 11 2015
Author: Jeroen Beemster
Website: www.arduinesp.com
2.
Example sketch: adafruit BMP 085
Sensor api BMP180
*/ 


//library DHT22
#include <DHT.h>

//library esp
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

//library bmp180
#include <Wire.h>
#include <Adafruit_Sensor.h>


// replace with your channel’s thingspeak API key,
String apiKey = "I4CNQBYEG6HGFMEV";                                     //fill in the api key from thingspeak
const char* ssid = "Torre Stark";                                  //fill in your wifi name
const char* password = "abacate15";                              //fill in your wifi password

const char* server = "api.thingspeak.com";
#define DHTPIN D5 // what pin we’re connected to

DHT dht(DHTPIN, DHT11,15);
WiFiClientSecure client;

int sensorPin = A0;    // input for LDR and rain sensor
int enable1 = 15;      // enable reading LDR
int enable2 = 13;      // enable reading Rain sensor


int sensorValue1 = 0;  // variable to store the value coming from sensor LDR
int sensorValue2 = 0;  // variable to store the value coming from sensor Rain sensor


//--------------------------setup-------------------------
void setup() {
  
  // declare the enable and ledPin as an OUTPUT:
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);
  
    
  Serial.begin(115200);
  delay(10);
  
  dht.begin();
  
  WiFi.begin(ssid, password);
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.print("..........");
  Serial.println();
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  
  }
  Serial.println("WiFi connected");
  Serial.println();

}


void loop() {
//--------------------------DHT22/DHT11-------------------------

float h = dht.readHumidity();
float t = dht.readTemperature();

if (isnan(h) || isnan(t)) {
Serial.println("Failed to read from DHT sensor!");
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

//--------------------------thingspeak-------------------------

const int httpPort = 443;
  if (!client.connect(server, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/update";
  url += "?api_key=";
  url += apiKey;
  url +="&field1=";
  url += String(t);
  url +="&field2=";
  url += String(h);
  url +="&field3=";
  url += String(dp);
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + server + "\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");


// thingspeak needs minimum 15 sec delay between updates
delay(20000);
}

