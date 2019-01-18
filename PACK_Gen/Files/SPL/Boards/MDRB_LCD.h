#ifndef _MDRB_LCD_H
#define _MDRB_LCD_H

 
#include <MDR_GPIO.h>
#include <MDR_Funcs.h>

#include "MDRB_BoardSelect.h"

// Стандартные библиотеки языка Си
#include <string.h>
#include <stdio.h>


//============    Функции, общие для всех экранов =================
//  Функции инициализации
void MDRB_LCD_Init(uint32_t CPU_FreqHz);
void MDRB_LCD_Clear(void);

//  Переключение необходимых пинов для работы с LCD и возврат в конфигурацию перед захватом.
void MDRB_LCD_CapturePins(void);
void MDRB_LCD_ReleasePins(void);

// Функция сдвига строки, для отображения бегущей строки
void MDRB_LCD_ShiftString (const char* string, uint8_t shift, uint8_t screenWidth, char* outString);


//============    7-ми секционный экран MT-10T7 на демоплатах 1986VE4 =================
#ifdef LCD_MT_10T7_DISPLAY

  #define LCD_IS_7SEG_DISPLAY
  #define LCD_SCREEN_WIDTH    10
  
  void MDRB_LCD_Print       (const char* string);                            // Вывод строки    
  void MDRB_LCD_ScrollString(const char* string, uint8_t shift);             // Горизональное перемещение строки. Необходимо менять shift.
  void MDRB_LCD_ScrollStringLeft(const char* inpString, uint8_t strLength);  //  Автономное горизональное перемещение строки.
  
  //  Пересчет задержек при смене частоты CPU
  void MDRB_LCD_ChangeFreqCPU(uint32_t CPU_FreqHz);

//============    11-ти секционный экран HTD-B083 на демоплатах 1986VK234 и трехфазных счетчиках "Милур"   ===========      
#elif defined (LCD_HTD_B083_DISPLAY)

  #define LCD_IS_7SEG_DISPLAY
  #define LCD_SCREEN_WIDTH    11  
  
  void MDRB_LCD_Print       (const char* string);                            // Вывод строки    
  void MDRB_LCD_ScrollString(const char* string, uint8_t shift);             // Горизональное перемещение строки. Необходимо менять shift.
  void MDRB_LCD_ScrollStringLeft(const char* inpString, uint8_t strLength);  //  Автономное горизональное перемещение строки.

  //  LCD HTD Specific control
  #include "MDRB_LCD_HTD_B083.h"
  
  //  Функции для работы с пользовательским регистром (переменной) типа LCD_HTD_REG128.
  //  Можно сконфигурировать сразу несколько регистров (переменных) и затем записывать их в LCD.
  //  Стирание всего регистра
  void MDRB_HTD_RegClear(LCD_HTD_REG128 *lcdReg);
  //  Стирание только цифровых индикаторов
  void MDRB_HTD_RegClearStr(LCD_HTD_REG128 *lcdReg);
  //  Запись цифровых индикаторов
  void MDRB_HTD_RegWriteStr(LCD_HTD_REG128 *lcdReg, const char* string);
  //  Вывод регистра в LCD экран - Show
  void MDRB_HTD_RegApply(LCD_HTD_REG128 *lcdReg);
  //  Вывод строки на цифровые индикаторы на LCD экране - Show
  void MDRB_HTD_RegPring(LCD_HTD_REG128 *lcdReg, const char* string);

  // Функции работы через глобальную переменную регистра - для упрощения вывода.
  extern LCD_HTD_REG128 _MDR_LCD_Reg128;
  
  //  Экран работает при всех доступных частотах при MDR_Delay(0) в качестве четверти такта
  #define _LCD_DELAY_TICK_DEF   0
  #define MDRB_LCD_ChangeFreqCPU(x)   UNUSED(x)
  
