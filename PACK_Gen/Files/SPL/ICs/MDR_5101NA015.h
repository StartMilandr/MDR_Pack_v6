#ifndef MDR_5101NA015_H
#define MDR_5101NA015_H

#include <MDR_SSP.h>
#include <MDR_PER_Clock.h>
#include <MDR_GPIO.h>
#include <MDR_Config.h>


#define MDR_5101NA015_VALUE_MIN   0x0000
#define MDR_5101NA015_VALUE_MAX   0xFFFF


//==================  Инициализация задержек, необходимых по протоколу ======================
#define MDR_5101NA015_CALIBR_DELAY_US   500
#define MDR_5101NA015_CS_DELAY_NS       10

typedef struct {
  uint32_t        TicksCalibr;      //  Время на калибровку
  uint32_t        TicksCS_10ns;     //  CS - Задержка между активацией SPI и передачей данных
} MDR_5101NA015_Delays;

void MDR_5101NA015_InitDelaysDef(uint32_t CPU_FregHz);
void MDR_5101NA015_InitDelays(const MDR_5101NA015_Delays *delays);  
  

//==================  Инициализация и управление SPI ======================
//  Скорости для чтения и записи в ЦАП
typedef union {
  uint32_t Rates;
  struct {
    //  Write SPI BitRate - max 30MHz (min 33ns)     // BitRate = SSP_Clock / (PSR * (1 + SCR))
    uint8_t                    WR_DivSCR_0_255;      // 0 - 255, Serial Clock Rate
    uint8_t                    WR_DivPSR_2_254;      // 2 - 254, EVEN ONLY! Clock prescaller
    //  Read SPI BitRate - max 2.5MHz (min 400ns)
    uint8_t                    RD_DivSCR_0_255;
    uint8_t                    RD_DivPSR_2_254;    
  };
} MDR_5101NA015_Rates;

// Параметры для инициализации работы с 5101NA015
typedef struct { 
  MDR_5101NA015_Rates        rates;  
  //  Pins
  const MDR_SSP_CfgPinGPIO  *pPinCLK;
  const MDR_SSP_CfgPinGPIO  *pPinTX;
  const MDR_SSP_CfgPinGPIO  *pPinRX;
  const MDR_SSP_CfgPinGPIO  *pPinManualCS;
  MDR_PIN_PWR                pinsPower;
} MDR_5101NA015_Cfg;


//  Объект с параметрами необходимыми для работы функций. Возвращается функцией инициализации MDR_5101NA015_Init.
typedef struct {
  MDR_SSP_Type       *SSPx;
  MDR_PORT_Type      *CS_Port;
  uint32_t            CS_PinSel;
//  uint32_t        CompletedTimeoutCount;
  
  MDR_5101NA015_Rates rates;
} MDR_5101NA015_Obj;

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop  
#endif

//  Инициализация SPI для работы с 5101NA015, с пинами. 
//  Предварительно включить SSP_Clock для SPI, например через - MDR_SSPex_SetSSPClock_InpPLLCPU(MDR_SSP1ex, MDR_Div128P_div1);
MDR_5101NA015_Obj MDR_5101NA015_Init(const MDR_SSP_TypeEx *exSSPx, const MDR_5101NA015_Cfg *cfgDAC);

//  Отдельная инициализация пина CS на случай нескольких CS при одном SPI. Заполняет pObjDAC настройками пина. 
//  Поле pObjDAC.SSPx проинициализировать самостоятельно!
void MDR_5101NA015_InitPinCS(const MDR_SSP_CfgPinGPIO  *pPinManualCS, MDR_PIN_PWR pinsPower, MDR_5101NA015_Obj *pObjDAC);


//  ==================    Функции работы с 5101NA015   ===========================
void MDR_5101NA015_WriteTransfer(const MDR_5101NA015_Obj *pObjDAC, uint8_t comID, uint16_t value);

