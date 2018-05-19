#include "main.h"
#include "stm32f7xx_hal.h"
#include "cmsis_os.h"
#include "lwip.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"
#include <stdio.h>

char bufferRx[256];
char buffer[10];
int c2='A';
void start_io_task(void const * argument)
{
	/* init code for LWIP */
	MX_LWIP_Init();
	setvbuf(stdin, NULL, _IONBF, 0);
	HAL_GPIO_TogglePin(LEDR_GPIO_Port, LEDR_Pin);

	/* USER CODE BEGIN start_io_task */
	/* Infinite loop */
	for (;;)
	{
//		int nb;
//		scanf("%d", &nb);
//		printf("nb = %d\n", nb);

			int c=getchar();
//		printf("C = %c\n", c2);
		osDelay(1000);
	}
	/* USER CODE END start_io_task */
}

/* start_asserv_task function */
void start_asserv_task(void const * argument)
{

	TickType_t xLastWakeTime = xTaskGetTickCount();
	for (;;)
	{
//		printf("#");
		c2++;
		HAL_GPIO_TogglePin(LEDB_GPIO_Port, LEDB_Pin);
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
	}
}

/* start_background_task function */
void start_background_task(void const * argument)
{

	for (;;)
	{
		HAL_GPIO_TogglePin(LEDG_GPIO_Port, LEDG_Pin);
//		printf("b.a.c.k\n");
		osDelay(1000);
	}
}

