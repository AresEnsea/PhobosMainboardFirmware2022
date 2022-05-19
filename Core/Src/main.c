/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "propulsion.h"
#include "odometry.h"
#include "robot.h"
#include "bezier.h"
#include "strategy.h"
#include "serial.h"
#include <stdio.h>
#include <math.h>

extern Robot robot;
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

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

int _write(int file, char *ptr, int len) {
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++) {
		HAL_UART_Transmit(&huart2, (uint8_t *) ptr++, 1, HAL_MAX_DELAY);
	}
	return len;
}
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
  MX_TIM1_Init();
  MX_TIM8_Init();
  MX_TIM11_Init();
  MX_TIM3_Init();
  MX_TIM7_Init();
  MX_TIM2_Init();
  MX_TIM6_Init();
  MX_TIM4_Init();
  MX_USART2_UART_Init();
  MX_TIM5_Init();
  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start(&htim1);
  HAL_TIM_Base_Start(&htim3);
  HAL_TIM_Base_Start_IT(&htim5);

  //char test[] = "Hello, World!\r\n";

  //serial_send(test, 15);

  printf("Initializing propulsion system.\r\n");
  propulsion_initialize();

  printf("Enabling propulsion system.\r\n");
  propulsion_enableMotors();

  HAL_Delay(2000);

  odometry_updatePosition();

  //Bezier** curves = (Bezier**) malloc(sizeof(Bezier*) * 5);
  //curves[0] = bezier_new(0, 0, 200, 0, 300, 0, 500, 0, 30);
  //curves[1] = bezier_new(500, 0, 500, 200, 500, 300, 500, 500, 30);
  //curves[2] = bezier_new(500, 500, 700, 500, 800, 500, 1000, 500, 30);
  //curves[3] = bezier_new(1000, 500, 1000, 300, 700, 0, 500, 0, 30);
  //curves[4] = bezier_new(500, 0, 300, 0, 200, 0, 0, 0, 30);

  Bezier** curves = (Bezier**) malloc(sizeof(Bezier*) * 10);
  curves[0] = bezier_new(2002, 1803, 2002, 1348, 2012, 1052, 1503, 1045, 30);
  curves[1] = bezier_new(1503, 1045, 994, 1038, 995, 1083, 997, 1318, 30);
  curves[2] = bezier_new(997, 1318, 1000, 1553, 922, 1641, 667, 1645, 30);
  curves[3] = bezier_new(667, 1645, 412, 1648, 401, 1512, 401, 1242, 30);
  curves[4] = bezier_new(401, 1242, 401, 973, 505, 887, 796, 890, 30);
  curves[5] = bezier_new(796, 890, 1087, 894, 1089, 1124, 1082, 1409, 30);
  curves[6] = bezier_new(1082, 1409, 1075, 1693, 719, 1695, 637, 1692, 30);
  curves[7] = bezier_new(637, 1692, 555, 1690, 456, 1679, 458, 1177, 30);
  curves[8] = bezier_new(458, 1177, 461, 675, 1996, 1545, 1985, 1113, 30);
  curves[9] = bezier_new(1985, 1113, 1974, 1300, 2002, 1802, 2002, 1803, 30);

  //Bezier* b = bezier_new(0, 0, 200, 0, 300, 0, 500, 0, 30);
  //Bezier* b = bezier_new(125, 849, 799, 843, 1698, 1654, 1698, 202, 30);
  odometry_setPosition(curves[0]->p1.x, curves[0]->p1.y);
  //odometry_setPosition(0, 0);
  odometry_setAngle(-M_PI/2);
  robot.measuredSpeed = 0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  int curveIndex = 0;

  float t = 0;

  //char* ptr = test;

  while (1) {
	  //HAL_UART_Transmit(&huart6, (uint8_t *) ptr, 15, HAL_MAX_DELAY);
	  //HAL_Delay(20);

	  //updateRobotPosition();

	  if (curveIndex == 9) {
		  t = propulsion_followBezier(curves[curveIndex], BACKWARD);
	  } else {
		  t = propulsion_followBezier(curves[curveIndex], FORWARD);
	  }

	  if (t > 0.99) {
	    curveIndex = (curveIndex + 1) % 10;
	  }

	//t = propulsion_followBezier(b, BACKWARD);

	//propulsion_disableMotors();

    /* USER CODE END WHILE */

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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
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
  printf("A runtime error occurred.\r\n");
  while (1) {
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

