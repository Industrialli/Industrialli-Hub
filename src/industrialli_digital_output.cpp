#include "industrialli_digital_output.h"

void industrialli_digital_output::begin(){
    pinMode(SPI4_NSS, OUTPUT);
    pinMode(ISO_DIS, OUTPUT);
    pinMode(IC1_ISO_DIAG, INPUT);
    pinMode(IC2_ISO_DIAG, INPUT);
    digitalWrite(ISO_DIS, LOW);

    spi_iso.setMISO(SPI4_MISO);
    spi_iso.setMOSI(SPI4_MOSI);
    spi_iso.setSCLK(SPI4_SCK);
    spi_iso.begin();
    spi_iso.beginTransaction(SPISettings(20000000UL, MSBFIRST, SPI_MODE3));
    
    digital_outputs = 0;
}

void industrialli_digital_output::enable(){
    digitalWrite(ISO_DIS, HIGH);
}

void industrialli_digital_output::disable(){
    digitalWrite(ISO_DIS, LOW);
}

void industrialli_digital_output::update(){
    digitalWrite(SPI4_NSS, LOW);
    spi_iso.transfer16(digital_outputs);
    digitalWrite(SPI4_NSS, HIGH);

    leds.update();
    
    digital_outputs = 0;
}

void industrialli_digital_output::write(uint8_t _output, bool _value){
    if(_value){
        digital_outputs |= 0x01 << (_output - 1);
    }else {
        digital_outputs &= ~(0x01 << (_output - 1));
    }

    set_digital_output_led(_output - 1, _value);
}

void industrialli_digital_output::set_digital_output_led(uint8_t _led, bool _value){
    if(_led < 8){
        leds.set_led(_led + 12, _value);
    }else {
        leds.set_led(_led + 16, _value);
    }
}

void industrialli_digital_output::update_power_leds_status(){
    if (digitalRead(IC1_ISO_DIAG)){
        leds.set_led(22, HIGH);
    }else{
        leds.set_led(22, LOW);
    }

    if (digitalRead(IC2_ISO_DIAG)){
        leds.set_led(23, HIGH);
    }else{
        leds.set_led(23, LOW);
    }
}

bool industrialli_digital_output::output_1_to_8_status(){
    return digitalRead(IC1_ISO_DIAG);
}

bool industrialli_digital_output::output_9_to_16_status(){
    return digitalRead(IC2_ISO_DIAG);
}
