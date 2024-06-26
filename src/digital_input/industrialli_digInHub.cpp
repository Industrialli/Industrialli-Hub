#include "digital_input/industrialli_digInHub.h"

void industrialli_digitalInputsHub::begin(){
    pinMode(EXTI_01, INPUT);
    pinMode(EXTI_02, INPUT);
    pinMode(EXTI_03, INPUT);
    pinMode(EXTI_04, INPUT);
    pinMode(EXTI_05, INPUT);
    pinMode(EXTI_06, INPUT);
    pinMode(EXTI_07, INPUT);
    pinMode(EXTI_08, INPUT);

    for (uint8_t i = 0; i < 8; i++){
        sensor_type[i] = PNP;
        led_status[i]  = 1;
        input_type[i]  = -1;
        count[i]       = 0;
    }

    for (size_t i = 0; i < 4; i++){
        encoder_sense[i]       = true;
        encoder_velocity[i]    = 0;
        encoder_last_update[i] = 0;
    }
    

    set_all_leds_off();
}

void industrialli_digitalInputsHub::begin_interrupt_input(uint8_t _pin, bool _sensor_type, bool _count_mode){
    attachInterrupt(digitalPinToInterrupt(_pin), [this, _pin, _count_mode]() {
        this->count_interrupts(_pin, _count_mode);
    }, _count_mode ? FALLING : RISING);
}

void industrialli_digitalInputsHub::count_interrupts(uint8_t _pin, bool _count_mode){
    noInterrupts();

    switch (_pin){
        case EXTI_01:
            count[0] += (_count_mode) ? -1 : 1;
            break;
        case EXTI_02:
            count[1] += (_count_mode) ? -1 : 1;
            break;
        case EXTI_03:
            count[2] += (_count_mode) ? -1 : 1;
            break;
        case EXTI_04:
            count[3] += (_count_mode) ? -1 : 1;
            break;
        case EXTI_05:
            count[4] += (_count_mode) ? -1 : 1;
            break;
        case EXTI_06:
            count[5] += (_count_mode) ? -1 : 1;
            break;
        case EXTI_07:
            count[6] += (_count_mode) ? -1 : 1;
            break;
        case EXTI_08:
            count[7] += (_count_mode) ? -1 : 1;
            break;
    }

    interrupts();
}

void industrialli_digitalInputsHub::begin_digital_input_counting(uint8_t _pin, bool _sensor_type, bool _count_mode){
    sensor_type[_pin - 1] = _sensor_type;

    switch(_pin - 1){
        case 0:
            begin_interrupt_input(EXTI_01, _sensor_type, _count_mode);
            break;
        case 1:
            begin_interrupt_input(EXTI_02, _sensor_type, _count_mode);
            break;
        case 2:
            begin_interrupt_input(EXTI_03, _sensor_type, _count_mode);
            break;
        case 3:
            begin_interrupt_input(EXTI_04, _sensor_type, _count_mode);
            break;
        case 4:
            begin_interrupt_input(EXTI_05, _sensor_type, _count_mode);
            break;
        case 5:
            begin_interrupt_input(EXTI_06, _sensor_type, _count_mode);
            break;
        case 6:
            begin_interrupt_input(EXTI_07, _sensor_type, _count_mode);
            break;
        case 7:
            begin_interrupt_input(EXTI_08, _sensor_type, _count_mode);
            break;
    }
}

int industrialli_digitalInputsHub::get_count(uint8_t _pin){
    return count[_pin - 1];
}

void industrialli_digitalInputsHub::clear_count(uint8_t _pin){
    count[_pin - 1] = 0;
}

void industrialli_digitalInputsHub::update_leds(){

    led_status[0] = digitalRead(EXTI_01);
    led_status[1] = digitalRead(EXTI_02);
    led_status[2] = digitalRead(EXTI_03);
    led_status[3] = digitalRead(EXTI_04);
    led_status[4] = digitalRead(EXTI_05);
    led_status[5] = digitalRead(EXTI_06);
    led_status[6] = digitalRead(EXTI_07);
    led_status[7] = digitalRead(EXTI_08);

    for (int i = 0; i < 8; i++){
        if(sensor_type[i] == PNP){
            if(led_status[i] == HIGH) {
                leds.set_led(4 + i, LOW);
            }else {
                leds.set_led(4 + i, HIGH);
            }
        }

        if(sensor_type[i] == NPN){
            if(led_status[i] == HIGH) {
                leds.set_led(4 + i, HIGH);
            }else {
                leds.set_led(4 + i, LOW);
            }
        }
    }
}

