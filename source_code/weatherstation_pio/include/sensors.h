#include "DHT.h"

// Uncomment one of the lines below for whatever DHT sensor type you're using!
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

// DHT Sensor pin SD3
uint8_t DHTPin = 10;

// Proximity Sensor pin SD2
const int ProxSensor = 9;

// Anemometer pin D7
int windPin = 13;

int calibrationTime = 30;
long unsigned int lowIn;
long unsigned int pause;
boolean lockLow = true;
boolean takeLowTime;
int PIRValue = 0;

volatile byte pulse;
int rpm = 0;
float mps = 0;

unsigned long previousTime;
const long interval = 1000;
// Radius of anenometer
float rRadius = 0.108;
// float rRadius = 0.02;

// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);

// Set PINMODE for setup()
void setPINMODE()
{
  pinMode(DHTPin, INPUT);
  pinMode(ProxSensor, INPUT);
  pinMode(windPin, INPUT_PULLUP);
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

// Gets the values of the windspeed
float getWindSpeed()
{
  return mps;
}

// Set motion pause for set seconds
void setMotionDelay(int timer)
{
  timer = timer*(1000);
  pause = timer;
  digitalWrite(ProxSensor, LOW);
}

// Pulse counter for interrupt
void ICACHE_RAM_ATTR pulseCount()
{
  pulse++;
}

// Initialize variables for setup() in main file
void setupWindSpeed()
{
  attachInterrupt(digitalPinToInterrupt(windPin), pulseCount, RISING);
  pulse = 0;
  previousTime = 0;
}

// Detect and calculate windspeed
void speedDetect()
{
  unsigned long currentTime = millis();
  if (currentTime - previousTime > interval)
  {
    noInterrupts();
    int count = pulse;
    rpm = 60000.0 / (currentTime - previousTime) * count;   
    mps = ((TWO_PI*rRadius)/60)*rpm;
    pulse = 0;
    interrupts();
    previousTime = millis();

    // FOR DEBUG PURPOSES ONLY
    // Serial.print(rpm);
    // Serial.println(" RPM ");
    // Serial.print(mps);
    // Serial.println(" m/s ");
    // Serial.println(count);
    // Serial.println(digitalRead(windPin));
  }
}