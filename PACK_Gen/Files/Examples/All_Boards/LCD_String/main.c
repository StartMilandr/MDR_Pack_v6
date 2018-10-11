#include <MDR_GPIO.h>
#include <MDRB_LCD.h>

#define PERIOD_MS     300

#ifndef LCD_IS_7SEG_DISPLAY
  #define LCD_LINE_IND    5
  static char message[] = "  Hello World!  ";
#else
  //  Для LED экрана в 1986ВЕ4У
  static char message[] = "123456789 ABCDEF ";
#endif   


int main(void)
{  
  static uint8_t strLength;
  strLength = (uint8_t) strlen(message);
  
  MDRB_LCD_Init(HSI_FREQ_HZ); 
  
  while (1)
  {
  #ifndef LCD_IS_7SEG_DISPLAY      
    MDRB_LCD_ScrollStringLeft(message, LCD_LINE_IND, strLength);
  #else  
    MDRB_LCD_ScrollStringLeft(message, strLength);
  #endif   
    
    MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);  
  };
}

