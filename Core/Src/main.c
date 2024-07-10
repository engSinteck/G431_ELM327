/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "fdcan.h"
#include "rtc.h"
#include "usart.h"
#include "usb.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "ctype.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
void NewCmdAT(void);
void resp_ok(void);
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
//static const char ErrMessage [] = "?";
//static const char OkMessage  [] = "OK";
//static const char Version    [] = "1.12";
//static const char Interface  [] = "ELM329 v2.1";
//static const char Copyright  [] = "Copyright (c) 2009-2024 ObdDiag.Net";
//static const char Copyright2 [] = "This is free software; see the source for copying conditions. There is NO";
//static const char Copyright3 [] = "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.";

extern volatile uint16_t pointer;
extern volatile uint8_t rx_uart[];
extern volatile uint8_t flag_rx;
uint32_t timer_led = 0;
char string_tx[1024] = {0};
uint8_t rx_cmd[100] = {0};

volatile uint16_t pointer_rx = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
  MX_FDCAN1_Init();
  MX_RTC_Init();
  MX_USART1_UART_Init();
  MX_USB_PCD_Init();
  /* USER CODE BEGIN 2 */
  pointer = 0;
  HAL_UART_Receive_IT(&huart1, (uint8_t *)rx_uart, 1);
  string_tx[0] = '>';
  string_tx[1] = '\r';
  string_tx[2] = '\0';
  HAL_UART_Transmit(&huart1, (uint8_t *)string_tx, strlen(string_tx), 1000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	if(HAL_GetTick() - timer_led > 500) {
	    timer_led = HAL_GetTick();
	    HAL_GPIO_TogglePin(LED_INT_GPIO_Port, LED_INT_Pin);
	}
	if(flag_rx == 1) {
		flag_rx = 0;
		NewCmdAT();
		//rx_cmd
		if ( (strncmp((char *)&rx_cmd, "Z", 1) == 0) || (strncmp((char *)&rx_cmd, "z", 1) == 0) ) {
			string_tx[0] = 'E';
			string_tx[1] = 'L';
			string_tx[2] = 'M';
			string_tx[3] = '3';
			string_tx[4] = '2';
			string_tx[5] = '7';
			string_tx[6] = ' ';
			string_tx[7] = 'v';
			string_tx[8] = '2';
			string_tx[9] = '.';
			string_tx[10] = '3';

			string_tx[11] = '\r';
			string_tx[12] = '\n';
			string_tx[13] = 0;
			HAL_UART_Transmit(&huart1, (uint8_t *)string_tx, strlen(string_tx), 1000);

			string_tx[0] = '>';
			string_tx[1] = '\r';
			string_tx[2] = '\0';
			HAL_UART_Transmit(&huart1, (uint8_t *)string_tx, strlen(string_tx), 1000);
		}
		else if(strncmp((char *)&rx_cmd, "I", 1) == 0) {
			string_tx[0] = 'E';
			string_tx[1] = 'L';
			string_tx[2] = 'M';
			string_tx[3] = '3';
			string_tx[4] = '2';
			string_tx[5] = '7';
			string_tx[6] = ' ';
			string_tx[7] = 'v';
			string_tx[8] = '2';
			string_tx[9] = '.';
			string_tx[10] = '3';

			string_tx[11] = '\r';
			string_tx[12] = '\n';
			string_tx[13] = 0;
			HAL_UART_Transmit(&huart1, (uint8_t *)string_tx, strlen(string_tx), 1000);

			string_tx[0] = '>';
			string_tx[1] = '\r';
			string_tx[2] = '\0';
			HAL_UART_Transmit(&huart1, (uint8_t *)string_tx, strlen(string_tx), 1000);
		}
		else if(strncmp((char *)&rx_cmd, "@1", 2) == 0) {
			string_tx[0] = '1';
			string_tx[1] = '.';
			string_tx[2] = '1';
			string_tx[3] = '3';

			string_tx[4] = '\r';
			string_tx[5] = '\n';
			string_tx[6] = 0;
			HAL_UART_Transmit(&huart1, (uint8_t *)string_tx, strlen(string_tx), 1000);

			string_tx[0] = '>';
			string_tx[1] = '\r';
			string_tx[2] = '\0';
			HAL_UART_Transmit(&huart1, (uint8_t *)string_tx, strlen(string_tx), 1000);
		}
		else if(strncmp((char *)&rx_cmd, "@2", 2) == 0) {
			//"Copyright (c) 2009-2016 ObdDiag.Net";
			// Copyright
			string_tx[0] = 'C';
			string_tx[1] = 'o';
			string_tx[2] = 'p';
			string_tx[3] = 'y';
			string_tx[4] = 'r';
			string_tx[5] = 'i';
			string_tx[6] = 'g';
			string_tx[7] = 'h';
			string_tx[8] = 't';
			string_tx[9] = ' ';
			string_tx[10] = '(';
			string_tx[11] = 'c';
			string_tx[12] = ')';
			string_tx[13] = ' ';
			string_tx[14] = '2';
			string_tx[15] = '0';
			string_tx[16] = '0';
			string_tx[17] = '9';
			string_tx[18] = '-';
			string_tx[19] = '2';
			string_tx[20] = '0';
			string_tx[21] = '1';
			string_tx[22] = '6';
			string_tx[23] = ' ';
			string_tx[24] = 'O';
			string_tx[25] = 'b';
			string_tx[26] = 'd';
			string_tx[27] = 'D';
			string_tx[28] = 'i';
			string_tx[29] = 'a';
			string_tx[30] = 'g';
			string_tx[31] = '.';
			string_tx[32] = 'N';
			string_tx[33] = 'e';
			string_tx[34] = 't';
			string_tx[35] = '\r';
			string_tx[36] = '\n';
			string_tx[37] = 0;
			HAL_UART_Transmit(&huart1, (uint8_t *)string_tx, strlen(string_tx), 1000);
			string_tx[0] = '>';
			string_tx[1] = '\r';
			string_tx[2] = '\0';
			HAL_UART_Transmit(&huart1, (uint8_t *)string_tx, strlen(string_tx), 1000);
		}
		else if( (strncmp((char *)&rx_cmd, "E0", 2) == 0) || (strncmp((char *)&rx_cmd, "e0", 2) == 0) ) {
			resp_ok();
		}
		else if( (strncmp((char *)&rx_cmd, "E1", 2) == 0) || (strncmp((char *)&rx_cmd, "e1", 2) == 0) ) {
			resp_ok();
		}
		else if( (strncmp((char *)&rx_cmd, "L0", 2) == 0) || (strncmp((char *)&rx_cmd, "l0", 2) == 0)) {
			resp_ok();
		}
		else if( (strncmp((char *)&rx_cmd, "S0", 2) == 0) || (strncmp((char *)&rx_cmd, "s0", 2) == 0)) {
			resp_ok();
		}
		else if( (strncmp((char *)&rx_cmd, "M0", 2) == 0) || (strncmp((char *)&rx_cmd, "m0", 2) == 0)) {
			resp_ok();
		}
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV2;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV6;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART1) {	// COMM
		HAL_UART_Receive_IT(&huart1, (uint8_t *)rx_uart, 1);
	}
}

