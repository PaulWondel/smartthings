#include <Arduino.h>

#include <SmartThings.h>
#include "sensors.h"
#include "lcd.h"
#include "wifi_settings.h"
#include "httpclient.h"
#include "webserver.h"

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer for 10 minutes (600000)
// Timer for 30 seconds (30000)
unsigned long timerDelay = 600000;


// API settings
API api;
int weatherStationId = stationId;
int studentId;

// Send data to the API
void sendToAPI()
{
  api.postWeatherData("Humidity", getHumid(), weatherStationId);
  api.postWeatherData("Temperature", getTempCel(), weatherStationId);
  Serial.println("Data successfully sent to API");
}

// Initialize display and dht sensor
void init_all()
{
  initDisplay();
  initDHT();
}

void setup()
{
  Serial.begin(115200);
  delay(100);

  pinMode(DHTPin, INPUT);
  pinMode(ProxSensor, INPUT);

  init_all();

  connectWiFi();
  initWebserver();

  sendHTTP();

  studentId = api.login(idStudent, pwStudent, false);
  sendToAPI();
}

void loop()
{
  // Will upload data when device connects to webpage or refreshes
  runServer();

  //Send data every 10 minutes
  if ((millis() - lastTime) > timerDelay)
  {
    // Send data to website through HTTP
    sendHTTP();
    // Send data to website through an API
    sendToAPI();

    lastTime = millis();
  }
  // Update values on lcd screen
  updateStats(getTempCel(), getHumid());
  // Turn display on and of if object is detected in front of weather station
  screen();
}