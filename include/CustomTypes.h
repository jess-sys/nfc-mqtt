#ifndef CUSTOMTYPES_H
#define CUSTOMTYPES_H

typedef enum {
    STATE_BOOTING,
    STATE_SYNCING,
    STATE_KEYX_RX,
    STATE_KEYX_TX,
    STATE_AUTHREQ_RX,
    STATE_AUTHREQ_TX,
    STATE_AUTHREQ_SUCCESS,
    STATE_AUTHREQ_DENIED,
    STATE_REGISTER_PENDING,
    STATE_REGISTER_DETECTED,
    STATE_ALERT_BLUE,
    STATE_ALERT_ORANGE,
    STATE_ALERT_RED,
    STATE_READY
} STATE_t;

#endif // CUSTOMTYPES_H