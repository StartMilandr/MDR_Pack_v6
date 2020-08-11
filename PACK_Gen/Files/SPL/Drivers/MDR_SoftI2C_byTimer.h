#ifndef MDR_SOFT_I2C_BY_TIMER_H
#define MDR_SOFT_I2C_BY_TIMER_H

#include <MDR_Config.h>
#include <MDR_Types.h>
#include <MDR_Funcs.h>
#include <MDR_GPIO.h>
#include <MDR_Timer.h>
#include <MDR_SoftI2C_States.h>


////  Подавление warnings компилятора V6 о добавлении  "пустот" в структуры
//#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
//  #pragma clang diagnostic push
//  #pragma clang diagnostic ignored "-Wpadded"
//#endif

//===================   I2C GPIO pins Init ==========================
//  Функция инициализации выводов GPIO в функции I2C
typedef struct {
  const MDR_GPIO_Port *portGPIO;
  uint32_t       pinIndex;
  MDR_PIN_FUNC   pinFunc;
} MDR_I2C_CfgPinGPIO;


typedef struct {
  const MDR_I2C_CfgPinGPIO *pPinSCL;  
  const MDR_I2C_CfgPinGPIO *pPinSDA;
} MDR_I2C_CfgPinsGPIO;


typedef struct {
  //  Timer
  const MDR_TIMER_TypeEx    *timerEx;
  MDR_TIMER_CH_Type 	      *timerCh_PWM;
  MDR_Div128P                timClockBRG;
  uint16_t                   timClockPSG;
  uint_tim                   timPeriod;
  //  Pins
  const MDR_I2C_CfgPinsGPIO *pinsCfg;
  MDR_PIN_PWR                pinsPower;
  bool                       pullUpPins;
} MDR_I2Cs_MasterInitCfg;

//  CLK генерируется режимом ШИМ канала таймера. SDA программно.
MDR_I2Cst_MasterObj MDR_I2Cst_InitMasterPWM(MDR_I2Cs_MasterInitCfg *cfgI2C);
//  CLK генерируется программно, по периоду таймера. SDA программно.
MDR_I2Cst_MasterObj MDR_I2Cst_InitMasterSoft(MDR_I2Cs_MasterInitCfg *cfgI2C);

// Обработчик, вызывать в прерывании таймера
void MDR_I2Cst_MasterHandlerIRQ_PWM(MDR_I2Cst_MasterObj *i2cObj);
void MDR_I2Cst_MasterHandlerIRQ_Soft(MDR_I2Cst_MasterObj *i2cObj);

void MDR_I2Cst_MasterStartWrite(MDR_I2Cst_MasterObj    *i2cObj, uint8_t addr_7bit, uint8_t *data, uint8_t dataLen);
void MDR_I2Cst_MasterStartRead(MDR_I2Cst_MasterObj     *i2cObj, uint8_t addr_7bit, uint8_t *data, uint8_t dataLen);
//void MDR_I2Cst_MasterStartReadRegs(MDR_I2Cst_MasterObj *i2cObj, uint8_t addr_7bit, uint8_t *wrData, uint8_t wrDataLen, MDR_I2Cst_pData *pRegValues);
void MDR_I2Cst_MasterStartReadRegs(MDR_I2Cst_MasterObj *i2cObj, uint8_t addr_7bit, uint8_t *wrData, uint8_t wrDataLen, uint8_t *rdData, uint8_t rdDataLen, bool byRestart);

__STATIC_INLINE bool MDR_I2Cst_MasterGetStarted(MDR_I2Cst_MasterObj *i2cObj) { return i2cObj->started; }
__STATIC_INLINE bool MDR_I2Cst_MasterGetCompleted(MDR_I2Cst_MasterObj *i2cObj) { return !i2cObj->started; }



//================================   I2C Soft SLAVE   ================================
typedef struct {
  MDR_TIMER_CH_Type 	      *timerCh;
  uint32_t                   selIRQ_CCR_Rise;
  uint32_t                   selIRQ_CCR1_Fall;
  MDR_TIM_FLTR               filter;
} MDR_I2Cs_TimCapCfg;

typedef struct {
  //  Timer
  const MDR_TIMER_TypeEx    *timerEx;
  //  Timer Capture
  MDR_I2Cs_TimCapCfg         timCapCh_CLK;
  MDR_I2Cs_TimCapCfg         timCapCh_SDA;
  //  Timer "SampleRate"
  MDR_Div128P                timClockBRG;
  uint16_t                   timClockPSG;
  //  Pins
  const MDR_I2C_CfgPinsGPIO *pinsCfg;
  MDR_PIN_PWR                pinsPower;
  bool                       pullUpPins;
  //  callbasks
  pOnCheckAddrI2C_f          OnCheckAddr;
  pOnEventI2C_f              OnCompleted;
} MDR_I2Cs_InitSlaveCfg;


MDR_I2Cst_SlaveObj MDR_I2Cst_InitSlave(MDR_I2Cs_InitSlaveCfg *cfgI2C);
__STATIC_INLINE void MDR_I2Cst_StartSlave(MDR_I2Cst_SlaveObj *cfgI2C) { MDR_Timer_Start(cfgI2C->timerEx); }
__STATIC_INLINE void MDR_I2Cst_StopSlave(MDR_I2Cst_SlaveObj *cfgI2C)  { MDR_Timer_Stop(cfgI2C->timerEx); }

void MDR_I2Cst_SlaveHandlerIRQ(MDR_I2Cst_SlaveObj *i2cObj);


//  ======  Чтение данных по внутреннему адресу устройства (часто используется) ======
void MDR_I2C_StartReadAddrData(MDR_I2Cst_MasterObj *i2cObj, uint8_t addr, uint8_t *rdAddr, uint8_t rdCount, uint8_t *rdData, bool byRestart);




#endif // MDR_SOFT_I2C_BY_TIMER_H

