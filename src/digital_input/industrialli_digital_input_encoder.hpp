#ifndef INDUSTRIALLI_DIGITAL_INPUT_ENCODER_H
#define INDUSTRIALLI_DIGITAL_INPUT_ENCODER_H

#include <Arduino.h>
#include "digital_input/industrialli_digital_input.h"

extern industrialli_digital_input digital_input;

volatile uint32_t encoder_last_update = 0;
volatile uint32_t encoder_last_count  = 0;
volatile int count                    = 0;
volatile double encoder_velocity      = 0;
volatile bool encoder_sense           = true;
volatile int encoder_a;
volatile int encoder_b;

void ENCODER_INTERRUPTION(){
    noInterrupts();

	encoder_a = digitalRead(digital_input.digital_input[I05].port);
	encoder_b = digitalRead(digital_input.digital_input[I06].port);

	if(HAL_GetTick() - encoder_last_update >= 500){
		encoder_velocity    = (150.0 * (count - encoder_last_count)) / (HAL_GetTick() - encoder_last_update);
		encoder_last_update = HAL_GetTick();
		encoder_last_count  = count;
	}

	if (encoder_a != encoder_b){
		encoder_sense = true;

	}else{
		encoder_sense = false;
	}

    count++;

    interrupts();
}

#endif