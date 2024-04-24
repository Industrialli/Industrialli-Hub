#ifndef INDUSTRIALLI_HUBINIT_H
#define INDUSTRIALLI_HUBINIT_H

#include <Arduino.h>
#include <stdlib.h>
#include <HardwareSerial.h>

#define DEBUG_LED PB10
#define RS485_TER_SEL PE10


class industrialli_hubInit{
    private:
    public:
    void begin(void);
};

#endif