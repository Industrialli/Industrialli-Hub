/* Consertar problema de receber requisições rapidas de mais
 * Montar frames de resposta
 */

#include <Arduino.h>
#include <HardwareSerial.h>

#include "industrialli_hubInit.h"
#include "industrialli_ledsHub.h"
#include "industrialli_modbus_rtu.h"

#define RS485_USART2_RX PD6
#define RS485_USART2_TX PD5
#define RS485_USART2_RE_DE PD4

industrialli_hubInit startHub;
industrialli_ledsHubCtrl ledsCtrl;
HardwareSerial rs485_usart2_serial(RS485_USART2_RX, RS485_USART2_TX);
IndustrialliModbusRTU modbus;

void setup(){
	startHub.begin();
	rs485_usart2_serial.begin(9600);
	SerialUSB.begin(9600);

	modbus.begin(&rs485_usart2_serial);
	modbus.set_server_address(10);

	for (size_t i = 0; i < 32; i++){
		modbus.create_holding_register(i, LOW);
	}

	ledsCtrl.begin();
}

void loop() {
	modbus.task();

	for (int i = 0; i < 32; i++){
		ledsCtrl._shiftRegisterLed[i] = modbus.get_holding_register(i);
	}

	ledsCtrl.ledsUpdate();
}