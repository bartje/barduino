/*
  wifi_mqtt.cpp - Library for connection to wifi and mqtt
  Created by me
*/

#include "Arduino.h"
#include "wifi_mqtt.h"
#include <WiFi.h>         //For Wifi
#include <PubSubClient.h> //For MQTT

DEFINE intervalMQTT = 10000   //tijd tussen mqtt reconnect attempts
DEFINE intervalWifi = 30000   //tijd tussen wifi reconnect attempts

wifi_mqtt::wifi_mqtt(char wifiSsid, char wifiPassword)
{
    _wifiSsid = wifiSsid;
    _wifiPassword = wifiPassword ;
    _mqttServer;
    _mqttActive = false;
    _previousTimeMqtt = millis();                  
    _previousTimeWifi = millis();                  
 
}

wifi_mqtt::wifi_mqtt(char wifiSsid, char wifiPassword, char mqttServer)
{
    _wifiSsid = wifiSsid;
    _wifiPassword = wifiPassword ;
    _mqttServer = mqttServer;
    _mqttActive = true;
    _previousTimeMqtt = millis();                  
    _previousTimeWifi = millis();                  
    _intervalMqtt = 10000;                   //tijd tussen mqtt reconnect attempts
    _intervalWifi = 30000;
}

void wifi_mqtt::begin()
{
  //placeholder
}

bool wifi_mqtt::connect_wifi()
{
  return true 
}

bool wifi_mqtt::connect_mqtt()
{
  return true 
}

bool wifi_mqtt::reconnect()
{
  return true 
}