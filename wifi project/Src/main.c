/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define OLED_I2C_ADDR 0x78
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define max_ids 8
#define max_char 32
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
char outgoing[80];
int i=0;
int j;
char buffer[20];
int val;
int val2;
char names[max_ids][max_char];
int count = 0;
int a;
int b;
int c;
int z=0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

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
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  OLED_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
		HAL_UART_Receive(&huart2, outgoing, sizeof(outgoing), 1000);

		int val = strcmp(buffer, outgoing);

		if (val != 0) {
			OLED_SetCursor(i, 10);
			OLED_PrintString(outgoing);
			i++;

			if (count < max_ids) {
				strncpy(names[count], outgoing, max_char - 1); // ✅ copy outgoing, not buffer
				names[count][max_char - 1] = '\0';  // Always null-terminate
				count++;
			}

			strcpy(buffer, outgoing);  // ✅ update buffer after using outgoing
		}

		memset(outgoing, 0, sizeof(outgoing)); // ✅ clear outgoing for next UART receive

		if (i > 7)
			break;
	}


	while (1)
	{
		OLED_SetCursor(0, 2);
		OLED_PrintChar('>');

		a = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_12);
		if (a == 1) {
			HAL_Delay(500);
			z = z + 1;
		}
		b = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_13);
		c = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_14);
		if (c == 1) {
			HAL_Delay(500);
			z = z - 1;
		}

		if (z == 1)
		{
			OLED_RangeClear(7, 2);
			OLED_RangeClear(1, 2);
			OLED_RangeClear(2, 2);
			OLED_RangeClear(3, 2);
			OLED_RangeClear(4, 2);
			OLED_RangeClear(5, 2);
			OLED_RangeClear(6, 2);
			OLED_SetCursor(0, 2);
			OLED_PrintChar('>');
			if (b == 1)
			{
				OLED_Clear();
				OLED_SetCursor(0, 1);
				OLED_PrintString(names[0]);
				HAL_UART_Transmit(&huart2, names[0], strlen(names[0]), 1000);
				break;
			}
		}
		if (z == 2)
		{
			OLED_RangeClear(0, 2);
			OLED_RangeClear(3, 2);
			OLED_RangeClear(2, 2);
			OLED_RangeClear(4, 2);
			OLED_RangeClear(5, 2);
			OLED_RangeClear(6, 2);
			OLED_RangeClear(7, 2);
			OLED_SetCursor(1, 2);
			OLED_PrintChar('>');
			if (b == 1)
			{
				OLED_Clear();
				OLED_SetCursor(0, 1);
				OLED_PrintString(names[1]);
				HAL_UART_Transmit(&huart2, names[1], strlen(names[1]), 1000);
				break;
			}
		}
		if (z == 3)
		{
			OLED_RangeClear(0, 2);
			OLED_RangeClear(1, 2);
			OLED_RangeClear(3, 2);
			OLED_RangeClear(4, 2);
			OLED_RangeClear(5, 2);
			OLED_RangeClear(6, 2);
			OLED_RangeClear(7, 2);
			OLED_SetCursor(2, 2);
			OLED_PrintChar('>');
			if (b == 1)
			{
				OLED_Clear();
				OLED_SetCursor(0, 1);
				OLED_PrintString(names[2]);
				HAL_UART_Transmit(&huart2, names[2], strlen(names[2]), 1000);
				break;
			}
		}
		if (z == 4)
		{
			OLED_RangeClear(0, 2);
			OLED_RangeClear(1, 2);
			OLED_RangeClear(2, 2);
			OLED_RangeClear(4, 2);
			OLED_RangeClear(5, 2);
			OLED_RangeClear(6, 2);
			OLED_RangeClear(7, 2);
			OLED_SetCursor(3, 2);
			OLED_PrintChar('>');
			if (b == 1)
			{
				OLED_Clear();
				OLED_SetCursor(0, 1);
				OLED_PrintString(names[3]);
				HAL_UART_Transmit(&huart2, names[3], sizeof(names[3]), 1000);
				break;
			}
		}
		if (z == 5)
		{
			OLED_RangeClear(0, 2);
			OLED_RangeClear(1, 2);
			OLED_RangeClear(2, 2);
			OLED_RangeClear(3, 2);
			OLED_RangeClear(5, 2);
			OLED_RangeClear(6, 2);
			OLED_RangeClear(7, 2);
			OLED_SetCursor(4, 2);
			OLED_PrintChar('>');
			if (b == 1)
			{
				OLED_Clear();
				OLED_SetCursor(0, 1);
				OLED_PrintString(names[4]);
				HAL_UART_Transmit(&huart2, names[4], sizeof(names[4]), 1000);
				break;
			}
		}

		if (z == 6)
		{
			OLED_RangeClear(0, 2);
			OLED_RangeClear(1, 2);
			OLED_RangeClear(2, 2);
			OLED_RangeClear(3, 2);
			OLED_RangeClear(4, 2);
			OLED_RangeClear(6, 2);
			OLED_RangeClear(7, 2);
			OLED_SetCursor(5, 2);
			OLED_PrintChar('>');
			if (b == 1)
			{
				OLED_Clear();
				OLED_SetCursor(0, 1);
				OLED_PrintString(names[5]);
				HAL_UART_Transmit(&huart2, names[5], sizeof(names[5]), 1000);
				break;
			}
		}
		if (z == 7)
		{
			OLED_RangeClear(0, 2);
			OLED_RangeClear(1, 2);
			OLED_RangeClear(2, 2);
			OLED_RangeClear(3, 2);
			OLED_RangeClear(4, 2);
			OLED_RangeClear(5, 2);
			OLED_RangeClear(7, 2);
			OLED_SetCursor(6, 2);
			OLED_PrintChar('>');
			if (b == 1)
			{
				OLED_Clear();
				OLED_SetCursor(0, 1);
				OLED_PrintString(names[6]);
				HAL_UART_Transmit(&huart2, names[6], sizeof(names[6]), 1000);
				break;
			}
		}
		if (z == 8)
		{
			OLED_RangeClear(0, 2);
			OLED_RangeClear(1, 2);
			OLED_RangeClear(2, 2);
			OLED_RangeClear(3, 2);
			OLED_RangeClear(4, 2);
			OLED_RangeClear(6, 2);
			OLED_RangeClear(5, 2);
			OLED_SetCursor(7, 2);
			OLED_PrintChar('>');
			if (b == 1)
			{
				OLED_Clear();
				OLED_SetCursor(0, 1);
				OLED_PrintString(names[7]);
				HAL_UART_Transmit(&huart2, names[7], sizeof(names[7]), 1000);
				break;
			}
		}

		if (z == 9 || z > 9)
		{
			z = 8;
		}

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
  while(1)
  {
	  HAL_UART_Receive(&huart2, outgoing,sizeof(outgoing),1000);
	  buffer[20] = "Connected successfully!";
	  val2 = strcmp(buffer,outgoing);
	  if(val2 == 0)
	  {
		  HAL_UART_Receive(&huart2, outgoing,sizeof(outgoing),1000);
		  HAL_Delay(1000);
		  HAL_UART_Transmit(&huart1, outgoing,sizeof(outgoing),1000);
	  }
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

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
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, RS_Pin|D4_Pin|D5_Pin|D6_Pin
                          |D7_Pin|E_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RS_Pin D4_Pin D5_Pin D6_Pin
                           D7_Pin E_Pin */
  GPIO_InitStruct.Pin = RS_Pin|D4_Pin|D5_Pin|D6_Pin
                          |D7_Pin|E_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD13 PD14 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void OLED_SendCommand(uint8_t cmd) {
    uint8_t data[2] = {0x00, cmd};
    HAL_I2C_Master_Transmit(&hi2c1, OLED_I2C_ADDR, data, 2, HAL_MAX_DELAY);
}

void OLED_SendData(uint8_t data) {
    uint8_t buf[2] = {0x40, data};
    HAL_I2C_Master_Transmit(&hi2c1, OLED_I2C_ADDR, buf, 2, HAL_MAX_DELAY);
}
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
