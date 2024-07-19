#include "digital_input/industrialli_digital_input.h"

void industrialli_digital_input::begin(){
    gpio_irq_conf[0].GPIOx     = EXTI_01_PE15_GPIO_Port;
    gpio_irq_conf[0].GPIO_Pin  = EXTI_01_PE15_Pin;
    gpio_irq_conf[0].GPIO_Mode = GPIO_MODE_IT_RISING;
    gpio_irq_conf[0].callback  = NULL;
    gpio_irq_conf[0].irqnb     = EXTI15_10_IRQn;

    gpio_irq_conf[1].GPIOx     = EXTI_02_PE14_GPIO_Port;
    gpio_irq_conf[1].GPIO_Pin  = EXTI_02_PE14_Pin;
    gpio_irq_conf[1].GPIO_Mode = GPIO_MODE_IT_RISING;
    gpio_irq_conf[1].callback  = NULL;
    gpio_irq_conf[1].irqnb     = EXTI15_10_IRQn;

    gpio_irq_conf[2].GPIOx     = EXTI_03_PE13_GPIO_Port;
    gpio_irq_conf[2].GPIO_Pin  = EXTI_03_PE13_Pin;
    gpio_irq_conf[2].GPIO_Mode = GPIO_MODE_IT_RISING;
    gpio_irq_conf[2].callback  = NULL;
    gpio_irq_conf[2].irqnb     = EXTI15_10_IRQn;

    gpio_irq_conf[3].GPIOx     = EXTI_04_PE12_GPIO_Port;
    gpio_irq_conf[3].GPIO_Pin  = EXTI_04_PE12_Pin;
    gpio_irq_conf[3].GPIO_Mode = GPIO_MODE_IT_RISING;
    gpio_irq_conf[3].callback  = NULL;
    gpio_irq_conf[3].irqnb     = EXTI15_10_IRQn;

    gpio_irq_conf[4].GPIOx     = EXTI_05_PB4_GPIO_Port;
    gpio_irq_conf[4].GPIO_Pin  = EXTI_05_PB4_Pin;
    gpio_irq_conf[4].GPIO_Mode = GPIO_MODE_IT_RISING;
    gpio_irq_conf[4].callback  = NULL;
    gpio_irq_conf[4].irqnb     = EXTI4_IRQn;

    gpio_irq_conf[5].GPIOx     = EXTI_06_PB5_GPIO_Port;
    gpio_irq_conf[5].GPIO_Pin  = EXTI_06_PB5_Pin;
    gpio_irq_conf[5].GPIO_Mode = GPIO_MODE_IT_RISING;
    gpio_irq_conf[5].callback  = NULL;
    gpio_irq_conf[5].irqnb     = EXTI9_5_IRQn;

    gpio_irq_conf[6].GPIOx     = EXTI_07_PB6_GPIO_Port;
    gpio_irq_conf[6].GPIO_Pin  = EXTI_07_PB6_Pin;
    gpio_irq_conf[6].GPIO_Mode = GPIO_MODE_IT_RISING;
    gpio_irq_conf[6].callback  = NULL;
    gpio_irq_conf[6].irqnb     = EXTI9_5_IRQn;

    gpio_irq_conf[7].GPIOx     = EXTI_08_PB7_GPIO_Port;
    gpio_irq_conf[7].GPIO_Pin  = EXTI_08_PB7_Pin;
    gpio_irq_conf[7].GPIO_Mode = GPIO_MODE_IT_RISING;
    gpio_irq_conf[7].callback  = NULL;
    gpio_irq_conf[7].irqnb     = EXTI9_5_IRQn;

    for (int i = 0; i < 8; i++){
        leds.set_led(4 + i, LOW);
    }
}

void industrialli_digital_input::attach_interrupt(DIGITAL_INPUT_PIN _pin, void (*_callback)(), uint32_t _mode){
    gpio_irq_conf[_pin].callback  = _callback;
    gpio_irq_conf[_pin].GPIO_Mode = _mode;

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin  = gpio_irq_conf[_pin].GPIO_Pin;
    GPIO_InitStruct.Mode = gpio_irq_conf[_pin].GPIO_Mode;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(gpio_irq_conf[_pin].GPIOx, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(gpio_irq_conf[_pin].irqnb, 1, 1);
    HAL_NVIC_EnableIRQ(gpio_irq_conf[_pin].irqnb);
}

void industrialli_digital_input::update_leds(){
    bool led_status[8];

    led_status[0] = HAL_GPIO_ReadPin(EXTI_01_PE15_GPIO_Port, EXTI_01_PE15_Pin);
    led_status[1] = HAL_GPIO_ReadPin(EXTI_02_PE14_GPIO_Port, EXTI_02_PE14_Pin);
    led_status[2] = HAL_GPIO_ReadPin(EXTI_03_PE13_GPIO_Port, EXTI_03_PE13_Pin);
    led_status[3] = HAL_GPIO_ReadPin(EXTI_04_PE12_GPIO_Port, EXTI_04_PE12_Pin);
    led_status[4] = HAL_GPIO_ReadPin(EXTI_05_PB4_GPIO_Port, EXTI_05_PB4_Pin);
    led_status[5] = HAL_GPIO_ReadPin(EXTI_06_PB5_GPIO_Port, EXTI_06_PB5_Pin);
    led_status[6] = HAL_GPIO_ReadPin(EXTI_07_PB6_GPIO_Port, EXTI_07_PB6_Pin);
    led_status[7] = HAL_GPIO_ReadPin(EXTI_08_PB7_GPIO_Port, EXTI_08_PB7_Pin);

    for (int i = 0; i < 8; i++){
        if(gpio_irq_conf[i].GPIO_Mode == GPIO_MODE_IT_RISING){
            if(led_status[i] == HIGH) {
                leds.set_led(4 + i, LOW);
            }else {
                leds.set_led(4 + i, HIGH);
            }
        }

        if(gpio_irq_conf[i].GPIO_Mode == GPIO_MODE_IT_FALLING){
            if(led_status[i] == HIGH) {
                leds.set_led(4 + i, HIGH);
            }else {
                leds.set_led(4 + i, LOW);
            }
        }
    }
}