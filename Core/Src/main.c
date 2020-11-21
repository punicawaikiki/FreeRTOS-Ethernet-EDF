/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "eth.h"
#include "rng.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOS_IP.h"
#include "queue.h"
#include "FreeRTOS_Sockets.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define mainLED_TASK_PRIORITY          ( tskIDLE_PRIORITY )
#define mainHOST_NAME					"RTOSDemo"
#define mainDEVICE_NICK_NAME			"stm32"
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* Default MAC address configuration.  The demo creates a virtual network
connection that uses this MAC address by accessing the raw Ethernet data
to and from a real network connection on the host PC.  See the
configNETWORK_INTERFACE_TO_USE definition for information on how to configure
the real network connection to use. */
const uint8_t ucMACAddress[ 6 ] = { configMAC_ADDR0, configMAC_ADDR1, configMAC_ADDR2, configMAC_ADDR3, configMAC_ADDR4, configMAC_ADDR5 };

/* The default IP and MAC address used by the demo.  The address configuration
defined here will be used if ipconfigUSE_DHCP is 0, or if ipconfigUSE_DHCP is
1 but a DHCP server could not be contacted.  See the online documentation for
more information. */
static const uint8_t ucIPAddress[ 4 ] = { configIP_ADDR0, configIP_ADDR1, configIP_ADDR2, configIP_ADDR3 };
static const uint8_t ucNetMask[ 4 ] = { configNET_MASK0, configNET_MASK1, configNET_MASK2, configNET_MASK3 };
static const uint8_t ucGatewayAddress[ 4 ] = { configGATEWAY_ADDR0, configGATEWAY_ADDR1, configGATEWAY_ADDR2, configGATEWAY_ADDR3 };
static const uint8_t ucDNSServerAddress[ 4 ] = { configDNS_SERVER_ADDR0, configDNS_SERVER_ADDR1, configDNS_SERVER_ADDR2, configDNS_SERVER_ADDR3 };

/* Use by the pseudo random number generator. */
static UBaseType_t ulNextRand;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
const char *pcApplicationHostnameHook( void )
{
	/* Assign the name "rtosdemo" to this network node.  This function will be
	called during the DHCP: the machine will be registered with an IP address
	plus this name. */
	return mainHOST_NAME;
}

static void prvSRand( UBaseType_t ulSeed )
{
	/* Utility function to seed the pseudo random number generator. */
	ulNextRand = ulSeed;
}

UBaseType_t uxRand( void )
{
const uint32_t ulMultiplier = 0x015a4e35UL, ulIncrement = 1UL;
static BaseType_t xInitialised = pdFALSE;

	/* Don't initialise until the scheduler is running, as the timeout in the
	random number generator uses the tick count. */
	if( xInitialised == pdFALSE )
	{
		if( xTaskGetSchedulerState() !=  taskSCHEDULER_NOT_STARTED )
		{
		RNG_HandleTypeDef xRND;
		uint32_t ulSeed;

			/* Generate a random number with which to seed the local pseudo random
			number generating function. */
			HAL_RNG_Init( &xRND );
			HAL_RNG_GenerateRandomNumber( &xRND, &ulSeed );
			prvSRand( ulSeed );
			xInitialised = pdTRUE;
		}
	}

	/* Utility function to generate a pseudo random number. */

	ulNextRand = ( ulMultiplier * ulNextRand ) + ulIncrement;
	return( ( int ) ( ulNextRand >> 16UL ) & 0x7fffUL );
}

void vLoggingPrintf( const char *pcFormatString, ... ){
	return;
}

BaseType_t xApplicationDNSQueryHook( const char *pcName )
{
BaseType_t xReturn;

	/* Determine if a name lookup is for this node.  Two names are given
	to this node: that returned by pcApplicationHostnameHook() and that set
	by mainDEVICE_NICK_NAME. */
	if( strcasecmp( pcName, pcApplicationHostnameHook() ) == 0 )
	{
		xReturn = pdPASS;
	}
	else if( strcasecmp( pcName, mainDEVICE_NICK_NAME ) == 0 )
	{
		xReturn = pdPASS;
	}
	else
	{
		xReturn = pdFAIL;
	}

	return xReturn;
}

/*
 * Supply a random number to FreeRTOS+TCP stack.
 * THIS IS ONLY A DUMMY IMPLEMENTATION THAT RETURNS A PSEUDO RANDOM NUMBER
 * SO IS NOT INTENDED FOR USE IN PRODUCTION SYSTEMS.
 */
