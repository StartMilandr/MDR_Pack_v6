#ifndef MDR_1636RR52_H
#define MDR_1636RR52_H

#include <MDR_RST_Clock.h>
#include <MDR_SSP.h>
#include <MDR_PER_Clock.h>
#include <MDR_GPIO.h>
#include <MDR_Config.h>

#ifndef MDR_RR52_USE_READ_DBL
//  Выставить двойное чтение для высоких скоростей
  #define MDR_RR52_USE_READ_DBL     0
#endif

#ifndef MDR_RR52_CHECK_COMPLETED_COUNT_DEF
  #define MDR_RR52_CHECK_COMPLETED_COUNT_DEF     10
#endif

//==================  Инициализация задержек, необходимых по протоколу ======================

typedef struct {
  uint32_t        Erase_55ms;   //  SectorErase / ChipErase
  uint32_t        Program_45us; //  ByteProgram
  uint32_t        Reset_30us;   //  Reset
  uint32_t        CS_20ns;      //  CS - Задержка между активацией SPI и передачей данных
  uint32_t        RD_30ns;      //  CS - удержание между чтениями
  uint32_t        WR_1us;       //  CS - удержание между записями
} MDR_RR52_Delays;

void MDR_RR52_InitDelays(uint32_t CPU_FregHz);
void MDR_RR52_InitDelaysEx(const MDR_RR52_Delays *delays);
  
  

//==================  Инициализация и управление SPI ======================
// Параметры для инициализации работы с 1636РР52
typedef struct {
  //  SPI BitRate                               // BitRate = SSP_Clock / (PSR * (1 + SCR))
  uint8_t               DivSCR_0_255;           // 0 - 255, Serial Clock Rate
  uint8_t               DivPSR_2_254;           // 2 - 254, EVEN ONLY! Clock prescaller
  MDR_BRG_DIV_128       ClockBRG;               // SPI Делитель для частоты SSP_Clock
 
  //  Pins
  const MDR_SSP_CfgPinGPIO  *pPinCLK;
  const MDR_SSP_CfgPinGPIO  *pPinTX;
  const MDR_SSP_CfgPinGPIO  *pPinRX;
  const MDR_SSP_CfgPinGPIO  *pPinManualCS;
  MDR_PIN_PWR                pinsPower;
} MDR_1636RR52_Cfg;

//  Объект с параметрами необходимыми для работы функций. Возвращается функцией инициализации MDR_RR52_Init.
typedef struct {
  MDR_SSP_Type   *SSPx;
  MDR_PORT_Type  *CS_Port;
  uint32_t        CS_PinSel;
  uint32_t        CompletedTimeoutCount;
} MDR_1636RR52_Obj;

//  Инициализация SPI для работы с 1636РР52, с тактированием и пинами. 
MDR_1636RR52_Obj MDR_RR52_Init(const MDR_SSP_TypeEx *exSSPx, const MDR_1636RR52_Cfg *cfgRR52);

//  Отдельная инициализация пина CS на случай нескольких CS при одном SPI. Заполняет pObjRR52 настройками пина. 
//  Поле ObjRR52.SSPx проинициализировать самостоятельно!
void MDR_RR52_InitPinCS(const MDR_SSP_CfgPinGPIO  *pPinManualCS, MDR_PIN_PWR pinsPower, MDR_1636RR52_Obj *pObjRR52);


//  Вспомогательные функции
void MDR_RR52_CS_SetActive  (const MDR_1636RR52_Obj *objRR52);
void MDR_RR52_CS_SetInactive(const MDR_1636RR52_Obj *objRR52);


//  ==================    Функции работы с 1636РР52   ===========================
#define MDR_1636RR52_SectSize    0x10000UL //65K
#define MDR_1636RR52_SectCount   2

typedef enum {
  RR52_Sector1 = 0,
  RR52_Sector2 = 1,
} MDR_1636RR52_Sector;

__STATIC_INLINE  uint32_t MDR_RR52_SectToAddr(MDR_1636RR52_Sector sect) {return (uint32_t)sect * MDR_1636RR52_SectSize;}


#define MDR_RR52_CMD__READ_ARRAY_15MHz   0x03
#define MDR_RR52_CMD__READ_ARRAY         0x0B
#define MDR_RR52_CMD__SECTOR_ERASE       0xD8
#define MDR_RR52_CMD__CHIP_ERASE         0x60
#define MDR_RR52_CMD__BYTE_PROGRAM       0x02
#define MDR_RR52_CMD__WRITE_ENABLE       0x06
#define MDR_RR52_CMD__WRITE_DISABLE      0x04
#define MDR_RR52_CMD__PROTECT_SECTOR     0x36
#define MDR_RR52_CMD__UNPROTECT_SECTOR   0x39
#define MDR_RR52_CMD__READ_SECT_PROT_REG 0x3C
#define MDR_RR52_CMD__READ_STATUS_REG    0x05
#define MDR_RR52_CMD__WRITE_STATUS_REG   0x01
#define MDR_RR52_CMD__RESET              0xF0
#define MDR_RR52_CMD__RESET_CONFIRM      0xD0
#define MDR_RR52_CMD__READ_ID            0x9F


