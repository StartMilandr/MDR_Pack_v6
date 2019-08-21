#include <MDR_Config.h>
#include <MDR_RST_Clock.h>
#include <MDRB_LCD.h>
#include <MDRB_UART_Debug.h>

#include "test_Defs.h"
#include "MDRB_ShowMess.h"

#define MDR_ENA_LOG_TO_UART

#ifdef MDRB_HAS_LCD
  static bool _useLCD;
#endif  

#ifdef MDR_ENA_LOG_TO_UART
  #include <MDRB_UART_Debug.h>
  static bool _useUart;  
#endif

//  ====    User Defined messID to string output  ====
static void MDR_CUSTOM_ShowMessToStr(MDR_SHOW_MessID messID);


void MDR_ShowInit(bool useLCD, bool useUartDbg)
{
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  
#ifdef MDRB_HAS_LCD  
  _useLCD = useLCD;  
  if (_useLCD)
    MDRB_LCD_Init(freqCPU_Hz);
#else
  UNUSED(useLCD);
#endif
  
#ifdef MDR_ENA_LOG_TO_UART  
  _useUart = useUartDbg;  
  if (_useUart)
    MDR_UART_DBG_Init(true);
#else
  UNUSED(useUartDbg);  
#endif
}

void MDR_ShowMessStr(char *mess, uint8_t lineInd)
{
#if defined(MDRB_HAS_LCD) && !defined(LCD_IS_7SEG_DISPLAY)
  if (_useLCD)
    MDRB_LCD_Print(mess, lineInd);
#else
  UNUSED(mess);
  UNUSED(lineInd);
#endif
  
#ifdef MDR_ENA_LOG_TO_UART    
  if (_useUart)
    printf("%s\n", mess);
#endif
}

bool MDR_ShowRestore_IfConflTim(void)
{
#if defined(MDRB_HAS_LCD) && defined(LCD_CONFLICT_TIM)
  MDRB_LCD_Init(MDR_CPU_GetFreqHz(false));
  return true;
#else
  return false;
#endif
}

bool MDR_ShowRestore_IfConflLED(void)
{
#if defined(MDRB_HAS_LCD) && defined(LCD_CONFLICT_LED)  
  MDRB_LCD_CapturePins();   
  return true; 
#else
  return false;
#endif
}

void MDR_ShowMess(MDR_SHOW_MessID messID)
{
  //  Output to LCD ond/or UART
  MDR_CUSTOM_ShowMessToStr(messID);
  
#ifdef LCD_IS_7SEG_DISPLAY
  char mess[20];
  sprintf(mess, "%d", (uint8_t)messID);
  MDRB_LCD_Print(mess);
  
  #ifdef LCD_CONFLICT_TIM  
    #ifdef LCD_BLINKY_ENA
      MDR_LCD_BlinkyStart(MDR_LCD_Blink_2Hz, MDR_Off);
      MDR_LCD_DeInit();
    #endif
    MDR_Delay_ms(LCD_HIDE_DELAY, MDR_CPU_GetFreqHz(false));  
  #endif  
#endif
}


//  ====    User Defined messID to string output  ====
static void MDR_CUSTOM_ShowMessToStr(MDR_SHOW_MessID messID)
{
#if defined(MDRB_HAS_LCD) && !defined(LCD_IS_7SEG_DISPLAY)
  if (_useLCD)
  {
    MDRB_LCD_ClearLine(5);
    MDRB_LCD_ClearLine(7);
  }
#endif  
  
  switch (messID) {
    case MESS__SIMPLE_FLASH: 
      { MDR_ShowMessStr("Simplest Timer", 3);
        MDR_ShowMessStr("and Sync Run", 5);
        break; }  
    case MESS__COUNT_TIM_CLOCK: 
      { MDR_ShowMessStr("Count TimClock", 3);
        MDR_ShowMessStr("All Dirs", 5);    
        break;
      }
    case MESS__COUNT_CASCADE:
      { MDR_ShowMessStr("Cascade Timer", 3);
        break;
      }      
    case MESS__PULSE:
      { MDR_ShowMessStr("Pulse Width", 3);
        break;
      }       
    case MESS__PWM:
      { MDR_ShowMessStr("PWM simplest", 3);
        MDR_ShowMessStr("and Sync Run", 5);
        break;
      }       
    case MESS__PWM_DTG: 
      { MDR_ShowMessStr("PWM with DTG", 3);
        break;
      }       
    case MESS__PWM_ETRBRK: 
      { MDR_ShowMessStr("PWM ETR & BRK", 3);
        break;
      }       
    case MESS__CAP_SIMPLEST: 
      { MDR_ShowMessStr("CAP Simplest", 3);
        break;
      }       
    case MESS__CAP_PERIOD: 
      { MDR_ShowMessStr("CAP Period", 3);
        break;
      }       
    case MESS__COUNT_CAP: 
      { MDR_ShowMessStr("CAP Count", 3);
        break;
      }       
    case MESS__COUNT_ETR: 
      { MDR_ShowMessStr("Count ETR", 3);
        break;
      }
    }      
}