void NewCmdAT(void)
{
    uint8_t indice = 0;

    if(rx_uart[pointer_rx] == '?' && rx_uart[pointer_rx+1] == '\r') {
    	resp_ok();
    	pointer_rx++;
    	pointer_rx++;
    }
    else if( (rx_uart[pointer_rx] == 'A' && rx_uart[pointer_rx+1] == 'T')  ||
    	     (rx_uart[pointer_rx] == 'a' && rx_uart[pointer_rx+1] == 't') ){
    	pointer_rx += 2;
    	indice = 0;
    	while(rx_uart[pointer_rx+indice] != '\r') {
    		rx_cmd[indice] = toupper(rx_uart[pointer_rx+indice]);
    		indice++;
    	}
    	pointer_rx +=indice+1;
    }
}


void resp_ok(void)
{
	string_tx[0] = 'O';
	string_tx[1] = 'K';
	string_tx[2] = '\r';
	string_tx[3] = '\n';
	string_tx[4] = 0;
	HAL_UART_Transmit(&huart1, (uint8_t *)string_tx, strlen(string_tx), 1000);
	string_tx[0] = '>';
	string_tx[1] = '\r';
	string_tx[2] = '\0';
	HAL_UART_Transmit(&huart1, (uint8_t *)string_tx, strlen(string_tx), 1000);
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
