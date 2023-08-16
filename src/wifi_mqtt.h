/*
  wifi_mqtt.h - Library for connection to wifi and mqtt
  Created by me
*/

#ifndef wifi_mqtt_h
#define wifi_mqtt_h

#include <Arduino.h>      //
#include "IPAddress.h"
#include "WiFi.h"         //For Wifi
#include "PubSubClient.h" //For MQTT

class wifi_mqtt
{
  public:
    wifi_mqtt(char wifiSsid, char wifiPassword);
    wifi_mqtt(char wifiSsid, char wifiPassword, char mqttServer);
    
    void begin();
    bool connect_wifi();
    bool connect_mqtt();
    bool reconnect();
  private:
    char _wifiSsid;
    char _wifiPassword;
    char _mqttServer;
    bool _mqttActive;
    unsigned long _previousTimeMqtt;                  
    unsigned long _previousTimeWifi;                  
    uint32_t _notConnectedCounter;
    String _mqtt_client_id;
    

};

#endif