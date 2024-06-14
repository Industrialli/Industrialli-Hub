#ifndef INDUSTRIALLI_DIGINHUB_H
#define INDUSTRIALLI_DIGINHUB_H

#include <Arduino.h>
#include <stdlib.h>
#include "leds/industrialli_leds.h"

extern industrialli_leds leds;
extern volatile int _aState_ENCA;
extern volatile int _pulses_ENCA;
extern volatile bool _rotation_ENCA;
extern uint32_t _userMode;

extern callback_function_t _userFunction;

// Input dig.
#define EXTI_01 PE15
#define EXTI_02 PE14
#define EXTI_03 PE13
#define EXTI_04 PE12
#define EXTI_05 PB4
#define EXTI_06 PB5
#define EXTI_07 PB6
#define EXTI_08 PB7

#define I01 1
#define I02 2
#define I03 3
#define I04 4
#define I05 5
#define I06 6
#define I07 7
#define I08 8

#define PNP 0 // Ativado -> HIGH(LED ACESO), Desativado -> LOW(LED APAGADO)
#define NPN 1 // Ativado -> LOW(LED APAGADO), Desativado -> HIGH(LED ACESO)

#define ENCODER_01_02 0
#define ENCODER_03_04 1
#define ENCODER_05_06 2
#define ENCODER_07_08 3

#define UP 0
#define DOWN 1

class industrialli_digitalInputsHub
{
public:
    static volatile bool _input_00; // interrupt
    static volatile bool _input_01;
    static volatile bool _input_02;
    static volatile bool _input_03;
    static volatile bool _input_04;
    static volatile bool _input_05;
    static volatile bool _input_06;
    static volatile bool _input_07;

    static volatile bool _upOrDown;

    static volatile int _count_00;
    static volatile int _count_01;
    static volatile int _count_02;
    static volatile int _count_03;
    static volatile int _count_04;
    static volatile int _count_05;
    static volatile int _count_06;
    static volatile int _count_07;

    static volatile int _aStateEncoder_I01_A;
    static volatile int _aStateEncoder_I03_A;
    static volatile int _aStateEncoder_I05_A;
    static volatile int _aStateEncoder_I07_A;

    static volatile int _aLastStateEncoder_I01_A;
    static volatile int _aLastStateEncoder_I03_A;
    static volatile int _aLastStateEncoder_I05_A;
    static volatile int _aLastStateEncoder_I07_A;

    static volatile int _pulsesEncoder_I01_I02;
    static volatile int _pulsesEncoder_I03_I04;
    static volatile int _pulsesEncoder_I05_I06;
    static volatile int _pulsesEncoder_I07_I08;

    static volatile bool _rotationEncoder_I01_I02;
    static volatile bool _rotationEncoder_I03_I04;
    static volatile bool _rotationEncoder_I05_I06;
    static volatile bool _rotationEncoder_I07_I08;

    /////////////////////////////////////////////////// USUARIO //////////////////////////////////////////////////////////////////

