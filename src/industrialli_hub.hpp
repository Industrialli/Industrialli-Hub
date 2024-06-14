#include <Arduino.h>

#include "leds/industrialli_leds.h"
#include "loramesh/industrialli_loramesh.h"
#include "digital_output/industrialli_digital_output.h"
#include "digital_input/industrialli_digInHub.h"
#include "analog_input/industrialli_anlgInHub.h"
#include "nextion/industrialli_nextion.h"
#include "modbus/industrialli_modbus_rtu_client.h"
#include "modbus/industrialli_modbus_rtu_server.h"

#define DEBUG_LED PB10
#define RS485_TER_SEL PE10

SPIClass spi_leds;
SPIClass spi_iso;

HardwareSerial modbus_serial(RS485_USART2_RX, RS485_USART2_TX);
HardwareSerial lora_serial(LORA_CMD_UART8_RX, LORA_CMD_UART8_TX);
HardwareSerial nextion_serial(NEXTION_USART3_RX, NEXTION_USART3_TX);

industrialli_leds leds;
industrialli_digital_output digital_output;
Industrialli_Modbus_RTU_Server modbus_server;
Industrialli_Modbus_RTU_Client modbus_client;
industrialli_digitalInputsHub digInHub;
industrialli_analogInputsHub anlgInHub;
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