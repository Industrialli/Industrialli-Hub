/* 	Registrador: possui um nome como por exemplo SENSOR_HUB e um valor
 * 	o mestre cadastra um registrador com o nome SENSOR_HUB que deve ser um número pertencente a um range pré-determinado
 *	e o escravo responde esse frame com o valor do sensor
 */ 

#include <Arduino.h>
#include <HardwareSerial.h>

#include "industrialli_hubInit.h"
#include "industrialli_ledsHub.h"
#include "industrialli_modbus_rtu.h"

#define RS485_USART2_RX PD6
#define RS485_USART2_TX PD5

industrialli_hubInit startHub;
industrialli_ledsHubCtrl ledsCtrl;
HardwareSerial Serial2(RS485_USART2_RX, RS485_USART2_TX);
IndustrialliModbusRTU mb;

const int LED0_COIL  = 100;
const int LED1_COIL  = 101; 
const int LED2_COIL  = 102; 
const int LED3_COIL  = 103; 
const int LED4_COIL  = 104; 
const int LED5_COIL  = 105; 
const int LED6_COIL  = 106; 
const int LED7_COIL  = 107; 
const int LED8_COIL  = 108; 
const int LED9_COIL  = 109; 
const int LED10_COIL = 110; 
const int LED11_COIL = 111; 
const int LED12_COIL = 112; 
const int LED13_COIL = 113; 
const int LED14_COIL = 114; 
const int LED15_COIL = 115; 
const int LED16_COIL = 116; 
const int LED17_COIL = 117; 
const int LED18_COIL = 118; 
const int LED19_COIL = 119; 
const int LED20_COIL = 120; 
const int LED21_COIL = 121; 
const int LED22_COIL = 122; 
const int LED23_COIL = 123; 
const int LED24_COIL = 124; 
const int LED25_COIL = 125; 
const int LED26_COIL = 126; 
const int LED27_COIL = 127; 
const int LED28_COIL = 128; 
const int LED29_COIL = 129; 
const int LED30_COIL = 130; 
const int LED31_COIL = 131; 

void setup(){
	startHub.begin();
	Serial2.begin(9600);

	mb.begin(&Serial2);
	mb.set_slave_id(10);
	
	mb.create_register(LED0_COIL, LOW);
	mb.create_register(LED1_COIL, LOW);
	mb.create_register(LED2_COIL, LOW);
	mb.create_register(LED3_COIL, LOW);
	mb.create_register(LED4_COIL, LOW);
	mb.create_register(LED5_COIL, LOW);
	mb.create_register(LED6_COIL, LOW);
	mb.create_register(LED7_COIL, LOW);
	mb.create_register(LED8_COIL, LOW);
	mb.create_register(LED9_COIL, LOW);
	mb.create_register(LED10_COIL, LOW);
	mb.create_register(LED11_COIL, LOW);
	mb.create_register(LED12_COIL, LOW);
	mb.create_register(LED13_COIL, LOW);
	mb.create_register(LED14_COIL, LOW);
	mb.create_register(LED15_COIL, LOW);
	mb.create_register(LED16_COIL, LOW);
	mb.create_register(LED17_COIL, LOW);
	mb.create_register(LED18_COIL, LOW);
	mb.create_register(LED19_COIL, LOW);
	mb.create_register(LED20_COIL, LOW);
	mb.create_register(LED21_COIL, LOW);
	mb.create_register(LED22_COIL, LOW);
	mb.create_register(LED23_COIL, LOW);
	mb.create_register(LED24_COIL, LOW);
	mb.create_register(LED25_COIL, LOW);
	mb.create_register(LED26_COIL, LOW);
	mb.create_register(LED27_COIL, LOW);
	mb.create_register(LED28_COIL, LOW);
	mb.create_register(LED29_COIL, LOW);
	mb.create_register(LED30_COIL, LOW);
	mb.create_register(LED31_COIL, LOW);
	
	ledsCtrl.begin();
}

void loop() {
	//cenário: o mestre envia uma requisição para o escravo para saber o status de cada led,
	//         cada led da placa será alterado aleatóriamente e o mestre ira utilizaros valores
	//         das requests para ligar os mesmos leds do escravo
	// mb.task(); isto é para os escravos

    ledsCtrl._shiftRegisterLed[0] = mb.search_register(LED0_COIL)->value;
	ledsCtrl._shiftRegisterLed[1] = mb.search_register(LED1_COIL)->value;
	ledsCtrl._shiftRegisterLed[2] = mb.search_register(LED2_COIL)->value;
	ledsCtrl._shiftRegisterLed[3] = mb.search_register(LED3_COIL)->value;
	ledsCtrl._shiftRegisterLed[4] = mb.search_register(LED4_COIL)->value;
	ledsCtrl._shiftRegisterLed[5] = mb.search_register(LED5_COIL)->value;
	ledsCtrl._shiftRegisterLed[6] = mb.search_register(LED6_COIL)->value;
	ledsCtrl._shiftRegisterLed[7] = mb.search_register(LED7_COIL)->value;
	ledsCtrl._shiftRegisterLed[8] = mb.search_register(LED8_COIL)->value;
	ledsCtrl._shiftRegisterLed[9] = mb.search_register(LED9_COIL)->value;
	ledsCtrl._shiftRegisterLed[10] = mb.search_register(LED10_COIL)->value;
	ledsCtrl._shiftRegisterLed[11] = mb.search_register(LED11_COIL)->value;
	ledsCtrl._shiftRegisterLed[12] = mb.search_register(LED12_COIL)->value;
	ledsCtrl._shiftRegisterLed[13] = mb.search_register(LED13_COIL)->value;
	ledsCtrl._shiftRegisterLed[14] = mb.search_register(LED14_COIL)->value;
	ledsCtrl._shiftRegisterLed[15] = mb.search_register(LED15_COIL)->value;
	ledsCtrl._shiftRegisterLed[16] = mb.search_register(LED16_COIL)->value;
	ledsCtrl._shiftRegisterLed[17] = mb.search_register(LED17_COIL)->value;
	ledsCtrl._shiftRegisterLed[18] = mb.search_register(LED18_COIL)->value;
	ledsCtrl._shiftRegisterLed[19] = mb.search_register(LED19_COIL)->value;
	ledsCtrl._shiftRegisterLed[20] = mb.search_register(LED20_COIL)->value;
	ledsCtrl._shiftRegisterLed[21] = mb.search_register(LED21_COIL)->value;
	ledsCtrl._shiftRegisterLed[22] = mb.search_register(LED22_COIL)->value;
	ledsCtrl._shiftRegisterLed[23] = mb.search_register(LED23_COIL)->value;
	ledsCtrl._shiftRegisterLed[24] = mb.search_register(LED24_COIL)->value;
	ledsCtrl._shiftRegisterLed[25] = mb.search_register(LED25_COIL)->value;
	ledsCtrl._shiftRegisterLed[26] = mb.search_register(LED26_COIL)->value;
	ledsCtrl._shiftRegisterLed[27] = mb.search_register(LED27_COIL)->value;
	ledsCtrl._shiftRegisterLed[28] = mb.search_register(LED28_COIL)->value;
	ledsCtrl._shiftRegisterLed[29] = mb.search_register(LED29_COIL)->value;
	ledsCtrl._shiftRegisterLed[30] = mb.search_register(LED30_COIL)->value;
	ledsCtrl._shiftRegisterLed[31] = mb.search_register(LED31_COIL)->value;

	ledsCtrl.ledsUpdate();
}