BaseType_t xApplicationGetRandomNumber(uint32_t* pulNumber)
{
	*(pulNumber) = uxRand();
	return pdTRUE;
}
uint32_t ulApplicationGetNextSequenceNumber( uint32_t ulSourceAddress,
													uint16_t usSourcePort,
													uint32_t ulDestinationAddress,
													uint16_t usDestinationPort ){
	return 306;
}

static void vUDPSendUsingStandardInterface( void *pvParameters )
{
	Socket_t xSocket;
	struct freertos_sockaddr xDestinationAddress;
	uint8_t cString[ 50 ];
	uint32_t ulCount = 0UL;
	const TickType_t x900ms = 900UL / portTICK_PERIOD_MS;

   /* Send strings to port 55555 on IP address 192.168.1.1. */
   xDestinationAddress.sin_addr = FreeRTOS_inet_addr( "192.168.1.1" );
   xDestinationAddress.sin_port = FreeRTOS_htons( 55555 );

   /* Create the socket. */
   xSocket = FreeRTOS_socket( FREERTOS_AF_INET,
                              FREERTOS_SOCK_DGRAM,/*FREERTOS_SOCK_DGRAM for UDP.*/
                              FREERTOS_IPPROTO_UDP );

   /* Check the socket was created. */
   configASSERT( xSocket != FREERTOS_INVALID_SOCKET );

   /* NOTE: FreeRTOS_bind() is not called.  This will only work if
   ipconfigALLOW_SOCKET_SEND_WITHOUT_BIND is set to 1 in FreeRTOSIPConfig.h. */

   for( ;; )
   {
	   HAL_GPIO_WritePin(LD_USER2_GPIO_Port, LD_USER2_Pin, 1);
       /* Create the string that is sent. */
       sprintf( cString,
                "Standard send message number %lurn",
                ulCount );

       /* Send the string to the UDP socket.  ulFlags is set to 0, so the standard
       semantics are used.  That means the data from cString[] is copied
       into a network buffer inside FreeRTOS_sendto(), and cString[] can be
       reused as soon as FreeRTOS_sendto() has returned. */
       FreeRTOS_sendto( xSocket,
                        cString,
                        strlen( cString ),
                        0,
                        &xDestinationAddress,
                        sizeof( xDestinationAddress ) );

       ulCount++;
       vTaskDelay( 100UL / portTICK_PERIOD_MS);
       HAL_GPIO_WritePin(LD_USER2_GPIO_Port, LD_USER2_Pin, 0);
       /* Wait until it is time to send again. */
       vTaskDelay( x900ms );
   }
}

