#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "WiFiHandler.h"
#include "MQTTHandler.h"
#include "CustomTypes.h"

// Create WiFI and MQTT objects
WiFiClient WirelessClient;
PubSubClient MQTTClient(WirelessClient);

// Global variables - state, timestamp for async actions
STATE_t state;
long lastMessageTimestamp = 0;

void setup() {
  state = STATE_BOOTING;
  setup_wifi();
  setup_mqtt(MQTTClient);
}

void loop() {
  if (!MQTTClient.connected()) {
    reconnect(MQTTClient);
  }
  MQTTClient.loop();

  long now = millis();
  if (now - lastMessageTimestamp > 5000) {
    lastMessageTimestamp = now;
    
    MQTTClient.publish("", "");
  }
  state = STATE_READY;
}