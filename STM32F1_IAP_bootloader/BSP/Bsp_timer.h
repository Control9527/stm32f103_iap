#ifndef BSP_TIMER_H_
#define BSP_TIMER_H_

#include "header.h"

void Bsp_TimerConfig(void);
void Bsp_TimerNVIC(void);
void Bsp_TimerInit(void);

void Timer_harder(void);

void delay_ms(uint32_t ms);


extern volatile uint32_t SetTimeCountLed;

#endif
