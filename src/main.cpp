/* A fazer:- Referenciar bibliotecas utilizadas como base (a finalizar)
 *         - Fazer tabela de registradores para hub (a finalizar)
 *         - Implementar alternativa analogRead
 *         - DMA
 *         - PWM (fazendo)
 */
#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <task.h>

#include "industrialli_leds.h"
#include "industrialli_digital_output.h"
#include "industrialli_hub.h"

SPIClass spi_leds;
SPIClass spi_iso;

industrialli_leds leds;
industrialli_digital_output iso;
industrialli_hub hub;

void DWT_Init();
void DWT_Delay(uint32_t us);

typedef struct{
	int _pin;
	int _value;
	double _frequency;
	int _resolution;
} analog_write_params;

void analogWrite(void *parameters);

void setup(){
	DWT_Init();

	hub.begin();

	iso.write(Q02, HIGH);
	iso.update();

	static const analog_write_params p1 = {Q01, 127, 500, 0xFF};
	static const analog_write_params p3 = {Q03, 204, 1000, 0xFF};

	xTaskCreate(analogWrite, "analogWrite", 256, (analog_write_params *)&p1, 1 , NULL);
	xTaskCreate(analogWrite, "analogWrite", 256, (analog_write_params *)&p3, 1 , NULL);

	vTaskStartScheduler();
}

void loop(){}

void DWT_Init(void) {
    if (!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk)) {
        CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
        DWT->CYCCNT = 0;
        DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    }
}

void DWT_Delay(uint32_t us){
    uint32_t startTick  = DWT->CYCCNT,
             delayTicks = us * (SystemCoreClock/1000000);

    while (DWT->CYCCNT - startTick < delayTicks);
}

void analogWrite(void *parameters){
	bool pwm_status = LOW;

	analog_write_params p = *(analog_write_params *)parameters;

	int period       = (1/p._frequency) * 1000000;
	int duty_high    = (period * p._value) / p._resolution;
	int duty_low     = period - duty_high;

	for(;;){

		if(pwm_status){
			iso.write(p._pin, LOW);
			iso.update();
			pwm_status = LOW;
			DWT_Delay(duty_low);
			
		} else {
			iso.write(p._pin, HIGH);
			iso.update();
			pwm_status = HIGH;
			DWT_Delay(duty_high);
		}
	}
}