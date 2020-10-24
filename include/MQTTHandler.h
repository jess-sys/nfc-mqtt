#ifndef MQTTHANDLER_H
#define MQTTHANDLER_H

#include <Arduino.h>
#include <PubSubClient.h>

void setup_mqtt(PubSubClient MQTTClient);
void callback(char *topic, byte *message, unsigned int length);

#endif //MQTTHANDLER_H