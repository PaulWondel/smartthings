
// button
int reading = digitalRead(buttonPin);
if (reading != buttonState)
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

// http
HTTPClient http;

// Your Domain name with URL path or IP address with path
http.begin(serverName);

// Specify content-type header
http.addHeader("Content-Type", "application/x-www-form-urlencoded");

// Prepare your HTTP POST request data
String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName + "&location=" + sensorLocation + "&value1=" + String(dht.readTemperature()) + "&value2=" + String(dht.readHumidity()) + "&value3=" + String(/*bme.readPressure() 1 / 100.0F*/ 0) + "";
Serial.print("httpRequestData: ");
Serial.println(httpRequestData);

// You can comment the httpRequestData variable above
// then, use the httpRequestData variable below (for testing purposes without the BME280 sensor)
//String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&location=Office&value1=24.75&value2=49.54&value3=1005.14";

// Send HTTP POST request
int httpResponseCode = http.POST(httpRequestData);

// If you need an HTTP request with a content type: text/plain
// http.addHeader("Content-Type", "text/plain");
// int httpResponseCode = http.POST("Hello, World!");

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