static void vUDPReceivingUsingStandardInterface( void *pvParameters )
{
	int32_t lBytes;
	uint8_t *pucUDPPayloadBuffer;
	struct freertos_sockaddr xClient, xBindAddress;
	uint32_t xClientLength = sizeof( xClient ), ulIPAddress;
	Socket_t xListeningSocket;

   /* Attempt to open the socket. */
   xListeningSocket = FreeRTOS_socket( FREERTOS_AF_INET,
									   FREERTOS_SOCK_DGRAM, /*FREERTOS_SOCK_DGRAM for UDP.*/
									   FREERTOS_IPPROTO_UDP );

   /* Check the socket was created. */
   configASSERT( xListeningSocket != FREERTOS_INVALID_SOCKET );

   /* Bind to port 55556. */
   xBindAddress.sin_port = FreeRTOS_htons( 55556 );
   FreeRTOS_bind( xListeningSocket, &xBindAddress, sizeof( xBindAddress ) );

   for( ;; )
   {
	   /* Receive data from the socket.  ulFlags has the zero copy bit set
	   (FREERTOS_ZERO_COPY) indicating to the stack that a reference to the
	   received data should be passed out to this RTOS task using the second
	   parameter to the FreeRTOS_recvfrom() call.  When this is done the
	   IP stack is no longer responsible for releasing the buffer, and
	   the RTOS task must return the buffer to the stack when it is no longer
	   needed.  By default the block time is portMAX_DELAY but it can be
	   changed using FreeRTOS_setsockopt(). */
	   lBytes = FreeRTOS_recvfrom( xListeningSocket,
								   &pucUDPPayloadBuffer,
								   0,
								   FREERTOS_ZERO_COPY,
								   &xClient,
								   &xClientLength );

	   if( lBytes > 0 )
	   {
		   HAL_GPIO_WritePin(LD_USER1_GPIO_Port, LD_USER1_Pin, 1);
		   char myString = pucUDPPayloadBuffer[1];
		   vTaskDelay(100UL / portTICK_PERIOD_MS);
		   HAL_GPIO_WritePin(LD_USER1_GPIO_Port, LD_USER1_Pin, 0);
		   /* Data was received and can be processed here. */
	   }

	   if( lBytes >= 0 )
	   {
		   /* The receive was successful so this RTOS task is now responsible for
		   the buffer.  The buffer must be freed once it is no longer
		   needed. */
           /* Data was received and can be process here. */
		   /*
			* The data can be processed here.
			*/

		   /* Return the buffer to the TCP/IP stack. */
		   FreeRTOS_ReleaseUDPPayloadBuffer( pucUDPPayloadBuffer );
	   }
   }
//
//
//	long lBytes;
//	uint8_t cReceivedString[ 256 ];
//	struct freertos_sockaddr xClient, xBindAddress;
//	uint32_t xClientLength = sizeof( xClient );
//	Socket_t xListeningSocket;
//
//   /* Attempt to open the socket. */
//   xListeningSocket = FreeRTOS_socket( FREERTOS_AF_INET,
//                                       FREERTOS_SOCK_DGRAM,/*FREERTOS_SOCK_DGRAM for UDP.*/
//                                       FREERTOS_IPPROTO_UDP );
//
//   /* Check the socket was created. */
//   configASSERT( xListeningSocket != FREERTOS_INVALID_SOCKET );
//
//   /* Bind to port 55556. */
//   xBindAddress.sin_port = FreeRTOS_htons( 55556 );
//   FreeRTOS_bind( xListeningSocket, &xBindAddress, sizeof( xBindAddress ) );
//
//   for( ;; )
//   {
//       /* Receive data from the socket.  ulFlags is zero, so the standard
//       interface is used.  By default the block time is portMAX_DELAY, but it
//       can be changed using FreeRTOS_setsockopt(). */
//       lBytes = FreeRTOS_recvfrom( xListeningSocket,
//                                   cReceivedString,
//                                   sizeof( cReceivedString ),
//                                   0,
//                                   &xClient,
//                                   &xClientLength );
//
//       if( lBytes > 0 )
//       {
//		   HAL_GPIO_WritePin(LD_USER1_GPIO_Port, LD_USER1_Pin, 1);
//		   vTaskDelay(100UL / portTICK_PERIOD_MS);
//		   HAL_GPIO_WritePin(LD_USER1_GPIO_Port, LD_USER1_Pin, 0);
//           /* Data was received and can be process here. */
//       }
//   }
}

void vApplicationIPNetworkEventHook( eIPCallbackEvent_t eNetworkEvent )
{
static BaseType_t xTasksAlreadyCreated = pdFALSE;
    /* Both eNetworkUp and eNetworkDown events can be processed here. */
    if( eNetworkEvent == eNetworkUp )
    {
    	xTaskCreate( vUDPSendUsingStandardInterface, "UDPSend", configMINIMAL_STACK_SIZE, NULL, mainLED_TASK_PRIORITY, NULL );
    	xTaskCreate( vUDPReceivingUsingStandardInterface, "UDPReceive", configMINIMAL_STACK_SIZE, NULL, mainLED_TASK_PRIORITY, NULL );
        /* Create the tasks that use the TCP/IP stack if they have not already
        been created. */
        if( xTasksAlreadyCreated == pdFALSE )
        {
            /*
             * For convenience, tasks that use FreeRTOS+TCP can be created here
             * to ensure they are not created before the network is usable.
             */

            xTasksAlreadyCreated = pdTRUE;
        }
    }
    else
    {
    	if (HAL_GPIO_ReadPin(LD_USER1_GPIO_Port, LD_USER1_Pin) != 1)
    	{
    		HAL_GPIO_WritePin(LD_USER1_GPIO_Port, LD_USER1_Pin, 1);
    	}
    }
}
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void vAssertCalled( uint32_t ulLine, const char *pcFile )
{
volatile unsigned long ul = 0;

	( void ) pcFile;
	( void ) ulLine;

	taskENTER_CRITICAL();
	{
		/* Set ul to a non-zero value using the debugger to step out of this
		function. */
		while( ul == 0 )
		{
			__NOP();
		}
	}
	taskEXIT_CRITICAL();
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
//  MX_ETH_Init();
  MX_RNG_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  FreeRTOS_IPInit( ucIPAddress,
                   ucNetMask,
                   ucGatewayAddress,
                   ucDNSServerAddress,
                   ucMACAddress );
  vTaskStartScheduler();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
