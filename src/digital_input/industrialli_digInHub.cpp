#include "digital_input/industrialli_digInHub.h"

void industrialli_digitalInputsHub::beginUserInterruptInput(uint8_t _pin){
    attachInterrupt(digitalPinToInterrupt(_pin), _userFunction, _userMode);
}

void industrialli_digitalInputsHub::beginInterruptInput(uint8_t _pin, bool _count_mode){
    attachInterrupt(digitalPinToInterrupt(_pin), []() {instance->interruptInput(_pin, false);}, _count_mode);
}

void industrialli_digitalInputsHub::beginInterruptInput(uint8_t _pin, bool _count_mode){
    attachInterrupt(digitalPinToInterrupt(_pin), []() {instance->interruptInput(_pin, false);}, _count_mode);
}

void industrialli_digitalInputsHub::interruptInput(uint8_t _pin, bool _count_mode){
    noInterrupts();

    switch (_pin){
        case EXTI_01:
            _count_00 += (_count_mode) ? -1 : 1;
            break;
        case EXTI_02:
            _count_01 += (_count_mode) ? -1 : 1;
            break;
        case EXTI_03:
            _count_02 += (_count_mode) ? -1 : 1;
            break;
        case EXTI_04:
            _count_03 += (_count_mode) ? -1 : 1;
            break;
        case EXTI_05:
            _count_04 += (_count_mode) ? -1 : 1;
            break;
        case EXTI_06:
            _count_05 += (_count_mode) ? -1 : 1;
            break;
        case EXTI_07:
            _count_06 += (_count_mode) ? -1 : 1;
            break;
        case EXTI_08:
            _count_07 += (_count_mode) ? -1 : 1;
            break;
    }

    interrupts();
}

    /////////////////////////////////////////////////// ENCODER EXTI01 & EXTI02 //////////////////////////////////////////////////////////////////
    // EXTI01 -> ENCODER A
    // EXTI02 -> ENCODER B

    static void beginEncoder_I01_A_Falling() // Encoder A PNP
    {
        attachInterrupt(digitalPinToInterrupt(EXTI_01), Encoder_I01_A, FALLING);
    }
    static void Encoder_I01_A(void)
    {
        noInterrupts();
        _input_00 = digitalRead(EXTI_01);
        _aStateEncoder_I01_A = _input_00;
        _input_01 = digitalRead(EXTI_02);

        if (_input_01 != _aStateEncoder_I01_A)
        {
            _pulsesEncoder_I01_I02++; // CW
        }
        else
        {
            _pulsesEncoder_I01_I02--; // CCW
        }

        interrupts();
    }

    /////////////////////////////////////////////////// ENCODER EXTI03 & EXTI04 //////////////////////////////////////////////////////////////////
    // EXTI03 -> ENCODER A
    // EXTI04 -> ENCODER B

    static void beginEncoder_I03_A_Falling() // Encoder A PNP
    {
        attachInterrupt(digitalPinToInterrupt(EXTI_03), Encoder_I03_A, FALLING);
    }
    static void Encoder_I03_A(void)
    {
        noInterrupts();
        _input_02 = digitalRead(EXTI_03);
        _aStateEncoder_I03_A = _input_02;
        _input_03 = digitalRead(EXTI_04);

        if (_input_03 != _aStateEncoder_I03_A)
        {
            _pulsesEncoder_I03_I04++; // CW
        }
        else
        {
            _pulsesEncoder_I03_I04--; // CCW
        }

        interrupts();
    }

    /////////////////////////////////////////////////// ENCODER EXTI05 & EXTI06 //////////////////////////////////////////////////////////////////
    // EXTI05 -> ENCODER A
    // EXTI06 -> ENCODER B

    static void beginEncoder_I05_A_Falling() // Encoder A PNP
    {
        attachInterrupt(digitalPinToInterrupt(EXTI_05), Encoder_I05_A, FALLING);
    }
    static void Encoder_I05_A(void)
    {
        noInterrupts();
        _input_04 = digitalRead(EXTI_05);
        _aStateEncoder_I05_A = _input_04;
        _input_05 = digitalRead(EXTI_06);

        if (_input_05 != _aStateEncoder_I05_A)
        {
            _pulsesEncoder_I05_I06++; // CW
        }
        else
        {
            _pulsesEncoder_I05_I06--; // CCW
        }

        interrupts();
    }

    /////////////////////////////////////////////////// ENCODER EXTI07 & EXTI08 //////////////////////////////////////////////////////////////////
    // EXTI07 -> ENCODER A
    // EXTI08 -> ENCODER B

    static void beginEncoder_I07_A_Falling() // Encoder A PNP
    {
        attachInterrupt(digitalPinToInterrupt(EXTI_07), Encoder_I07_A, FALLING);
    }
    static void Encoder_I07_A(void)
    {
        noInterrupts();
        _input_06 = digitalRead(EXTI_07);
        _aStateEncoder_I07_A = _input_06;
        _input_07 = digitalRead(EXTI_08);

        if (_input_07 != _aStateEncoder_I07_A)
        {
            _pulsesEncoder_I07_I08++; // CW
        }
        else
        {
            _pulsesEncoder_I07_I08--; // CCW
        }

        interrupts();
    }

