#include "main.h"
#include "stm32f7xx_hal.h"
#include "cmsis_os.h"
#include "lwip.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> //exit(0);
#include <lwip/sockets.h>
#include "udp.h"



void start_io_task(void const * argument)
{
	printf("start_io_task\n");
	/* init code for LWIP */
	setvbuf(stdin, NULL, _IONBF, 0);
	HAL_GPIO_TogglePin(LEDR_GPIO_Port, LEDR_Pin);

	/* USER CODE BEGIN start_io_task */
	/* Infinite loop */
	for (;;)
	{
		int nb;
		scanf("%d", &nb);
		printf("%d\n", nb);
	}
	/* USER CODE END start_io_task */
}

/* start_asserv_task function */
void start_asserv_task(void const * argument)
{
	printf("start_asserv_task\n");
	TickType_t xLastWakeTime = xTaskGetTickCount();
	for (;;)
	{
//		printf("#");
		HAL_GPIO_TogglePin(LEDB_GPIO_Port, LEDB_Pin);
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(8));
	}
}
unsigned int *ptr = (unsigned int*)0x20aa8c0;
/* start_background_task function */
void start_background_task(void const * argument)
{
	MX_LWIP_Init();
	printf("start_background_task\n");

	int s;
//	asm volatile ("cpsid i");

	unsigned short port;
	struct sockaddr_in server, si_other;
	long unsigned int slen=sizeof(si_other);
	memset(&server, 0, sizeof(server));

	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		printf("socket failed..\n");

	/* Set up the server name */
	server.sin_family      = AF_INET;            /* Internet Domain    */
	server.sin_port        = htons(6666);               /* Server Port        */
//	server.sin_addr.s_addr = inet_addr("192.168.10.1"); /* Server's Address   */
	server.sin_addr.s_addr = htonl(INADDR_ANY);


	if (bind(s, &server, sizeof(server))==-1)
		printf("bind failed..\n");
    char buf[5];
	for (;;)
	{
		 if (recvfrom(s, buf, 4, 0, &si_other, &slen)==-1)
			  printf("recvfrom failed\n");
		 buf[4] = 0;
		 printf("Recv '%s'\n", buf);

		 if (sendto(s, buf, (strlen(buf)), 0, (struct sockaddr *)&si_other, sizeof(si_other)) < 0)
			 printf("sendto failed\n");

		 HAL_Delay(1000);
	}
}

