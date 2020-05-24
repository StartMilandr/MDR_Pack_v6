#ifndef MDR_5600BB3_H
#define MDR_5600BB3_H

#include <MDR_SSP.h>
#include <MDR_PER_Clock.h>
#include <MDR_GPIO.h>
#include <MDR_Config.h>

#include <MDR_5600BB3_defs.h>


// Инициализация SPI для общения с 5600ВВ3
MDR_SSP_Type*  MDR_5600BB3_Init(const MDR_SSP_TypeEx *exSSPx, MDR_SSP_Rates spiRates, const MDR_SSP_CfgPinsGPIO *spiPins, MDR_PIN_PWR pinsPower);


//  Запись значения в адрес 5600ВВ3, (возвращает текущее значение по адресу)
__STATIC_INLINE uint8_t MDR_5600BB3_Write(MDR_SSP_Type *SSPx, MDR_5600BB3_Reg reg, uint8_t data)
{
	return (uint8_t)MDR_SSP_MasterTransfer(SSPx, ((uint8_t)reg << MDR_5600BB3_ADDR_POS) | data | MDR_5600BB3_WR_MSK);
}

//  Чтение значения из адреса 5600ВВ3
__STATIC_INLINE uint8_t MDR_5600BB3_Read(MDR_SSP_Type *SSPx, MDR_5600BB3_Reg reg)
{
	return (uint8_t)MDR_SSP_MasterTransfer(SSPx, (uint8_t)reg << MDR_5600BB3_ADDR_POS);
}


//  --------------   MAC Table Control  -------------------
typedef struct {
  uint8_t     srcMAC[6];  
	union {
		uint16_t  Ctrl;
		struct {
			uint16_t AgeCnt    : 12;   // Счётчик старения
			uint16_t isActive  : 1;    // Флаг активности записанной строки
			uint16_t srcPort   : 3;	   // Номер порта, от которого пришел фрейм с данным МАС адресом
		};
	};
} MDR_5600BB3_TableMAC_Item; 

uint16_t MDR_5600BB3_TableMAC_CalcIndex(uint8_t *MAC, uint8_t userSubIndex);

bool MDR_5600BB3_TableMAC_Write(MDR_SSP_Type *SSPx, uint16_t tableIndex, const MDR_5600BB3_TableMAC_Item *itemMac, uint16_t timeoutRdStatusCnt);
bool MDR_5600BB3_TableMAC_Read (MDR_SSP_Type *SSPx, uint16_t tableIndex, MDR_5600BB3_TableMAC_Item *itemMac, uint16_t timeoutRdStatusCnt);




#endif  //MDR_5600BB3_H

