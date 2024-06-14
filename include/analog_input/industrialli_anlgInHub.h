#ifndef INDUSTRIALLI_ANLGINHUB_H
#define INDUSTRIALLI_ANLGINHUB_H

#include <Arduino.h>
#include <stdlib.h>
#include "leds/industrialli_leds.h"

extern industrialli_leds leds;

#define ADC_01 PB1
#define ADC_02 PC5
#define ADC_03 PC4
#define ADC_04 PA0

#define ANLG_SEL_01 PA9
#define ANLG_SEL_02 PA10
#define ANLG_SEL_03 PD0
#define ANLG_SEL_04 PD1

#define A01 0
#define A02 1
#define A03 2
#define A04 3

#define BITS_8 8
#define BITS_10 10
#define BITS_12 12
#define BITS_16 16

#define READ_010 0
#define READ_020 1

class industrialli_analogInputsHub{
public:
    void begin(void);
    void setAnalogResolution(int anlgRes);
    void setReadMode(uint8_t anlgPin, uint8_t readMode);
    int readRawInput(uint8_t anlgPin);
    int getVRefRaw(void);
    double getVIN(uint8_t anlgPin);
    double get010V(uint8_t anlgPin);
    double get020mA(uint8_t anlgPin);
    bool alarm020mA(float alarm020Val, float threshold);
    int getIntParamVREF(void);
    int getIntParamTSCAL1(void);
    int getIntParamTSCAL2(void);
    void test010V();
    void test020mA();

private:
    uint8_t _anlgRes = 12;
    uint8_t _anlgPin;
    uint8_t _pin;
    uint8_t _readMode;

    int _VREFINT;
    int _TS_CAL1;
    int _TS_CAL2;
    int _VREF_RAW = 0;
    int _VIN_RAW[4] = {0};
    int _bitsADC = 4095;
    double _VREF_INTERNAL = 1.212;
    double _VDDA = 0.00;
    double _VIN[4] = {0.00};
    double _VIN010[4] = {0.00};
    double _AIN020[4] = {0.00};
    bool _alarm = false;
    float _alarm020Val = 0.00;
};

#endif