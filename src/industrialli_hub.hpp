#include <Arduino.h>
<<<<<<< HEAD
#include <Ethernet2.h>
#include <EasyNextionLibrary.h>
#include <LoRaMESH.h>
=======
>>>>>>> f6538ce05652f915e65e9a7680b3b738f9becd15

#include "leds/industrialli_leds.h"
#include "digital_output/industrialli_digital_output.h"
#include "digital_input/industrialli_digital_input.h"
#include "analog_input/industrialli_analog_input.h"
#include "modbus/industrialli_modbus_rtu_client.h"
#include "modbus/industrialli_modbus_rtu_server.h"

#define DEBUG_LED PB10
#define RS485_TER_SEL PE10

SPIClass spi_leds;
SPIClass spi_iso;
SPIClass spi_ethernet;

HardwareSerial modbus_serial(PD6, PD5);
HardwareSerial lora_serial(PE0, PE1);
HardwareSerial nextion_serial(PD9, PD8);

industrialli_leds leds;
industrialli_digital_output digital_output;
industrialli_digital_input digital_input;
industrialli_analog_input analog_input;
Industrialli_Modbus_RTU_Server modbus_server(&modbus_serial);
Industrialli_Modbus_RTU_Client modbus_client(&modbus_serial);
LoRaMESH lora(&lora_serial);
EasyNex nextion(nextion_serial);

class industrialli_hub{
    public:
    void begin();
};

void industrialli_hub::begin(){
    pinMode(DEBUG_LED, OUTPUT);
    pinMode(RS485_TER_SEL, OUTPUT);

    modbus_serial.begin(9600);
    lora_serial.begin(9600);
    nextion_serial.begin(9600);

    leds.begin();
}