void industrialli_digitalInputsHub::updateDigitalInputsLeds() // Atualiza o valor dos LEDs
{

    _ledStatus[0] = digitalRead(EXTI_01);
    _ledStatus[1] = digitalRead(EXTI_02);
    _ledStatus[2] = digitalRead(EXTI_03);
    _ledStatus[3] = digitalRead(EXTI_04);
    _ledStatus[4] = digitalRead(EXTI_05);
    _ledStatus[5] = digitalRead(EXTI_06);
    _ledStatus[6] = digitalRead(EXTI_07);
    _ledStatus[7] = digitalRead(EXTI_08);

    // PNP 0 // Ativado -> HIGH(LED ACESO), Desativado -> LOW(LED APAGADO)
    // NPN 1 // Ativado -> LOW(LED APAGADO), Desativado -> HIGH(LED ACESO)

    // INPUT CONNECTOR: LOW -> OUTPUT OPTO: HIGH
    // INPUT CONNECTOR: HIGH -> OUTPUT OPTO: LOW

    for (int i = 0; i < 8; i++){
        if (_sensorType[i] == 0){
            if (_ledStatus[i] == 1)
            {
                leds.set_led(4 + i, 0); // PNP desativado
            }
            else
            {
                leds.set_led(4 + i, 1); // PNP ativado
            }
        }
        else if (_sensorType[i] == 1) // Sensor NPN
        {
            if (_ledStatus[i] == 1)
            {
                leds.set_led(4 + i, 1); // NPN ativado
            }
            else
            {
                leds.set_led(4 + i, 0); // NPN desativado
            }
        }
    }
}

void industrialli_digitalInputsHub::begin(){
    pinMode(EXTI_01, INPUT);
    pinMode(EXTI_02, INPUT);
    pinMode(EXTI_03, INPUT);
    pinMode(EXTI_04, INPUT);
    pinMode(EXTI_05, INPUT);
    pinMode(EXTI_06, INPUT);
    pinMode(EXTI_07, INPUT);
    pinMode(EXTI_08, INPUT);
    allLedsOff();
}

void industrialli_digitalInputsHub::allLedsOff(){
    for (int i = 0; i < 8; i++){
        _sensorType[i] = PNP;
        leds.set_led(4 + i, 0);
    }
}

void industrialli_digitalInputsHub::beginEncoder(uint8_t encoder, bool sensorType){
    _encoder = encoder;

    if (sensorType == PNP)
        switch (_encoder)
        {
        case 0:
            pinMode(EXTI_01, INPUT);
            pinMode(EXTI_02, INPUT);
            _sensorType[0] = sensorType;
            _sensorType[1] = sensorType;
            _input_00 = digitalRead(EXTI_01);
            _input_01 = digitalRead(EXTI_02);
            beginEncoder_I01_A_Falling();
            break;
        case 1:
            pinMode(EXTI_03, INPUT);
            pinMode(EXTI_04, INPUT);
            _sensorType[2] = sensorType;
            _sensorType[3] = sensorType;
            _input_02 = digitalRead(EXTI_03);
            _input_02 = digitalRead(EXTI_04);
            beginEncoder_I03_A_Falling();
            break;
        case 2:
            pinMode(EXTI_05, INPUT);
            pinMode(EXTI_06, INPUT);
            _sensorType[4] = sensorType;
            _sensorType[5] = sensorType;
            _input_04 = digitalRead(EXTI_05);
            _input_02 = digitalRead(EXTI_06);
            beginEncoder_I05_A_Falling();
            break;
        case 3:
            pinMode(EXTI_07, INPUT);
            pinMode(EXTI_08, INPUT);
            _sensorType[6] = sensorType;
            _sensorType[7] = sensorType;
            _input_06 = digitalRead(EXTI_07);
            _input_02 = digitalRead(EXTI_08);
            beginEncoder_I07_A_Falling();
            break;

        default:
            break;
        }
}

int industrialli_digitalInputsHub::getPulsesEncoder(uint8_t encoder){
    _encoder = encoder;

    switch (_encoder){
    case 0:
        return _pulsesEncoder_I01_I02;
        break;
    case 1:
        return _pulsesEncoder_I03_I04;
        break;
    case 2:
        return _pulsesEncoder_I05_I06;
        break;
    case 3:
        return _pulsesEncoder_I07_I08;
        break;

    default:
        return -1;
        break;
    }
}

