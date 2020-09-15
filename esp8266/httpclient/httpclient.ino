#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>

// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Uncomment one of the lines below for whatever DHT sensor type you're using!
#define DHTTYPE DHT11 // DHT 11

const char *ssid = "";         // Enter SSID here
const char *password = ""; //Enter Password here

// Domain Name with full URL Path for HTTP POST Request
const char *serverName = "http://api.thingspeak.com/update";
// Service API Key
String apiKey = "C7H8P0DJA9KCCJ3B";

String apiKeyValue = "Bj4mXo9xpJtd2D";
String sensorName = "DHT11";
String sensorLocation = "Living Room";

// DHT Sensor
uint8_t DHTPin = D5;

// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);

float Temperature;
float Humidity;

// THE DEFAULT TIMER IS SET TO 10 SECONDS FOR TESTING PURPOSES
// For a final application, check the API call limits per hour/minute to avoid getting blocked/banned
unsigned long lastTime = 0;
// Set timer to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Timer set to 10 seconds (10000)
unsigned long timerDelay = 10000;

void setup()
{
    Serial.begin(115200);

    initDisplay();
    lcd.printstr("Starting up.....");

    Serial.begin(115200);
    delay(100);

    pinMode(DHTPin, INPUT);

    dht.begin();

    WiFi.begin(ssid, password);
    Serial.println("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");

        searchMesg();
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");

    // Random seed is a number used to initialize a pseudorandom number generator
    randomSeed(analogRead(0));

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Weather Station");
    lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP());
    delay(3000);
    lcd.clear();
}

void loop()
{
    //Send an HTTP POST request every 10 seconds
    if ((millis() - lastTime) > timerDelay)
    {
        Temperature = dht.readTemperature(); // Gets the values of the temperature
        Humidity = dht.readHumidity();       // Gets the values of the humidity
        updateStats();
        //Check WiFi connection status
        if (WiFi.status() == WL_CONNECTED)
        {
            HTTPClient http;

            // Your Domain name with URL path or IP address with path
            http.begin(serverName);

            // Specify content-type header
            http.addHeader("Content-Type", "application/x-www-form-urlencoded");
            // Data to send with HTTP POST
            String httpRequestData = "api_key=" + apiKey + "&field1=" + Temperature + "&field2=" + fahrn(Temperature) + "&field3=" + Humidity;
            // Send HTTP POST request
            int httpResponseCode = http.POST(httpRequestData);

            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);

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
    lcd.print("WiFi Connection");
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
