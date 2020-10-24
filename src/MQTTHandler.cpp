#include <PubSubClient.h>
#include <Arduino.h>
#include <WiFi.h>

#include "VariablesMQTT.h"

void callback(char *topic, byte *message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(0, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(0, LOW);
    }
  }
}

void setup_mqtt(PubSubClient MQTTClient) {
  MQTTClient.setServer(mqtt_server, 1883);
  MQTTClient.setCallback(callback);
}