#include <MDR_SN74HC595D_ShiftReg.h>
#include <MDR_GPIO.h>
#include <MDR_Funcs.h>

void MDR_SN74HC595D_PinsInid(void)
{
  MDR_GPIO_Enable(MDR_SN74HC595D_PORT);
  
  MDR_GPIO_Init_PortOUT(MDR_SN74HC595D_PORT, MDR_SN74HC595D_PIN_ALL, MDR_SN74HC595D_PIN_POWER);
}


void MDR_SN74HC595D_SetShiftValue(uint16_t value, uint32_t delayTicks)
{
  uint32_t i;
#if MDR_SN74HC595D_DO_REVBIT    
    i = __RBIT(value);
  #if MDR_SN74HC595D_RSHIFT
    value = (i >> MDR_SN74HC595D_RSHIFT);
  #endif   
#endif 
  
  //  Confirm Inactive State
  MDR_SN74HC595D_SRCLK_0;
  MDR_SN74HC595D_RCLK_0;
  
  //  New value to ShiftReg
  for (i = 0; i < MDR_SN74HC595D_SHIFT_LEN; ++i)
  {
    //  Output Bit
    if (value & (1 << i))
      MDR_SN74HC595D_IN_1;
    else
      MDR_SN74HC595D_IN_0;
    MDR_Delay(delayTicks);
    
    //  Shift Bit
    MDR_SN74HC595D_SRCLK_1;
    MDR_Delay(delayTicks);
    MDR_SN74HC595D_SRCLK_0;      
  }
  //  Apply ShiftReg to HoldReg
  MDR_SN74HC595D_RCLK_1;
  MDR_Delay(delayTicks);
  MDR_SN74HC595D_RCLK_0;
  
  //  Leave Inp pin in zero    
  MDR_SN74HC595D_IN_0;
}

void MDR_SN74HC595D_Clear(uint32_t delayTicks)
{  
  //  Start Levels fo clear
  MDR_SN74HC595D_SRCLK_0;
  MDR_SN74HC595D_RCLK_0;
  MDR_SN74HC595D_CLR_0;
  MDR_Delay(delayTicks);
  
  //  Apply ShiftReg to HoldReg
  MDR_SN74HC595D_RCLK_1;
  MDR_Delay(delayTicks);
  MDR_SN74HC595D_RCLK_0;
  MDR_SN74HC595D_CLR_1;
}