    static void beginUserInterruptInput_00() // EXTI01 USER
    {
        pinMode(EXTI_01, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_01), _userFunction, _userMode);
    }
    static void beginUserInterruptInput_01() // EXTI02 USER
    {
        pinMode(EXTI_02, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_02), _userFunction, _userMode);
    }
    static void beginUserInterruptInput_02() // EXTI03 USER
    {
        pinMode(EXTI_03, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_03), _userFunction, _userMode);
    }
    static void beginUserInterruptInput_03() // EXTI04 USER
    {
        pinMode(EXTI_04, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_04), _userFunction, _userMode);
    }
    static void beginUserInterruptInput_04() // EXTI05 USER
    {
        pinMode(EXTI_05, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_05), _userFunction, _userMode);
    }
    static void beginUserInterruptInput_05() // EXTI06 USER
    {
        pinMode(EXTI_06, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_06), _userFunction, _userMode);
    }
    static void beginUserInterruptInput_06() // EXTI07 USER
    {
        pinMode(EXTI_07, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_07), _userFunction, _userMode);
    }
    static void beginUserInterruptInput_07() // EXTI08 USER
    {
        pinMode(EXTI_08, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_08), _userFunction, _userMode);
    }

    /////////////////////////////////////////////////// CONTAGEM EXTI01 //////////////////////////////////////////////////////////////////

    static void beginInterruptInputFalling_00() // EXTI01 FALLING CONTAGEM PNP
    {
        pinMode(EXTI_01, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_01), interruptInputFalling_00, FALLING);
    }
    static void interruptInputFalling_00(void)
    {
        noInterrupts();
        if (_upOrDown == 0)
        {
            _count_00++;
        }
        else
        {
            _count_00--;
        }

        interrupts();
    }

    static void beginInterruptInputRising_00() // EXTI01 RISING CONTAGEM NPN
    {
        pinMode(EXTI_01, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_01), interruptInputRising_00, RISING);
    }
    static void interruptInputRising_00(void)
    {
        noInterrupts();
        if (_upOrDown == 0)
        {
            _count_00++;
        }
        else
        {
            _count_00--;
        }

        interrupts();
    }

    /////////////////////////////////////////////////// CONTAGEM EXTI02 //////////////////////////////////////////////////////////////////

    static void beginInterruptInputFalling_01() // EXTI02 FALLING CONTAGEM PNP
    {
        pinMode(EXTI_02, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_02), interruptInputFalling_01, FALLING);
    }
    static void interruptInputFalling_01(void)
    {
        noInterrupts();
        if (_upOrDown == 0)
        {
            _count_01++;
        }
        else
        {
            _count_01--;
        }

        interrupts();
    }

    static void beginInterruptInputRising_01() // EXTI02 RISING CONTAGEM NPN
    {
        pinMode(EXTI_02, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_02), interruptInputRising_01, RISING);
    }
    static void interruptInputRising_01(void)
    {
        noInterrupts();
        if (_upOrDown == 0)
        {
            _count_01++;
        }
        else
        {
            _count_01--;
        }

        interrupts();
    }

    /////////////////////////////////////////////////// CONTAGEM EXTI03 //////////////////////////////////////////////////////////////////

    static void beginInterruptInputFalling_02() // EXTI03 FALLING CONTAGEM PNP
    {
        pinMode(EXTI_03, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_03), interruptInputFalling_02, FALLING);
    }
    static void interruptInputFalling_02(void)
    {
        noInterrupts();
        if (_upOrDown == 0)
        {
            _count_02++;
        }
        else
        {
            _count_02--;
        }

        interrupts();
    }

    static void beginInterruptInputRising_02() // EXTI03 RISING CONTAGEM NPN
    {
        pinMode(EXTI_03, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_03), interruptInputRising_02, RISING);
    }
    static void interruptInputRising_02(void)
    {
        noInterrupts();
        if (_upOrDown == 0)
        {
            _count_02++;
        }
        else
        {
            _count_02--;
        }

        interrupts();
    }

    /////////////////////////////////////////////////// CONTAGEM EXTI04 //////////////////////////////////////////////////////////////////

    static void beginInterruptInputFalling_03() // EXTI04 FALLING CONTAGEM PNP
    {
        pinMode(EXTI_04, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_04), interruptInputFalling_03, FALLING);
    }
    static void interruptInputFalling_03(void)
    {
        noInterrupts();
        if (_upOrDown == 0)
        {
            _count_03++;
        }
        else
        {
            _count_03--;
        }

        interrupts();
    }

    static void beginInterruptInputRising_03() // EXTI04 RISING CONTAGEM NPN
    {
        pinMode(EXTI_04, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_04), interruptInputRising_03, RISING);
    }
    static void interruptInputRising_03(void)
    {
        noInterrupts();
        if (_upOrDown == 0)
        {
            _count_03++;
        }
        else
        {
            _count_03--;
        }

        interrupts();
    }

    /////////////////////////////////////////////////// CONTAGEM EXTI05 //////////////////////////////////////////////////////////////////

    static void beginInterruptInputFalling_04() // EXTI05 FALLING CONTAGEM PNP
    {
        pinMode(EXTI_05, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_05), interruptInputFalling_04, FALLING);
    }
    static void interruptInputFalling_04(void)
    {
        noInterrupts();
        if (_upOrDown == 0)
        {
            _count_04++;
        }
        else
        {
            _count_04--;
        }

        interrupts();
    }

    static void beginInterruptInputRising_04() // EXTI05 RISING CONTAGEM NPN
    {
        pinMode(EXTI_05, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_05), interruptInputRising_04, RISING);
    }
    static void interruptInputRising_04(void)
    {
        noInterrupts();
        if (_upOrDown == 0)
        {
            _count_04++;
        }
        else
        {
            _count_04--;
        }

        interrupts();
    }

    /////////////////////////////////////////////////// CONTAGEM EXTI06 //////////////////////////////////////////////////////////////////

    static void beginInterruptInputFalling_05() // EXTI06 FALLING CONTAGEM PNP
    {
        pinMode(EXTI_06, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_06), interruptInputFalling_05, FALLING);
    }
    static void interruptInputFalling_05(void)
    {
        noInterrupts();
        if (_upOrDown == 0)
        {
            _count_05++;
        }
        else
        {
            _count_05--;
        }

        interrupts();
    }

    static void beginInterruptInputRising_05() // EXTI06 RISING CONTAGEM NPN
    {
        pinMode(EXTI_06, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_06), interruptInputRising_05, RISING);
    }
    static void interruptInputRising_05(void)
    {
        noInterrupts();
        if (_upOrDown == 0)
        {
            _count_05++;
        }
        else
        {
            _count_05--;
        }

        interrupts();
    }

    /////////////////////////////////////////////////// CONTAGEM EXTI07 //////////////////////////////////////////////////////////////////

    static void beginInterruptInputFalling_06() // EXTI07 FALLING CONTAGEM PNP
    {
        pinMode(EXTI_07, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_07), interruptInputFalling_06, FALLING);
    }
    static void interruptInputFalling_06(void)
    {
        noInterrupts();
        if (_upOrDown == 0)
        {
            _count_06++;
        }
        else
        {
            _count_06--;
        }

        interrupts();
    }

    static void beginInterruptInputRising_06() // EXTI07 RISING CONTAGEM NPN
    {
        pinMode(EXTI_07, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_07), interruptInputRising_06, RISING);
    }
    static void interruptInputRising_06(void)
    {
        noInterrupts();
        if (_upOrDown == 0)
        {
            _count_06++;
        }
        else
        {
            _count_06--;
        }

        interrupts();
    }

    /////////////////////////////////////////////////// CONTAGEM EXTI08 //////////////////////////////////////////////////////////////////

    static void beginInterruptInputFalling_07() // EXTI08 FALLING CONTAGEM PNP
    {
        pinMode(EXTI_08, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_08), interruptInputFalling_07, FALLING);
    }
    static void interruptInputFalling_07(void)
    {
        noInterrupts();
        if (_upOrDown == 0)
        {
            _count_07++;
        }
        else
        {
            _count_07--;
        }

        interrupts();
    }

    static void beginInterruptInputRising_07() // EXTI08 RISING CONTAGEM NPN
    {
        pinMode(EXTI_08, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_08), interruptInputRising_07, RISING);
    }
    static void interruptInputRising_07(void)
    {
        noInterrupts();
        if (_upOrDown == 0)
        {
            _count_07++;
        }
        else
        {
            _count_07--;
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
    void begin(void);
    void updateDigitalInputsLeds();                                                                            // Atualiza os valores dos LEDs
    void beginEncoder(uint8_t encoder, bool sensorType);                                                       // Inicia o encoder
    int getPulsesEncoder(uint8_t encoder);                                                                     // Retorna o valor dos pulos do encoder selecionado
    void beginDigitalInputCounting(uint8_t pin, bool sensorType, bool upOrDown);                               // Retorna a contagem da entrada selecionada
    int getCountVal(uint8_t pin);
    void clearCount(uint8_t pin);                                                                              // Limpa o valor da contagem na entrada
    void beginUserDigitalInput(uint8_t pin, callback_function_t userFunction, uint32_t mode, bool sensorType); // inicia a entrada selecionada para chamar a funcao do usuario
    void initTestInterrupts();
    void testDigitalInputs();
    void allLedsOff();

private:
    uint8_t _pin;
    uint8_t _ledStatus[8] = {
        _ledStatus[0] = 1,
        _ledStatus[1] = 1,
        _ledStatus[2] = 1,
        _ledStatus[3] = 1,
        _ledStatus[4] = 1,
        _ledStatus[5] = 1,
        _ledStatus[6] = 1,
        _ledStatus[7] = 1};

    int _inputType[8] = {
        _inputType[0] = -1,
        _inputType[1] = -1,
        _inputType[2] = -1,
        _inputType[3] = -1,
        _inputType[4] = -1,
        _inputType[5] = -1,
        _inputType[6] = -1,
        _inputType[7] = -1

    };
    uint8_t _sensorType[8] = {
        _sensorType[0] = PNP,
        _sensorType[1] = PNP,
        _sensorType[2] = PNP,
        _sensorType[3] = PNP,
        _sensorType[4] = PNP,
        _sensorType[5] = PNP,
        _sensorType[6] = PNP,
        _sensorType[7] = PNP
    };

    uint8_t _encoder;
};

#endif