#include "Bsp_flash.h"


#define FLASH_BASE_ADDR	0x08000000



bool Flash_Write(uint32_t address,uint32_t *buff,uint32_t length)   //length < FlashMax - 1
{
	FLASH_Status FlashFlag;
	
	if(address < FLASH_BASE_ADDR || address % 4)//�Ƿ���ַ
	{
		return false;
	}		
	
	FLASH_Unlock();  //�����ſɲ���
	
  
	FlashFlag = FLASH_ErasePage(address);  //start  
	if(FlashFlag != FLASH_COMPLETE)    //flash complete
	{
		return false;
	}
	for(int i = 0; i < length;i++)
	{
		FlashFlag = FLASH_ProgramWord(address + i * 4,buff[i]);
		if(FlashFlag != FLASH_COMPLETE)   //  write fail -> 
		{
		  return false;
		}
	}
	
	FLASH_Lock();

	return true;	
}







