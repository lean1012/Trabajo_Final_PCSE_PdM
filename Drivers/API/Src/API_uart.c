/*
 * API_uart.c
 *
 *  Created on: Apr 3, 2023
 *      Author: leandro
 */

#include "API_uart.h"
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include <string.h>

#include "main.h"

/* UART handler declaration */
static UART_HandleTypeDef UartHandle;

#define UART_BaudRate 115200

uint8_t conf_uart[]="UART INICIALIZADA EN 9600 8N1"; //(1 bit de inicio, 8 bits de datos, ningún (N) bit de paridad, y un (1) bit de parada)";


bool_t uartInit(){

	  /*##-1- Configure the UART peripheral ######################################*/
	  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	  /* UART configured as follows:
	      - Word Length = 8 Bits (7 data bit + 1 parity bit) :
		                  BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
	      - Stop Bit    = One Stop bit
	      - Parity      = ODD parity
	      - BaudRate    = 9600 baud
	      - Hardware flow control disabled (RTS and CTS signals) */
	  UartHandle.Instance        = USARTx;
	  UartHandle.Init.BaudRate   = UART_BaudRate;
	  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	  UartHandle.Init.StopBits   = UART_STOPBITS_1;
	  UartHandle.Init.Parity     = UART_PARITY_NONE;
	  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	  UartHandle.Init.Mode       = UART_MODE_TX_RX;
	  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	  if (HAL_UART_Init(&UartHandle) != HAL_OK)
	  {
	    return false;

	  }else{
	      uartSendString(conf_uart);
		  return true;

	  }
}
void uartSendString(uint8_t * pstring){

	//strlen cuenta los caracteres hasta un \0
	uint16_t size = strlen((char *)pstring);
	uint16_t uart_time_out = (uint16_t)(10.0*((size))*(1.0/UART_BaudRate)*10.0*1000.0);
	HAL_UART_Transmit(&UartHandle,pstring,size,uart_time_out);


}
void uartSendStringSize(uint8_t * pstring, uint16_t size){

	/*calculo el tiempo como 10 bits de la transmisión UART * size (veces transmitidas) * velocidad (1/BAUDRATE) + margen multiplico x10
	 *ultimo multiplico por 1000 para los ms*/
	uint16_t uart_time_out = (uint16_t)(10.0*((size))*(1.0/UART_BaudRate)*10.0*1000.0);
	HAL_UART_Transmit(&UartHandle,pstring,size,uart_time_out);


}
void uartReceiveStringSize(uint8_t * pstring, uint16_t size){
	/*calculo el tiempo como 10 bits de la transmisión UART * size (veces transmitidas) * velocidad (1/BAUDRATE) + margen multiplico x10
	 *ultimo multiplico por 1000 para los ms*/
	uint16_t uart_time_out = (10*((size))*(1/UART_BaudRate))*10*1000;
	HAL_UART_Receive(&UartHandle,pstring,size,uart_time_out);
}
