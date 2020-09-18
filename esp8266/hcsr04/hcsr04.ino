#include "DHT.h"

#define DHTTYPE DHT11 // DHT 11

uint8_t DHTPin = 14;
DHT dht(DHTPin, DHTTYPE);

float Temperature;
float Humidity;

// defines pins numbers
const int trigPin = 13; //D4
const int echoPin = 12; //D3

// defines variables
long duration;
int distance;

void setup()
{
    pinMode(DHTPin, INPUT);
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
    Serial.begin(115200);     // Starts the serial communication
}

void loop()
{

    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculating the distance
    distance = duration * 0.034 / 2;
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);

    // // Gets the values of the temperature
    // Serial.println(dht.readTemperature());
    // // Gets the values of the humidity
    // Serial.println(dht.readHumidity());
    // delay(400);
}