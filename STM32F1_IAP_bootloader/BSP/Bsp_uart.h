#ifndef UART_H_
#define UART_H_

#include "header.h"

#define RX_BuffSize	1024*40


typedef enum 
{
	UART_1 = 0,
	UART_2 = 1,
	UART_3 = 2,
}_UARTX;

typedef enum 
{
	PARITY_NO = 0,
	PARITY_EVEN = 1,
	PARITY_ODD = 2,
}_PARTY;

typedef enum 
{
	STOPBIT_1 = 0,
	STOPBIT_2 = 1,
}_STOPBIT;

typedef enum 
{
	BAUD_1200 = 0,
	BAUD_2400 = 1,
	BAUD_4800 = 2,
	BAUD_9600 = 3,
	BAUD_19200 = 4,
	BAUD_38400 = 5,
	BAUD_57600 = 6,
	BAUD_115200 = 7,
	BAUD_230400 = 8,
}_BAUDRATE;

typedef struct
{
	u8 BaudRate;
	u8 StopBit;
	u8 Parity;
}_UART_PARA;

typedef struct
{
	bool ReciveFig;
	bool RxBusy;
	bool TxBusy;
	
	uint8_t  PreemptionPriority;
	uint8_t  SubPriority;
	uint16_t Rx_Pin;
	uint16_t Tx_Pin;
	uint32_t Parity;
	uint32_t Baud_Rate;
	uint32_t RCC_PinPort;
	uint32_t RCC_UARTx;
	
	IRQn_Type UARTx_IRQn;
	USART_TypeDef* USARTx;
	GPIO_TypeDef* Pinport;
}UART_DEF;


extern UART_DEF Uart_Table[ 1 ];
extern uint8_t rx_table[RX_BuffSize];
extern uint32_t rxlength;


void Uart_Init(UART_DEF *Uart);
void Bsp_Receiverdata(UART_DEF *Uart);
void Bsp_SendData(UART_DEF *Uart,uint8_t *buff,uint32_t length);   //·¢ËÍÊý¾Ý
void Bsp_Complete(UART_DEF *Uart);

#endif

