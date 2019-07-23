#ifndef _MDR_PER_CLOCK_VE8x_H
#define _MDR_PER_CLOCK_VE8x_H

#include <MDR_Config.h>
#include <MDR_Funcs.h>
#include <MDR_Types.h>

//  Получение частоты "источника асинхронной частоты", т.е. до делителя
uint32_t MDR_GetClockHz_AsyncSrc(uint32_t freqSel, bool doUpdate);

//  Получение частот UART_Clock, SSP_CLock  и т.д.
uint32_t  MDR_GetFreqHz_PerAsync(MDR_PERCLK_ASYNC_REG asyncRegValue, bool doUpdate);
uint32_t  MDR_GetFreqHz_PerSync (MDR_PERCLK_SYNC_REG  syncRegValue, bool doUpdate);

//  Выбор источника частоты для UART_Clock, SSP_CLock
#define  MDR_SetClock_AsyncSelect(reg)  reg = MDR_MaskClrSet(reg, MDR_RST_ASYNC_CLK_SELECT_Msk, VAL2FLD_Pos(selClockSrc, MDR_RST_ASYNC_CLK_SELECT_Pos))

__STATIC_INLINE void MDR_SetClock_Uart1(MDR_RST_ASYNC_IN_SEL selClockSrc) { MDR_SetClock_AsyncSelect(MDR_CLOCK->UART1_CLK); }
__STATIC_INLINE void MDR_SetClock_Uart2(MDR_RST_ASYNC_IN_SEL selClockSrc) { MDR_SetClock_AsyncSelect(MDR_CLOCK->UART2_CLK); }


  
#endif  // _MDR_PER_CLOCK_VE8x_H

