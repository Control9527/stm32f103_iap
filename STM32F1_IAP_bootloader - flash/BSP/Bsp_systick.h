#ifndef BSP_SYSTICK_H_
#define BSP_SYSTICK_H_

#include "header.h"

void Bsp_SystickInit(void);
void Bsp_Tick(void);
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);

#endif

