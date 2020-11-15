#include <SmartThings.h>
#include "sensors.h"
#include "roomsphere.h"
#include "lcd.h"
#include "wifi_settings.h"
#include "httpclient.h"
#include "webserver.h"

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
// Timer for 10 minutes (600000), 30 seconds (30000)
unsigned long timerDelay = 300000;
unsigned long lastTime = 0;

// API settings
API api;
int weatherStationId = stationId;
int studentId;

// Send data to the API
void sendToAPI()
{
  api.postWeatherData("Temperature", getTempCel(), weatherStationId);
  api.postWeatherData("Humidity", getHumid(), weatherStationId);
  api.postWeatherData("WindSpeed", getWindSpeed(), weatherStationId);
  Serial.println("Data successfully sent to API");
}

// Initialize display and dht sensor
void init_all()
{
  initDisplay();
  initDHT();
  initRGB();
}

void setup()
{
  Serial.begin(115200);
  delay(100);

  setPINMODE();
  setupWindSpeed();
  init_all();

  // Leave display on for a few seconds
  setMotionDelay(2);

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

  // Update values on lcd screen
  updateStats(getTempCel(), getHumid(), getWindSpeed());
  
  // Turn display on and of if object/motion is detected near weather station
  PIRSensor();
  speedDetect();
  pickColor(int(getTempCel()));

  //Send data every 10 minutes
  if ((millis() - lastTime) > timerDelay)
  {
    // Send data to website through HTTP
    sendHTTP();
    // Send data to website through an API
    sendToAPI();

    lastTime = millis();
  }
}