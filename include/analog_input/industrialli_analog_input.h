#ifndef INDUSTRIALLI_ANALOG_INPUT_H
#define INDUSTRIALLI_ANALOG_INPUT_H

#include <Arduino.h>
#include "leds/industrialli_leds.h"

extern industrialli_leds leds;

typedef struct {
    uint32_t port;
    uint32_t sel;
    uint8_t read_mode;
} analog_input_struct;

#define A01 0
#define A02 1
#define A03 2
#define A04 3

#define READ_10V 0
#define READ_20mA 1

class industrialli_analog_input{
public:
    void begin();
    void set_read_mode(uint8_t _pin, uint8_t _read_mode);
    void set_resolution(uint16_t _resolution);
    double analog_read(uint8_t _pin);
    double map(double _value, double _in_min, double _in_max, double _out_min, double _out_max);
    double map_pin(uint8_t _pin, double _in_min, double _in_max, double _out_min, double _out_max);
    bool alarm_020mA(float _mA, float _threshold);

private:
    analog_input_struct analog_input[4];
    uint16_t bits_resolution;

    uint16_t get_vrefint_cal();
    uint16_t get_vrefint_data();
};

#endif