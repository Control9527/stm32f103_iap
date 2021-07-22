#include "Bsp_uart.h"

uint32_t Baud_Table[] = { 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400 };
uint32_t Parity_Table[] = { USART_Parity_No, USART_Parity_Even, USART_Parity_Odd };

UART_DEF Uart_Table[ 1 ] = {
	                            [UART_1] = 
									{
										.RxBusy = false,
										.TxBusy = false,
										.ReciveFig = false,
										.PreemptionPriority = 2,
										.SubPriority = 3,
										.RCC_PinPort = RCC_APB2Periph_GPIOA,
										.Rx_Pin = GPIO_Pin_10,
										.Tx_Pin = GPIO_Pin_9,
										.Pinport = GPIOA,
										.UARTx_IRQn = USART1_IRQn,
										.USARTx = USART1,
										.RCC_UARTx = RCC_APB2Periph_USART1,
										.Parity = USART_Parity_No,
										.Baud_Rate = BAUD_115200,
									}					
                           };

						   
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif
						   
						   
													 
void Uart_NVIC(UART_DEF *Uart)
{
	NVIC_InitTypeDef NVIC_InitStruction;
	
	NVIC_InitStruction.NVIC_IRQChannel = Uart->UARTx_IRQn;
	NVIC_InitStruction.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruction.NVIC_IRQChannelPreemptionPriority = Uart->PreemptionPriority;
	NVIC_InitStruction.NVIC_IRQChannelSubPriority = Uart->SubPriority;
	NVIC_Init(&NVIC_InitStruction);
}
													 
													 
void Uart_Config(UART_DEF *Uart)
{
	GPIO_InitTypeDef GPIO_InitStruction;
	USART_InitTypeDef USART_InitStruction;
	
	RCC_APB2PeriphClockCmd(Uart->RCC_PinPort , ENABLE);
	
	if(Uart->USARTx == USART1)
	{
		RCC_APB2PeriphClockCmd(Uart->RCC_UARTx , ENABLE);
	}
	else
	{
		RCC_APB1PeriphClockCmd(Uart->RCC_UARTx , ENABLE);
	}
	
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruction.GPIO_Pin = Uart->Tx_Pin;
	GPIO_InitStruction.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Uart->Pinport, &GPIO_InitStruction);
	
	GPIO_InitStruction.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruction.GPIO_Pin = Uart->Rx_Pin;
	GPIO_Init(Uart->Pinport, &GPIO_InitStruction);
	
	if(Uart->Parity == USART_Parity_No)
	{
		USART_InitStruction.USART_WordLength = USART_WordLength_8b;
	}
	else
	{
		USART_InitStruction.USART_WordLength = USART_WordLength_9b;
	}
	USART_InitStruction.USART_BaudRate = Baud_Table[Uart->Baud_Rate];
	USART_InitStruction.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruction.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruction.USART_Parity = Uart->Parity;
	USART_InitStruction.USART_StopBits = USART_StopBits_1;
	USART_Init(Uart->USARTx, &USART_InitStruction);
	
	USART_ITConfig( Uart->USARTx, USART_IT_RXNE , ENABLE );
	USART_ITConfig( Uart->USARTx, USART_IT_IDLE , ENABLE ); 
	USART_ITConfig( Uart->USARTx, USART_IT_TXE , DISABLE ); 
	
	USART_Cmd(Uart->USARTx,ENABLE);
}



void Uart_Init(UART_DEF *Uart)  //���贮�ڳ�ʼ��
{
	Uart_NVIC(Uart);
	Uart_Config(Uart);
}

uint32_t rxlength = 0;
uint8_t rx_table[RX_BuffSize] __attribute__ ((at(0x20001000)));   //0x20000000��0x20001000����¼�㷨
void Bsp_Receiverdata(UART_DEF *Uart)   //�������ݺ���  �����жϽ���
{
	uint8_t data;
	
	data = USART_ReceiveData(Uart->USARTx);
	rx_table[rxlength] = data;
	rxlength++;
	
	Uart->RxBusy = true;
}

void Bsp_SendData(UART_DEF *Uart,uint8_t *buff,uint32_t length)   //��������
{
	for(uint32_t i = 0; i < length; i++)
	{
		USART_SendData(Uart->USARTx, buff[i]);
		while(USART_GetFlagStatus(Uart->USARTx,USART_FLAG_TC)!=SET);		//�ȴ����ͽ���	
	}
}

void Bsp_Complete(UART_DEF *Uart)    //�������ݵı�־λ
{
  Uart->RxBusy = false;
  if(rxlength != 0)
  {
    Uart->ReciveFig = true;
  }
}
