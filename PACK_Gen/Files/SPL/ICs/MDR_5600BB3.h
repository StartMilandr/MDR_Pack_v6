#ifndef MDR_5600BB3_H
#define MDR_5600BB3_H

#include <MDR_SSP.h>
#include <MDR_PER_Clock.h>
#include <MDR_GPIO.h>
#include <MDR_Config.h>
#include <MDR_Funcs.h>

#include <MDR_5600BB3_defs.h>


// Инициализация SPI для общения с 5600ВВ3
MDR_SSP_Type*  MDR_5600BB3_Init(const MDR_SSP_TypeEx *exSSPx, MDR_SSP_Rates spiRates, const MDR_SSP_CfgPinsGPIO *spiPins, MDR_PIN_PWR pinsPower);


//  Запись значения в адрес 5600ВВ3, (возвращает текущее значение по адресу)
__STATIC_INLINE uint8_t MDR_5600BB3_Write(MDR_SSP_Type *SSPx, MDR_5600BB3_Reg reg, uint8_t data)
{  
	return (uint8_t)MDR_SSP_MasterTransfer(SSPx,  VAL2FLD(reg, MDR_5600BB3_ADDR) | data | MDR_5600BB3_WR_Msk);
}

//  Чтение значения из адреса 5600ВВ3
__STATIC_INLINE uint8_t MDR_5600BB3_Read(MDR_SSP_Type *SSPx, MDR_5600BB3_Reg reg)
{
	return (uint8_t)MDR_SSP_MasterTransfer(SSPx, VAL2FLD(reg, MDR_5600BB3_ADDR));
}

__STATIC_INLINE uint8_t MDR_5600BB3_WriteAddr(MDR_SSP_Type *SSPx, uint8_t addr, uint8_t data)
{  
	return (uint8_t)MDR_SSP_MasterTransfer(SSPx,  VAL2FLD(addr, MDR_5600BB3_ADDR) | data | MDR_5600BB3_WR_Msk);
}

__STATIC_INLINE uint8_t MDR_5600BB3_ReadAddr(MDR_SSP_Type *SSPx, uint8_t addr)
{
	return (uint8_t)MDR_SSP_MasterTransfer(SSPx, VAL2FLD(addr, MDR_5600BB3_ADDR));
}


//__STATIC_INLINE uint8_t MDR_5600BB3_WriteAddrDBG(MDR_SSP_Type *SSPx, uint8_t addr, uint8_t data)
//{  
//  uint16_t wrData = VAL2FLD(addr, MDR_5600BB3_ADDR) | data | MDR_5600BB3_WR_Msk;
//  printf("WR: %x\n", wrData);   
//	uint16_t out = MDR_SSP_MasterTransfer(SSPx, wrData);
//  printf("RD: %x\n", out);
//  return (uint8_t) out;   
//}

//__STATIC_INLINE uint8_t MDR_5600BB3_WriteDBG(MDR_SSP_Type *SSPx, MDR_5600BB3_Reg reg, uint8_t data)
//{  
//  uint16_t wrData = VAL2FLD(reg, MDR_5600BB3_ADDR) | data | MDR_5600BB3_WR_Msk;
//  printf("WR: %x\n", wrData);   
//	uint16_t out = MDR_SSP_MasterTransfer(SSPx, wrData);
//  printf("RD: %x\n", out);
//  return (uint8_t) out;  
//}


//__STATIC_INLINE uint8_t MDR_5600BB3_ReadDBG(MDR_SSP_Type *SSPx, MDR_5600BB3_Reg reg)
//{
//  uint16_t wrData = VAL2FLD(reg, MDR_5600BB3_ADDR);
//  printf("WR: %x\n", wrData);   
//	uint16_t out = MDR_SSP_MasterTransfer(SSPx, wrData);
//  printf("RD: %x\n", out);
//  return (uint8_t) out;
//}

//  --------------   MAC Table Control  -------------------
typedef __PACKED_STRUCT {
  uint8_t     srcMAC[6];  
	__PACKED_UNION {
		uint16_t  Ctrl;
		__PACKED_STRUCT {
			uint16_t AgeCnt    : 12;   // Счётчик старения
			uint16_t isActive  : 1;    // Флаг активности записанной строки
			uint16_t srcPort   : 3;	   // Номер порта, от которого пришел фрейм с данным МАС адресом
		};
	};
} MDR_5600BB3_TableMAC_Item; 

uint16_t MDR_5600BB3_TableMAC_CalcIndex(uint8_t *MAC, uint8_t userSubIndex);

bool MDR_5600BB3_TableMAC_Write(MDR_SSP_Type *SSPx, uint16_t tableIndex, const MDR_5600BB3_TableMAC_Item *itemMac, uint16_t timeoutRdStatusCnt);
bool MDR_5600BB3_TableMAC_Read (MDR_SSP_Type *SSPx, uint16_t tableIndex, MDR_5600BB3_TableMAC_Item *itemMac, uint16_t timeoutRdStatusCnt);


bool MDR_5600BB3_TableMAC_ReadRAW(MDR_SSP_Type *SSPx, uint16_t tableIndex, uint8_t *data, uint16_t timeoutRdStatusCnt);

//---------------- Полезные функции ------------------
__STATIC_INLINE void MDR_5600BB3_MII_SetFD(MDR_SSP_Type *SSPx)
{
  MDR_5600BB3_Write(SSPx, MDR_5600BB3_regFD_Mode5, MDR_5600BB3_regFD_Mode5_FD);
}

__STATIC_INLINE void MDR_5600BB3_MII_OldClearStop(MDR_SSP_Type *SSPx)
{
  MDR_5600BB3_Write(SSPx, MDR_5600BB3_regAgeCtrl0, MDR_5600BB3_AgeCtrl0_MAC_AGECLR_OFF);
}

//  Подобрано эмпирически для максимального значения счетчика старения 0xFFF (который стоит по умолчанию при включении)
#define MDR_5600BB3_DIV_PER_MIN  0x18
__STATIC_INLINE void MDR_5600BB3_SetAgeClearPeriod(MDR_SSP_Type *SSPx, uint8_t ageClearMinutes)
{
  MDR_5600BB3_Write(SSPx, MDR_5600BB3_regAgeCtrl2, ageClearMinutes * MDR_5600BB3_DIV_PER_MIN);
}



#endif  //MDR_5600BB3_H

