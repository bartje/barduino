/*
  wifi_mqtt.cpp - Library for connection to wifi and mqtt
  Created by me
*/

#include "Arduino.h"
#include "wifi_mqtt.h"
#include <WiFi.h>         //For Wifi
#include <PubSubClient.h> //For MQTT

wifi_mqtt::wifi_mqtt(int pin)
{
  _pin = pin;
}

void wifi_mqtt::begin()
{
  pinMode(_pin, OUTPUT);
}

void wifi_mqtt::dot()
{
  digitalWrite(_pin, HIGH);
  delay(250);
  digitalWrite(_pin, LOW);
  delay(250);  
}

void wifi_mqtt::dash()
{
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(250);
}