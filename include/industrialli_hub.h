#ifndef INDUSTRIALLI_HUB_H
#define INDUSTRIALLI_HUB_H

#include <Arduino.h>

#include "industrialli_leds.h"
#include "industrialli_digital_output.h"

#define DEBUG_LED PB10
#define RS485_TER_SEL PE10

extern industrialli_leds leds;
extern industrialli_digital_output iso;

class industrialli_hub{
    public:
    void begin();
};

#endif