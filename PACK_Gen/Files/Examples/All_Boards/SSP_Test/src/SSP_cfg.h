#ifndef _SSP_CFG_H
#define _SSP_CFG_H

#include <MDR_SSP.h>
#include <MDRB_BoardSelect.h>

#if defined(USE_BOARD_VE93) || defined(USE_BOARD_VE4) || defined (USE_BOARD_VK214) || defined (USE_BOARD_VK234)
  // VE93 - На отл. плате НЕТ выводов GPIO для SSP2. 
  // VE4, VK214, VK234 - Только один SSP в микроконтроллере
  // Некуда подключать FSS и CLK, поэтому доступны только тесты LBM и TX-RX.  
  #define BDR_NO_SLAVE_SSP  
#endif

//  Количество слов передаваемых в тестах
#define TRANSFER_WORD_COUNT   0x10000UL

//  Выбранный для МК мастер и ведомый
extern const MDR_SSP_TypeEx *SSP_MASTER;
extern const MDR_SSP_TypeEx *SSP_SLAVE;

//  Настройки SSP
extern MDR_SSP_ConfigEx cfgSSPex;

//  Инициализация масок для захвата пинов под SSP и освобождения
void  Cfg_SSP_CapturePinsInit(MDR_PIN_PWR pinsPower);

void Cfg_SSP_Master_CapturePins(void);
void Cfg_SSP_Master_ReleasePins(void);
void Cfg_SSP_Slave_CapturePins(void);
void Cfg_SSP_Slave_ReleasePins(void);

//  Смена активного режима SPI - CPO и CPH
void Cfg_NextSPI_Mode(void);

//  Смена активного делителя скорости
void Cfg_NextDIV_PSR_2_254(void);

//  Смена количества бит в посылке
extern uint16_t Cfg_DataMaxValue;
void Cfg_NextDataBits(void);

//  ------  Смена активного протокола обмена SPI, SSI, Microwire  ------
void  Cfg_NextSSP_FrameFormat(void);
char *Cfg_getActiveFrameName(void);

//  ------  Индекс блока SSP - для отображения на LCD  --------------
uint32_t Cfg_GetIndexSPI(const MDR_SSP_TypeEx *exSSPx);

//  Строки на экране LCD
#define LCD_LINE_NAME     0
#define LCD_LINE_INIT     3
#define LCD_LINE_RESULT   5

//  ------ Перебор всех блоков SSP ---------------
extern const MDR_SSP_TypeEx  *SSP_List[];
extern uint8_t activeIndSSP;
uint8_t NextIndexSSP(void);

#endif  //_SSP_CFG_H

