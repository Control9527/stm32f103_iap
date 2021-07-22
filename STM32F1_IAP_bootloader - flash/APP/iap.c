#include "iap.h"



bool Iap_WriteFlashFunction(uint32_t addr,uint8_t *iapbuff,uint32_t iaplength)
{
	bool flag = false;
	uint32_t count = 0,temp = 0;
	uint32_t writebuff[512];//2K����
	
	while(iaplength)
	{
		temp = (uint32_t)iapbuff[3] << 24;
		temp |= (uint32_t)iapbuff[2] << 16;
		temp |= (uint32_t)iapbuff[1] << 8;
		temp |= (uint32_t)iapbuff[0];
		iapbuff += 4;
		iaplength -= 4;
		writebuff[count++] = temp;
		if(count == 512)
		{
			count = 0;
			flag = Flash_Write(addr,writebuff,512);//2K����һ�δ��� һҳΪ2K
			if(!flag)
			{
				return flag;
			}
			addr += 2048;
		}
	}
	if(count != 0)
	{
		flag = Flash_Write(addr,writebuff,count);//ʣ�಻��2K
	}
	
	return flag;
}

//��֧�ֻ�� ����
//����ջ����ַ
//addr:ջ����ַ
__asm void MSR_MSP(u32 addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}
//��ת���û���������
void Iap_Load_App(uint32_t addr)
{
	if(((*(uint32_t *)addr) & 0x2FFE0000) == 0x20000000)//STM32������ʼ��ַ�������ջ����ַ 0x2FFE0000������RAM���Ϊ0x20010000
	{
		MSR_MSP(*(vu32*)addr);//��ʼ��APP��ջָ��(�û��������ĵ�һ�������ڴ��ջ����ַ)
		void (*function)(void);//����һ������ָ��
		function = (void (*)(void))addr;
		function();
	}
}






