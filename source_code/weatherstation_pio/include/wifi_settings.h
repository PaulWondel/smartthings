#include <ESP8266WiFi.h>
// Make your own credentials.h file by using credentials_example.h
#include "credentials.h"

// Network SSID
const char *ssid = ssid_wifi;
// Network's password for SSID
const char *password = password_wifi;

String getSSID(){
  return WiFi.localIP().toString();
}

int getWiFiStatus(){
  return WiFi.status();
}

void connectWiFi()
{
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
  startUpMesg(getSSID());
}