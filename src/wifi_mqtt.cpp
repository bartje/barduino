/*
  wifi_mqtt.cpp - Library for connection to wifi and mqtt
  Created by me
*/

#include "wifi_mqtt.h"
#include "Arduino.h"

//#include <WiFi.h>         //For Wifi
//#include <PubSubClient.h> //For MQTT

#define intervalMQTT 10000   //tijd tussen mqtt reconnect attempts
#define intervalWifi 30000   //tijd tussen wifi reconnect attempts
#define maxNotConnectedCounter 150

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
  
    PubSubClient mqtt_client(espClient);
    for(int i=0; i<17; i=i+8) {
	    _chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
	  }
    _mqtt_client_id="ESP32-";
    _mqtt_client_id=_mqtt_client_id+_chipId;        

}

void wifi_mqtt::begin()
{
  //placeholder
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
  Serial.println("   IP address: ");
  Serial.print(WiFi.localIP());
  return true;
}

bool wifi_mqtt::connect_mqtt()
{
  mqtt_client.setServer(_mqttServer, 1883);
  mqtt_client.setBufferSize(1024);
  Serial.printf("   Server IP: %s\r\n",_mqttServer);  
  //Serial.printf("   Username:  %s\r\n",mqtt_user);
  //Serial.println("   Cliend Id: "+mqtt_client_id);  
  Serial.println("   MQTT configured!");       
  
  if (!mqtt_client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect   
    //if (mqtt_client.connect(mqtt_client_id.c_str(), mqtt_user, mqtt_password)) {
    if (mqtt_client.connect(_mqtt_client_id.c_str())) {
      Serial.println("MQTT connected");
      //mqtt_client.publish(topic, "init of mqtt");
      //Serial.println(topic_discovery);

      // homeassistant discovery
      //char payload[] ="{\"automation_type\":\"trigger\",\"type\":\"button_short_press\",\"subtype\":\"button_1\",\"topic\":\"home/deurbel\",\"payload\":\"single\",\"device\":{\"identifiers\":[\"ESP8266-13360373\"],\"name\":\"Deurbel\",\"model\":\"esp_deurbel\",\"manufacturer\":\"Witje\"}}";
      //Serial.println(sizeof(payload)/sizeof(char));
      //mqtt_client.publish(topic, payload);
      //mqtt_client.publish(topic_discovery_b, "{\"automation_type\":\"trigger\",\"type\":\"button_short_press\",\"subtype\":\"button_1\",\"topic\":\"home/deurbel\",\"device\":{\"identifiers\":[\"ESP8266-13360373\"],\"name\":\"Deurbel\",\"model\":\"esp_deurbel\",\"manufacturer\":\"Witje\"}}");
      //mqtt_client.publish(topic_discovery, payload,true);
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqtt_client.state());
    }
  }
  return true;
}

bool wifi_mqtt::reconnect()
{
  return true;
}