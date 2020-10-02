/*
/ In this file is the information of the website
*/

#include <ESP8266HTTPClient.h>

//Your Domain name with URL path or IP address with path
const char *serverName = "http://espweatherstation.000webhostapp.com/esp-post-data.php";

// Keep this API Key value to be compatible with the PHP code provided in the project page.
// If you change the apiKeyValue value, the PHP file /esp-post-data.php also needs to have the same key
String apiKeyValue = "Bj4mXo9xpJtd2D";
String sensorName = "DHT11";
String sensorLocation = "Living Room";

// Send a HTTP POST request
void sendHTTP()
{
  if (getWiFiStatus() == WL_CONNECTED)
  {
    HTTPClient http;
    http.begin(serverName);

    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName + "&location=" \
    + sensorLocation + "&value1=" + String(getTempCel()) + "&value2=" \
    + String((int)getHumid()) + "&value3=" \
    + String(getTempFah()) + "";
    
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