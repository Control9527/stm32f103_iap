#include "iap.h"



bool Iap_WriteFlashFunction(uint32_t addr,uint8_t *iapbuff,uint32_t iaplength)
{
	bool flag = false;
	uint32_t count = 0,temp = 0;
	uint32_t writebuff[512];//2K内容
	
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
			flag = Flash_Write(addr,writebuff,512);//2K内容一次存入 一页为2K
			if(!flag)
			{
				return flag;
			}
			addr += 2048;
		}
	}
	if(count != 0)
	{
		flag = Flash_Write(addr,writebuff,count);//剩余不足2K
	}
	
	return flag;
}

//不支持汇编 内联
//设置栈顶地址
//addr:栈顶地址
__asm void MSR_MSP(u32 addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}
//跳转到用户程序运行
void Iap_Load_App(uint32_t addr)
{
	if(((*(uint32_t *)addr) & 0x2FFE0000) == 0x20000000)//STM32程序起始地址处存的是栈顶地址 0x2FFE0000是由于RAM最大为0x20010000
	{
		MSR_MSP(*(vu32*)addr);//初始化APP堆栈指针(用户代码区的第一个字用于存放栈顶地址)
		void (*function)(void);//定义一个函数指针
		function = (void (*)(void))addr;
		function();
	}
}






