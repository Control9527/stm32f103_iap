#ifndef BSP_FLASH_H_
#define BSP_FLASH_H_

#include "header.h"

#define   rw(adr)   (*((uint32_t volatile *)(adr)))

bool Flash_Write(uint32_t address,uint32_t *buff,uint32_t length);  

#endif

