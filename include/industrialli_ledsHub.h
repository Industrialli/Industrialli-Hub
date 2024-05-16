#ifndef INDUSTRIALLI_LEDSHUB_H
#define INDUSTRIALLI_LEDSHUB_H
#include <Arduino.h>
#include <stdlib.h>
#include <SPI.h>

#define SPI1_NSS PA4  // shiftRegisterPin 12
#define SPI1_SCK PA5  // shiftRegisterPin 11
#define SPI1_MOSI PA7 // shiftRegisterPin 14
#define SPI1_MISO PA6

class industrialli_ledsHubCtrl
{
public:
    void begin(void);
    void start(void);
    void ledsOff(void);
    void ledOn(uint8_t ledNum);
    void ledOff(uint8_t ledNum);
    void ledsUpdate(void);

private:

    SPIClass *_spiPort;

    uint8_t _shiftRegisterLed[32] = {

        _shiftRegisterLed[0],
        _shiftRegisterLed[1],
        _shiftRegisterLed[2],
        _shiftRegisterLed[3],
        _shiftRegisterLed[4],
        _shiftRegisterLed[5],
        _shiftRegisterLed[6],
        _shiftRegisterLed[7],

        _shiftRegisterLed[8],
        _shiftRegisterLed[9],
        _shiftRegisterLed[10],
        _shiftRegisterLed[11],
        _shiftRegisterLed[12],
        _shiftRegisterLed[13],
        _shiftRegisterLed[14],
        _shiftRegisterLed[15],

        _shiftRegisterLed[16],
        _shiftRegisterLed[17],
        _shiftRegisterLed[18],
        _shiftRegisterLed[19],
        _shiftRegisterLed[20],
        _shiftRegisterLed[21],
        _shiftRegisterLed[22],
        _shiftRegisterLed[23],

        _shiftRegisterLed[24],
        _shiftRegisterLed[25],
        _shiftRegisterLed[26],
        _shiftRegisterLed[27],
        _shiftRegisterLed[28],
        _shiftRegisterLed[29],
        _shiftRegisterLed[30],
        _shiftRegisterLed[31]};

    uint8_t _leds0to7[8] = {0};
    uint8_t _leds8to15[8] = {0};
    uint8_t _leds16to23[8] = {0};
    uint8_t _leds24to31[8] = {0};

    uint8_t _transferLeds0to7 = 0;
    uint8_t _transferLeds8to15 = 0;
    uint8_t _transferLeds16to23 = 0;
    uint8_t _transferLeds24to31 = 0;

    uint8_t _ledNum;
};
#endif