//============    8-ми секционный экран HTD-B083 на демоплатах 1986VK214 и однофазных счетчиках "Милур"   ===========      
#elif defined (LCD_XT13468PSPA_DISPLAY)

  #define LCD_IS_7SEG_DISPLAY
  #define LCD_SCREEN_WIDTH    8
  
  void MDRB_LCD_Print       (const char* string);                            // Вывод строки    
  void MDRB_LCD_ScrollString(const char* string, uint8_t shift);             // Горизональное перемещение строки. Необходимо менять shift.
  void MDRB_LCD_ScrollStringLeft(const char* inpString, uint8_t strLength);  //  Автономное горизональное перемещение строки.

  //  LCD XT13468PSPA Specific control
  #include "MDRB_LCD_XT13468PSPA.h"

  
  //  Функции для работы с пользовательской структурой (переменной) типа LCD_XT_DATA.
  //  На экран выводится основная структура. Альтернативная используется при организации мигания.
  typedef enum {
    LCD_XT_NUM1,
    LCD_XT_NUM2,
    LCD_XT_NUM3,
    LCD_XT_NUM4,
    LCD_XT_NUM5,
    LCD_XT_NUM6,
    LCD_XT_NUM7,
    LCD_XT_NUM8
  } MDRB_XT_NUM_Item;

  #define LCD_XT_NUM_HIGH   LCD_XT_NUM8

  //  Стирание всего регистра
  void MDRB_XT_DataClear(LCD_XT_DATA *lcdData);   
  //  Стирание только цифровых индикаторов  
  void MDRB_XT_DataClearStr(LCD_XT_DATA *lcdData);
  //  Стирание только одного цифрового индикатора
  void MDRB_XT_DataClearNUM(LCD_XT_DATA *lcdData, MDRB_XT_NUM_Item numItem);
  //  Запись символа в один индикатор
  static void MDRB_XT_AddChar(LCD_XT_DATA *lcdData, MDRB_XT_NUM_Item numItem, uint8_t symbol);
  //  Запись цифровых индикаторов
  void MDRB_XT_DataWriteStr(LCD_XT_DATA *lcdData, const char* string);
  
  //  Вывод регистра в LCD экран - Show
  void MDRB_XT_DataApply(LCD_XT_DATA *lcdData, MDR_OnOff toAlterMem);
  //  Вывод строки на цифровые индикаторы на LCD экране - Show
  void MDRB_XT_DataPring(LCD_XT_DATA *lcdData, const char* string, MDR_OnOff toAlterMem);

  extern LCD_XT_DATA _MDR_LCD_Data;
  
  

//============    Пиксельный экран MT-12864J на всех остальных демо-платах =================
#else

  #define LCD_SCREEN_WIDTH    16   // Ширина дисплея (в символах 8x8)

  void MDRB_LCD_PutSymbol   (uint8_t symbol, uint8_t x, uint8_t y);                     // Вывод символа

  void MDRB_LCD_ClearLine   (uint8_t y);                                                // Стирание строки
  void MDRB_LCD_Print       (const char* string, uint8_t y);                            // Вывод строки  
  void MDRB_LCD_ScrollString(const char* string, uint8_t y, uint8_t shift);             // Горизональное перемещение строки. Необходимо менять shift.
  void MDRB_LCD_ScrollStringLeft(const char* inpString, uint8_t y, uint8_t strLength);  //  Автономное горизональное перемещение строки.
  
  void MDRB_LCD_PutImage    (const uint8_t* image, uint8_t top,    uint8_t left,        // Вывод изображения
                                                   uint8_t bottom, uint8_t right);
  
  //  Пересчет задержек при смене частоты CPU
  void MDRB_LCD_ChangeFreqCPU(uint32_t CPU_FreqHz);  
#endif


//  Вариант вывода на экран
//void LCD_ShowDelay(uint32_t presc, uint32_t delay)
//{
//  static char message[64];
//  
//  sprintf(message , "PSC=%d  T=%d ", presc, delay);
//  MDRB_LCD_Print (message, 3);
//}


#endif // _MDRB_LCD_H
