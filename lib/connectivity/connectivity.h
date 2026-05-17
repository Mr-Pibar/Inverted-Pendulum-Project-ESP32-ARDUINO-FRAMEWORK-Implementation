#ifndef CONNECTIVITY_H
#define CONNECTIVITY_H

#include "wifiAndMQTT.h"

extern volatile unsigned int step_mqtt;
extern volatile unsigned int dir_mqtt;

void initWifi();

void initMQTT();

void reconnectMQTT();

void updateMQTT();


#endif