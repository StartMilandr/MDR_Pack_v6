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

#ifdef LCD_HTD_B083_DISPLAY
  void ShowDisplay_VKx(void);
#endif

int main(void)
{  
  static uint8_t strLength;
  strLength = (uint8_t) strlen(message);
  
  MDRB_LCD_Init(HSI_FREQ_HZ); 
  
  //  Демонстрация дисплея электросчетчиков
#ifdef LCD_HTD_B083_DISPLAY
  ShowDisplay_VKx();
#endif  
  
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

#ifdef LCD_HTD_B083_DISPLAY
  void ShowDisplay_VKx(void)
  {  
    LCD_HTD_REG128 my_LCD_Reg128;
    
    //  Show All
    my_LCD_Reg128.LCD_REG1 = 0xFFFFFFFFUL;
    my_LCD_Reg128.LCD_REG2 = 0xFFFFFFFFUL;
    my_LCD_Reg128.LCD_REG3 = 0xFFFFFFFFUL;
    my_LCD_Reg128.LCD_REG4 = 0xFFFFFFFFUL;
    
    MDRB_HTD_RegApply(&my_LCD_Reg128);
    MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);  

    //  Clear All
    MDRB_HTD_RegClear(&my_LCD_Reg128);
    MDRB_HTD_RegApply(&my_LCD_Reg128);
    MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);
    
    //  Case 1
    my_LCD_Reg128.LCD_REG1_b.s1_T1_A = 1;
    my_LCD_Reg128.LCD_REG1_b.s2_T2_Ar = 1;
    my_LCD_Reg128.LCD_REG1_b.s5_T4_R = 1;
    my_LCD_Reg128.LCD_REG1_b.s6_T5_Rl = 1;
    my_LCD_Reg128.LCD_REG1_b.s32_PHASE = 1;
    
    MDRB_HTD_RegApply(&my_LCD_Reg128);
    MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);    
    
    //  Case 2  
    my_LCD_Reg128.LCD_REG2_b.s33_F1_A = 1;
    my_LCD_Reg128.LCD_REG2_b.s34_F2_B = 1;
    my_LCD_Reg128.LCD_REG2_b.s35_F3_C = 1;
    my_LCD_Reg128.LCD_REG2_b.s60_TIME = 1;
    my_LCD_Reg128.LCD_REG2_b.s61_DATE = 1;
    my_LCD_Reg128.LCD_REG2_b.s62_SYM = 1;  
    
    MDRB_HTD_RegApply(&my_LCD_Reg128);
    MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ); 
    
    //  Case 3
    my_LCD_Reg128.LCD_REG3_b.s90_MONTH = 1;
    my_LCD_Reg128.LCD_REG3_b.s89_K1 = 1;
    
    MDRB_HTD_RegApply(&my_LCD_Reg128);
    MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);
    
    //  Case 4
    my_LCD_Reg128.LCD_REG4_b.s98_Circle = 1;
    my_LCD_Reg128.LCD_REG4_b.s106_Battery = 1;
    my_LCD_Reg128.LCD_REG4_b.s108_Akkum = 1;
    my_LCD_Reg128.LCD_REG4_b.s109_Lock = 1;
    
    MDRB_HTD_RegApply(&my_LCD_Reg128);
    MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);    
    
    //  Clear all
    MDRB_LCD_Clear();
  }
#endif
