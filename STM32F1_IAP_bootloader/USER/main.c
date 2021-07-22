#include "header.h"

#define MYAPP	0//ֱ�Ӽ��ع̼�
#define MYIAP	1//����IAP״̬

volatile uint8_t Mode = MYAPP;//Ĭ��ֱ�Ӽ��ع̼�
int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	Bsp_gpio(gpio_num);
	Bsp_TimerInit();
	Uart_Init(&Uart_Table[0]);
	
	uint8_t count = 0;
	while(WKUP() == 1)
	{
		delay_ms(500);
		if((++count) >= 6) 
		{	//3s
			printf("����IAP����ģʽ���뷢�����bin�ļ�......");
			SetTimeCountLed = 500; 
			Mode = MYIAP;
			break;
		}
	}
	
	while(1)
	{		
		if(Mode == MYAPP)
		{
			if(((*(uint32_t*)(FLASH_APP_BASE_ADDR+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0x08xxxxxx
			{
				printf("���й̼�......");
				delay_ms(100);
				Iap_Load_App(FLASH_APP_BASE_ADDR);
			}
			else
			{
				printf("�޹̼�������......");
				delay_ms(1000);
			}
		}
		else if(Mode == MYIAP)
		{
			if( Uart_Table[0].ReciveFig == 1)
			{			
				Uart_Table[0].ReciveFig = 0;
				printf("������ɣ���ȷ�ϻ������......");
				SetTimeCountLed = 1000;  
			}
			
			if(rxlength != 0)
			{
				switch(KeyNumberFunction())
				{
					case 1://KEY1  //���
						rxlength = 0;
						printf("�����......");
						break;	

					case 2://WKUP  //ȷ��
						if(((*(uint32_t*)(0X20001000 + 4)) & 0xff000000) == 0x08000000)//�ж��Ƿ�Ϊ0x08xxxxxx 0X20001000��ǰ����д�㷨����
						{
							printf("����д��̼����������......");
							SetTimeCountLed = 200;
							if(Iap_WriteFlashFunction(FLASH_APP_BASE_ADDR,rx_table,rxlength))
							{
								printf("д����ɣ����Զ����й̼�......");
								rxlength = 0;
								Mode = MYAPP;
								delay_ms(100);
							}
							else
							{
								rxlength = 0;
								printf("д��ʧ�ܣ�����������ϴ�д��......");
							}
							SetTimeCountLed = 1000;
						}
						else
						{
							rxlength = 0;
							printf("�̼���ַ���������·��͹̼�......");
						}
						break;	
					
					default:
						break;
				}
			}
		}
	}
}

