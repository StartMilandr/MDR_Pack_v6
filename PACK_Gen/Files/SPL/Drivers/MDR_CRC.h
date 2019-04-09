#ifndef MDR_CRC_H
#define MDR_CRC_H

#include <MDR_Config.h>
#include <MDR_Types.h>
#include <MDR_Funcs.h>

//  Инициализация модуля с включением тактирования.
void MDR_CRC_Init(MDR_CRC_CfgReg cfg, uint16_t polinomBitSel);

//  Аналогичная инициализация, но без включения тактирования.
void MDR_CRC_ReInit(MDR_CRC_CfgReg cfg, uint16_t polinomBitSel);
//  Выключение блока
void MDR_CRC_DeInit(void);

__STATIC_INLINE bool MDR_CRC_CheckStatusFlagSet(uint32_t flag) {return (MDR_CRC->STAT & flag);}

__STATIC_INLINE bool MDR_CRC_GetCompleted(void)     {return MDR_CRC_CheckStatusFlagSet(MDR_CRC_STAT_ConvComp_Msk);}
__STATIC_INLINE bool MDR_CRC_GetFIFO_Full(void)     {return MDR_CRC_CheckStatusFlagSet(MDR_CRC_STAT_FIFO_Full_Msk);}
__STATIC_INLINE bool MDR_CRC_GetFIFO_Empty(void)    {return MDR_CRC_CheckStatusFlagSet(MDR_CRC_STAT_FIFO_Empty_Msk);}
__STATIC_INLINE bool MDR_CRC_GetFIFO_Over(void)     {return MDR_CRC_CheckStatusFlagSet(MDR_CRC_STAT_FIFO_Over_Msk);}

__STATIC_INLINE void MDR_CRC_ClearFIFO_Over(void)   {MDR_CRC->STAT |= MDR_CRC_STAT_FIFO_Over_Msk;}
__STATIC_INLINE void MDR_CRC_EnableDMA(void)        {MDR_CRC->CTRL |=  MDR_CRC_CTRL_DMA_En_Msk;}
__STATIC_INLINE void MDR_CRC_DisableDMA(void)       {MDR_CRC->CTRL &= ~MDR_CRC_CTRL_DMA_En_Msk;}

uint16_t MDR_CRC_Calc(uint16_t startValue, uint32_t count,  uint8_t  *data);

//  Не тестировались
//uint16_t MDR_CRC_CalcCRC_D16(uint16_t startValue, uint32_t count, uint16_t *data);
//uint16_t MDR_CRC_CalcCRC_D32(uint16_t startValue, uint32_t count, uint32_t *data);



#endif // MDR_CRC_H

