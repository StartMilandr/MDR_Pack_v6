#include "BasisCfg.h"


void SFP_PresencePinsInit(void)
{
  MDR_CLOCK->PER_CLOCK |= SFP_PRES_PORT_CLK;
  
  SFP_PRES_PORT->ANALOG = SFP_PRES_PIN_ALL;
}

void PhyResetPinsInit(void)
{ 
  MDR_CLOCK->PER_CLOCK |= SHIFT_REG_PORT_CLK;
  
  SHIFT_REG_PORT->PULL   = PIN_PULL_UP(SHIFT_REG_PIN_ALL);      //0xFFE00000;	//Pull up (PB[15:5])
	SHIFT_REG_PORT->ANALOG = SHIFT_REG_PIN_ALL;                   //0xFFFF;
	SHIFT_REG_PORT->OE     = SHIFT_REG_PIN_ALL;                   //0x07C0;	                                                            //PB6 - BP10 - shift reg
  SHIFT_REG_PORT->PWR    = SHIFT_REG_PIN_PWR(MDR_PIN_MAXFAST);  //0x3FF000;
}  


void vResetPhys( void )
{
    uint8_t ucI;
    uint32_t ulPause;
    
    SHIFT_REG_OE_1;
    SHIFT_REG_IN_0;
    //SHIFT_REG_IN_1;
    
    SHIFT_REG_CLR_0;
    for( ulPause = 100; ulPause > 0; ulPause-- ){}
    SHIFT_REG_CLR_1;
    
    for( ucI = 0; ucI < 17; ucI++ )
    {
        SHIFT_REG_SRCLK_0;
        SHIFT_REG_RCLK_0;
        for( ulPause = 100; ulPause > 0; ulPause-- ){}
        SHIFT_REG_SRCLK_1;
        SHIFT_REG_RCLK_1;
        for( ulPause = 100; ulPause > 0; ulPause-- ){}
    }
    
    SHIFT_REG_OE_0;
    for( ulPause = 100; ulPause > 0; ulPause-- ){}
    SHIFT_REG_OE_1;    
}

uint32_t SFP_PinSel[SFP_COUNT] = {SFP_PRES_PIN_X1_1, SFP_PRES_PIN_X1_2, SFP_PRES_PIN_X8_1, SFP_PRES_PIN_X8_2};

uint32_t SFP_PresenceGetMask(void)
{
  return SFP_PRES_PORT->RXTX & SFP_PRES_PIN_ALL;
}
