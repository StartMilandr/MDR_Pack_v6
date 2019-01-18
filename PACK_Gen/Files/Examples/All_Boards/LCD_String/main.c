#include <MDR_GPIO.h>
#include <MDRB_LCD.h>

#ifndef LCD_IS_7SEG_DISPLAY
  #define PERIOD_MS     300
  #define LCD_LINE_IND    3
  static char message[] = "  Hello World!  ";
#else
  #define PERIOD_MS     500
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

