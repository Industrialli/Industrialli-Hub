#ifndef INDUSTRIALLI_DIGITAL_INPUT_H
#define INDUSTRIALLI_DIGITAL_INPUT_H

#include <Arduino.h>
#include "leds/industrialli_leds.h"

#define I01 0
#define I02 1
#define I03 2
#define I04 3
#define I05 4
#define I06 5
#define I07 6
#define I08 7

#define PNP RISING
#define NPN FALLING

extern industrialli_leds leds;

typedef struct {
    uint32_t port;
    uint8_t read_mode;
} digital_input_struct;

class industrialli_digital_input{
public:
    void begin();
    void attach_interrupt(uint8_t _pin, void (*_callback)(), uint8_t _read_mode);
    void update_leds();

private:
    digital_input_struct digital_input[8];
};


























// #define EXTI_01 PE15
// #define EXTI_02 PE14
// #define EXTI_03 PE13
// #define EXTI_04 PE12
// #define EXTI_05 PB4
// #define EXTI_06 PB5
// #define EXTI_07 PB6
// #define EXTI_08 PB7

// #define ENCODER_01_02 0
// #define ENCODER_03_04 1
// #define ENCODER_05_06 2
// #define ENCODER_07_08 3

// class industrialli_digitalInputsHub{
// public:
//     void begin();
//     void update_leds();
//     void set_all_leds_off();

//     void beginUserInterruptInput(uint8_t _pin);

//     void begin_interrupt_input(uint8_t _pin, bool _sensor_type, bool _count_mode);
//     void begin_digital_input_counting(uint8_t pin, bool _sensor_type, bool _count_mode);   
//     void count_interrupts(uint8_t _pin, bool _count_mode);

//     int get_count(uint8_t pin);
//     void clear_count(uint8_t pin);

//     void begin_encoder_counting(uint8_t _encoder, bool _sensor_type);
//     void begin_interrupt_encoder(uint8_t _encoder, bool _sensor_type);
//     void count_encoder_interruption(uint8_t _encoder);
//     int get_pulses_encoder(uint8_t _encoder);
//     bool get_encoder_sense(uint8_t _encoder);
//     double get_encoder_velocity(uint8_t _encoder);
    
// private:
//     uint8_t led_status[8];
//     int input_type[8];
//     bool sensor_type[8];
//     volatile int count[8];

//     volatile int encoder_a;
//     volatile int encoder_b;
//     volatile bool encoder_sense[4];
//     volatile double encoder_velocity[4];
//     volatile uint32_t encoder_last_update[4];
//     volatile uint32_t encoder_last_count[4];
// };

#endif