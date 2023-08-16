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
    wifi_mqtt(char wifi_ssid, char wifi_password, char mqtt_server);
    void begin();
    bool connect_wifi();
    bool connect_mqtt();
    bool reconnect()
  private:
    char _wifi_ssid;
    char _wifi_password;
    char _mqtt_server;
    bool _mqtt;
    

};

#endif