#ifndef INDUSTRIALLI_DIGITALOUTPUT_H
#define INDUSTRIALLI_DIGITALOUTPUT_H

#include <Arduino.h>
#include <SPI.h>

#include "leds/industrialli_leds.h"

#define SPI4_SCK PE2
#define SPI4_NSS PE4
#define SPI4_MOSI PE6
#define SPI4_MISO PE5
#define ISO_DIS PE3
#define IC1_ISO_DIAG PC0
#define IC2_ISO_DIAG PC1

#define Q01 1
#define Q02 2
#define Q03 3
#define Q04 4
#define Q05 5
#define Q06 6
#define Q07 7
#define Q08 8

#define Q09 9
#define Q10 10
#define Q11 11
#define Q12 12
#define Q13 13
#define Q14 14
#define Q15 15
#define Q16 16

extern SPIClass spi_iso;
extern industrialli_leds leds;

class industrialli_digital_output{
public:
    void begin();
    void enable();
    void disable();
    void update();

    void write(uint8_t _port, bool _value);
    
    void update_power_leds_status();

    bool Q01_to_Q08_alarm();
    bool Q09_to_Q16_alarm();

private:
    uint16_t digital_outputs;

    void set_digital_output_led(uint8_t _led, bool _value);
};

#endif