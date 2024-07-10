#include "industrialli_hub.hpp"

#define ADC_04_PA0_Pin GPIO_PIN_0
#define ADC_04_PA0_GPIO_Port GPIOA
#define ADC_03_PC4_Pin GPIO_PIN_4
#define ADC_03_PC4_GPIO_Port GPIOC
#define ADC_02_PC5_Pin GPIO_PIN_5
#define ADC_02_PC5_GPIO_Port GPIOC
#define ADC_01_PB1_Pin GPIO_PIN_1
#define ADC_01_PB1_GPIO_Port GPIOB
#define ANLG_SEL_01_PA9_Pin GPIO_PIN_9
#define ANLG_SEL_01_PA9_GPIO_Port GPIOA
#define ANLG_SEL_02_PA10_Pin GPIO_PIN_10
#define ANLG_SEL_02_PA10_GPIO_Port GPIOA
#define ANLG_SEL_03_PD0_Pin GPIO_PIN_0
#define ANLG_SEL_03_PD0_GPIO_Port GPIOD
#define ANLG_SEL_04_PD1_Pin GPIO_PIN_1
#define ANLG_SEL_04_PD1_GPIO_Port GPIOD

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);

industrialli_hub hub;
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

void DWT_Init();
void DWT_Delay(uint32_t us);

uint32_t adctest;
bool ligado;

void setup(){
	// HAL_Init();
	// SystemClock_Config();

	// MX_GPIO_Init();
	// MX_DMA_Init();
	// MX_ADC1_Init();

	// HAL_ADC_Start_DMA(&hadc1, &adctest, 1);
	

	hub.begin();

	digital_output.begin();
	digital_output.enable();
	digital_output.write(Q03, HIGH);//on/off
	digital_output.write(Q01, HIGH);//direção
	ligado = true;
	
	
    digInHub.begin();
	digInHub.begin_encoder_counting(0, PNP);
    digInHub.begin_digital_input_counting(I03, NPN, UP);
	digInHub.begin_digital_input_counting(I04, PNP, UP);

    // anlgInHub.begin();  
    // anlgInHub.setAnalogResolution(BITS_12);
    // anlgInHub.setReadMode(A01, READ_020);

	// lora.begin();
	// lora.setnetworkId((uint16_t)1);
	// lora.config_bps(BW500, SF_LoRa_7, CR4_5);
	// lora.config_class(LoRa_CLASS_C, LoRa_WINDOW_15s);
	// lora.setpassword(22);
}

void loop() {
	if(ligado){
		digital_output.write(Q02, LOW);
		ligado = false;

	}else {
		digital_output.write(Q02, HIGH);
		ligado = true;
	}
	

	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10);
	// Serial.println(adctest);
	// uint16_t id_request;
    // uint8_t cmd_request;
	// uint8_t payload_request[MAX_PAYLOAD_SIZE];
	// uint8_t size_request;

	digInHub.update_leds();

	// if(lora.ReceivePacketCommand(&id_request, &cmd_request, payload_request, &size_request, 10)){
	// 	if(cmd_request == 0x05){
    //         uint8_t payload_response[2] = {digInHub.get_count(I03), (uint8_t)(anlgInHub.get020mA(A01) * 10)};

			Serial.println("#########################################");
			Serial.println(digInHub.get_pulses_encoder(0));
			Serial.println(digInHub.get_encoder_sense(0));
			Serial.println(digInHub.get_encoder_velocity(0));
			Serial.println("#########################################");
			

    //         lora.PrepareFrameCommand(0, 0x05, payload_response, 2);
    //         lora.SendPacket();
    //     }
	// }
    
    
    leds.update();
	digital_output.update();
	DWT_Delay(10000);
}

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

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc){
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(hadc->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    PeriphClkInitStruct.PLL2.PLL2M = 2;
    PeriphClkInitStruct.PLL2.PLL2N = 15;
    PeriphClkInitStruct.PLL2.PLL2P = 2;
    PeriphClkInitStruct.PLL2.PLL2Q = 2;
    PeriphClkInitStruct.PLL2.PLL2R = 2;
    PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_3;
    PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
    PeriphClkInitStruct.PLL2.PLL2FRACN = 2950;
    PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    __HAL_RCC_ADC12_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PA0     ------> ADC1_INP16
    PC4     ------> ADC1_INP4
    PC5     ------> ADC1_INP8
    PB1     ------> ADC1_INP5
    */
    GPIO_InitStruct.Pin = ADC_04_PA0_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ADC_04_PA0_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = ADC_03_PC4_Pin|ADC_02_PC5_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = ADC_01_PB1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ADC_01_PB1_GPIO_Port, &GPIO_InitStruct);

    /* ADC1 DMA Init */
    /* ADC1 Init */
    hdma_adc1.Instance = DMA1_Stream0;
    hdma_adc1.Init.Request = DMA_REQUEST_ADC1;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;
    hdma_adc1.Init.Priority = DMA_PRIORITY_LOW;
    hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(hadc,DMA_Handle,hdma_adc1);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }

}

static void MX_GPIO_Init(void){
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOD, ANLG_SEL_03_PD0_Pin|ANLG_SEL_04_PD1_Pin, GPIO_PIN_RESET);

  HAL_GPIO_WritePin(GPIOA, ANLG_SEL_01_PA9_Pin|ANLG_SEL_02_PA10_Pin, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = ANLG_SEL_03_PD0_Pin|ANLG_SEL_04_PD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = ANLG_SEL_01_PA9_Pin|ANLG_SEL_02_PA10_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

static void MX_DMA_Init(void){
  __HAL_RCC_DMA1_CLK_ENABLE();

  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
}

static void MX_ADC1_Init(void){

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_16B;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.NbrOfConversion = 4;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DMA_CIRCULAR;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
  hadc1.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK){
    Error_Handler();
  }

  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK){
    Error_Handler();
  }

  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  sConfig.OffsetSignedSaturation = DISABLE;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK){
    Error_Handler();
  }

  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK){
    Error_Handler();
  }

  sConfig.Rank = ADC_REGULAR_RANK_3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK){
    Error_Handler();
  }

  sConfig.Rank = ADC_REGULAR_RANK_4;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK){
    Error_Handler();
  }

}