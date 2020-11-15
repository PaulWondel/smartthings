#include <ESP8266WebServer.h>

ESP8266WebServer webServer(80);

// Send data of HTML page to webserver
String SendHTML(float Temperaturestat, float Humiditystat, float Fahrn, float WindSpeed)
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
  ptr += "<p>Wind Speed: ";
  ptr += (float)WindSpeed;
  ptr += "m/s</p>";

  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

// Update the values in the browser on point of connection of device to server
void handle_OnConnect()
{
  webServer.send(200, "text/html", SendHTML(getTempCel(), getHumid(), getTempFah(), getWindSpeed()));
}

// Give error message if data not found
void handle_NotFound()
{
  webServer.send(404, "text/plain", "Not found");
}

void initWebserver()
{
  webServer.on("/", handle_OnConnect);
  webServer.onNotFound(handle_NotFound);
  webServer.begin();

  Serial.println("HTTP server started");
}

void runServer()
{
  webServer.handleClient();
}