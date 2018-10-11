#ifndef _MDRB_LCD_H
#define _MDRB_LCD_H

 
#include <MDR_GPIO.h>
#include <MDR_Funcs.h>

#include "MDRB_BoardSelect.h"

// Стандартные библиотеки языка Си
#include <string.h>
#include <stdio.h>


#ifndef LCD_IS_7SEG_DISPLAY
  //  ===== Display MT-12864J ======

  #define LCD_SCREEN_WIDTH    16   // Ширина дисплея (в символах 8x8)

  void MDRB_LCD_PutSymbol   (uint8_t symbol, uint8_t x, uint8_t y);                     // Вывод символа
  
  void MDRB_LCD_Print       (const char* string, uint8_t y);                            // Вывод строки  
  void MDRB_LCD_ScrollString(const char* string, uint8_t y, uint8_t shift);             // Горизональное перемещение строки. Необходимо менять shift.
  void MDRB_LCD_ScrollStringLeft(const char* inpString, uint8_t y, uint8_t strLength);  //  Автономное горизональное перемещение строки.
  
  void MDRB_LCD_PutImage    (const uint8_t* image, uint8_t top,    uint8_t left,        // Вывод изображения
                                                   uint8_t bottom, uint8_t right);
  
#else
  //  ===== Display MT-10T7 ======
  void MDRB_LCD_Print       (const char* string, uint8_t y);                            // Вывод строки    
  void MDRB_LCD_ScrollString(const char* string, uint8_t shift);                        // Горизональное перемещение строки. Необходимо менять shift.
  
  void MDRB_LCD_ScrollStringLeft(const char* inpString, uint8_t strLength);             //  Автономное горизональное перемещение строки.
  
  
  #define LCD_SCREEN_WIDTH    10
#endif

  //  Функции инициализации
void MDRB_LCD_Init(uint32_t CPU_FreqHz);
void MDRB_LCD_ChangeFreqCPU(uint32_t CPU_FreqHz);
void MDRB_LCD_Clear (void);
 
void MDRB_LCD_CapturePins(void);
void MDRB_LCD_ReleasePins(void);

// Функция сдвига строки, для отображения бегущей строки
void MDRB_LCD_ShiftString (const char* string, uint8_t shift, uint8_t screenWidth, char* outString);


//  Вариант использования
//void LCD_ShowDelay(uint32_t presc, uint32_t delay)
//{
//  static char message[64];
//  
//  sprintf(message , "PSC=%d  T=%d ", presc, delay);
//  MDRB_LCD_Print (message, 3);
//}


#endif // _MDRB_LCD_H
