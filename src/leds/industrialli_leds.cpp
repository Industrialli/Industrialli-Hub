#include "leds/industrialli_leds.h"

void industrialli_leds::begin(){
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin  = SPI1_NSS_PA4_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(SPI1_NSS_PA4_GPIO_Port, &GPIO_InitStruct);

    start();
}

void industrialli_leds::start(){
    for (int i = 0; i < 32; i++){
        set_all(LOW);
        set_led(i, HIGH);
        update();
        HAL_Delay(25);
    }
    
    for (int i = 31; i >= 0; i--){
        set_all(LOW);
        set_led(i, HIGH);
        update();
        HAL_Delay(25);
    }

    set_all(LOW);
    update();
}

void industrialli_leds::set_led(uint8_t _led, bool _value){
    if(_value){
        leds |= 0x01 << _led;
    }else {
        leds &= ~(0x01 << _led);
    }
}

void industrialli_leds::set_all(bool _value){
    leds = _value;
}

void industrialli_leds::update(){
    HAL_GPIO_WritePin(SPI1_NSS_PA4_GPIO_Port, SPI1_NSS_PA4_Pin, GPIO_PIN_RESET);

    uint8_t a = (leds >> 24);
    uint8_t b = (leds >> 16);
    uint8_t c = (leds >> 8);
    uint8_t d = (leds & 0xFF);

    HAL_SPI_Transmit(&hspi1, &a, 1, 1);
    HAL_SPI_Transmit(&hspi1, &b, 1, 1);
    HAL_SPI_Transmit(&hspi1, &c, 1, 1);
    HAL_SPI_Transmit(&hspi1, &d, 1, 1);
    
    HAL_GPIO_WritePin(SPI1_NSS_PA4_GPIO_Port, SPI1_NSS_PA4_Pin, GPIO_PIN_SET);
}