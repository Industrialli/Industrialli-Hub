#include "digital_input/industrialli_digInHub.h"
uint32_t _userMode;

callback_function_t _userFunction;

volatile int industrialli_digitalInputsHub::_count_00;
volatile int industrialli_digitalInputsHub::_count_01;
volatile int industrialli_digitalInputsHub::_count_02;
volatile int industrialli_digitalInputsHub::_count_03;
volatile int industrialli_digitalInputsHub::_count_04;
volatile int industrialli_digitalInputsHub::_count_05;
volatile int industrialli_digitalInputsHub::_count_06;
volatile int industrialli_digitalInputsHub::_count_07;

volatile bool industrialli_digitalInputsHub::_upOrDown;
// interrupt
volatile bool industrialli_digitalInputsHub::_input_00 = false;
volatile bool industrialli_digitalInputsHub::_input_01 = false;
volatile bool industrialli_digitalInputsHub::_input_02 = false;
volatile bool industrialli_digitalInputsHub::_input_03 = false;
volatile bool industrialli_digitalInputsHub::_input_04 = false;
volatile bool industrialli_digitalInputsHub::_input_05 = false;
volatile bool industrialli_digitalInputsHub::_input_06 = false;
volatile bool industrialli_digitalInputsHub::_input_07 = false;

// ENCODER

volatile int industrialli_digitalInputsHub::_aStateEncoder_I01_A;
volatile int industrialli_digitalInputsHub::_aStateEncoder_I03_A;
volatile int industrialli_digitalInputsHub::_aStateEncoder_I05_A;
volatile int industrialli_digitalInputsHub::_aStateEncoder_I07_A;

volatile int industrialli_digitalInputsHub::_aLastStateEncoder_I01_A;
volatile int industrialli_digitalInputsHub::_aLastStateEncoder_I03_A;
volatile int industrialli_digitalInputsHub::_aLastStateEncoder_I05_A;
volatile int industrialli_digitalInputsHub::_aLastStateEncoder_I07_A;

volatile int industrialli_digitalInputsHub::_pulsesEncoder_I01_I02;
volatile int industrialli_digitalInputsHub::_pulsesEncoder_I03_I04;
volatile int industrialli_digitalInputsHub::_pulsesEncoder_I05_I06;
volatile int industrialli_digitalInputsHub::_pulsesEncoder_I07_I08;

volatile bool industrialli_digitalInputsHub::_rotationEncoder_I01_I02;
volatile bool industrialli_digitalInputsHub::_rotationEncoder_I03_I04;
volatile bool industrialli_digitalInputsHub::_rotationEncoder_I05_I06;
volatile bool industrialli_digitalInputsHub::_rotationEncoder_I07_I08;

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

void industrialli_digitalInputsHub::begin(void)
{
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
void industrialli_digitalInputsHub::allLedsOff()
{
    for (int i = 0; i < 8; i++)
    {
        _sensorType[i] = PNP;
        leds.set_led(4 + i, 0);
    }
}
void industrialli_digitalInputsHub::beginEncoder(uint8_t encoder, bool sensorType)
{
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
int industrialli_digitalInputsHub::getPulsesEncoder(uint8_t encoder)
{
    _encoder = encoder;
    // ENCODER_01_02 0
    // ENCODER_03_04 1
    // ENCODER_05_06 2
    // ENCODER_07_08 3

    switch (_encoder)
    {
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

void industrialli_digitalInputsHub::beginDigitalInputCounting(uint8_t pin, bool sensorType, bool upOrDown)
{
    _pin = pin - 1;
    _sensorType[_pin] = sensorType;
    _upOrDown = upOrDown;
    // PNP 0
    // NPN 1
    switch (_pin)
    {
    case 0:
        if (_sensorType)//NPN
        {
            beginInterruptInputFalling_00();
        }
        else //PNP
        {
            beginInterruptInputRising_00();
        }

        break;
    case 1:
        if (_sensorType)
        {
            beginInterruptInputFalling_01();
        }
        else
        {
            beginInterruptInputRising_01();
        }
        break;
    case 2:
        if (_sensorType)
        {
            beginInterruptInputFalling_02();
        }
        else
        {
            beginInterruptInputRising_02();
        }
        break;
    case 3:
        if (_sensorType)
        {
            beginInterruptInputFalling_03();
        }
        else
        {
            beginInterruptInputRising_03();
        }
        break;
    case 4:
        if (_sensorType) 
        {
            beginInterruptInputFalling_04();
        }
        else
        {
            beginInterruptInputRising_04();
        }
        break;
    case 5:
        if (_sensorType)
        {
            beginInterruptInputFalling_05();
        }
        else
        {
            beginInterruptInputRising_05();
        }
        break;
    case 6:
        if (_sensorType)
        {
            beginInterruptInputFalling_06();
        }
        else 
        {
            beginInterruptInputRising_06();
        }
        break;
    case 7:
        if (_sensorType) 
        {
            beginInterruptInputFalling_07();
        }
        else 
        {
            beginInterruptInputRising_07();
        }
        break;

    default:
        break;
    }
}
int industrialli_digitalInputsHub::getCountVal(uint8_t pin)
{
    _pin = pin - 1;
    switch (_pin)
    {
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
void industrialli_digitalInputsHub::clearCount(uint8_t pin)
{
    _pin = pin - 1;
    switch (_pin)
    {
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

void industrialli_digitalInputsHub::beginUserDigitalInput(uint8_t pin, callback_function_t userFunction, uint32_t mode, bool sensorType)
{
    _pin = pin - 1;
    _userMode = mode;
    _userFunction = userFunction;
    _sensorType[_pin] = sensorType;
    switch (_pin)
    {
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
    for (int i = 0; i < 8; i++)
    {
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
void industrialli_digitalInputsHub::testDigitalInputs()
{
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
