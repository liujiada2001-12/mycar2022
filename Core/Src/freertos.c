/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "gotask.h"	//go task
#include "handtask.h"	//hand task
#include "getdatatask.h"	//getdata task
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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId getdata_taskHandle;
osThreadId go_taskHandle;
osThreadId hand_taskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void Start_getdata_task(void const * argument);
void Start_go_task(void const * argument);
void Start_hand_task(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of getdata_task */
  osThreadDef(getdata_task, Start_getdata_task, osPriorityRealtime, 0, 128);
  getdata_taskHandle = osThreadCreate(osThread(getdata_task), NULL);

  /* definition and creation of go_task */
  osThreadDef(go_task, Start_go_task, osPriorityIdle, 0, 128);
  go_taskHandle = osThreadCreate(osThread(go_task), NULL);

  /* definition and creation of hand_task */
  osThreadDef(hand_task, Start_hand_task, osPriorityIdle, 0, 128);
  hand_taskHandle = osThreadCreate(osThread(hand_task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Start_getdata_task */
/**
* @brief Function implementing the getdata_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_getdata_task */
void Start_getdata_task(void const * argument)
{
  /* USER CODE BEGIN Start_getdata_task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
    getdatatask();
  }
  /* USER CODE END Start_getdata_task */
}

/* USER CODE BEGIN Header_Start_go_task */
/**
* @brief Function implementing the go_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_go_task */
void Start_go_task(void const * argument)
{
  /* USER CODE BEGIN Start_go_task */
  HAL_Delay(500);
  /* Infinite loop */
  for(;;)
  {
    osDelay(4);
    gotask();
  }
  /* USER CODE END Start_go_task */
}

/* USER CODE BEGIN Header_Start_hand_task */
/**
* @brief Function implementing the hand_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_hand_task */
void Start_hand_task(void const * argument)
{
  /* USER CODE BEGIN Start_hand_task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(8);
    handtask();
  }
  /* USER CODE END Start_hand_task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
