// #include <Arduino.h>
// #include <HardwareSerial.h>

// #include "industrialli_hubInit.h"
// #include "industrialli_ledsHub.h"
// #include "modbus/industrialli_modbus_rtu_client.h"

// #define RS485_USART2_RX PD6
// #define RS485_USART2_TX PD5
// #define RS485_USART2_RE_DE PD4

// industrialli_hubInit startHub;
// industrialli_ledsHubCtrl ledsCtrl;
// HardwareSerial rs485_usart2_serial(RS485_USART2_RX, RS485_USART2_TX);
// Industrialli_Modbus_RTU_Client modbus;

// void setup(){
// 	startHub.begin();
// 	rs485_usart2_serial.begin(9600);

// 	modbus.begin(&rs485_usart2_serial);

// 	pinMode(RS485_USART2_RE_DE, OUTPUT);
// 	digitalWrite(RS485_USART2_RE_DE, HIGH);

// 	ledsCtrl.begin();
// }

// void loop() {
// 	for (int i = 0; i < 32; i++){
// 		ledsCtrl._shiftRegisterLed[i] = rand() % 2;
// 	}

// 	modbus.write_multiple_coils(10, 0, ledsCtrl._shiftRegisterLed, 0);
// 	SerialUSB.println(modbus.get_last_exception_response());
// 	ledsCtrl.ledsUpdate();

// 	delay(500);
// }