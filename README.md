# INDUSTRIALLI HUB

### Modbus
O mestre gera uma configuração aleatória dos leds na Hub e manda uma requisição write_multiple_registers com as configurações dos leds para o escravo. Que por sua vez irá  atualizar as configurações dos seus leds conforme a requisição do mestre.

#### Servidor
```cpp
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
	rs485_usart2_serial.begin(9600, SERIAL_8N1);

	modbus.begin(&rs485_usart2_serial);
	modbus.set_slave_id(10);

	for (size_t i = 0; i < 32; i++){
		modbus.create_register(i + 100, LOW);
	}

	ledsCtrl.begin();
}

void loop() {
	modbus.task();

	for (int i = 0; i < 32; i++){
		ledsCtrl._shiftRegisterLed[i] = modbus.search_register(i+100)->value;
	}

	ledsCtrl.ledsUpdate();
}
```

#### Cliente

```cpp
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
HardwareSerial rs485_usart2_serial(RS485_USART2_RX, RS485_USART2_TX);
IndustrialliModbusRTU modbus;

void setup(){
	startHub.begin();
	rs485_usart2_serial.begin(9600);

	modbus.begin(&rs485_usart2_serial);

	pinMode(RS485_USART2_RE_DE, OUTPUT);
	digitalWrite(RS485_USART2_RE_DE, HIGH);

	for (size_t i = 0; i < 32; i++){
		modbus.create_register(i + 100, LOW);
	}

	ledsCtrl.begin();
}

void loop() {
	srand(time(NULL));

	for (int i = 0; i < 32; i++){
		ledsCtrl._shiftRegisterLed[i] = rand() % 2;
	}

	uint8_t *pdu = (uint8_t*)malloc(70);

	pdu[0] = FC_WRITE_MULTIPLE_REGISTERS;
	pdu[1] = 0;
	pdu[2] = 100;
	pdu[3] = 0;
	pdu[4] = 32;
	pdu[5] = 0;

	for (int i = 0; i < 64; i += 2){
		pdu[6 + i]     = 0;
		pdu[6 + i + 1] = ledsCtrl._shiftRegisterLed[i / 2];
	}

	modbus.send_frame(10, pdu, 70);
	ledsCtrl.ledsUpdate();
	delay(100);
}
```
