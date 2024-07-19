#ifndef INDUSTRIALLI_DIGITAL_INPUT_H
#define INDUSTRIALLI_DIGITAL_INPUT_H

#include "leds/industrialli_leds.h"

extern industrialli_leds leds;

enum DIGITAL_INPUT_PIN {
    I01 = 0,
    I02 = 1,
    I03 = 2,
    I04 = 3,
    I05 = 4,
    I06 = 5,
    I07 = 6,
    I08 = 7
};

typedef struct {
    GPIO_TypeDef *GPIOx;
    uint16_t GPIO_Pin;
    uint32_t GPIO_Mode;
    IRQn_Type irqnb;
    void (*callback)();
} gpio_irq_conf_str;

class industrialli_digital_input{
public:
    void begin();
    void attach_interrupt(DIGITAL_INPUT_PIN _pin, void (*_callback)(), uint32_t _mode);
    void update_leds();

    gpio_irq_conf_str gpio_irq_conf[8];
};

#endif