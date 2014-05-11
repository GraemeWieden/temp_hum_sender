/*
Temperature and humidity sensor / sender

Uses a DHT series temperature and humidity sensor and an ASK RF transmitter

Requires the following Arduino libraries to be installed in the libraries directory:
- DHT from https://github.com/markruys/arduino-DHT
- WT450Sender from https://github.com/GraemeWieden/WT450Sender

*/

#include <DHT.h>
#include <WT450Sender.h>

// set up the hardware pins
byte sensorPin = 3; // digital pin for DHT sensor
byte txPin = 4; // digital pin for RF transmitter
byte ledPin = 13; // digital pin for LED

// define our desired house and channel codes
byte houseCode = 15; // from 1 to 15
byte channelCode = 4; // from 1 to 4

DHT sensor; // create the sensor object
WT450Sender sender; // create the sender object

void setup()
{
  sensor.setup(sensorPin);
  sender.setup(txPin, houseCode, channelCode);
  
  pinMode(ledPin, OUTPUT);  
  
  Serial.begin(9600);
  Serial.println("Temperature and Humidity Sender");
}

void loop()
{
  delay(20000); // send every 20 seconds
  double t = sensor.getTemperature();
  double h = sensor.getHumidity();

  // output readings to the serial monitor
  Serial.print(t);
  Serial.print("C ");
  Serial.print(h);
  Serial.println("%");
  
  sender.send(h, t); // send the sensor readings
  
  blinkLed(); // flash the led
}

void blinkLed()
{
  digitalWrite(ledPin, HIGH);
  delay(30);   
  digitalWrite(ledPin, LOW);
}