//  Функции обмена
void    MDR_RR52_SendComAndAddr(const MDR_1636RR52_Obj *objRR52, uint8_t command, uint32_t addr);
void    MDR_RR52_SendCom       (const MDR_1636RR52_Obj *objRR52, uint8_t command);
void    MDR_RR52_SendComAndData(const MDR_1636RR52_Obj *objRR52, uint8_t command, uint8_t data);
//uint8_t MDR_RR52_SendComRD     (const MDR_1636RR52_Obj *objRR52, uint8_t command);


//  -----------------   1636RR52 API  -----------------
uint16_t MDR_RR52_ReadID(const MDR_1636RR52_Obj *objRR52);

__STATIC_INLINE void MDR_RR52_WriteEnable    (const MDR_1636RR52_Obj *objRR52) {MDR_RR52_SendCom(objRR52, MDR_RR52_CMD__WRITE_ENABLE);}
__STATIC_INLINE void MDR_RR52_WriteDisable   (const MDR_1636RR52_Obj *objRR52) {MDR_RR52_SendCom(objRR52, MDR_RR52_CMD__WRITE_DISABLE);}


//  Sector protection
#define MDR_RR52_SECTOR_PROTECTION_OFF   0
#define MDR_RR52_SECTOR_PROTECTION_ON    0xFF

void    MDR_RR52_ProtectSector   (const MDR_1636RR52_Obj *objRR52, uint32_t addrSector);
void    MDR_RR52_UnprotectSector (const MDR_1636RR52_Obj *objRR52, uint32_t addrSector);
uint8_t MDR_RR52_ReadProtSectReg (const MDR_1636RR52_Obj *objRR52, uint32_t addrSector);


//  Status
typedef enum {
  RR52_Prot_AllSectorsOff = 0,
  RR52_Prot_SomeSectorsOn = 1,
  RR52_Prot_Reserved      = 2,
  RR52_Prot_AllSectorsOn  = 3,
} MDR_RR52_ProtStatus;


typedef struct {
      __IM  MDR_OnOff             Busy     : 1;    //  0 - ready, 1 - operation in progress
      __IM  MDR_OnOff             WEL      : 1;    //  0 - Write Disable, 1 - Write Enable
      __IM  MDR_RR52_ProtStatus   SWP      : 2;    //  Sector Protection
      __IM  uint8_t               Reserved : 1;
      __IM  MDR_OnOff             EPE      : 1;    //  0 - Ok, 1 - Fault of Clear/Write operation
      __IOM MDR_OnOff             RSTE     : 1;    //  0 - Reset command Disable, 1 - Reset command Enable
      __IOM MDR_OnOff             SPRL     : 1;    //  0 - Unblocked, 1 - Blocked: Protection registers
} MDR_RR52_STATUS_Bits;

#define MDR_RR52_STATUS__BUSY_Pos      (0UL)
#define MDR_RR52_STATUS__BUSY_Msk      (0x1UL)
#define MDR_RR52_STATUS__WEL_Pos       (1UL)
#define MDR_RR52_STATUS__WEL_Msk       (0x2UL)
#define MDR_RR52_STATUS__SWP_Pos       (2UL)
#define MDR_RR52_STATUS__SWP_Msk       (0xCUL)
#define MDR_RR52_STATUS__EPE_Pos       (5UL)
#define MDR_RR52_STATUS__EPE_Msk       (0x20UL)
#define MDR_RR52_STATUS__RSTE_Pos      (6UL)
#define MDR_RR52_STATUS__RSTE_Msk      (0x40UL)
#define MDR_RR52_STATUS__SPRL_Pos      (7UL)
#define MDR_RR52_STATUS__SPRL_Msk      (0x80UL)

typedef union {
    __IOM uint8_t         Value;
    MDR_RR52_STATUS_Bits  Bits;
} MDR_RR52_Status;  

void    MDR_RR52_WriteStatusReg(const MDR_1636RR52_Obj *objRR52, uint8_t status);
uint8_t MDR_RR52_ReadStatusReg (const MDR_1636RR52_Obj *objRR52);


void MDR_RR52_Reset(const MDR_1636RR52_Obj *objRR52);

                void MDR_RR52_ChipErase       (const MDR_1636RR52_Obj *objRR52);
                void MDR_RR52_SectorErase     (const MDR_1636RR52_Obj *objRR52, uint32_t addrSector);
__STATIC_INLINE void MDR_RR52_SectorEraseByInd(const MDR_1636RR52_Obj *objRR52, MDR_1636RR52_Sector sect) {MDR_RR52_SectorErase(objRR52, MDR_RR52_SectToAddr(sect));}

bool     MDR_RR52_ByteProgram (const MDR_1636RR52_Obj *objRR52, uint32_t addr, uint8_t Data);
uint32_t MDR_RR52_ProgramArray(const MDR_1636RR52_Obj *objRR52, uint32_t addr, uint32_t count, uint8_t *pData);

void MDR_RR52_ReadArray_15MHz (const MDR_1636RR52_Obj *objRR52, uint32_t addr, uint32_t count, uint8_t *pData);
void MDR_RR52_ReadArray       (const MDR_1636RR52_Obj *objRR52, uint32_t addr, uint32_t count, uint8_t *pData);

void MDR_RR52_Reset           (const MDR_1636RR52_Obj *objRR52);




#endif  //MDR_1636RR52_H

