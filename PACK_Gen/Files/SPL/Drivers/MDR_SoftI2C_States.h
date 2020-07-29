#ifndef MDR_SOFT_I2C_STATES_H
#define MDR_SOFT_I2C_STATES_H

#include <MDR_Config.h>
#include <MDR_Types.h>
#include <MDR_GPIO.h>
//#include <MDR_Funcs.h>



////  Подавление warnings компилятора V6 о добавлении  "пустот" в структуры
//#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
//  #pragma clang diagnostic push
//  #pragma clang diagnostic ignored "-Wpadded"
//#endif

#define SET_SDA_0(i2cObj)     MDR_Port_ClearPins((i2cObj)->portSDA, (i2cObj)->pinSelSDA)
#define FREE_SDA_1(i2cObj)    MDR_Port_SetPins((i2cObj)->portSDA, (i2cObj)->pinSelSDA)
#define GET_SDA_1(i2cObj)    (bool)(MDR_Port_Get((i2cObj)->portSDA) & (i2cObj)->pinSelSDA)
#define GET_SDA_0            !GET_SDA_1

#define GET_CLK_1(i2cObj)    (bool)(MDR_Port_Get((i2cObj)->portCLK) & (i2cObj)->pinSelCLK)
#define GET_CLK_0            !GET_SDA_1

#define GET_SDA_ACK   GET_SDA_0
//#define GET_SDA_ACK   GET_SDA_1 // for debug!

#define SET_SDA_ACK   SET_SDA_0
#define CLR_SDA_ACK   FREE_SDA_1

#define SET_CLK_0(i2cObj)     MDR_Port_ClearPins((i2cObj)->portCLK, (i2cObj)->pinSelCLK)
#define FREE_CLK_1(i2cObj)    MDR_Port_SetPins((i2cObj)->portCLK, (i2cObj)->pinSelCLK)


//===================   Soft I2C Master  ====================
typedef bool (*pProcessFuncI2C)(void *, bool);
typedef void (*pOnEventI2C_f)(void *);

#define MDR_I2C_RD_Msk    1

#define MDR_I2Cs_BIT_CNT  8
#define uintI2C_t         uint8_t

typedef struct {
  // Data Array for transfer
  uint8_t         dataCnt;
  uintI2C_t       *pData;  
} MDR_I2Cst_pData;

typedef struct {
  // User Stop Handle
  const void      *timerEx;
  pOnEventI2C_f    TimerEventsStart;
  pOnEventI2C_f    TimerEventsStop;
  uint8_t          addr_7bit;
  uint8_t          timTact;
  // Status
  bool             started;
  bool             writeMode;
  // Data Array for transfer
  uint8_t          dataCnt;
  uintI2C_t       *pData;
  uint8_t          dataInd;  
  //  Active Byte Transfer
  uint8_t          bitInd;
  uintI2C_t        activeByte;  
  bool             ackOk;
  pProcessFuncI2C  ProcessFunc;
  // GPIO - SDA, CLK
  MDR_PORT_Type   *portSDA;
  uint32_t         pinSelSDA;
  MDR_PORT_Type   *portCLK;
  uint32_t         pinSelCLK;  
  //  Buff for RegRead - set NULL for simple write and read transfer
  MDR_I2Cst_pData *pRegValues;
} MDR_I2Cst_MasterObj;


                void MDR_I2Cs_MasterStart(MDR_I2Cst_MasterObj *i2cObj, bool writeMode);
__STATIC_INLINE bool MDR_I2Cs_MasterProcessCompleted(MDR_I2Cst_MasterObj *i2cObj, bool isClkDown)
{
  if (i2cObj->started)
    return i2cObj->ProcessFunc(i2cObj, isClkDown);
  else
    return true;
}




//===================   Soft I2C Slave  ====================
typedef bool (*pOnCheckAddrI2C_f)(uint8_t addr_7bit, bool isWriteMode, bool restarted, uintI2C_t  **buff,  uint8_t *buffLen);

typedef struct {
  // Status
  bool                started;
  bool                reStarted;
  // Data Array for transfer
  uint8_t             dataLen; 
  uintI2C_t          *pData;
  uint8_t             dataInd;  
  //  Active Byte Transfer
  uint8_t             bitInd;
  uintI2C_t           activeByte;  
  bool                ackOk;
  pProcessFuncI2C     ProcessFunc;
  // GPIO - SDA
  MDR_PORT_Type      *portSDA;
  uint32_t            pinSelSDA;
  MDR_PORT_Type      *portCLK;
  uint32_t            pinSelCLK;
  // SDA PinFunc control. Uses for switch SDA to Port for set ACK
  MDR_GPIO_PinFuncMasks  pinFuncMasks;
  // slave Fields
  bool                addrMatch;
  bool                isWriteTransf;
  uint8_t             transfDataCnt; 
  //  CallBacks for user:
  const void         *timerEx;
  uint32_t            eventFallCLK;
  uint32_t            eventRiseCLK;
  uint32_t            eventFallSDA;
  uint32_t            eventRiseSDA;  
  pOnCheckAddrI2C_f   OnCheckAddr;
  pOnEventI2C_f       OnCompleted;
} MDR_I2Cst_SlaveObj;


void MDR_I2Cs_SlaveStart(MDR_I2Cst_SlaveObj *i2cObj);
void MDR_I2Cs_SlaveStop(MDR_I2Cst_SlaveObj *i2cObj);

__STATIC_INLINE bool MDR_I2Cs_SlaveProcessCompleted(MDR_I2Cst_SlaveObj *i2cObj, bool isClkDown)
{
  if (i2cObj->started)
    return i2cObj->ProcessFunc(i2cObj, isClkDown);
  else
    return true;
}



//#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
//  #pragma clang diagnostic pop  
//#endif




#endif // MDR_SOFT_I2C_STATES_H