#define MDR_5101NA015_CMD__SET_VALUE      0x00
#define MDR_5101NA015_CMD__STAND_BY       0x01
#define MDR_5101NA015_CMD__STAND_BY_100   0x02
#define MDR_5101NA015_CMD__STAND_BY_1     0x03
#define MDR_5101NA015_CMD__WR_OFFSET      0x04
#define MDR_5101NA015_CMD__WR_MIN         0x05
#define MDR_5101NA015_CMD__WR_CALIBR      0x08
#define MDR_5101NA015_CMD__WR_MEMT_START  0x10
#define MDR_5101NA015_CMD__WR_MEMT_END    0x17
#define MDR_5101NA015_CMD__WR_MEM_START   0x40
#define MDR_5101NA015_CMD__WR_MEM_END     0x7F

#define MDR_5101NA015_CMD__RD_ACC         0x81
#define MDR_5101NA015_CMD__RD_BAS_LSB     0x82
#define MDR_5101NA015_CMD__RD_BAS_MSB     0x83
#define MDR_5101NA015_CMD__RD_OFFSET      0x84
#define MDR_5101NA015_CMD__RD_MIN         0x85
#define MDR_5101NA015_CMD__RD_CALIBR      0x88
#define MDR_5101NA015_CMD__RD_MEMT_START  0x90
#define MDR_5101NA015_CMD__RD_MEMT_END    0x97
#define MDR_5101NA015_CMD__RD_MEM_START   0xC0
#define MDR_5101NA015_CMD__RD_MEM_END     0xFF

//  BAS         - 23 bit
//  Calibration - 16 bit
//  Offset      -  9 bit
//  DAC Calibt  -  9 bit
//  Mem, MemT, MemA, Acc, Min - 17 bit


//  DAC Calibration
#define MDR_5101NA015_VAL_CALIBR_RUN_DEF      0x0311
#define MDR_5101NA015_VAL_CALIBR_CLEAR_DEF    0x0312

#define MDR_5101NA015_VAL_CALIBR_OFFS_EN_MSK  0x0020

void MDR_5101NA015_RunCalibr(const MDR_5101NA015_Obj *pObjDAC, uint16_t calibrFlags);

__STATIC_INLINE void MDR_5101NA015_RunCalibrDef(const MDR_5101NA015_Obj *pObjDAC) 
{ MDR_5101NA015_RunCalibr(pObjDAC, MDR_5101NA015_VAL_CALIBR_RUN_DEF); }

__STATIC_INLINE void MDR_5101NA015_CalibrClear(const MDR_5101NA015_Obj *pObjDAC) 
{ MDR_5101NA015_RunCalibr(pObjDAC, MDR_5101NA015_VAL_CALIBR_CLEAR_DEF); }


//  DAC Set Output
__STATIC_INLINE void MDR_5101NA015_SetValue(const MDR_5101NA015_Obj *pObjDAC, uint16_t valueDAC) 
{ MDR_5101NA015_WriteTransfer(pObjDAC, MDR_5101NA015_CMD__SET_VALUE, valueDAC); }


//  ----------------    Read Operation  -------------------
// При чтении необходим режим SPH = 1, при записи SPH = 0.
// SPO = 1 в обоих случаях.
// Частота чтения значительно ниже частоты записи.
// Переход от режима записи к чтению и обратно реализован функциями - MDR_5101NA015_ReadEnter и MDR_5101NA015_ReadExit
// Между этими функциями можно вызывать несколько чтений функцией MDR_5101NA015_ReadTransfer

void MDR_5101NA015_ReadEnter(const MDR_5101NA015_Obj *pObjDAC);
uint32_t MDR_5101NA015_ReadTransfer(const MDR_5101NA015_Obj *pObjDAC, uint8_t comID);
void MDR_5101NA015_ReadExit(const MDR_5101NA015_Obj *pObjDAC);

//  В данной функции собраны все три функции для единичного чтения регистров
//    MDR_5101NA015_ReadEnter()
//    MDR_5101NA015_ReadTransfer()
//    MDR_5101NA015_ReadExit()
uint32_t MDR_5101NA015_Read(const MDR_5101NA015_Obj *pObjDAC, uint8_t comID);





#endif  //MDR_5101NA015_H

