# nfc-mqtt
Arbitrary firmware to check NFC tags through MQTT via an ESP32/ESP8266.

## Disclaimer

This project is not intended for production uses. Its code has been designed for a proof-of-concept only.

There are multiple known security flaws. Pull requests will be reviewed, don't hesitate to take part !

## What's this ?

This is a simple ESP32 firmware that allows NFC authentication. Here's how it works :

#####    Syncing

- At boot, the ESP32 will connect to the network, then to the MQTT Broker, it's the `STATE_BOOTING`.
- Then, it'll send a ciphered message (obtained using the PSK in `include/variables.h`) to the `NFC/sync` MQTT Topic, it's the `STATE_SYNCING`.
- Another party is supposed to send on the `NFC/sync` MQTT topic, a message ciphered with the same PSK, containing a public key, it's the `STATE_KEYX_RX` state.
- Then, the ESP32 will send its own generated public key on the `NFC/sync` MQTT Topic, it's the `STATE_KEYX_TX` state.
- After the successful key exchange, it'll move to the `STATE_READY` state.

##### Usage as NFC Authentication tool :

- When a NFC tag is detected, it sends an encrypted message (with the remote's public key) containing the tag ID to the `NFC/auth/req` MQTT Topic, it's the `STATE_AUTHREQ_TX` state.
- The other party is supposed to answer with an encrypted message (with the remote's public key) containing either `AUTHREQ_SUCCESS` or `AUTHREQ_DENIED` on the `NFC/auth/response` MQTT Topic.
- When the ESP32 receives the message, it enters the `STATE_AUTHREQ_RX`. Depending on the response, it'll switch to the state `STATE_AUTHREQ_SUCCESS` or `STATE_AUTHREQ_DENIED` for 2 seconds.
- It'll then switch to the `STATE_READY`

--

- The other party can send an encrypted message on the `NFC/register/request` MQTT Topic. The ESP32 will enter the `STATE_REGISTER_PENDING` state.
- The ESP32 will wait for an NFC tag to be detected, and will send an encrypted MQTT message containing its ID to the `NFC/register/response` MQTT Topic. It's the `STATE_REGISTER_DETECTED` state (it stays for 2 seconds before switching back to the `STATE_READY` state)

##### Usage as MQTT alerting tool 

Note : The following require being in `STATE_READY` state (except last step)

- Another party is supposed to send an encrypted MQTT message on the `NFC/alert` MQTT Topic. This message should be either `ALERT_RED_BEGIN`, `ALERT_RED_CLEAR`, `ALERT_ORANGE_BEGIN`, `ALERT_ORANGE_CLEAR`, `ALERT_BLUE_BEGIN`, `ALERT_BLUE_CLEAR`
- The ESP32 will switch to the corresponding state (`STATE_ALERT_$COLOR`)
- The ESP32 will stop beeping and showing the corresponding color if it receives a valid clearing message
- The ESP32 will stop beeping and showing the corresponding color if a detected NFC tag passes the AUTHREQ process (see 1.)


## Getting started

1. Get VSCode and PlatformIO.

2. Edit the variables in `include/variables.h` to suit your configuration (SSID, password, MQTT broker address, PSK).

3. You're ready to compile and upload the firmware to the board !