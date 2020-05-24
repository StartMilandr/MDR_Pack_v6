#ifndef MDR_1923KX028_H
#define MDR_1923KX028_H

#include <MDR_Config.h>
#include <MDR_SSP.h>
#include <MDR_PER_Clock.h>
#include <MDR_GPIO.h>
#include <MDR_1923KX028_defs.h>

// Настройки SPI для общения с 1923KX028
typedef struct {
  //  SPI BitRate                               // BitRate = SSP_Clock / (PSR * (1 + SCR))
  uint8_t                   divSCR_0_255;       // 0 - 255, Serial Clock Rate
  uint8_t                   divPSR_2_254;       // 2 - 254, EVEN ONLY! Clock prescaller
 
  //  Pins
  const MDR_SSP_CfgPinGPIO  *pPinCLK;
  const MDR_SSP_CfgPinGPIO  *pPinTX;
  const MDR_SSP_CfgPinGPIO  *pPinRX;
  const MDR_SSP_CfgPinGPIO  *pPinManualCS;
  MDR_PIN_PWR                pinsPower;
  //  Delays
  uint32_t                   ticksDelayCS;      //  Задержка после выставления (перед снятием) активного CS.
} MDR_1923KX028_Cfg;


//  Объект с параметрами необходимыми для последующей работы функций. Возвращается функцией инициализации MDR_1923KX028_Init.
typedef struct {
  MDR_SSP_Type   *SSPx;
  MDR_PORT_Type  *CS_Port;
  uint32_t        CS_PinSel;
  uint32_t        ticksDelayCS;                 //  Задержка после выставления (перед снятием) активного CS.
} MDR_1923KX028_Obj;


// Инициализация SPI для общения с 1923KX028
MDR_1923KX028_Obj  MDR_1923KX028_Init(const MDR_SSP_TypeEx *exSSPx, MDR_1923KX028_Cfg *cfg);


//  Commands
#define MDR_1923KX028_CMD_AXI_RD    0x0B
#define MDR_1923KX028_CMD_AXI_WR    0x02
#define MDR_1923KX028_CMD_REG_RD    0x05
#define MDR_1923KX028_CMD_REG_WR    0x01
#define MDR_1923KX028_CMD_ID_RD     0x9F

//  Write unified function
void MDR_1923KX028_Write(MDR_1923KX028_Obj *objKX028, uint32_t addr24, uint32_t data, uint8_t cmd);


//  for debug:
void MDR_1923KX028_CS_SetActive(const MDR_1923KX028_Obj *objKX028);
void MDR_1923KX028_CS_SetInactive(const MDR_1923KX028_Obj *objKX028);

//  ----------------    AXI Bus control ------------------

//  Функции для последовательного чтения с некоторого адреса
//    _Begin: CS = 0, Write fromAddr
//    _Next : Read data consequently
//    _End  : CS = 1
            void     MDR_1923KX028_ReadAXI_Begin(MDR_1923KX028_Obj *objKX028, uint32_t fromAddr);
            uint32_t MDR_1923KX028_ReadAXI_Next(MDR_1923KX028_Obj *objKX028);
__STATIC_INLINE void MDR_1923KX028_ReadAXI_End(MDR_1923KX028_Obj *objKX028)
{
  MDR_1923KX028_CS_SetInactive(objKX028);
}

//  Одиночное чтение / запись
            uint32_t MDR_1923KX028_ReadAXI(MDR_1923KX028_Obj *objKX028, uint32_t addr);
__STATIC_INLINE void MDR_1923KX028_WriteAXI(MDR_1923KX028_Obj *objKX028, uint32_t addr, uint32_t data)
{
  MDR_1923KX028_Write(objKX028, addr, data, MDR_1923KX028_CMD_AXI_WR);
}


//  ----------------    Registers control ------------------
            uint32_t MDR_1923KX028_ReadReg (MDR_1923KX028_Obj *objKX028, uint32_t addr);
__STATIC_INLINE void MDR_1923KX028_WriteReg(MDR_1923KX028_Obj *objKX028, uint32_t addr, uint32_t data)
{ 
  MDR_1923KX028_Write(objKX028, addr, data, MDR_1923KX028_CMD_REG_WR);
}


//  ----------------    Read ID ------------------
uint16_t MDR_1923KX028_ReadID  (MDR_1923KX028_Obj *objKX028);




//=============================================================================
//==============    Функции для работы с ресурсами базиса   ===================
//===    Переопределить с CriticalSection при использовании с FreeRTOS  =======
//=============================================================================

typedef uint32_t (*FnReadAXI_t)(uint32_t addr);
typedef void     (*FnWriteAXI_t)(uint32_t addr, uint32_t data);
typedef void     (*FnReadBeginAXI_t)(uint32_t fromAddr);
typedef uint32_t (*FnReadNextAXI_t)(void);
typedef void     (*FnReadEndAXI_t)(void);

//  Обеспечить thread-safe:
//  Функции работы с Базисом заданы переменными,
//  для того чтобы их можно было перекрыть в многопоточных 
//  приложениях с использованием критических секций. (если требуется)
//  Изначально переменным назначены функции MDR_KX028_ReadAXI_def() и т.д.
extern FnReadAXI_t      MDR_KX028_ReadAXI;
extern FnWriteAXI_t     MDR_KX028_WriteAXI;
extern FnReadBeginAXI_t MDR_KX028_ReadBeginAXI;
extern FnReadNextAXI_t  MDR_KX028_ReadNextAXI;
extern FnReadEndAXI_t   MDR_KX028_ReadEndAXI;

//  Новые функции, в необходимой обертке если требуется.
typedef struct {
  FnReadAXI_t      funcReadAXI; 
  FnWriteAXI_t     funcWriteAXI;
  FnReadBeginAXI_t funcReadBeginAXI;
  FnReadNextAXI_t  funcReadNextAXI;
  FnReadEndAXI_t   funcReadEndAXI;
} MDR_KX028_CritSectFuncs;


//  Функция инициализации MDR_1923KX028_Init() с локальным значением MDR_1923KX028_Obj,
//  которое используется в функциях типа MDR_KX028_ReadAXI_def().
MDR_1923KX028_Obj* MDR_KX028_InitDef(const MDR_SSP_TypeEx *exSSPx, MDR_1923KX028_Cfg *cfg);
//  Тоже самое с возможностью перекрытия функций для обеспечения thread-safe
MDR_1923KX028_Obj* MDR_KX028_Init(const MDR_SSP_TypeEx *exSSPx, MDR_1923KX028_Cfg *cfg, MDR_KX028_CritSectFuncs *funcs);

//  Функции работы с 1923KX028 с локальным объектом MDR_1923KX028_Obj.
uint32_t MDR_KX028_ReadAXI_def(uint32_t addr);
void     MDR_KX028_WriteAXI_def(uint32_t addr, uint32_t data);
void     MDR_KX028_ReadBeginAXI_def(uint32_t fromAddr);
uint32_t MDR_KX028_ReadNextAXI_def(void);
void     MDR_KX028_ReadEndAXI_def(void);



#endif  //MDR_1923KX028_H

