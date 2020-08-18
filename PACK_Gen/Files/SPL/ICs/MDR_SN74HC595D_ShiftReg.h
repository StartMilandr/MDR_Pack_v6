#ifndef _MDR_SN74HC595D_SHIFT_REG_H
#define _MDR_SN74HC595D_SHIFT_REG_H

#include <stdint.h>
#include <MDR_SN74HC595D_ShiftReg_Config.h>


// Инициализация пинов
void MDR_SN74HC595D_PinsInid(void);


// Управление выводом
#define MDR_SN74HC595D_OutEnable()      MDR_SN74HC595D_OE_0
#define MDR_SN74HC595D_OutDisable()     MDR_SN74HC595D_OE_1

void MDR_SN74HC595D_SetShiftValue(uint16_t value, uint32_t delayTicks);
void MDR_SN74HC595D_Clear(uint32_t delayTicks);


//  Типовые операции
__STATIC_INLINE void MDR_SN74HC595D_OutputZero(uint32_t delayTicks)
{
  MDR_SN74HC595D_OutDisable();
  MDR_SN74HC595D_Clear(delayTicks);
  MDR_SN74HC595D_OutEnable();
}

__STATIC_INLINE void MDR_SN74HC595D_OutputValue(uint16_t value, uint32_t delayTicks)
{
  MDR_SN74HC595D_OutDisable();
  MDR_SN74HC595D_SetShiftValue(value, delayTicks);
  MDR_SN74HC595D_OutEnable();
}


#endif	//_MDR_SN74HC595D_SHIFT_REG_H
