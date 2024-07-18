#include "industrialli_hub.hpp"

industrialli_hub hub;

int main(){
    hub.begin();

    digital_output.begin();
	digital_output.enable();
	digital_output.write(Q08, HIGH);
	digital_output.update();
	digital_output.update_power_leds_status();

	analog_input.begin();
	analog_input.set_input_voltage(A01, INPUT_VOLTAGE_10V);
	analog_input.set_input_voltage(A02, INPUT_VOLTAGE_20V);
	leds.update();

    while(1){
      	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10);
      	HAL_Delay(500);

		__IO double a01V = analog_input.analog_read(A01);
		__IO double a02V = analog_input.analog_read(A02);
	}
}