#include "digital_input/industrialli_digital_input.h"

void industrialli_digital_input::begin(){
    digital_input[I01] = {PE15, PNP};
    digital_input[I02] = {PE14, PNP};
    digital_input[I03] = {PE13, PNP};
    digital_input[I04] = {PE12, PNP};
    digital_input[I05] = {PB4,  PNP};
    digital_input[I06] = {PB5,  PNP};
    digital_input[I07] = {PB6,  PNP};
    digital_input[I08] = {PB7,  PNP};

    pinMode(digital_input[I01].port, INPUT);
    pinMode(digital_input[I02].port, INPUT);
    pinMode(digital_input[I03].port, INPUT);
    pinMode(digital_input[I04].port, INPUT);
    pinMode(digital_input[I05].port, INPUT);
    pinMode(digital_input[I06].port, INPUT);
    pinMode(digital_input[I07].port, INPUT);
    pinMode(digital_input[I08].port, INPUT);

    for (int i = 0; i < 8; i++){
        leds.set_led(4 + i, LOW);
    }
}

void industrialli_digital_input::attach_interrupt(uint8_t _pin, void (*_callback)(), uint8_t _read_mode){
    digital_input[_pin].read_mode = _read_mode;
    attachInterrupt(digital_input[_pin].port, _callback, _read_mode);
}

void industrialli_digital_input::update_leds(){
    uint8_t digital_input_status[8];

    digital_input_status[I01] = digitalRead(digital_input[I01].port);
    digital_input_status[I02] = digitalRead(digital_input[I02].port);
    digital_input_status[I03] = digitalRead(digital_input[I03].port);
    digital_input_status[I04] = digitalRead(digital_input[I04].port);
    digital_input_status[I05] = digitalRead(digital_input[I05].port);
    digital_input_status[I06] = digitalRead(digital_input[I06].port);
    digital_input_status[I07] = digitalRead(digital_input[I07].port);
    digital_input_status[I08] = digitalRead(digital_input[I08].port);

    for (int i = 0; i < 8; i++){
        if(digital_input[i].read_mode == PNP){
            if(digital_input_status[i] == HIGH) {
                leds.set_led(4 + i, LOW);
            }else {
                leds.set_led(4 + i, HIGH);
            }
        }

        if(digital_input[i].read_mode == NPN){
            if(digital_input_status[i] == HIGH) {
                leds.set_led(4 + i, HIGH);
            }else {
                leds.set_led(4 + i, LOW);
            }
        }
    }
}

// void industrialli_digitalInputsHub::set_all_leds_off(){
//     for (int i = 0; i < 8; i++){
//         leds.set_led(4 + i, 0);
//     }
// }

// void industrialli_digitalInputsHub::begin_encoder_counting(uint8_t _encoder, bool _sensor_type){
//     switch (_encoder){
//         case 0:
//             sensor_type[0] = _sensor_type;
//             sensor_type[1] = _sensor_type;
//             break;
//         case 1:
//             sensor_type[2] = _sensor_type;
//             sensor_type[3] = _sensor_type;
//             break;
//         case 2:
//             sensor_type[4] = _sensor_type;
//             sensor_type[5] = _sensor_type;
//             break;
//         case 3:
//             sensor_type[6] = _sensor_type;
//             sensor_type[7] = _sensor_type;
//             break;
//     }
    
//     begin_interrupt_encoder(_encoder, _sensor_type);
// }

// void industrialli_digitalInputsHub::begin_interrupt_encoder(uint8_t _encoder, bool _sensor_type){
//     switch (_encoder){
//         case 0:
//             attachInterrupt(digitalPinToInterrupt(EXTI_01), [this, _encoder]() {
//                 this->count_encoder_interruption(_encoder);
//             }, FALLING);
//             break;
//         case 1:
//             attachInterrupt(digitalPinToInterrupt(EXTI_03), [this, _encoder]() {
//                 this->count_encoder_interruption(_encoder);
//             }, FALLING);
//             break;
//         case 2:
//             attachInterrupt(digitalPinToInterrupt(EXTI_05), [this, _encoder]() {
//                 this->count_encoder_interruption(_encoder);
//             }, FALLING);
//             break;
//         case 3:
//             attachInterrupt(digitalPinToInterrupt(EXTI_07), [this, _encoder]() {
//                 this->count_encoder_interruption(_encoder);
//             }, FALLING);
//             break;
//     }

    
// }

