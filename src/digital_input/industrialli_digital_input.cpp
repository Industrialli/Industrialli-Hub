#include "digital_input/industrialli_digital_input.h"

void industrialli_digital_input::begin(){
    digital_input[A01] = {PB1, NPN, false};
    digital_input[A02] = {PC5, NPN, false};
    digital_input[A03] = {PC4, NPN, false};
    digital_input[A04] = {PA0, NPN, false};

    digital_input[I01] = {PE15, PNP, false};
    digital_input[I02] = {PE14, PNP, false};
    digital_input[I03] = {PE13, PNP, false};
    digital_input[I04] = {PE12, PNP, false};
    digital_input[I05] = {PB4,  PNP, false};
    digital_input[I06] = {PB5,  PNP, false};
    digital_input[I07] = {PB6,  PNP, false};
    digital_input[I08] = {PB7,  PNP, false};

    pinMode(digital_input[A01].port, INPUT);
    pinMode(digital_input[A02].port, INPUT);
    pinMode(digital_input[A03].port, INPUT);
    pinMode(digital_input[A04].port, INPUT);

    pinMode(digital_input[I01].port, INPUT);
    pinMode(digital_input[I02].port, INPUT);
    pinMode(digital_input[I03].port, INPUT);
    pinMode(digital_input[I04].port, INPUT);
    pinMode(digital_input[I05].port, INPUT);
    pinMode(digital_input[I06].port, INPUT);
    pinMode(digital_input[I07].port, INPUT);
    pinMode(digital_input[I08].port, INPUT);

    for (int i = 0; i < 12; i++){
        leds.set_led(i, LOW);
    }
}

void industrialli_digital_input::attach_interrupt(uint8_t _pin, void (*_callback)(), uint32_t _read_mode){
    digital_input[_pin].read_mode = _read_mode;
    attachInterrupt(digital_input[_pin].port, _callback, _read_mode);
}

int industrialli_digital_input::read(uint8_t _pin){
    return digitalRead(digital_input[_pin].port);
}

void industrialli_digital_input::enable_analog(uint8_t _pin){
    digital_input[_pin].analog_as_digital = true;
}

void industrialli_digital_input::update_leds(){
    int digital_input_status[12];

    digital_input_status[A01] = digitalRead(digital_input[A01].port);
    digital_input_status[A02] = digitalRead(digital_input[A02].port);
    digital_input_status[A03] = digitalRead(digital_input[A03].port);
    digital_input_status[A04] = digitalRead(digital_input[A04].port);

    digital_input_status[I01] = digitalRead(digital_input[I01].port);
    digital_input_status[I02] = digitalRead(digital_input[I02].port);
    digital_input_status[I03] = digitalRead(digital_input[I03].port);
    digital_input_status[I04] = digitalRead(digital_input[I04].port);
    digital_input_status[I05] = digitalRead(digital_input[I05].port);
    digital_input_status[I06] = digitalRead(digital_input[I06].port);
    digital_input_status[I07] = digitalRead(digital_input[I07].port);
    digital_input_status[I08] = digitalRead(digital_input[I08].port);

    for (uint8_t i = 0; i < 12; i++) {
        if (i < 4) {
            if (digital_input[i].analog_as_digital) {
                leds.set_led(i, digital_input_status[i]);

            }

        } else {
            if (digital_input[i].read_mode == PNP) {
                leds.set_led(i, !digital_input_status[i]);

            } else if (digital_input[i].read_mode == NPN) {
                leds.set_led(i, digital_input_status[i]);

            }
        }
    }
}