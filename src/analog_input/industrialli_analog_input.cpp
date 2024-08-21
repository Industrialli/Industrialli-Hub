#include "analog_input/industrialli_analog_input.h"

void industrialli_analog_input::begin(){
    analog_input[A01] = {PB1, PA9,  READ_10V};
    analog_input[A02] = {PC5, PA10, READ_10V};
    analog_input[A03] = {PC4, PD0,  READ_10V};
    analog_input[A04] = {PA0, PD1,  READ_10V};

    pinMode(analog_input[A01].port, INPUT);
    pinMode(analog_input[A02].port, INPUT);
    pinMode(analog_input[A03].port, INPUT);
    pinMode(analog_input[A04].port, INPUT);

    pinMode(analog_input[A01].sel, OUTPUT);
    pinMode(analog_input[A02].sel, OUTPUT);
    pinMode(analog_input[A03].sel, OUTPUT);
    pinMode(analog_input[A04].sel, OUTPUT);

    digitalWrite(analog_input[A01].sel, READ_10V);
    digitalWrite(analog_input[A02].sel, READ_10V);
    digitalWrite(analog_input[A03].sel, READ_10V);
    digitalWrite(analog_input[A04].sel, READ_10V);

    set_resolution(12);
}

void industrialli_analog_input::set_read_mode(uint8_t _pin, uint8_t _read_mode){
    digitalWrite(analog_input[_pin].sel, _read_mode);
    analog_input[_pin].read_mode = _read_mode;
    leds.set_led(_pin, HIGH);
}

void industrialli_analog_input::set_resolution(uint16_t _resolution){
    analogReadResolution(_resolution);
    bits_resolution = (1 << _resolution) - 1;
}

double industrialli_analog_input::analog_read(uint8_t _pin){
    double vdda = (3.3 * get_vrefint_cal()) / get_vrefint_data();
    double vchannel_internal = (vdda / bits_resolution) * analogRead(analog_input[_pin].port);
    double vchannel_external;

    if(analog_input[_pin].read_mode == READ_10V){
        vchannel_external = (10 * vchannel_internal) / 3.3;
    }

    if(analog_input[_pin].read_mode == READ_20mA){
        vchannel_external = (20 * vchannel_internal) / 3.3;
    }

    return vchannel_external;
}

uint16_t industrialli_analog_input::get_vrefint_cal(){
    return *((uint16_t *)0x1FF1E860);
}

uint16_t industrialli_analog_input::get_vrefint_data(){
    return analogRead(AVREF);
}

// bool industrialli_analogInputsHub::alarm020mA(float alarm020Val, float threshold){
//     _alarm020Val = alarm020Val;
   
//     if (_alarm020Val < threshold){
//         _alarm = true;

//     }else{
//         _alarm = false;
//     }

//     return _alarm;
// }

// int industrialli_analogInputsHub::getIntParamTSCAL1(){

//     _TS_CAL1 = *((unsigned short *)0x1FF1E820); // TEMP_RAW1 = 3.3V@30degreeC
//     return _TS_CAL1;
// }

// int industrialli_analogInputsHub::getIntParamTSCAL2(){
//     _TS_CAL2 = *((unsigned short *)0x1FF1E840);
//     return _TS_CAL2;
// }