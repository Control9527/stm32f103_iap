#ifndef BSP_GPIO_H_
#define BSP_GPIO_H_

#include "header.h"

#define gpio_num 4

//LED
#define LED0_R() GPIO_ResetBits(GPIOA,GPIO_Pin_8)  
#define LED1_R() GPIO_SetBits(GPIOA,GPIO_Pin_8)
#define LED0_G() GPIO_ResetBits(GPIOD,GPIO_Pin_2)  
#define LED1_G() GPIO_SetBits(GPIOD,GPIO_Pin_2)

//KEY
#define KEY1()	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//0
#define WKUP()	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//1

typedef struct
{
	uint16_t gpio_Pin;
	uint32_t gpio_rcc;
	GPIO_TypeDef* gpio_port;
	GPIOMode_TypeDef  gpio_mode;
	GPIOSpeed_TypeDef gpio_speed;
}gpio_def;


void Bsp_gpio(uint8_t num);
uint8_t KeyNumberFunction(void);

#endif
