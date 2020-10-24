#ifndef WIFIHANDLER_H
#define WIFIHANDLER_H

#include <PubSubClient.h>

void setup_wifi(void);
void reconnect(PubSubClient MQTTClient);

#endif //WIFIHANDLER_H