void industrialli_digitalInputsHub::beginDigitalInputCounting(uint8_t pin, bool sensorType, bool upOrDown){
    _pin              = pin - 1;
    _sensorType[_pin] = sensorType;
    _upOrDown         = upOrDown;

    switch (_pin){
    case 0:
        if(_sensorType){//NPN
            beginInterruptInputFalling_00();
        }else {//PNP
            beginInterruptInputRising_00();
        }

        break;
    case 1:
        if(_sensorType){
            beginInterruptInputFalling_01();
        }else{
            beginInterruptInputRising_01();
        }
        break;
    case 2:
        if(_sensorType){
            beginInterruptInputFalling_02();
        }else {
            beginInterruptInputRising_02();
        }
        break;
    case 3:
        if(_sensorType){
            beginInterruptInputFalling_03();
        }else{
            beginInterruptInputRising_03();
        }
        break;
    case 4:
        if(_sensorType){
            beginInterruptInputFalling_04();
        }else {
            beginInterruptInputRising_04();
        }
        break;
    case 5:
        if(_sensorType){
            beginInterruptInputFalling_05();
        }else {
            beginInterruptInputRising_05();
        }
        break;
    case 6:
        if(_sensorType){
            beginInterruptInputFalling_06();
        }else {
            beginInterruptInputRising_06();
        }
        break;
    case 7:
        if(_sensorType){
            beginInterruptInputFalling_07();
        }else {
            beginInterruptInputRising_07();
        }
        break;

    default:
        break;
    }
}

int industrialli_digitalInputsHub::getCountVal(uint8_t pin){
    _pin = pin - 1;

    switch (_pin){
        case 0:
            return _count_00;
            break;
        case 1:
            return _count_01;
            break;
        case 2:
            return _count_02;
            break;
        case 3:
            return _count_03;
            break;
        case 4:
            return _count_04;
            break;
        case 5:
            return _count_05;
            break;
        case 6:
            return _count_06;
            break;
        case 7:
            return _count_07;
            break;

        default:
        return -1;
            break;
    }
}

void industrialli_digitalInputsHub::clearCount(uint8_t pin){
    _pin = pin - 1;

    switch (_pin){
        case 0:
            _count_00 = 0;
            break;
        case 1:
            _count_01 = 0;
            break;
        case 2:
            _count_02 = 0;
            break;
        case 3:
            _count_03 = 0;
            break;
        case 4:
            _count_04 = 0;
            break;
        case 5:
            _count_05 = 0;
            break;
        case 6:
            _count_06 = 0;
            break;
        case 7:
            _count_07 = 0;
            break;

        default:
            break;
    }
}

void industrialli_digitalInputsHub::beginUserDigitalInput(uint8_t pin, callback_function_t userFunction, uint32_t mode, bool sensorType){
    _pin              = pin - 1;
    _userMode         = mode;
    _userFunction     = userFunction;
    _sensorType[_pin] = sensorType;
    
    switch (_pin){
        case 0:
            beginUserInterruptInput_00();
            break;
        case 1:
            beginUserInterruptInput_01();
            break;
        case 2:
            beginUserInterruptInput_02();
            break;
        case 3:
            beginUserInterruptInput_03();
            break;
        case 4:
            beginUserInterruptInput_04();
            break;
        case 5:
            beginUserInterruptInput_05();
            break;
        case 6:
            beginUserInterruptInput_06();
            break;
        case 7:
            beginUserInterruptInput_07();
            break;

        default:
            break;
    }
}
void industrialli_digitalInputsHub::initTestInterrupts()
{
    _userMode = FALLING;

    for (int i = 0; i < 8; i++){
        _sensorType[i] = PNP;
    }

    beginUserInterruptInput_00();
    beginUserInterruptInput_01();
    beginUserInterruptInput_02();
    beginUserInterruptInput_03();
    beginUserInterruptInput_04();
    beginUserInterruptInput_05();
    beginUserInterruptInput_06();
    beginUserInterruptInput_07();
}

void industrialli_digitalInputsHub::testDigitalInputs(){
    SerialUSB.print(digitalRead(EXTI_01));
    SerialUSB.print(" ");
    SerialUSB.print(digitalRead(EXTI_02));
    SerialUSB.print(" ");
    SerialUSB.print(digitalRead(EXTI_03));
    SerialUSB.print(" ");
    SerialUSB.print(digitalRead(EXTI_04));
    SerialUSB.print(" ");
    SerialUSB.print(digitalRead(EXTI_05));
    SerialUSB.print(" ");
    SerialUSB.print(digitalRead(EXTI_06));
    SerialUSB.print(" ");
    SerialUSB.print(digitalRead(EXTI_07));
    SerialUSB.print(" ");
    SerialUSB.print(digitalRead(EXTI_08));
    SerialUSB.print(" ");
    SerialUSB.println();
}
