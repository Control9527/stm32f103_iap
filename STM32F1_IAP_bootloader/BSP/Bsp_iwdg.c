#include "Bsp_iwdg.h"


/*======================================================================================================*/
__IO uint16_t LsiFreq = 40000;  //内部低速时钟
/*=======================================================================================================
*Function:  Bsp_IWDG_Config( ) => IWDG config
*Input   :  None
*Output  :  None
========================================================================================================*/
void Bsp_IWDG_Config(void)
{
  if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
  { 
    /* Clear reset flags */
    RCC_ClearFlag();
  }
 /* IWDG timeout equal to 250 ms (the timeout may varies due to LSI frequency
     dispersion) */
  /* Enable write access to IWDG_PR and IWDG_RLR registers */
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

  /* IWDG counter clock: LSI/32 */
  IWDG_SetPrescaler(IWDG_Prescaler_32);

  /* Set counter reload value to obtain 250ms IWDG TimeOut.
     Counter Reload Value = 250ms/IWDG counter clock period
                          = 250ms / (LSI/32)
                          = 0.25s / (LsiFreq/32)
                          = LsiFreq/(32 * 4)
                          = LsiFreq/128  -> 250ms
   */
  IWDG_SetReload(LsiFreq/16);  //2s  -> 0.25*8

  /* Reload IWDG counter */
  IWDG_ReloadCounter();
  
  /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
  IWDG_Enable();
  
}

