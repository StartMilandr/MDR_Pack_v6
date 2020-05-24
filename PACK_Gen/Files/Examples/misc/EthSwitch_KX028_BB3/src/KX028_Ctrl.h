#ifndef KX028_CTRL_H
#define KX028_CTRL_H

#include <stdint.h>
#include <MDR_1923KX028.h>

// Инициализация SPI
void KX028_SPI_Init(uint32_t freqCPU_Hz);

//  Чтение пинов MODE
uint32_t KX028_GetModePins(void);

__STATIC_INLINE MDR_1923KX028_Mode KX028_GetMode(void)
{
  return (MDR_1923KX028_Mode)KX028_GetModePins();
}

#endif
