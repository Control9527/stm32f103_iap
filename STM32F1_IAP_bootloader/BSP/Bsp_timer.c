#include "Bsp_timer.h"


void Bsp_TimerConfig(void)//1ms
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruction;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	TIM_TimeBaseInitStruction.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruction.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruction.TIM_Period = (1000 - 1);  //
	TIM_TimeBaseInitStruction.TIM_Prescaler = (72 - 1);  //
	TIM_TimeBaseInitStruction.TIM_RepetitionCounter = 0; 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruction);
	
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	TIM_Cmd(TIM3, ENABLE);	
}


void Bsp_TimerNVIC(void)
{
	NVIC_InitTypeDef NVIC_InitStruction;
	
	NVIC_InitStruction.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruction.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruction.NVIC_IRQChannelPreemptionPriority = 0;   //抢占
	NVIC_InitStruction.NVIC_IRQChannelSubPriority = 0;   //
	NVIC_Init(&NVIC_InitStruction);
}


void Bsp_TimerInit(void)
{
	Bsp_TimerNVIC();
	Bsp_TimerConfig();
}

volatile uint32_t DelayConut = 0;
void delay_ms(uint32_t ms)
{
	DelayConut = ms;
	while(DelayConut);
}

volatile uint32_t SetTimeCountLed = 1000;
volatile uint32_t TimeCountLed = 0;
void Timer_harder(void)//1ms
{
	if(DelayConut) DelayConut--;
	
	if((++TimeCountLed) > SetTimeCountLed)
	{
		static bool flag = true;
		TimeCountLed = 0;
		if(flag) {LED0_R();LED0_G();flag = false;}
		else {LED1_R();LED1_G();flag = true;}
	}
}


