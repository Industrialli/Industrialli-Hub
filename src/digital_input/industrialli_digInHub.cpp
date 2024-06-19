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

// /////////////////////////////////////////////////// ENCODER EXTI01 & EXTI02 //////////////////////////////////////////////////////////////////
// // EXTI01 -> ENCODER A
// // EXTI02 -> ENCODER B

// static void beginEncoder_I01_A_Falling() // Encoder A PNP
// {
//     attachInterrupt(digitalPinToInterrupt(EXTI_01), Encoder_I01_A, FALLING);
// }
// static void Encoder_I01_A(void)
// {
//     noInterrupts();
//     _input_00 = digitalRead(EXTI_01);
//     _aStateEncoder_I01_A = _input_00;
//     _input_01 = digitalRead(EXTI_02);

//     if (_input_01 != _aStateEncoder_I01_A)
//     {
//         _pulsesEncoder_I01_I02++; // CW
//     }
//     else
//     {
//         _pulsesEncoder_I01_I02--; // CCW
//     }

//     interrupts();
// }

// /////////////////////////////////////////////////// ENCODER EXTI03 & EXTI04 //////////////////////////////////////////////////////////////////
// // EXTI03 -> ENCODER A
// // EXTI04 -> ENCODER B

// static void beginEncoder_I03_A_Falling() // Encoder A PNP
// {
//     attachInterrupt(digitalPinToInterrupt(EXTI_03), Encoder_I03_A, FALLING);
// }
// static void Encoder_I03_A(void)
// {
//     noInterrupts();
//     _input_02 = digitalRead(EXTI_03);
//     _aStateEncoder_I03_A = _input_02;
//     _input_03 = digitalRead(EXTI_04);

//     if (_input_03 != _aStateEncoder_I03_A)
//     {
//         _pulsesEncoder_I03_I04++; // CW
//     }
//     else
//     {
//         _pulsesEncoder_I03_I04--; // CCW
//     }

//     interrupts();
// }

// /////////////////////////////////////////////////// ENCODER EXTI05 & EXTI06 //////////////////////////////////////////////////////////////////
// // EXTI05 -> ENCODER A
// // EXTI06 -> ENCODER B

// static void beginEncoder_I05_A_Falling() // Encoder A PNP
// {
//     attachInterrupt(digitalPinToInterrupt(EXTI_05), Encoder_I05_A, FALLING);
// }
// static void Encoder_I05_A(void)
// {
//     noInterrupts();
//     _input_04 = digitalRead(EXTI_05);
//     _aStateEncoder_I05_A = _input_04;
//     _input_05 = digitalRead(EXTI_06);

//     if (_input_05 != _aStateEncoder_I05_A)
//     {
//         _pulsesEncoder_I05_I06++; // CW
//     }
//     else
//     {
//         _pulsesEncoder_I05_I06--; // CCW
//     }

//     interrupts();
// }

/////////////////////////////////////////////////// ENCODER EXTI07 & EXTI08 //////////////////////////////////////////////////////////////////
// EXTI07 -> ENCODER A
// EXTI08 -> ENCODER B

// static void beginEncoder_I07_A_Falling() // Encoder A PNP
// {
//     attachInterrupt(digitalPinToInterrupt(EXTI_07), Encoder_I07_A, FALLING);
// }
// static void Encoder_I07_A(void)
// {
//     noInterrupts();
//     _input_06 = digitalRead(EXTI_07);
//     _aStateEncoder_I07_A = _input_06;
//     _input_07 = digitalRead(EXTI_08);

//     if (_input_07 != _aStateEncoder_I07_A)
//     {
//         _pulsesEncoder_I07_I08++; // CW
//     }
//     else
//     {
//         _pulsesEncoder_I07_I08--; // CCW
//     }

//     interrupts();
// }

// void industrialli_digitalInputsHub::beginEncoder(uint8_t encoder, bool sensorType){
//     _encoder = encoder;

//     if (sensorType == PNP)
//         switch (_encoder)
//         {
//         case 0:
//             pinMode(EXTI_01, INPUT);
//             pinMode(EXTI_02, INPUT);
//             _sensorType[0] = sensorType;
//             _sensorType[1] = sensorType;
//             _input_00 = digitalRead(EXTI_01);
//             _input_01 = digitalRead(EXTI_02);
//             beginEncoder_I01_A_Falling();
//             break;
//         case 1:
//             pinMode(EXTI_03, INPUT);
//             pinMode(EXTI_04, INPUT);
//             _sensorType[2] = sensorType;
//             _sensorType[3] = sensorType;
//             _input_02 = digitalRead(EXTI_03);
//             _input_02 = digitalRead(EXTI_04);
//             beginEncoder_I03_A_Falling();
//             break;
//         case 2:
//             pinMode(EXTI_05, INPUT);
//             pinMode(EXTI_06, INPUT);
//             _sensorType[4] = sensorType;
//             _sensorType[5] = sensorType;
//             _input_04 = digitalRead(EXTI_05);
//             _input_02 = digitalRead(EXTI_06);
//             beginEncoder_I05_A_Falling();
//             break;
//         case 3:
//             pinMode(EXTI_07, INPUT);
//             pinMode(EXTI_08, INPUT);
//             _sensorType[6] = sensorType;
//             _sensorType[7] = sensorType;
//             _input_06 = digitalRead(EXTI_07);
//             _input_02 = digitalRead(EXTI_08);
//             beginEncoder_I07_A_Falling();
//             break;

//         default:
//             break;
//         }
// }

// int industrialli_digitalInputsHub::getPulsesEncoder(uint8_t encoder){
//     _encoder = encoder;

//     switch (_encoder){
//     case 0:
//         return _pulsesEncoder_I01_I02;
//         break;
//     case 1:
//         return _pulsesEncoder_I03_I04;
//         break;
//     case 2:
//         return _pulsesEncoder_I05_I06;
//         break;
//     case 3:
//         return _pulsesEncoder_I07_I08;
//         break;

//     default:
//         return -1;
//         break;
//     }
// }

// void industrialli_digitalInputsHub::beginUserDigitalInput(uint8_t pin, callback_function_t userFunction, uint32_t mode, bool sensorType){
//     _pin              = pin - 1;
//     _userMode         = mode;
//     _userFunction     = userFunction;
//     _sensorType[_pin] = sensorType;
    
//     switch (_pin){
//         case 0:
//             beginUserInterruptInput_00();
//             break;
//         case 1:
//             beginUserInterruptInput_01();
//             break;
//         case 2:
//             beginUserInterruptInput_02();
//             break;
//         case 3:
//             beginUserInterruptInput_03();
//             break;
//         case 4:
//             beginUserInterruptInput_04();
//             break;
//         case 5:
//             beginUserInterruptInput_05();
//             break;
//         case 6:
//             beginUserInterruptInput_06();
//             break;
//         case 7:
//             beginUserInterruptInput_07();
//             break;

//         default:
//             break;
//     }
// }
