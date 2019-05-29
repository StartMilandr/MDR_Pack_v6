#include <MDR_GPIO.h>
#include <MDR_Funcs.h>
#include <MDR_Config.h>
#include <MDRB_LEDs.h>
#include <MDRB_Buttons.h>

//  Вывод кнопок только на один светодиод, если светодиодов меньше трех
#ifndef MDRB_LED_2
  #define MDRB_LED_2  MDRB_LED_1
  #define ONLY_OneLED
#endif

#ifndef MDRB_LED_3
  #define ONLY_OneLED
#endif

#define PERIOD_MS     1000
#define DEBOUNCE_MS   10

void LED_Flash(uint32_t LedSel);

int main(void)
{ 
  MDRB_LED_InitALL();
  MDRB_Buttons_Init(DEBOUNCE_MS, HSI_FREQ_HZ);
  
  MDRB_LED_Set(MDRB_LED_PinAll, true);
  MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);
  MDRB_LED_Set(MDRB_LED_PinAll, false);
   
  while (1)
  {    
    // Опрос нажатия кнопок
    if (MDRB_BntClicked_Up(false))
      LED_Flash(1);
    if (MDRB_BntClicked_Right(false))
      LED_Flash(2);
    if (MDRB_BntClicked_Down(false))
      LED_Flash(3);
    
  #if defined (MDRB_BTN_PIN_KEY5)   
    if (MDRB_BntClicked_Left(false))
      LED_Flash(4);
  #endif  

  #if defined (MDRB_BTN_PIN_KEY5) 
    if (MDRB_BntClicked_Select(false))
      LED_Flash(5);
  #endif
    
  #if defined (MDRB_BTN_PIN_KEY6)  
    if (MDRB_BntClicked_Back(false))
      LED_Flash(6);
  #endif
  }
}

void LED_Flash(uint32_t LedSel)
{
#ifndef ONLY_OneLED
  LED_SetOut(LedSel);
#else
  LED_SetOut(1);
#endif
  MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);
  LED_SetOut(0);
}



