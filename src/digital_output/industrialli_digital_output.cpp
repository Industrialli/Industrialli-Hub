#include "digital_output/industrialli_digital_output.h"

void industrialli_digital_output::begin(){
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = SPI4_NSS_PE4_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(SPI4_NSS_PE4_GPIO_Port, &GPIO_InitStruct);

    digital_outputs = 0;
}

void industrialli_digital_output::enable(){
    HAL_GPIO_WritePin(ISO_DIS_PE3_GPIO_Port, ISO_DIS_PE3_Pin, GPIO_PIN_SET);
}

void industrialli_digital_output::disable(){
    HAL_GPIO_WritePin(ISO_DIS_PE3_GPIO_Port, ISO_DIS_PE3_Pin, GPIO_PIN_RESET);
}

void industrialli_digital_output::update(){
    HAL_GPIO_WritePin(SPI4_NSS_PE4_GPIO_Port, SPI4_NSS_PE4_Pin, GPIO_PIN_RESET);

    uint8_t a = digital_outputs >> 8;
    uint8_t b = digital_outputs & 0xFF;

    HAL_SPI_Transmit(&hspi4, &a, 1, 1);
    HAL_SPI_Transmit(&hspi4, &b, 1, 1);

    HAL_GPIO_WritePin(SPI4_NSS_PE4_GPIO_Port, SPI4_NSS_PE4_Pin, GPIO_PIN_SET);

    leds.update();
}

void industrialli_digital_output::write(DIGITAL_OUTPUT_PIN _pin, bool _value){
    if(_value){
        digital_outputs |= 0x01 << (_pin - 1);
    }else {
        digital_outputs &= ~(0x01 << (_pin - 1));
    }

    set_digital_output_led(_pin - 1, _value);
}

void industrialli_digital_output::set_digital_output_led(uint8_t _led, bool _value){
    if (_led < 8){
        leds.set_led(_led + 12, _value);
    }else {
        leds.set_led(_led + 16, _value);
    }
}

void industrialli_digital_output::update_power_leds_status(){
    if (output_1_to_8_status()){
        leds.set_led(22, HIGH);
    }else {
        leds.set_led(22, LOW);
    }

    if (output_9_to_16_status()){
        leds.set_led(23, HIGH);
    }else{
        leds.set_led(23, LOW);
    }
}

bool industrialli_digital_output::output_1_to_8_status(){
    return HAL_GPIO_ReadPin(IC1_ISO_DIAG_PC0_GPIO_Port, IC1_ISO_DIAG_PC0_Pin);
}

bool industrialli_digital_output::output_9_to_16_status(){
    return HAL_GPIO_ReadPin(IC2_ISO_DIAG_PC1_GPIO_Port, IC2_ISO_DIAG_PC1_Pin);
}
