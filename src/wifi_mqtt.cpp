/*
  wifi_mqtt.cpp - Library for connection to wifi and mqtt
  Created by me
*/

#include "wifi_mqtt.h"
#include "Arduino.h"

//#include <WiFi.h>         //For Wifi
//#include <PubSubClient.h> //For MQTT

#define intervalMqtt 10000   //tijd tussen mqtt reconnect attempts
#define intervalWifi 30000   //tijd tussen wifi reconnect attempts
#define maxNotConnectedCounter 150

wifi_mqtt::wifi_mqtt(String wifiSsid, String wifiPassword)
{
    _wifiSsid = wifiSsid;
    _wifiPassword = wifiPassword ;
    //_mqttServer;
    _mqttActive = false;
    _previousTimeMqtt = millis();                  
    _previousTimeWifi = millis();                  
 
}

wifi_mqtt::wifi_mqtt(String wifiSsid, String wifiPassword, const char* mqttServer)
{
    _wifiSsid = wifiSsid;
    _wifiPassword = wifiPassword ;
    _mqttServer = mqttServer;
    _mqttActive = true;
    _previousTimeMqtt = millis();                  
    _previousTimeWifi = millis();
  
    PubSubClient mqtt_client(espClient);
    for(int i=0; i<17; i=i+8) {
	    _chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
	  }
    _mqtt_client_id="ESP32-";
    _mqtt_client_id=_mqtt_client_id+_chipId;        

}

void wifi_mqtt::begin()
{
  connect_wifi();
  if (_mqttActive) {
    connect_mqtt();
  }
}

bool wifi_mqtt::connect_wifi()
{
  _notConnectedCounter = 0;
  delay(2);
  Serial.print("Connecting to ");
  Serial.print(_wifiSsid);
  WiFi.begin(_wifiSsid, _wifiPassword);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
    _notConnectedCounter++;
      if(_notConnectedCounter > maxNotConnectedCounter) { // Reset board if not connected after xxx attempts
          Serial.println("Resetting due to Wifi not connecting...");
          ESP.restart();
          return false;
      }
  }
  Serial.println("OK");
  Serial.print("   IP address: ");
  Serial.println(WiFi.localIP());
  return true;
}

bool wifi_mqtt::connect_mqtt() {
  bool rc;
  mqtt_client.setServer(_mqttServer, 1883);
  mqtt_client.setBufferSize(1024);
  Serial.printf("   Server IP: %s\r\n",_mqttServer);  
  //Serial.printf("   Username:  %s\r\n",mqtt_user);
  //Serial.println("   Cliend Id: "+mqtt_client_id);  
  Serial.println("   MQTT configured!");       
  
  if (!mqtt_client.connected()) {
    Serial.println("Attempting MQTT connection...");
    Serial.print("   client: ");
    Serial.println(&_mqtt_client_id); 
    // Attempt to connect   
    //if (mqtt_client.connect(mqtt_client_id.c_str(), mqtt_user, mqtt_password)) {
    //String mci = _mqtt_client_id;
    //if (mqtt_client.connect(&mci)) {
    //if (mqtt_client.connect(_mqtt_client_id.c_str())) {
    if (mqtt_client.connect("test")) {
      Serial.println("MQTT connected");
      rc = true;
    } else {
      //Serial.print("failed, rc=");
      //Serial.print(mqtt_client.state());
      rc = false;
    }
  } else {
    rc = true;
  }
  return rc;
}

bool wifi_mqtt::reconnect() {
  bool rc;
  _diffWifi = millis() - _previousTimeWifi;
  
  if (WiFi.status() == WL_CONNECTED) {
    _previousTimeWifi += _diffWifi;

    if (!_mqttActive) {
      rc = true;
    } else {
      _diffMqtt = millis() - _previousTimeMqtt;
      
      // indien mqtt connected, dan mag je .loop doen
      if (mqtt_client.connected()){ 
        mqtt_client.loop();
        _previousTimeMqtt += _diffMqtt;
        rc  = true;
      } else {
        if (_diffMqtt>intervalMqtt) {
          rc = connect_mqtt();
          _previousTimeMqtt += _diffMqtt;
        } else {
          rc = false;
        }
      }
      
    }
  } else if (_diffWifi > intervalWifi) {
      WiFi.reconnect();
      _previousTimeWifi += _diffWifi;
      rc = false;
  }
  return rc;
}