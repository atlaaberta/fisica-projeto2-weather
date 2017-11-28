//library DHT22
#include <DHT.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
const char* ssid = "Torre Stark1";
const char* password = "abacate15";

#define DHTPIN D5 // what pin we’re connected to
DHT dht(DHTPIN, DHT11,15);
 
void setup () {
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  delay(10);
  
  dht.begin();
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print("Connecting..");
 
  }

  Serial.println("WiFi connected");
  Serial.println();
 
}
 
void loop() {

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

  // We now create a URI for the request
  String url = "https://api.thingspeak.com/update?api_key=I4CNQBYEG6HGFMEV";
  url +="&field1=";
  url += String(t);
  url +="&field2=";
  url += String(h);
  url +="&field3=";
  url += String(dp);
  
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient

    Serial.println("Requesting: " + url);
 
    http.begin("http://jsonplaceholder.typicode.com/users/1");  //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request
 
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload
 
    } else  {
      Serial.println("Error! Que bosta");
    }
 
    http.end();   //Close connection
 
  }
 
  delay(30000);    //Send a request every 30 seconds
 
}

