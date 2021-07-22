#include "header.h"

int main(void)
{		
	SCB->VTOR = FLASH_BASE | 0x10000;//����ƫ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	Bsp_TimerInit();
	Bsp_gpio(gpio_num);
	Uart_Init(&Uart_Table[0]);
	
	while(1)
	{		
		if( Uart_Table[0].ReciveFig == 1)
		{			
			Uart_Table[0].ReciveFig = 0;
			Bsp_SendData(&Uart_Table[0],rx_table,rxlength);
			rxlength = 0;
		}
		
		switch(KeyNumberFunction())
		{
			case 1://��KEY1
				SetTimeCountLed -= 50;
				printf("SetTimeCountLed : %d",SetTimeCountLed);
				break;	

			case 2://��WKUP
				SetTimeCountLed += 50;
				printf("SetTimeCountLed : %d",SetTimeCountLed);
				break;	
			
			default:
				break;
		}
	}
}

