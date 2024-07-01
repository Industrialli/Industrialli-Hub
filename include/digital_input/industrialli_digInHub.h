#ifndef INDUSTRIALLI_DIGINHUB_H
#define INDUSTRIALLI_DIGINHUB_H

#include <Arduino.h>
#include <stdlib.h>
#include <math.h>
#include "leds/industrialli_leds.h"

extern industrialli_leds leds;

#define EXTI_01 PE15
#define EXTI_02 PE14
#define EXTI_03 PE13
#define EXTI_04 PE12
#define EXTI_05 PB4
#define EXTI_06 PB5
#define EXTI_07 PB6
#define EXTI_08 PB7

#define I01 1
#define I02 2
#define I03 3
#define I04 4
#define I05 5
#define I06 6
#define I07 7
#define I08 8

#define PNP 0
#define NPN 1

#define ENCODER_01_02 0
#define ENCODER_03_04 1
#define ENCODER_05_06 2
#define ENCODER_07_08 3

#define UP 0
#define DOWN 1

class industrialli_digitalInputsHub{
public:
    void begin();
    void update_leds();
    void set_all_leds_off();

    void beginUserInterruptInput(uint8_t _pin);

    void begin_interrupt_input(uint8_t _pin, bool _sensor_type, bool _count_mode);
    void begin_digital_input_counting(uint8_t pin, bool _sensor_type, bool _count_mode);   
    void count_interrupts(uint8_t _pin, bool _count_mode);

    int get_count(uint8_t pin);
    void clear_count(uint8_t pin);

    void begin_encoder_counting(uint8_t _encoder, bool _sensor_type);
    void begin_interrupt_encoder(uint8_t _encoder, bool _sensor_type);
    void count_encoder_interruption(uint8_t _encoder);
    int get_pulses_encoder(uint8_t _encoder);
    bool get_encoder_sense(uint8_t _encoder);
    double get_encoder_velocity(uint8_t _encoder);
    
private:
    uint8_t led_status[8];
    int input_type[8];
    bool sensor_type[8];
    volatile int count[8];

    volatile int encoder_a;
    volatile int encoder_b;
    volatile bool encoder_sense[4];
    volatile double encoder_velocity[4];
    volatile uint32_t encoder_last_update[4];
    volatile uint32_t encoder_last_count[4];
};

#endif