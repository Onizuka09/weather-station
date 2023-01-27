/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */
uint8_t hum_Byte1,hum_Byte2;
uint8_t tem_Byte1,temp_Byte2;
uint8_t presence;
uint16_t Hum,Temp,sum;
float humidity,temp ;
/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// overwrite the _wirte function

int _write (int file, char *ptr, int len){
	int i=0;
	for (i=0;i<len;i++){
		ITM_SendChar((*ptr++));
	}
	return len;
}
/* USER CODE END 0 */


void Delay_us(uint16_t time){
	__HAL_TIM_SET_COUNTER(&htim1,0);
	while (__HAL_TIM_GET_COUNTER(&htim1)<time)
	{

	}
}
void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void dht22_start(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	Set_Pin_Output(GPIOx, GPIO_Pin);
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, 0);
	Delay_us(1200);//wait for > 1ms
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin,1);
	Delay_us(30);
	Set_Pin_Input(GPIOx, GPIO_Pin);


}
uint8_t dht22_begin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	uint8_t res = 0 ;
	Delay_us(40);
	if ( !(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin))){
		// if its not 1
		Delay_us(80);
		if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)){
			res= 1 ;
		}
		else {
			res = -1;
		}
	}
	while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin));
	//printf("bgin done \n");
	// wait to go low
return res ;
}

uint8_t DHT22_Read(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	uint8_t i=0,j;
	for (j=0;j<8;j++){

		while (!(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)));// it's not low
		Delay_us(40);
		if(!( HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)))
		{
			i &= ~(1<<(7-j));
		}
		else {
			i |= (1<<(7-j));
		}
		while (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin));

	}
	//printf("read done \n");
	return i ;

}
/**
  * @brief  The application entry point.
  * @retval int
  */uint8_t k = 10;
  char buff[50]={0};

int main(void)
{
  /* USER CODE BEGIN 1 */
//unsigned char test []= "hello\n\r";
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start(&htim1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

      /* USER CODE BEGIN 3 */

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  //printf("starting the dht22\n\r");
  while (1)
  {//printf("starting the dht22\n");
    /* USER CODE END WHILE */

//printf("hii %u\n",k++);
/*
	   HAL_UART_Transmit(&huart1, test, sizeof(test),100);

	  HAL_Delay(1000); */
	 HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	  dht22_start(DHT22_GPIO_Port, DHT22_Pin);
	  presence= dht22_begin(DHT22_GPIO_Port, DHT22_Pin);

	  //printf("persence: %u",presence);


if (presence ==1){

	  hum_Byte1= DHT22_Read(DHT22_GPIO_Port, DHT22_Pin);
	 // printf("hum_Byte1: %u\n",hum_Byte1);
	  hum_Byte2=DHT22_Read(DHT22_GPIO_Port, DHT22_Pin);
	 // printf("hum_Byte2: %u\n",hum_Byte2);
	  tem_Byte1=DHT22_Read(DHT22_GPIO_Port, DHT22_Pin);
	 // printf("temp_Byte1: %u\n",tem_Byte1);
	  temp_Byte2=DHT22_Read(DHT22_GPIO_Port, DHT22_Pin);
	 // printf("temp_Byte2: %u\n",temp_Byte2);
	  sum=DHT22_Read(DHT22_GPIO_Port, DHT22_Pin);
	 // printf("sum: %u\n",sum);
	//  if (sum == (hum_Byte1+hum_Byte2+tem_Byte1+temp_Byte2)){
		  Temp= ((tem_Byte1<<8)|temp_Byte2);
		  Hum = ((hum_Byte1<<8)|hum_Byte2);
	 // }
	  temp = (float) (Temp/10.0);
	  humidity = (float) (Hum/10.0) ;
	  //sprintf (buff,"[\"data\",{\"data\":\"%.2f\"}]\n",temp);//,humidity);
	  sprintf(buff,"{\"temp\":%.2f,\"hum\":%.2f}\n",temp,humidity);
	  //sprintf(buff,"%.2f\n",temp);
	  HAL_UART_Transmit(&huart1,(uint8_t*) buff, sizeof(buff),100);
	  //printf("TEMP: %.2f \n Hum: %.2f \n",temp,humidity);
	  //printf(buff);
	  sprintf (buff," ");//,humidity);


}
else {
	//printf("dht22 not detected");
}
	 //printf("hii %u\n",k++);
	  HAL_Delay(2000);

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 84-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|DHT22_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin DHT22_Pin */
  GPIO_InitStruct.Pin = LD2_Pin|DHT22_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
