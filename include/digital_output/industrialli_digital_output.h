#ifndef INDUSTRIALLI_DIGITALOUTPUT_H
#define INDUSTRIALLI_DIGITALOUTPUT_H

#include "leds/industrialli_leds.h"

enum DIGITAL_PIN {
    Q01 = 1,
    Q02 = 2,
    Q03 = 3,
    Q04 = 4,
    Q05 = 5,
    Q06 = 6,
    Q07 = 7,
    Q08 = 8,
    
    Q09 = 9,
    Q10 = 10,
    Q11 = 11,
    Q12 = 12,
    Q13 = 13,
    Q14 = 14,
    Q15 = 15,
    Q16 = 16
};

extern SPI_HandleTypeDef hspi4;
extern industrialli_leds leds;

class industrialli_digital_output{
public:
    void begin();
    void enable();
    void disable();
    void update();

    void write(DIGITAL_PIN _pin, bool _value);
    
    void update_power_leds_status();

private:
    uint16_t digital_outputs;

    void set_digital_output_led(uint8_t _led, bool _value);

    bool output_1_to_8_status();
    bool output_9_to_16_status();
};

#endif