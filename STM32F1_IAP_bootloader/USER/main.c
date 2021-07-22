#include "header.h"

#define MYAPP	0//直接加载固件
#define MYIAP	1//进入IAP状态

volatile uint8_t Mode = MYAPP;//默认直接加载固件
int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	Bsp_gpio(gpio_num);
	Bsp_TimerInit();
	Uart_Init(&Uart_Table[0]);
	
	uint8_t count = 0;
	while(WKUP() == 1)
	{
		delay_ms(500);
		if((++count) >= 6) 
		{	//3s
			printf("进入IAP更新模式，请发送相关bin文件......");
			SetTimeCountLed = 500; 
			Mode = MYIAP;
			break;
		}
	}
	
	while(1)
	{		
		if(Mode == MYAPP)
		{
			if(((*(uint32_t*)(FLASH_APP_BASE_ADDR+4))&0xFF000000)==0x08000000)//判断是否为0x08xxxxxx
			{
				printf("运行固件......");
				delay_ms(100);
				Iap_Load_App(FLASH_APP_BASE_ADDR);
			}
			else
			{
				printf("无固件可运行......");
				delay_ms(1000);
			}
		}
		else if(Mode == MYIAP)
		{
			if( Uart_Table[0].ReciveFig == 1)
			{			
				Uart_Table[0].ReciveFig = 0;
				printf("接收完成，请确认或者清除......");
				SetTimeCountLed = 1000;  
			}
			
			if(rxlength != 0)
			{
				switch(KeyNumberFunction())
				{
					case 1://KEY1  //清除
						rxlength = 0;
						printf("已清除......");
						break;	

					case 2://WKUP  //确认
						if(((*(uint32_t*)(0X20001000 + 4)) & 0xff000000) == 0x08000000)//判断是否为0x08xxxxxx 0X20001000以前是烧写算法代码
						{
							printf("正在写入固件，请勿操作......");
							SetTimeCountLed = 200;
							if(Iap_WriteFlashFunction(FLASH_APP_BASE_ADDR,rx_table,rxlength))
							{
								printf("写入完成，将自动运行固件......");
								rxlength = 0;
								Mode = MYAPP;
								delay_ms(100);
							}
							else
							{
								rxlength = 0;
								printf("写入失败，请检查后重新上传写入......");
							}
							SetTimeCountLed = 1000;
						}
						else
						{
							rxlength = 0;
							printf("固件地址有误，请重新发送固件......");
						}
						break;	
					
					default:
						break;
				}
			}
		}
	}
}

