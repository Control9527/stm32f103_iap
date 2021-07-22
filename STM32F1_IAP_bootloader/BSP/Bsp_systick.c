#include "Bsp_systick.h"

static volatile uint32_t Tick_Time;

void Bsp_SystickInit(void)
{
	if( SysTick_Config(SystemCoreClock / 1000000) )   //1us
	{
		while(1);
	}
	
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;   //关闭滴答定时器
}

void Bsp_Tick(void)
{
	if(Tick_Time != 0x00)
	{
		Tick_Time--;
	}
}


void delay_us(uint32_t us)
{
	Tick_Time = us;
	
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;    //开启滴答定时器
	while(Tick_Time != 0);
}


void delay_ms(uint32_t ms)
{
	Tick_Time = ms * 1000;
	
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
	while(Tick_Time != 0);
}

