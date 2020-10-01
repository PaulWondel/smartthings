#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SmartThings.h>
#include "DHT.h"

#include "httpclient.h"
#include "lcd.h"
// Make your own credentials.h file by using credentials_example.h
#include "credentials.h"

// Uncomment one of the lines below for whatever DHT sensor type you're using!
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

// Network SSID
const char *ssid = ssid_wifi;
// Network's password for SSID
const char *password = password_wifi;

ESP8266WebServer webServer(80);

// DHT Sensor
uint8_t DHTPin = D5;

// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);

float Temperature;
float Humidity;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 30 seconds (30000)
unsigned long timerDelay = 600000;

// defines pins numbers
const int ProxSensor=A0;

// defines variables
long duration;
int distance;

// API settings
API api;
int weatherStationId = stationId;
int studentId;

// Send a HTTP POST request
void sendHTTP()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    http.begin(serverName);

    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName + "&location=" \
    + sensorLocation + "&value1=" + String(dht.readTemperature()) + "&value2=" \
    + String((int)dht.readHumidity()) + "&value3=" \
    + String(dht.readTemperature(true)) + "";
    
    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0)
    {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      if (httpResponseCode > 200)
      {
        errorSiteMesg();
      }
    }
    else
    {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
      errorSiteMesg();
    }
    http.end();
  }
  else
  {
    Serial.println("Wi-Fi Disconnected");
    errorMesg();
  }
}

// Send data of HTML page to webserver
String SendHTML(float Temperaturestat, float Humiditystat, float Fahrn)
{
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>ESP8266 Weather Station Report</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr += "p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>Paul's Home Weather Station</h1>\n";
  ptr += "<p>My website version <a href=https://espweatherstation.000webhostapp.com/>here</a>. </p>";
  ptr += "<p>More weather stations <a href=https://schetsboek.github.io/hr/map.html>here</a>. </p>\n";

  ptr += "<p>Temperature: ";
  ptr += (float)Temperaturestat;
  ptr += "<span>&#176;</span>";
  ptr += "C</p>";
  ptr += "<p>Temperature: ";
  ptr += (float)Fahrn;
  ptr += "<span>&#176;</span>";
  ptr += "F</p>";
  ptr += "<p>Humidity: ";
  ptr += (int)Humiditystat;
  ptr += "%</p>";

  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

// Update the values in the browser on point of connection of device to server
void handle_OnConnect()
{
  webServer.send(200, "text/html", SendHTML(dht.readTemperature(), dht.readHumidity(), dht.readTemperature(true)));
}

// Give error message if data not found
void handle_NotFound()
{
  webServer.send(404, "text/plain", "Not found");
}

// Turn display on and of if object is detected in front of weather station
void screen()
{
  long state = analogRead(ProxSensor);
  if (state > 100)
  {
    // Serial.println("Turn Display off");
    powerDisplay(false);
  }
  else
  {
    // Serial.println("Turn Display on");
    powerDisplay(true);
    delay(2000);
  }
}

// Send data to the API 
void sendToAPI(){
  api.postWeatherData("Humidity", dht.readHumidity(), weatherStationId);
  api.postWeatherData("Temperature", dht.readTemperature(), weatherStationId);
  Serial.println("Data successfully sent to API");
}

void setup()
{
  initDisplay();

  Serial.begin(115200);
  delay(100);

  pinMode(DHTPin, INPUT);
  pinMode(ProxSensor,INPUT);

  dht.begin();

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
    searchMesg();
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());

  webServer.on("/", handle_OnConnect);
  webServer.onNotFound(handle_NotFound);

  webServer.begin();
  Serial.println("HTTP server started");

  startUpMesg(WiFi.localIP().toString());

  sendHTTP();

  studentId = api.login(idStudent, pwStudent, false);
  sendToAPI();
}

void loop()
{
  // Gets the values of the temperature
  Temperature = dht.readTemperature();
  // Gets the values of the humidity
  Humidity = dht.readHumidity();

  // Will upload data when device connects to webpage or refreshes
  webServer.handleClient();

  //Send a HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay)
  {
    sendHTTP();
    sendToAPI();

    lastTime = millis();
  }
  
  // Update values on lcd screen
  updateStats(Temperature, Humidity);
  screen();
}