// void industrialli_digitalInputsHub::count_encoder_interruption(uint8_t _encoder){
//     noInterrupts();

//     switch(_encoder){
//         case 0:
//             encoder_a = digitalRead(EXTI_01);
//             encoder_b = digitalRead(EXTI_02);

//             if(encoder_last_update[0] - millis() >= 150){
//                 encoder_velocity[0]    = (60000.0 * abs((int32_t)encoder_last_count[0] - count[0])) / (400.0 * abs((int32_t)encoder_last_update[0] - (int32_t)millis()));
//                 encoder_last_update[0] = millis();
//                 encoder_last_count[0]  = count[0];
//             }

//             if (encoder_a != encoder_b){
//                 count[0]++;
//                 encoder_sense[0] = true;
        
//             }else{
//                 count[0]--;
//                 encoder_sense[0] = false;
//             }
//             break;
//         case 1:
//             encoder_a = digitalRead(EXTI_03);
//             encoder_b = digitalRead(EXTI_04);

//             if(encoder_last_update[1] - millis() >= 150){
//                 encoder_velocity[1]    = (60000.0 * abs((int32_t)encoder_last_count[1] - count[1])) / (400.0 * abs((int32_t)encoder_last_update[1] - (int32_t)millis()));
//                 encoder_last_update[1] = millis();
//                 encoder_last_count[1]  = count[1];
//             }

//             if (encoder_a != encoder_b){
//                 count[2]++;
//                 encoder_sense[1] = true;
        
//             }else{
//                 count[2]--;
//                 encoder_sense[1] = false;
//             }
//             break;
//         case 2:
//             encoder_a = digitalRead(EXTI_05);
//             encoder_b = digitalRead(EXTI_06);

//             if(encoder_last_update[2] - millis() >= 150){
//                 encoder_velocity[2]    = (60000.0 * abs((int32_t)encoder_last_count[2] - count[2])) / (400.0 * abs((int32_t)encoder_last_update[2] - (int32_t)millis()));
//                 encoder_last_update[2] = millis();
//                 encoder_last_count[2]  = count[2];
//             }

//             if (encoder_a != encoder_b){
//                 count[4]++;
//                 encoder_sense[2] = true;
        
//             }else{
//                 count[4]--;
//                 encoder_sense[2] = false;
//             }
//             break;
//         case 3:
//             encoder_a = digitalRead(EXTI_07);
//             encoder_b = digitalRead(EXTI_08);

//             if(encoder_last_update[3] - millis() >= 150){
//                 encoder_last_update[3] = millis();
//                 encoder_last_count[3]  = count[3];
//             }

//             if (encoder_a != encoder_b){
//                 count[6]++;
//                 encoder_sense[3] = true;
        
//             }else{
//                 count[6]--;
//                 encoder_sense[3] = false;
//             }
//             break;
//     }

//     interrupts();
// }

// int industrialli_digitalInputsHub::get_pulses_encoder(uint8_t _encoder){
//     switch (_encoder){
//         case 0:
//             return count[0];
//             break;
//         case 1:
//             return count[2];
//             break;
//         case 2:
//             return count[4];
//             break;
//         case 3:
//             return count[6];
//             break;
//     }
// }

// bool industrialli_digitalInputsHub::get_encoder_sense(uint8_t _encoder){
//     return encoder_sense[_encoder];
// }

// double industrialli_digitalInputsHub::get_encoder_velocity(uint8_t _encoder){
//     return encoder_velocity[_encoder];
// }