void industrialli_digitalInputsHub::set_all_leds_off(){
    for (int i = 0; i < 8; i++){
        leds.set_led(4 + i, 0);
    }
}

void industrialli_digitalInputsHub::begin_encoder_counting(uint8_t _encoder, bool _sensor_type){
    switch (_encoder){
        case 0:
            sensor_type[0] = _sensor_type;
            sensor_type[1] = _sensor_type;
            break;
        case 1:
            sensor_type[2] = _sensor_type;
            sensor_type[3] = _sensor_type;
            break;
        case 2:
            sensor_type[4] = _sensor_type;
            sensor_type[5] = _sensor_type;
            break;
        case 3:
            sensor_type[6] = _sensor_type;
            sensor_type[7] = _sensor_type;
            break;
    }
    
    begin_interrupt_encoder(_encoder, _sensor_type);
}

void industrialli_digitalInputsHub::begin_interrupt_encoder(uint8_t _encoder, bool _sensor_type){
    switch (_encoder){
        case 0:
            attachInterrupt(digitalPinToInterrupt(EXTI_01), [this, _encoder]() {
                this->count_encoder_interruption(_encoder);
            }, FALLING);
            break;
        case 1:
            attachInterrupt(digitalPinToInterrupt(EXTI_03), [this, _encoder]() {
                this->count_encoder_interruption(_encoder);
            }, FALLING);
            break;
        case 2:
            attachInterrupt(digitalPinToInterrupt(EXTI_05), [this, _encoder]() {
                this->count_encoder_interruption(_encoder);
            }, FALLING);
            break;
        case 3:
            attachInterrupt(digitalPinToInterrupt(EXTI_07), [this, _encoder]() {
                this->count_encoder_interruption(_encoder);
            }, FALLING);
            break;
    }

    
}

void industrialli_digitalInputsHub::count_encoder_interruption(uint8_t _encoder){
    noInterrupts();

    switch(_encoder){
        case 0:
            encoder_a = digitalRead(EXTI_01);
            encoder_b = digitalRead(EXTI_02);

            encoder_velocity[0]    = 150.0 / abs((int)encoder_last_update[0] - (int)millis());
            encoder_last_update[0] = millis();

            if (encoder_a != encoder_b){
                count[0]++;
                encoder_sense[0] = true;
        
            }else{
                count[0]--;
                encoder_sense[0] = false;
            }
            break;
        case 1:
            encoder_a = digitalRead(EXTI_03);
            encoder_b = digitalRead(EXTI_04);

            encoder_velocity[1]    = 150.0 / abs((int)encoder_last_update[1] - (int)millis());
            encoder_last_update[1] = millis();

            if (encoder_a != encoder_b){
                count[2]++;
                encoder_sense[1] = true;
        
            }else{
                count[2]--;
                encoder_sense[1] = false;
            }
            break;
        case 2:
            encoder_a = digitalRead(EXTI_05);
            encoder_b = digitalRead(EXTI_06);

            encoder_velocity[2]    = 150.0 / abs((int)encoder_last_update[2] - (int)millis());
            encoder_last_update[2] = millis();

            if (encoder_a != encoder_b){
                count[4]++;
                encoder_sense[2] = true;
        
            }else{
                count[4]--;
                encoder_sense[2] = false;
            }
            break;
        case 3:
            encoder_a = digitalRead(EXTI_07);
            encoder_b = digitalRead(EXTI_08);

            encoder_velocity[3]    = 150.0 / abs((int)encoder_last_update[3] - (int)millis());
            encoder_last_update[3] = millis();

            if (encoder_a != encoder_b){
                count[6]++;
                encoder_sense[3] = true;
        
            }else{
                count[6]--;
                encoder_sense[3] = false;
            }
            break;
    }

    interrupts();
}

int industrialli_digitalInputsHub::get_pulses_encoder(uint8_t _encoder){
    switch (_encoder){
        case 0:
            return count[0];
            break;
        case 1:
            return count[2];
            break;
        case 2:
            return count[4];
            break;
        case 3:
            return count[6];
            break;
    }
}

bool industrialli_digitalInputsHub::get_encoder_sense(uint8_t _encoder){
    return encoder_sense[_encoder];
}

double industrialli_digitalInputsHub::get_encoder_velocity(uint8_t _encoder){
    return encoder_velocity[_encoder];
}