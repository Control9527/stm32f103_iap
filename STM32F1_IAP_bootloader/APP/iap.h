#ifndef IAP_H_
#define IAP_H_

#include "header.h"

#define FLASH_APP_BASE_ADDR	0x08010000 //��һ��Ӧ�ó�����ʼ��ַ(�����FLASH)


bool Iap_WriteFlashFunction(uint32_t addr,uint8_t *iapbuff,uint32_t iaplength);
void Iap_Load_App(uint32_t addr);

#endif
