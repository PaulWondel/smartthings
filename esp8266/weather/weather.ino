#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

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

const int buttonPin = D6;
int buttonState = LOW;

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
const int trigPin = 13; //D7
const int echoPin = 12; //D6

// defines variables
long duration;
int distance;

void setup()
{
  initDisplay();
  lcd.printstr("Starting up.....");

  Serial.begin(115200);
  delay(100);

  pinMode(DHTPin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input

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

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Weather Station");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(3000);
  lcd.clear();

  sendHTTP();
}

void loop()
{
  // Gets the values of the temperature
  Temperature = dht.readTemperature();
  // Gets the values of the humidity
  Humidity = dht.readHumidity();

  webServer.handleClient();
  //Send a HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay)
  {
    sendHTTP();

    lastTime = millis();
  }
  updateStats(Temperature, Humidity);
  screen();

  // if (WiFi.status() != WL_CONNECTED)
  // {
  //   delay(1000);
  //   Serial.println("Reconnecting to Wi-Fi");
  //   WiFi.reconnect();
  //   reconnectMesg();
  // }
}

// Send a HTTP POST request
void sendHTTP()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    http.begin(serverName);

    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName + "&location=" + sensorLocation + "&value1=" + String(dht.readTemperature()) + "&value2=" + String(dht.readHumidity()) + "&value3=" + String(fahrn(dht.readTemperature())) + "";
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

// Celsius to Fahrenheit formula, F = C * 1.8 + 32
float fahrn(float temperature)
{
  float farh = temperature * 1.8;
  farh = farh + 32;
  return farh;
}

// Update the values in the browser on point of connection of device to server
void handle_OnConnect()
{
  webServer.send(200, "text/html", SendHTML(Temperature, Humidity));
}

// Give error message if data not found
void handle_NotFound()
{
  webServer.send(404, "text/plain", "Not found");
}

// Send data of HTML page to webserver
String SendHTML(float Temperaturestat, float Humiditystat)
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
  ptr += "<h1>ESP8266 Home Weather Station</h1>\n";

  ptr += "<p>Temperature: ";
  ptr += (int)Temperaturestat;
  ptr += "°C</p>";
  ptr += "<p>Humidity: ";
  ptr += (int)Humiditystat;
  ptr += "%</p>";

  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

void getDistance()
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(400);
}

void screen()
{
  getDistance();
  if (distance > 40)
  {
    Serial.println("Turn Display off");
    // lcd.noBacklight();
    lcd.noDisplay();
  }
  else
  {
    Serial.println("Turn Display on");
    // lcd.backlight();
    lcd.display();
  }
}