#include <MDR_GPIO.h>
#include <MDRB_LCD.h>

#define PERIOD_MS     500
static char message[] = "123456789 ABCDEF ";

void ShowDisplay_VK214(void);

int main(void)
{  
  static uint8_t strLength;
  strLength = (uint8_t) strlen(message);

  MDR_DebugerProtectDelay();
  
  MDRB_LCD_Init(HSI_FREQ_HZ); 
  
  //  Демонстрация дисплея электросчетчиков
  ShowDisplay_VK214();
  
  while (1)
  {
    MDRB_LCD_ScrollStringLeft(message, strLength);
    
    MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);  
  }
}

void ShowDisplay_VK214(void)
{  
  LCD_XT_DATA my_LCD_DATA;
  
  //  Show All
  my_LCD_DATA.LCD_ROW1 = 0xFFFFFFFFUL;
  my_LCD_DATA.LCD_ROW2 = 0xFFFFFFFFUL;
  my_LCD_DATA.LCD_ROW3 = 0xFFFFFFFFUL;
  my_LCD_DATA.LCD_ROW4 = 0xFFFFFFFFUL;
  
  MDRB_XT_DataApply(&my_LCD_DATA, MDR_Off);
  MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);  

  //  Clear Some NUMs
  MDRB_XT_DataClearNUM(&my_LCD_DATA, LCD_XT_NUM1);
  MDRB_XT_DataClearNUM(&my_LCD_DATA, LCD_XT_NUM3);
  MDRB_XT_DataClearNUM(&my_LCD_DATA, LCD_XT_NUM5);
  MDRB_XT_DataClearNUM(&my_LCD_DATA, LCD_XT_NUM7);
  MDRB_XT_DataApply(&my_LCD_DATA, MDR_Off);
  MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);    
  
  //  Clear NUMs
  MDRB_XT_DataClearStr(&my_LCD_DATA);
  MDRB_XT_DataApply(&my_LCD_DATA, MDR_Off);
  MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);  
  
  //  Apply Data to Alter Memory - without NUMs
  MDRB_XT_DataApply(&my_LCD_DATA, MDR_On);
  //  Apply Sting to Base Memory
  MDRB_XT_DataWriteStr(&my_LCD_DATA, "12345678");
  MDRB_XT_DataApply(&my_LCD_DATA, MDR_Off);

  //  Blinky to Off
  MDR_LCD_BlinkyStart(MDR_LCD_Blink_1Hz, MDR_Off);
  MDR_Delay_ms(4000, HSI_FREQ_HZ);
  //  Blinky to AlterMem
  MDR_LCD_BlinkyStart(MDR_LCD_Blink_2Hz, MDR_On);
  MDR_Delay_ms(4000, HSI_FREQ_HZ);  
  //  Blinky Off
  MDR_LCD_BlinkyStop();

  //  Clear All
  MDRB_XT_DataClear(&my_LCD_DATA);
  MDRB_XT_DataApply(&my_LCD_DATA, MDR_Off);
  MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);
  
  //  Case 1
  my_LCD_DATA.LCD_ROW1_b.s0_Reverse = 1;
  my_LCD_DATA.LCD_ROW1_b.s18_var_k = 1;
  my_LCD_DATA.LCD_ROW1_b.s19_A_plus = 1;
  my_LCD_DATA.LCD_ROW1_b.s1_Tar_1 = 1;
  my_LCD_DATA.LCD_ROW1_b.s20_W_k = 1;
  my_LCD_DATA.LCD_ROW1_b.s21_VA_A = 1;
  my_LCD_DATA.LCD_ROW1_b.s22_Circ_1 = 1;
  my_LCD_DATA.LCD_ROW1_b.s23_Num7_dot = 1;
  
  MDRB_XT_DataApply(&my_LCD_DATA, MDR_Off);
  MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);    
  
  //  Case 2
  my_LCD_DATA.LCD_ROW1 = 0;
  my_LCD_DATA.LCD_ROW2_b.s0_Tarif = 1;
  my_LCD_DATA.LCD_ROW2_b.s1_Tar_2 = 1;
  my_LCD_DATA.LCD_ROW2_b.s18_var_h = 1;
  my_LCD_DATA.LCD_ROW2_b.s19_A_minus = 1;
  my_LCD_DATA.LCD_ROW2_b.s20_VA_V = 1;
  my_LCD_DATA.LCD_ROW2_b.s21_var = 1;
  my_LCD_DATA.LCD_ROW2_b.s22_Circ_2 = 1;
  my_LCD_DATA.LCD_ROW2_b.s23_Lock = 1;   
  
  MDRB_XT_DataApply(&my_LCD_DATA, MDR_Off);
  MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);    
  
  //  Case 3
  my_LCD_DATA.LCD_ROW2 = 0;
  my_LCD_DATA.LCD_ROW3_b.s0_In = 1;
  my_LCD_DATA.LCD_ROW3_b.s1_Tar_3 = 1;
  my_LCD_DATA.LCD_ROW3_b.s18_Data = 1;
  my_LCD_DATA.LCD_ROW3_b.s19_R_Plus = 1;
  my_LCD_DATA.LCD_ROW3_b.s20_W = 1;
  my_LCD_DATA.LCD_ROW3_b.s21_W_h = 1;
  my_LCD_DATA.LCD_ROW3_b.s22_Circ_3 = 1;
  my_LCD_DATA.LCD_ROW3_b.s23_Battery = 1;   
    
  MDRB_XT_DataApply(&my_LCD_DATA, MDR_Off);
  MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);   
  
  //  Case 4
  my_LCD_DATA.LCD_ROW3 = 0;
  my_LCD_DATA.LCD_ROW4_b.s0_Lambda = 1;
  my_LCD_DATA.LCD_ROW4_b.s1_Tar_4 = 1;
  my_LCD_DATA.LCD_ROW4_b.s3_Plus_H = 1;
  my_LCD_DATA.LCD_ROW4_b.s19_R_Minus = 1;
  my_LCD_DATA.LCD_ROW4_b.s20_VA_k = 1;
  my_LCD_DATA.LCD_ROW4_b.s21_Hz = 1;
  my_LCD_DATA.LCD_ROW4_b.s22_Circ_4 = 1;
  my_LCD_DATA.LCD_ROW4_b.s23_Plus_V = 1;       
    
  MDRB_XT_DataApply(&my_LCD_DATA, MDR_Off);
  MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);   
   
  //  Clear all
  MDRB_LCD_Clear();
}
