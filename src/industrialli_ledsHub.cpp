#include "industrialli_ledsHub.h"
void industrialli_ledsHubCtrl::begin(void)
{

    pinMode(SPI1_NSS, OUTPUT);
    start();
    ledsOff();
}
void industrialli_ledsHubCtrl::start(void) // Animacao de startup
{
    for (int i = 0; i < 32; i++)
    {
        ledOn(i);
        ledOff(i - 1);
        ledsUpdate();
        delay(10);
    }
    for (int i = 32; i >= -1; i--)
    {
        ledOn(i);
        ledOff(i + 1);
        ledsUpdate();
        delay(10);
    }
}
void industrialli_ledsHubCtrl::ledsOff(void) // Atribui o valor LOW para todos os LEDs
{
    for (int i = 0; i > 32; i++)
    {
        _shiftRegisterLed[i] = 0;
    }
    ledsUpdate();
}
void industrialli_ledsHubCtrl::ledOn(uint8_t ledNum) // Atribui o valor HIGH para um LED especifico
{
    _ledNum = ledNum;
    _shiftRegisterLed[_ledNum] = 1;
}
void industrialli_ledsHubCtrl::ledOff(uint8_t ledNum) // Atribui o valor LOW para um LED especifico
{
    _ledNum = ledNum;
    _shiftRegisterLed[_ledNum] = 0;
}
void industrialli_ledsHubCtrl::ledsUpdate(void) // Transfere o valor atribuido para TODOS os LEDs
{
    _spiPort = &SPI;
    _spiPort->setMISO(SPI1_MISO);
    _spiPort->setMOSI(SPI1_MOSI);
    _spiPort->setSCLK(SPI1_SCK);
    _spiPort->begin();
    _spiPort->beginTransaction(SPISettings(10000000UL, LSBFIRST, SPI_MODE0));
    for (int i = 0; i < 8; i++)
    {

        _transferLeds0to7 += (_shiftRegisterLed[i] << (i));
        _transferLeds8to15 += (_shiftRegisterLed[8 + i] << (i));
        _transferLeds16to23 += (_shiftRegisterLed[16 + i] << (i));
        _transferLeds24to31 += (_shiftRegisterLed[24 + i] << (i));
    }
    _spiPort->transfer(_transferLeds24to31); // LED24 -> LED31
    _spiPort->transfer(_transferLeds16to23); // LED16 -> LED23
    _spiPort->transfer(_transferLeds8to15);  // LED8 -> LED15
    _spiPort->transfer(_transferLeds0to7);   // LED0 -> LED7

    _transferLeds0to7 = 0;
    _transferLeds8to15 = 0;
    _transferLeds16to23 = 0;
    _transferLeds24to31 = 0;

    digitalWrite(SPI1_NSS, LOW);
    digitalWrite(SPI1_NSS, HIGH);
    _spiPort->endTransaction();
    _spiPort->end();
}