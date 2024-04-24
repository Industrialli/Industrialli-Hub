#include "industrialli_ledsHub.h"

void industrialli_ledsHubCtrl::begin(){

    pinMode(SPI1_NSS, OUTPUT);
    start();
    ledsOff();
}

// Animacao de startup
void industrialli_ledsHubCtrl::start(){
    for (int i = 0; i < 32; i++){
        ledOn(i);
        ledOff(i - 1);
        ledsUpdate();
        delay(10);
    }

    for (int i = 32; i >= -1; i--){
        ledOn(i);
        ledOff(i + 1);
        ledsUpdate();
        delay(10);
    }
}

// Atribui o valor LOW para todos os LEDs
void industrialli_ledsHubCtrl::ledsOff(){
    for (int i = 0; i > 32; i++){
        _shiftRegisterLed[i] = 0;
    }

    ledsUpdate();
}

// Atribui o valor HIGH para um LED especifico
void industrialli_ledsHubCtrl::ledOn(uint8_t ledNum){ 
    _ledNum = ledNum;
    _shiftRegisterLed[_ledNum] = 1;
}

// Atribui o valor LOW para um LED especifico
void industrialli_ledsHubCtrl::ledOff(uint8_t ledNum) {
    _ledNum = ledNum;
    _shiftRegisterLed[_ledNum] = 0;
}

// Transfere o valor atribuido para TODOS os LEDs
void industrialli_ledsHubCtrl::ledsUpdate(){
    _spiPort = &SPI;
    _spiPort->setMISO(SPI1_MISO);
    _spiPort->setMOSI(SPI1_MOSI);
    _spiPort->setSCLK(SPI1_SCK);
    _spiPort->begin();
    _spiPort->beginTransaction(SPISettings(10000000UL, LSBFIRST, SPI_MODE0));
    
    for (int i = 0; i < 8; i++){
        _transferLeds0to7   += _shiftRegisterLed[i] << i;
        _transferLeds8to15  += _shiftRegisterLed[8 + i] << i;
        _transferLeds16to23 += _shiftRegisterLed[16 + i] << i;
        _transferLeds24to31 += _shiftRegisterLed[24 + i] << i;
    }

    _spiPort->transfer(_transferLeds24to31);
    _spiPort->transfer(_transferLeds16to23);
    _spiPort->transfer(_transferLeds8to15);
    _spiPort->transfer(_transferLeds0to7);

    _transferLeds0to7   = 0;
    _transferLeds8to15  = 0;
    _transferLeds16to23 = 0;
    _transferLeds24to31 = 0;

    digitalWrite(SPI1_NSS, LOW);
    digitalWrite(SPI1_NSS, HIGH);

    _spiPort->endTransaction();
    _spiPort->end();
}