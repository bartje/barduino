/*
  wifi_mqtt.h - Library for connection to wifi and mqtt
  Created by me
*/

#ifndef wifi_mqtt_h
#define wifi_mqtt_h

#include "Arduino.h"      //
#include <WiFi.h>         //For Wifi
#include <PubSubClient.h> //For MQTT

class wifi_mqtt
{
  public:
    wifi_mqtt(char wifiSsid, char wifiPassword);
    wifi_mqtt(char wifiSsid, char wifiPassword, char mqttServer);
    
    void begin();
    bool connect_wifi();
    bool connect_mqtt();
    bool reconnect()
  private:
    char _wifiSsid;
    char _wifiPassword;
    char _mqttServer;
    bool _mqttActive;
    unsigned long _previousTimeMqtt = millis();                  
    unsigned long _previousTimeWifi = millis();                  
    const unsigned long _intervalMqtt = 10000;                   //tijd tussen mqtt reconnect attempts
    const unsigned long _intervalWifi = 30000;                   //tijd tussen Wifi reconnect attempts
    

};

#endif