#ifndef MDRB_SHOW_MESS_H
#define MDRB_SHOW_MESS_H

#include <stdbool.h>
#include <stdint.h>

//  Инициалиазация LCD экрана и/или UART_DBG для вывода информации
void MDR_ShowInit(bool useLCD, bool useUartDbg);
//  Переинициализация экрана после использования пинов LCD под выводы таймера
bool MDR_ShowRestore_IfConflTim(void);
//  Переинициализация экрана после использования пинов LCD под выводы светодиодов
bool MDR_ShowRestore_IfConflLED(void);

// Вывод строки
void MDR_ShowMessStr(char *mess, uint8_t lineInd);

// Вывод сообщения по ID (для 7-секционного экрана выводится номер ID вместо строки)
typedef enum {
  MESS__SIMPLE_FLASH,
  MESS__COUNT_TIM_CLOCK,
  MESS__COUNT_CASCADE,
  MESS__PULSE,
  MESS__PWM,
  MESS__PWM_DTG,
  MESS__PWM_ETRBRK,
  MESS__CAP_SIMPLEST,
  MESS__CAP_PERIOD,
  MESS__COUNT_CAP,
  MESS__COUNT_ETR,
} MDR_SHOW_MessID;
  
void MDR_ShowMess(MDR_SHOW_MessID messID);


//  ======  Получение команд от UART  ======
typedef enum {
  MDRB_ACT_NEXT_TEST,
  MDRB_ACT_CHANGE_MODE,
  MDRB_ACT_EXEC,
  //  do not use - for count only
  _MDRB_ACT_Count,
} MDRB_Action;

bool MDRB_NeedActon(MDRB_Action action);

#endif  //MDRB_SHOW_MESS_H


