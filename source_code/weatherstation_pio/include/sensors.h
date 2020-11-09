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

// Anemometer pin
int windPin = 13;

volatile byte pulse;
int rpm = 0;
float mps = 0;

unsigned long previousTime;
const long interval = 1000;
// Radius of anenometer
float rRadius = 0.108;
// float rRadius = 0.02;

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

void ICACHE_RAM_ATTR pulseCount()
{
  pulse++;
}

void setupWindSpeed()
{
  attachInterrupt(digitalPinToInterrupt(windPin), pulseCount, RISING);
  pulse = 0;
  previousTime = 0;
}

void speedDetect()
{
  unsigned long currentTime = millis();
  if (currentTime - previousTime > interval)
  {
    // detachInterrupt(windPin);
    noInterrupts();
    int count = pulse;
    rpm = 60000.0 / (currentTime - previousTime) * count;
    // Serial.print(speed);
    // Serial.println(" RPM ");
    mps = ((TWO_PI*rRadius)/60)*rpm;
    // Serial.print(speed, DEC);
    // Serial.println(" m/s ");
    // Serial.println(digitalRead(windPin));
    pulse = 0;
    // attachInterrupt(digitalPinToInterrupt(windPin), pulseCount, FALLING);
    interrupts();
    previousTime = millis();
    // Serial.print(speed);
    // Serial.println(" m/s ");
    // Serial.println(count);
    // Serial.println(digitalRead(windPin));
  }
}