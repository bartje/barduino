/*
  wifi_mqtt.h - Library for connection to wifi and mqtt
  Created by me
*/

#ifndef wifi_mqtt_h
#define wifi_mqtt_h

#include <Arduino.h>      //
#include "WiFi.h"         //For Wifi
#include "PubSubClient.h" //For MQTT

class wifi_mqtt
{
  public:
    wifi_mqtt(String wifiSsid, String wifiPassword);
    wifi_mqtt(String wifiSsid, String wifiPassword, const char* mqttServer);
    
    void begin();
    bool connect_wifi();
    bool connect_mqtt();
    bool reconnect();
  private:
    String _wifiSsid;
    String _wifiPassword;
    const char* _mqttServer;
    bool _mqttActive;
    unsigned long _previousTimeMqtt;                  
    unsigned long _previousTimeWifi; 
    unsigned long _diffWifi;
    unsigned long _diffMqtt;                 
    uint32_t _notConnectedCounter;
    String _mqtt_client_id;
    uint32_t _chipId;
    WiFiClient espClient;
    PubSubClient mqtt_client;
    

};

#endif