#include "analog_input/industrialli_anlgInHub.h"

void industrialli_analogInputsHub::begin(){
    pinMode(ADC_01, INPUT);
    pinMode(ADC_02, INPUT);
    pinMode(ADC_03, INPUT);
    pinMode(ADC_04, INPUT);

    pinMode(ANLG_SEL_01, OUTPUT);
    pinMode(ANLG_SEL_02, OUTPUT);
    pinMode(ANLG_SEL_03, OUTPUT);
    pinMode(ANLG_SEL_04, OUTPUT);

    digitalWrite(ANLG_SEL_01, LOW);
    digitalWrite(ANLG_SEL_02, LOW);
    digitalWrite(ANLG_SEL_03, LOW);
    digitalWrite(ANLG_SEL_04, LOW);

    analogReadResolution(_anlgRes);
    getIntParamVREF();
}

void industrialli_analogInputsHub::setAnalogResolution(int anlgRes){
    switch(anlgRes){
        case 8:
            _anlgRes = 8;
            _bitsADC = 255;
            break;
        case 10:
            _anlgRes = 10;
            _bitsADC = 1023;
            break;
        case 12:
            _anlgRes = 12;
            _bitsADC = 4095; 
            break;
        case 16:
            _anlgRes = 16;
            _bitsADC = 65535;
            break;
    }
}
void industrialli_analogInputsHub::setReadMode(uint8_t anlgPin, uint8_t readMode){

    _anlgPin  = anlgPin;
    _readMode = readMode;

    if (_anlgPin == 0){
        digitalWrite(ANLG_SEL_01, _readMode);
        leds.set_led(_anlgPin, _readMode);
    }

    if (_anlgPin == 1){
        digitalWrite(ANLG_SEL_02, _readMode);
        leds.set_led(_anlgPin, _readMode);
    }
    
    if (_anlgPin == 2){
        digitalWrite(ANLG_SEL_03, _readMode);
        leds.set_led(_anlgPin, _readMode);
    }
    
    if (_anlgPin == 3){
        digitalWrite(ANLG_SEL_04, _readMode);
        leds.set_led(_anlgPin, _readMode);
    }
}
int industrialli_analogInputsHub::readRawInput(uint8_t anlgPin){

    _anlgPin = anlgPin;
    _pin     = anlgPin;

    switch (_anlgPin){
    case 0:
        _VIN_RAW[0] = analogRead(ADC_01);
        break;
    case 1:
        _VIN_RAW[1] = analogRead(ADC_02);
        break;
    case 2:
        _VIN_RAW[2] = analogRead(ADC_03);
        break;
    case 3:
        _VIN_RAW[3] = analogRead(ADC_04);
        break;
    }

    return _VIN_RAW[_pin];
}

int industrialli_analogInputsHub::getVRefRaw(){

    _VREF_RAW = analogRead(AVREF);
    return _VREF_RAW;
}

double industrialli_analogInputsHub::getVIN(uint8_t anlgPin){
    _anlgPin = anlgPin;
    _VDDA = (_VREF_INTERNAL * _bitsADC) / getVRefRaw();
    _VIN[_anlgPin] = _VDDA / _bitsADC * readRawInput(_anlgPin);
    return _VIN[_anlgPin];
}

double industrialli_analogInputsHub::get010V(uint8_t anlgPin){
    _anlgPin = anlgPin;
    _VDDA = (_VREF_INTERNAL * _bitsADC) / getVRefRaw();
    _VIN010[_anlgPin] = getVIN(_anlgPin) * (10.00 / _VDDA);
    return _VIN010[_anlgPin];
}

double industrialli_analogInputsHub::get020mA(uint8_t anlgPin){
    _anlgPin = anlgPin;
    _VDDA = (_VREF_INTERNAL * _bitsADC) / getVRefRaw();
    _AIN020[_anlgPin] = getVIN(_anlgPin) * (20.00 / _VDDA);
    return _AIN020[_anlgPin];
}

bool industrialli_analogInputsHub::alarm020mA(float alarm020Val, float threshold){
    _alarm020Val = alarm020Val;
   
    if (_alarm020Val < threshold){
        _alarm = true;

    }else{
        _alarm = false;
    }

    return _alarm;
}

int industrialli_analogInputsHub::getIntParamVREF(){
    _VREFINT       = *((unsigned short *)0x1FF1E860);
    _VREF_INTERNAL = _VREFINT;

    return _VREFINT;
}

int industrialli_analogInputsHub::getIntParamTSCAL1(){

    _TS_CAL1 = *((unsigned short *)0x1FF1E820); // TEMP_RAW1 = 3.3V@30degreeC
    return _TS_CAL1;
}

int industrialli_analogInputsHub::getIntParamTSCAL2(){
    _TS_CAL2 = *((unsigned short *)0x1FF1E840);
    return _TS_CAL2;
}

void industrialli_analogInputsHub::test010V(){
    SerialUSB.print(get010V(A01), 4);
    SerialUSB.print(" ");
    SerialUSB.print(get010V(A02), 4);
    SerialUSB.print(" ");
    SerialUSB.print(get010V(A03), 4);
    SerialUSB.print(" ");
    SerialUSB.print(get010V(A04), 4);
    SerialUSB.println();

}
void industrialli_analogInputsHub::test020mA(){

    SerialUSB.print(get020mA(A01), 4);
    SerialUSB.print(" ");
    SerialUSB.print(get020mA(A02), 4);
    SerialUSB.print(" ");
    SerialUSB.print(get020mA(A03), 4);
    SerialUSB.print(" ");
    SerialUSB.println(get020mA(A04), 4);
    SerialUSB.println();
}