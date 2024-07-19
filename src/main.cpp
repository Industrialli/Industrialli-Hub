#include "industrialli_hub.hpp"

industrialli_hub hub;

int counts = 0;
void count_interruptions(){
	__disable_irq();
	counts++;
	__enable_irq();
}

int main(){
    hub.begin();

	digital_input.begin();
	digital_input.attach_interrupt(I03, count_interruptions, GPIO_MODE_IT_FALLING);
	digital_input.attach_interrupt(I04, count_interruptions, GPIO_MODE_IT_RISING);
	
    digital_output.begin();
	digital_output.enable();
	digital_output.write(Q08, HIGH);
	digital_output.update();
	
	analog_input.begin();
	analog_input.set_input_voltage(A01, INPUT_VOLTAGE_10V);
	analog_input.set_input_voltage(A02, INPUT_VOLTAGE_20V);
	
    while(1){
      	// HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10);
      	HAL_Delay(1);

		// __IO double a01V = analog_input.analog_read(A01);
		// __IO double a02V = analog_input.analog_read(A02);

		digital_input.update_leds();
		digital_output.update_power_leds_status();
		leds.update();
	}
}