/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "stdbool.h"

/******* HARDWARE *******/
#include "VNH5019/vnh5019.h"

/******* SOFTWARE *******/
#include "FILTER/kalman.h"
#include "FUNCTIONS/math_functions.h"
#include "PIDAUTOTUNER/pidautotuner.h"
#include "PID/pid.h"
#include "AMT103_ENCODER/amt103_encoder.h"
#include "RS610WP_SERVO/rs610wp_servo.h"
#include "CONTROLLER/tesla.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define T_Sample 20

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
pid PID_Motor;
int32_t des_speed;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t rxdata[4] = {0, 0, 0, 0};
int16_t receive_speed;
int8_t receive_angle;
uint8_t flag_button=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
extern void user_setup(int16_t target, int8_t min, int8_t max);
extern void user_loop();
extern float kp, ki, kd;
extern bool start;

__IO uint32_t Micros;

uint32_t micros(void)
{
	return Micros;
}

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
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	/************** Configure micros() function **************/
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000000);
	
	/************** TIMER **************/
	HAL_TIM_Base_Start_IT(&htim1);
	
	/************** VNH5019 **************/
	VNH5019_Init();
	
	/************** ENCODER **************/
	AMT103_Init();
	
	/************** SERVO **************/
	RS610WP_Init();
	
	/************** PID TUNING **************/
//	user_setup(200, 0, 40);
	kp = 0.105649225;
	ki = 0.0;
	kd = 0.18860482;
	start = 1;
//	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	
	/************** PID Controller **************/
	PID_Reset(&PID_Motor);
	PID_Init(&PID_Motor, T_Sample, kp, 0, kd, 0, 40); //0.46, 0.27, 0.2
	
	/************** COMMUNICATION **************/
	while (HAL_UARTEx_ReceiveToIdle_DMA(&huart2, rxdata, 4) != HAL_OK) HAL_UART_DMAStop(&huart2);
  __HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		HAL_Delay(10);
				
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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

/* USER CODE BEGIN 4 */
/*********************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if(htim->Instance == TIM4) OverFlow();
	
  if (htim->Instance == TIM1) {
		if (start == 1) {
			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			
			/************* Encoder *************/ 
			des_speed = AMT103_GetPulse();
			
			/************* Processing *************/ 
			Run(receive_speed); //receive_speed
			PID_Process(&PID_Motor, Velocity.Output, des_speed);
			
			/************* PWM *************/ 
			if (flag_button == 0) {
				VNH5019_Run(0, 0); 
				Control_Angle(0); 
			}
			else {
				VNH5019_Run(PID_Motor.Output.Current, receive_speed); 
				Control_Angle(receive_angle); //receive_angle
			}
//			RS610WP_Run(135); //Control_Angle(PID_IMU.Output.Current); 
			// 0 do: 140 
			// 25 do: 200 -> phai 
			// -25 do: 80-> trai
			}
		}
}

/*********************************************************/
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
  if (huart->Instance == USART2) {
	  while (HAL_UARTEx_ReceiveToIdle_DMA(&huart2, rxdata, 4) != HAL_OK) HAL_UART_DMAStop(&huart2);
    __HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);
		if (Size == 4) {
			if (rxdata[3] == 25) {
				receive_speed = ((int16_t)rxdata[1]<<8)|rxdata[0];
				receive_angle = rxdata[2];
			}
			else {
				receive_speed = 0;
				receive_angle = 0;
			}
			
			/**** CHECK DATA ****/
//			if (receive_speed == 100 && receive_angle == 0) HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
//			else HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		}
  }
}

/*********************************************************/
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
  if (huart->Instance == USART2) {
		while (HAL_UARTEx_ReceiveToIdle_DMA(&huart2, rxdata, 4) != HAL_OK) HAL_UART_DMAStop(&huart2);
    __HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);
	}
}

/*********************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
 if (GPIO_Pin == STOP_Pin) flag_button=0;
 else if (GPIO_Pin == START_Pin) flag_button=1;
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
