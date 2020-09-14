#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Uncomment one of the lines below for whatever DHT sensor type you're using!
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

/*Put your SSID & Password*/
const char *ssid = "SamsungS8";    // Enter SSID here
const char *password = "yiwk1234"; //Enter Password here
// const char *ssid = "Tesla IoT";    // Enter SSID here
// const char *password = "fsL6HgjN"; //Enter Password here

//Your Domain name with URL path or IP address with path
const char *serverName = "https://espweatherstation.000webhostapp.com/esp-post-data.php";

// Keep this API Key value to be compatible with the PHP code provided in the project page.
// If you change the apiKeyValue value, the PHP file /esp-post-data.php also needs to have the same key
String apiKeyValue = "Bj4mXo9xpJtd2D";
String sensorName = "DHT22";
String sensorLocation = "Home";

ESP8266WebServer server(80);

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
unsigned long timerDelay = 30000;

void updateStats()
{
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");

  lcd.setCursor(13, 0);
  lcd.print((int)Temperature);
  lcd.setCursor(15, 0);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity:");

  lcd.setCursor(13, 1);
  lcd.print((int)Humidity);
  lcd.setCursor(15, 1);
  lcd.print("%");
  // delay(2000);
}

void setup()
{
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.display();

  Serial.begin(115200);
  delay(100);

  pinMode(DHTPin, INPUT);
  pinMode(buttonPin, INPUT);

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
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");

  lcd.setCursor(0, 0);
  lcd.print("Weather Station");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(5000);
  lcd.clear();
}

void loop()
{
  // int reading = digitalRead(buttonPin);
  // if (reading != buttonState){
  //   Serial.println("Turn Display off");
  //   // lcd.noBacklight();
  //   lcd.noDisplay();
  // }else{
  //   Serial.println("Turn Display on");
  //   // lcd.backlight();
  //   lcd.display();
  // }

  server.handleClient();
  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity();       // Gets the values of the humidity
  updateStats();

  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay)
  {
    //Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED)
    {
      HTTPClient http;

      // Your Domain name with URL path or IP address with path
      http.begin(serverName);

      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      // Prepare your HTTP POST request data
      String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName + "&location=" + sensorLocation + "&value1=" + String(dht.readTemperature()) + "&value2=" + String(dht.readHumidity()) + "&value3=" + String(/*bme.readPressure()*/ 1 / 100.0F) + "";
      // String httpRequestData = "api_key=Bj4mXo9xpJtd2D&sensor=BME280&location=Office&value1=24.75&value2=49.54&value3=1005.14";
      Serial.print("httpRequestData: ");
      Serial.println(httpRequestData);

      // You can comment the httpRequestData variable above
      // then, use the httpRequestData variable below (for testing purposes without the BME280 sensor)
      //String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&location=Office&value1=24.75&value2=49.54&value3=1005.14";

      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);

      // If you need an HTTP request with a content type: text/plain
      //http.addHeader("Content-Type", "text/plain");
      //int httpResponseCode = http.POST("Hello, World!");

      // If you need an HTTP request with a content type: application/json, use the following:
      //http.addHeader("Content-Type", "application/json");
      //int httpResponseCode = http.POST("{\"value1\":\"19\",\"value2\":\"67\",\"value3\":\"78\"}");

      if (httpResponseCode > 0)
      {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
      }
      else
      {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else
    {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

void handle_OnConnect()
{

  // Temperature = dht.readTemperature(); // Gets the values of the temperature
  // Humidity = dht.readHumidity();       // Gets the values of the humidity
  server.send(200, "text/html", SendHTML(Temperature, Humidity));
  // Serial.println(Temperature);
  // Serial.println(Humidity);
}

void handle_NotFound()
{
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float Temperaturestat, float Humiditystat)
{
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>ESP8266 Weather Report</title>\n";
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