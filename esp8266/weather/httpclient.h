#include <ESP8266HTTPClient.h>

//Your Domain name with URL path or IP address with path
const char *serverName = "http://espweatherstation.000webhostapp.com/esp-post-data.php";

// Keep this API Key value to be compatible with the PHP code provided in the project page.
// If you change the apiKeyValue value, the PHP file /esp-post-data.php also needs to have the same key
String apiKeyValue = "Bj4mXo9xpJtd2D";
String sensorName = "DHT11";
String sensorLocation = "Living Room";