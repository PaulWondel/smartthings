#include "DHT.h"

// Uncomment one of the lines below for whatever DHT sensor type you're using!
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

int calibrationTime = 30;
long unsigned int lowIn;
long unsigned int pause;
boolean lockLow = true;
boolean takeLowTime;
int PIRValue = 0;

// DHT Sensor
uint8_t DHTPin = D5;

// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);

// defines pins numbers
const int ProxSensor=D6;

// Set PINMODE for setup()
void setPINMODE()
{
  pinMode(DHTPin, INPUT);
  pinMode(ProxSensor, INPUT);
}

// Initialize dht pin
void initDHT()
{
  dht.begin();
}

// Gets the values of the temperature in celsius
float getTempCel()
{
  return dht.readTemperature();
}

// Gets the values of the temperature in fahrenheit
float getTempFah()
{
  return dht.readTemperature(true);
}

// Gets the values of the humidity
float getHumid()
{
  return dht.readHumidity();
}

// Set motion pause for set seconds
void setMotionDelay(int timer)
{
  timer = timer*(1000);
  pause = timer;
  digitalWrite(ProxSensor, LOW);
}