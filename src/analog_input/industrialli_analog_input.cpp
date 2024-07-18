#include "analog_input/industrialli_analog_input.h"

uint16_t industrialli_analog_input::get_vrefint_cal(){
    return *((uint16_t *)0x1FF1E860);
}

uint16_t industrialli_analog_input::get_vrefint_data(){
    __IO uint16_t vrefint_data = 0;
    
    if(HAL_ADCEx_Calibration_Start(&hadc3, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED) != HAL_OK){
		Error_Handler();
	}

    if (HAL_ADC_Start(&hadc3) != HAL_OK){
		Error_Handler();
	}

    if (HAL_ADC_PollForConversion(&hadc3, 10) != HAL_OK){
        Error_Handler();
    }

    if ((HAL_ADC_GetState(&hadc3) & HAL_ADC_STATE_REG_EOC) == HAL_ADC_STATE_REG_EOC) {
        vrefint_data = HAL_ADC_GetValue(&hadc3);
    }

    HAL_ADC_Stop(&hadc3);

    return vrefint_data;
}

void industrialli_analog_input::begin(){
    resolution      = 12;
    bits_resolution = 4095;

    pin_input_voltage[A01] = INPUT_VOLTAGE_10V;
    pin_input_voltage[A02] = INPUT_VOLTAGE_10V;
    pin_input_voltage[A03] = INPUT_VOLTAGE_10V;
    pin_input_voltage[A04] = INPUT_VOLTAGE_10V;
}

void industrialli_analog_input::set_input_voltage(ANALOG_PIN _pin, INPUT_VOLTAGE _input_voltage){
    switch(_pin){
        case A01:
            HAL_GPIO_WritePin(ANLG_SEL_01_PA9_GPIO_Port, ANLG_SEL_01_PA9_Pin, (GPIO_PinState)_input_voltage);
            break;
        case A02:
            HAL_GPIO_WritePin(ANLG_SEL_02_PA10_GPIO_Port, ANLG_SEL_02_PA10_Pin, (GPIO_PinState)_input_voltage);
            break;
        case A03:
            HAL_GPIO_WritePin(ANLG_SEL_03_PD0_GPIO_Port, ANLG_SEL_03_PD0_Pin, (GPIO_PinState)_input_voltage);
            break;
        case A04:
            HAL_GPIO_WritePin(ANLG_SEL_04_PD1_GPIO_Port, ANLG_SEL_04_PD1_Pin, (GPIO_PinState)_input_voltage);
            break;
    }

    pin_input_voltage[_pin] = _input_voltage;
    leds.set_led(_pin, HIGH);
}

double industrialli_analog_input::analog_read(ANALOG_PIN _pin){
    __IO double vdda = (3.3 * get_vrefint_cal()) / get_vrefint_data();
    __IO double vchannel_internal = (vdda / bits_resolution) * analog_input_values[_pin];
    __IO double vchannel_external;

    if(pin_input_voltage[_pin] == INPUT_VOLTAGE_10V){
        vchannel_external = (10 * vchannel_internal) / 3.3;
    }

    if(pin_input_voltage[_pin] == INPUT_VOLTAGE_20V){
        vchannel_external = (20 * vchannel_internal) / 3.3;
    }

    return vchannel_external;
}

// bool industrialli_analog_input::alarm020mA(float alarm020Val, float threshold){
//     _alarm020Val = alarm020Val;
   
//     if (_alarm020Val < threshold){
//         _alarm = true;

//     }else{
//         _alarm = false;
//     }

//     return _alarm;
// }

