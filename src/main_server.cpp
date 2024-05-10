/* A fazer:- Processamento de mensagens de erro 2
 *         - Referenciar bibliotecas utilizadas como base
 *         - Atualizar documentação
 *         - Fazer tabela de registradores para hub
 *         - Implementar alternativa analogRead
 *         - DMA
 *         - PWM
 */
#include <Arduino.h>
#include <HardwareSerial.h>

#include "industrialli_hubInit.h"
#include "industrialli_ledsHub.h"
#include "modbus/industrialli_modbus_rtu_server.h"

#define RS485_USART2_RX PD6
#define RS485_USART2_TX PD5
#define RS485_USART2_RE_DE PD4

industrialli_hubInit startHub;
industrialli_ledsHubCtrl ledsCtrl;
HardwareSerial rs485_usart2_serial(RS485_USART2_RX, RS485_USART2_TX);
Industrialli_Modbus_RTU_Server modbus;

void setup(){
	startHub.begin();
	rs485_usart2_serial.begin(9600);
	SerialUSB.begin(9600);

	modbus.begin(&rs485_usart2_serial, RS485_USART2_RE_DE);
	modbus.set_server_address(10);

    pinMode(RS485_USART2_RE_DE, OUTPUT);

	for (int i = 0; i < 32; i++){
		modbus.create_status_coil(i, LOW);
	}

	ledsCtrl.begin();
}

void loop() {
	modbus.task();


	for (int i = 0; i < 32; i++){
		ledsCtrl._shiftRegisterLed[i] = modbus.get_status_coil(i);
	}

	ledsCtrl.ledsUpdate();
}