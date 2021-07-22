#ifndef BSP_IWDG_H_
#define BSP_IWDG_H_

#include "header.h"


#define   FeedDog()     IWDG_ReloadCounter()

void Bsp_IWDG_Config(void);


#endif

