/* 	Registrador: possui um nome como por exemplo SENSOR_HUB e um valor
 * 	o mestre cadastra um registrador com o nome SENSOR_HUB que deve ser um número pertencente a um range pré-determinado
 *	e o escravo responde esse frame com o valor do sensor
 */ 

#include <time.h>
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
HardwareSerial Serial2(RS485_USART2_RX, RS485_USART2_TX);
IndustrialliModbusRTU mb;

void setup(){
	startHub.begin();
	Serial2.begin(9600);
	SerialUSB.begin(9600);

	mb.begin(&Serial2);
	mb.set_slave_id(10);

	// pinMode(RS485_USART2_RE_DE, OUTPUT);
	// digitalWrite(RS485_USART2_RE_DE, HIGH);

	for (size_t i = 0; i < 32; i++){
		mb.create_register(i + 100, LOW);
	}

	ledsCtrl.begin();
	
}

void loop() {
	// cenário: o mestre gera uma config aleatória de leds e manda uma requisição writeMultipleCoils para o escravo
	// delay(3000);
	mb.task();

	for (int i = 0; i < 32; i++){
		ledsCtrl._shiftRegisterLed[i] = mb.search_register(i+100)->value;
	}

	ledsCtrl.ledsUpdate();

	// srand(time(NULL));

	// for (int i = 0; i < 32; i++){
	// 	ledsCtrl._shiftRegisterLed[i] = rand() % 2;
	// }

	// uint8_t *pdu = (uint8_t*)malloc(70);

	// pdu[0] = FC_WRITE_MULTIPLE_REGISTERS;
	// pdu[1] = 0;
	// pdu[2] = 100;
	// pdu[3] = 0;
	// pdu[4] = 32;
	// pdu[5] = 0;

	// for (int i = 0; i < 64; i += 2){
	// 	pdu[6 + i]     = 0;
	// 	pdu[6 + i + 1] = ledsCtrl._shiftRegisterLed[i / 2];
	// }

	// mb.send(10, pdu, 70);
	// ledsCtrl.ledsUpdate();
	// delay(1000);
}
