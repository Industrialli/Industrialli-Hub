/* A fazer:- Referenciar bibliotecas utilizadas como base (a finalizar)
 *         - Fazer tabela de registradores para hub (a finalizar)
 *         - Implementar alternativa analogRead
 *         - DMA
 *         - PWM (fazendo)
 */
#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <task.h>

#include "industrialli_hubInit.h"

industrialli_hubInit hub;

void TIM1_Init();
void pwm_update(void *pvParameters);

void DWT_Init(void) {
    if (!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk)) {
        CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
        DWT->CYCCNT = 0;
        DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    }
}

void DelayUs(uint32_t us) {
    uint32_t start = DWT->CYCCNT;
    uint32_t delayTicks = us * (HAL_RCC_GetHCLKFreq() / 1000000);

    while ((DWT->CYCCNT - start) < delayTicks) {
        // Nada a fazer, apenas espera
    }
}

void setup(){
	HAL_Init();
	SystemClock_Config();
	DWT_Init();

	hub.begin();

	bool *status = (bool *)malloc(sizeof(bool));
	*status = HIGH;

	xTaskCreate(pwm_update, "pwm_update", 256, status, 1 , NULL);

	vTaskStartScheduler();
}

void loop(){}

void pwm_update(void *pvParameters){
	for(;;){
		bool *status = (bool*)pvParameters;

		if(*status){
			digitalWrite(DEBUG_LED, LOW);
			*status = LOW;
			DelayUs(1400);
		} else {
			digitalWrite(DEBUG_LED, HIGH);
			*status = HIGH;
			DelayUs(600);
		}
	}
}