#ifndef MDR_I2C_H
#define MDR_I2C_H

#include <MDR_Config.h>
#include <MDR_Types.h>
#include <MDR_I2C_defs.h>
#include <MDR_Funcs.h>
#include <MDR_GPIO.h>


//===================   I2C GPIO pins Init ==========================
//  Функция инициализации выводов GPIO в функции I2C
typedef struct {
  const MDR_GPIO_Port *portGPIO;
  uint32_t       pinIndex;
  MDR_PIN_FUNC   pinFunc;
} MDR_I2C_CfgPinGPIO;

//  Все пины кроме pPinCLK могут быть NULL и тогда они не будут проинициализированы.
//  Это на случай, если надо только принимать, или только посылать, или FSS не нужен.
typedef struct {
  const MDR_I2C_CfgPinGPIO *pPinSCL;  
  const MDR_I2C_CfgPinGPIO *pPinSDA;
} MDR_I2C_CfgPinsGPIO;

void MDR_I2C_InitPinsGPIO(const MDR_I2C_CfgPinsGPIO *pinsCfg, MDR_PIN_PWR pinsPower, bool pullUpPins);


//===================   I2C ==========================

//  Простейшая инициализация, минимальная производительность.
//  Делитель будет высчитан по формуле
//    F_SCL = HCLK /(5 * (DIV + 1))
//    DIV = HCLK / (F_SCL * 5) - 1;
//  Частота получается НЕ ТОЧНАЯ, но чуть меньше заданной.
//  При исползовании в формуле 6 (вместо 5) частота получается чуть больше заданной.
void MDR_I2C_Init(uint32_t freqHz, uint32_t freqCPU_Hz);
void MDR_I2C_InitWithIRQ(uint32_t freqHz, uint32_t freqCPU_Hz, bool activateNVIC, uint32_t priority);

//  Инициализация через структуру, средняя производительность
typedef struct {
  uint16_t      Clk_Div;
  MDR_I2C_Speed speedRange;
  MDR_OnOff     enableIRQ;
  
  bool          activateNVIC;
  uint32_t      priority;
} MDR_I2C_Cfg;

void MDR_I2C_InitEx(MDR_I2C_Cfg *cfg);

//  Инициализация через унифицированный регистр, минимальный объем, максимальная производительность.
void MDR_I2C_InitCfgReg(MDR_I2C_CfgReg *cfg, bool activateNVIC, uint32_t priority);

void MDR_I2C_ClearRegs(void);
void MDR_I2C_DeInit(void);


// -----------  Transfers Tacts ---------------
                bool MDR_I2C_StartTransfer(uint8_t addr_7bit, bool modeWrite);
                bool MDR_I2C_SendByte(uint8_t data);
                bool MDR_I2C_ReadByte(uint8_t *data, bool lastByte);
__STATIC_INLINE void MDR_I2C_StopTransfer(void) {MDR_I2C->CMD = MDR_I2C_CMD_Send_Stop_Msk;}


// --------------- Transfers  ---------------
#define  MDR_I2C_RESULT_ERROR_COUNT   0xFFFFFFFF

//  Функции возвращают количество переданных данных, при равенстве с заданным - успех.
//  Если количество данных задано 0, то при неуспехе возвращается MDR_I2C_RESULT_ERROR_COUNT
uint32_t MDR_I2C_TransferWrite(uint8_t addr_7bit, uint32_t count, uint8_t *pData);
uint32_t MDR_I2C_TransferRead (uint8_t addr_7bit, uint32_t count, uint8_t *pData);


//  --------------- Опрос статуса ---------------
__STATIC_INLINE bool MDR_I2C_CheckStatusFlagSet(uint32_t flag) {return (MDR_I2C->STA & flag);}

__STATIC_INLINE bool MDR_I2C_GetBusFree(void)     {return !MDR_I2C_CheckStatusFlagSet(MDR_I2C_STA_BUSY_Msk);}
__STATIC_INLINE bool MDR_I2C_GetAckOk(void)       {return !MDR_I2C_CheckStatusFlagSet(MDR_I2C_STA_RX_ACK_Msk);}
__STATIC_INLINE bool MDR_I2C_GetCollision(void)   {return  MDR_I2C_CheckStatusFlagSet(MDR_I2C_STA_Lost_ARB_Msk);}
__STATIC_INLINE bool MDR_I2C_GetTransfering(void) {return  MDR_I2C_CheckStatusFlagSet(MDR_I2C_STA_TR_Prog_Msk);}
__STATIC_INLINE bool MDR_I2C_GetEventActive(void) {return  MDR_I2C_CheckStatusFlagSet(MDR_I2C_STA_INT_Msk);}


//  --------------- Прерывания  ---------------
__STATIC_INLINE void MDR_I2C_EnableIRQ(void)  {MDR_I2C->CTR |=  MDR_I2C_CTR_EN_INT_Msk;}
__STATIC_INLINE void MDR_I2C_DisableIRQ(void) {MDR_I2C->CTR &= ~MDR_I2C_CTR_EN_INT_Msk;}

__STATIC_INLINE void MDR_I2C_ClearIRQ(void) {MDR_I2C->CMD |= MDR_I2C_CMD_CLR_INT_Msk;}


//======================    Реализация работы через IRQ    ===================
bool MDR_I2C_IRQ_TryStartTransfer(uint8_t addr_7bit, uint32_t count, uint8_t *pData, bool modeWrite, pVoidFunc_void stopCallBack);
void MDR_I2C_IRQ_HandlerProcess(void);
bool MDR_I2C_IRQ_GetCompleted(bool *success) ;


#endif // MDR_I2C_H

