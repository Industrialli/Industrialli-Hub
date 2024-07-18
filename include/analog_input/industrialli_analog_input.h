#ifndef INDUSTRIALLI_ANALOG_INPUT_H
#define INDUSTRIALLI_ANALOG_INPUT_H

#include "leds/industrialli_leds.h"

extern ADC_HandleTypeDef hadc3;
extern uint16_t analog_input_values[4];
extern industrialli_leds leds;

enum ANALOG_PIN {A01 = 0, A02 = 1, A03 = 2, A04 = 3};
enum INPUT_VOLTAGE {INPUT_VOLTAGE_10V = 0, INPUT_VOLTAGE_20V = 1};

class industrialli_analog_input{
private:
    uint8_t pin_input_voltage[4];
    uint8_t resolution;

    uint16_t bits_resolution;

    uint16_t get_vrefint_cal();
    uint16_t get_vrefint_data();
    // bool alarm020mA(float alarm020Val, float threshold);

public:
    void begin();
    void set_input_voltage(ANALOG_PIN _pin, INPUT_VOLTAGE _input_voltage);
    double analog_read(ANALOG_PIN _pin);
};

#endif