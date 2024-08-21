#include "leds/industrialli_leds.h"

void industrialli_leds::begin(){
    pinMode(SPI1_NSS, OUTPUT);
    
    spi_leds.setMISO(SPI1_MISO);
    spi_leds.setMOSI(SPI1_MOSI);
    spi_leds.setSCLK(SPI1_SCK);
    spi_leds.begin();
    spi_leds.beginTransaction(SPISettings(2000000UL, LSBFIRST, SPI_MODE0));

    start();
}

void industrialli_leds::start(){
    for (int i = 0; i < 32; i++){
        set_all(LOW);
        set_led(i, HIGH);
        update();
        delay(25);
    }
    
    for (int i = 31; i >= 0; i--){
        set_all(LOW);
        set_led(i, HIGH);
        update();
        delay(25);
    }

    set_all(LOW);
    update();
}

void industrialli_leds::set_led(uint8_t _led, bool _value){
    if(_value){
        leds |= 0x01 << _led;
    }else {
        leds &= ~(0x01 << _led);
    }
}

void industrialli_leds::set_all(bool _value){
    leds = _value;
}

void industrialli_leds::update(){
    digitalWrite(SPI1_NSS, LOW);
    spi_leds.transfer(leds >> 24);
    spi_leds.transfer(leds >> 16);
    spi_leds.transfer(leds >> 8);
    spi_leds.transfer(leds & 0xFF);
    digitalWrite(SPI1_NSS, HIGH);
}