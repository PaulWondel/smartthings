#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Uncomment one of the lines below for whatever DHT sensor type you're using!
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

/*Put your SSID & Password*/
// const char *ssid = "SamsungS8";    // Enter SSID here
// const char *password = "yiwk1234"; //Enter Password here
// const char *ssid = "Tesla IoT";    // Enter SSID here
// const char *password = "fsL6HgjN"; //Enter Password here
const char *ssid = "";         // Enter SSID here
const char *password = ""; //Enter Password here

//Your Domain name with URL path or IP address with path
const char *serverName = "http://espweatherstation.000webhostapp.com/esp-post-data.php";

// Keep this API Key value to be compatible with the PHP code provided in the project page.
// If you change the apiKeyValue value, the PHP file /esp-post-data.php also needs to have the same key
String apiKeyValue = "Bj4mXo9xpJtd2D";
String sensorName = "DHT11";
String sensorLocation = "Living Room";

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

void setup()
{
  initDisplay();
  lcd.printstr("Starting up.....");

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

  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity();       // Gets the values of the humidity

  webServer.handleClient();
  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay)
  {
    sendHTTP();

    lastTime = millis();
  }
  updateStats();

  // if (WiFi.status() != WL_CONNECTED)
  // {
  //   delay(1000);
  //   Serial.println("Reconnecting to Wi-Fi");
  //   WiFi.reconnect();
  //   reconnectMesg();
  // }
}

void sendHTTP()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    http.begin(serverName);

    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName + "&location=" + sensorLocation
        + "&value1=" + String(dht.readTemperature()) + "&value2=" + String(dht.readHumidity()) 
        + "&value3=" + String(fahrn(dht.readTemperature())) + "";
    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0)
    {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
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

void initDisplay()
{
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.display();
}

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
  // delay(1000);
}

void searchMesg()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Searching for a");
  lcd.setCursor(0, 1);
  lcd.print("Wi-Fi Connection");
}

void reconnectMesg()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Reconnecting");
  lcd.setCursor(0, 1);
  lcd.print("Wi-Fi Connection");
}

void errorMesg()
{
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("Wi-Fi");
  lcd.setCursor(2, 1);
  lcd.print("Disconnected");
  delay(2000);
  lcd.clear();
}

void errorSiteMesg()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Error uploading");
  lcd.setCursor(0, 1);
  lcd.print("to website");
  delay(10000);
  lcd.clear();
}

void handle_OnConnect()
{

  // Temperature = dht.readTemperature(); // Gets the values of the temperature
  // Humidity = dht.readHumidity();       // Gets the values of the humidity
  webServer.send(200, "text/html", SendHTML(Temperature, Humidity));
}

void handle_NotFound()
{
  webServer.send(404, "text/plain", "Not found");
}

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