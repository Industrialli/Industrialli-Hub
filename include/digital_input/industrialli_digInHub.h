#ifndef INDUSTRIALLI_DIGINHUB_H
#define INDUSTRIALLI_DIGINHUB_H

#include <Arduino.h>
#include <stdlib.h>
#include "leds/industrialli_leds.h"

extern industrialli_leds leds;
// extern volatile int _aState_ENCA;
// extern volatile int _pulses_ENCA;
// extern volatile bool _rotation_ENCA;

// interrupt
// volatile bool industrialli_digitalInputsHub::_input_00 = false;
// volatile bool industrialli_digitalInputsHub::_input_01 = false;
// volatile bool industrialli_digitalInputsHub::_input_02 = false;
// volatile bool industrialli_digitalInputsHub::_input_03 = false;
// volatile bool industrialli_digitalInputsHub::_input_04 = false;
// volatile bool industrialli_digitalInputsHub::_input_05 = false;
// volatile bool industrialli_digitalInputsHub::_input_06 = false;
// volatile bool industrialli_digitalInputsHub::_input_07 = false;

// ENCODER

// volatile int industrialli_digitalInputsHub::_aStateEncoder_I01_A;
// volatile int industrialli_digitalInputsHub::_aStateEncoder_I03_A;
// volatile int industrialli_digitalInputsHub::_aStateEncoder_I05_A;
// volatile int industrialli_digitalInputsHub::_aStateEncoder_I07_A;

// volatile int industrialli_digitalInputsHub::_aLastStateEncoder_I01_A;
// volatile int industrialli_digitalInputsHub::_aLastStateEncoder_I03_A;
// volatile int industrialli_digitalInputsHub::_aLastStateEncoder_I05_A;
// volatile int industrialli_digitalInputsHub::_aLastStateEncoder_I07_A;

// volatile int industrialli_digitalInputsHub::_pulsesEncoder_I01_I02;
// volatile int industrialli_digitalInputsHub::_pulsesEncoder_I03_I04;
// volatile int industrialli_digitalInputsHub::_pulsesEncoder_I05_I06;
// volatile int industrialli_digitalInputsHub::_pulsesEncoder_I07_I08;

// volatile bool industrialli_digitalInputsHub::_rotationEncoder_I01_I02;
// volatile bool industrialli_digitalInputsHub::_rotationEncoder_I03_I04;
// volatile bool industrialli_digitalInputsHub::_rotationEncoder_I05_I06;
// volatile bool industrialli_digitalInputsHub::_rotationEncoder_I07_I08;

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

// #define ENCODER_01_02 0
// #define ENCODER_03_04 1
// #define ENCODER_05_06 2
// #define ENCODER_07_08 3

#define UP 0
#define DOWN 1

class industrialli_digitalInputsHub{
public:
    // static volatile bool _input_00;
    // static volatile bool _input_01;
    // static volatile bool _input_02;
    // static volatile bool _input_03;
    // static volatile bool _input_04;
    // static volatile bool _input_05;
    // static volatile bool _input_06;
    // static volatile bool _input_07;

    // static volatile int _aStateEncoder_I01_A;
    // static volatile int _aStateEncoder_I03_A;
    // static volatile int _aStateEncoder_I05_A;
    // static volatile int _aStateEncoder_I07_A;

    // static volatile int _aLastStateEncoder_I01_A;
    // static volatile int _aLastStateEncoder_I03_A;
    // static volatile int _aLastStateEncoder_I05_A;
    // static volatile int _aLastStateEncoder_I07_A;

    // static volatile int _pulsesEncoder_I01_I02;
    // static volatile int _pulsesEncoder_I03_I04;
    // static volatile int _pulsesEncoder_I05_I06;
    // static volatile int _pulsesEncoder_I07_I08;

    // static volatile bool _rotationEncoder_I01_I02;
    // static volatile bool _rotationEncoder_I03_I04;
    // static volatile bool _rotationEncoder_I05_I06;
    // static volatile bool _rotationEncoder_I07_I08;

    // void beginEncoder(uint8_t encoder, bool _sensorType);                                                       // Inicia o encoder
    // int getPulsesEncoder(uint8_t encoder);                                                                     // Retorna o valor dos pulos do encoder selecionado
                               
    //                                                                              // Limpa o valor da contagem na entrada
    // void beginUserDigitalInput(uint8_t pin, callback_function_t userFunction, uint32_t mode, bool _sensorType); // inicia a entrada selecionada para chamar a funcao do usuario

    void begin();
    void update_leds();
    void set_all_leds_off();

    void beginUserInterruptInput(uint8_t _pin);

    void begin_interrupt_input(uint8_t _pin, bool _sensor_type, bool _count_mode);
    void begin_digital_input_counting(uint8_t pin, bool _sensorType, bool upOrDown);   
    void count_interrupts(uint8_t _pin, bool _count_mode);

    int get_count(uint8_t pin);
    void clear_count(uint8_t pin); 
    
private:
    // callback_function_t _userFunction;

    uint8_t led_status[8];
    int input_type[8];
    bool sensor_type[8];
    volatile int count[8];

    // uint8_t _encoder;
};

#endif