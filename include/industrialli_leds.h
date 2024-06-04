#ifndef INDUSTRIALLI_LEDS_H
#define INDUSTRIALLI_LEDS_H

#include <Arduino.h>
#include <SPI.h>

#define SPI1_NSS PA4
#define SPI1_SCK PA5
#define SPI1_MISO PA6
#define SPI1_MOSI PA7

extern SPIClass spi_leds;

class industrialli_leds{
public:
    void begin();
    void start();
    void set_led(uint8_t _led, bool _value);
    void set_all(bool _value);
    void update();

private:
    uint32_t leds;
};
#endif