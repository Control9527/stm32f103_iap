#include "Bsp_gpio.h"


gpio_def gpio_table[gpio_num] = 
{
	[0] = {
		       .gpio_Pin   = GPIO_Pin_8,//LED0
		       .gpio_port  = GPIOA,
		       .gpio_rcc   = RCC_APB2Periph_GPIOA,
		       .gpio_mode  = GPIO_Mode_Out_PP,
		       .gpio_speed = GPIO_Speed_50MHz,
	      },
	
	[1] = {
		       .gpio_Pin   = GPIO_Pin_2,//LED1
		       .gpio_port  = GPIOD,
		       .gpio_rcc   = RCC_APB2Periph_GPIOD,
		       .gpio_mode  = GPIO_Mode_Out_PP,
		       .gpio_speed = GPIO_Speed_50MHz,
	      },

	[2] = {
		       .gpio_Pin   = GPIO_Pin_15,//KEY1按下为低
		       .gpio_port  = GPIOA,
		       .gpio_rcc   = RCC_APB2Periph_GPIOA,
		       .gpio_mode  = GPIO_Mode_IPU,
		       .gpio_speed = GPIO_Speed_50MHz,
	      },

	[3] = {
		       .gpio_Pin   = GPIO_Pin_0,//WK_UP 按下为高
		       .gpio_port  = GPIOA,
		       .gpio_rcc   = RCC_APB2Periph_GPIOA,
		       .gpio_mode  = GPIO_Mode_IPD,
		       .gpio_speed = GPIO_Speed_50MHz,
	      }		  
};


void Init_gpio(uint8_t num)
{
	GPIO_InitTypeDef GPIO_InitStruction;
	
	RCC_APB2PeriphClockCmd(gpio_table[num].gpio_rcc , ENABLE);
	
	GPIO_InitStruction.GPIO_Mode  = gpio_table[num].gpio_mode;
	GPIO_InitStruction.GPIO_Pin   = gpio_table[num].gpio_Pin;
	GPIO_InitStruction.GPIO_Speed = gpio_table[num].gpio_speed;
	
	GPIO_Init( gpio_table[num].gpio_port, &GPIO_InitStruction);
}

void Bsp_gpio(uint8_t num)
{
	for(char i = 0; i < num; i++)
	{
		Init_gpio(i);
	}
}


uint8_t KeyNumberFunction(void)
{
	static bool flag = true;
	
	if((KEY1() == 0 || WKUP() == 1) && flag)
	{
		delay_ms(100);
		if(KEY1() == 0)
		{
			flag = false;
			return 1;
		}
		else if(WKUP() == 1)
		{
			flag = false;
			return 2;
		}
	}
	else if(KEY1() == 1 && WKUP() == 0 && flag == false)
	{
		delay_ms(100);
		if(KEY1() == 1 && WKUP() == 0 && flag == false)
		{
			flag = true;
		}
	}
	
	return 0;
}












