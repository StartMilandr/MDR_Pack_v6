#ifndef _MDRB_UART_DEBUG_H
#define _MDRB_UART_DEBUG_H

#include <MDRB_BoardSelect.h>
#include <MDR_UART.h>

extern const MDR_UART_TypeEx * UART_DBG;

// Параметр isCPUbyPLL задает тактируется ли ядро через PLL или напрямую от источника частоты.
// Это важно для 1986ВЕ4У, 1986ВК214, ВК1986ВК234 где источник частоты для UART_Clock выбирается мультиплексором PER1_C2
// Для остальных МК значение этого параметра не важно.

// Простейшая настройка UART_DBG для выводы сообщений наружу, RX (прием) выключен  
void MDR_UART_DBG_Init(bool isCPUbyPLL);

// Простейшая настройка UART_DBG с опциональным разрешением RX
void MDR_UART_DBG_InitEx(uint32_t baudRate, bool isCPUbyPLL, bool RX_Enable);

//  Настройка UART_DBG с заданием конфигурации
void MDR_UART_DBG_InitCfg(MDR_UART_Cfg *cfgUART, uint32_t baudRate, bool isCPUbyPLL);

//  Настройка UART_DBG с разрешением прерываний
void MDR_UART_DBG_InitIrq(uint32_t baudRate, bool isCPUbyPLL, uint32_t selEvents, MDR_UART_EventFIFO levelFIFO);

//  Настройка UART_DBG для приема команд снаружи - по прерыванию таймаута RT. Количество байт в команде не должно превышать размера буфера - 16 байт!!!
//  В прерывании по RT команды вычитывать полностью.
__STATIC_INLINE
void MDR_UART_DBG_InitIrqRT(uint32_t baudRate, bool isCPUbyPLL) { MDR_UART_DBG_InitIrq(baudRate, isCPUbyPLL, MDR_UART_EFL_RT, UART_FIFO_14); }

//  Выключение блока
void MDR_UART_DBG_Finit(void);
//  Смена скорости
void MDR_UART_DBG_ChangeRate(uint32_t baudRate);

//  Альтернативная посылка данных, основная через printf()
bool MDR_UART_DBG_TrySend(char data);


//  Подача CPU_Clock на UART_Clock 
void MDR_UART_DBG_SetClockCPU(bool isCPUbyPLL);
//  Настройка по UART_ClockHz
void MDR_UART_DBG_InitByClock(MDR_UART_Cfg *cfgUART, uint32_t baudRate, uint32_t UART_ClockHz);
//  Тоже самое с прерываниями
void MDR_UART_DBG_InitByClockIrq(uint32_t baudRate, uint32_t UART_ClockHz, uint32_t selEvents, MDR_UART_EventFIFO levelFIFO);

#endif  //_MDRB_UART_DEBUG_H

