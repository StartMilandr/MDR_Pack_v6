#ifndef MDR_CAN_H
#define MDR_CAN_H

// !!! ДРАЙВЕР НЕ РАБОЧИЙ, ЕЩЕ НИ РАЗУ НЕ ЗАПУСКАЛСЯ И НЕ ОТЛАЖИВАЛСЯ !!!

#include <MDR_Types.h>


#include <MDR_Config.h>
#include <MDR_CAN_defs.h>
#include <MDR_RST_Clock.h>
#include <MDR_PER_Clock.h>

#define MDR_CAN_BYTES_MAX 8

#define MDR_CAN_BufType  MDR_CAN_BUF_Type


typedef struct {
  uint32_t  DataLo;
  uint32_t  DataHi;
} MDR_CAN_Data;

typedef struct {
  MDR_CAN_Type*   CANx;
  // CAN_Clock and BRG
  MDR_PerClock_Cfg  CfgClock;
  //  IRQn
  IRQn_Type         CANx_IRQn;  
} MDR_CAN_TypeEx;

extern const MDR_CAN_TypeEx     _MDR_CAN1ex;
#define      MDR_CAN1ex       (&_MDR_CAN1ex)

//void MDR_CANex_SetCANClock(const MDR_CAN_TypeEx *CANex, MDR_Div128P divToClockCAN);
__STATIC_INLINE void MDR_CANex_SetCANClock(const MDR_CAN_TypeEx *CANex, MDR_Div128P divToClockCAN)
{
  MDR_PerClock_GateOpen(&CANex->CfgClock, divToClockCAN);
}


//  ----  CAN Timing  ----
typedef struct {
  MDR_CAN_BITTMNG_TQ    Delay_PSEG;         // = MDR_CAN_BITTMNG_2TQ,
  MDR_CAN_BITTMNG_TQ    Delay_SEG1;         // = MDR_CAN_BITTMNG_4TQ,
  MDR_CAN_BITTMNG_TQ    Delay_SEG2;         // = MDR_CAN_BITTMNG_3TQ,       // SEG2 <= PSEG + SEG1 !
  MDR_CAN_BITTMNG_SJW   SyncJumpWidth;      // = MDR_CAN_BITTMNG_SJW_2TQ,   // SJW < SEG2 !
  uint16_t              BaudRatePresc;      // = 3,                         // BRP = [CAN_Clock_Hz / ((1 + PSEG + SEG1 + SEG2) * SampleRate_Hz)] - 1 = 40M/(10*1M) - 1
  bool                  TrimpleSampling;    // = MDR_On    
} MDR_CAN_TimingCfg; 


void MDR_CAN_Init(MDR_CAN_Type *MDR_CANx, uint32_t regCtrl, MDR_CAN_TimingCfg *canTimeCfg);

__STATIC_INLINE void MDR_CAN_InitDef(MDR_CAN_Type *MDR_CANx, MDR_CAN_TimingCfg *canTimeCfg)
{
  MDR_CAN_Init(MDR_CANx, 0, canTimeCfg);
}

//  ----  CAN Buff RX-TX  ----

#define MDR_CAN_GET_BUFF(MDR_CAN, bufInd)    (MDR_CAN_BufType*)&(MDR_CAN->BUF_CON[bufInd])

typedef struct {
  uint8_t   dataCount;      // = COM_DATA_CNT,
  bool      isExtended;     // = COM_FRAME_EXT,
  bool      lowPrioity;     // = false
} MDR_CAN_BuffCfgTX;

void MDR_CANex_ClearBuffs(MDR_CAN_Type *MDR_CANx);

MDR_CAN_BufType* MDR_CAN_BuffInitTX(MDR_CAN_Type *MDR_CANx, uint32_t bufInd, uint32_t ID, MDR_CAN_BuffCfgTX *cfgTX);  
MDR_CAN_BufType* MDR_CAN_BuffInitRX(MDR_CAN_Type *MDR_CANx, uint32_t bufInd, bool enOverwrite, uint32_t filterMask, uint32_t ID);

__STATIC_INLINE  MDR_CAN_BufType* MDR_CAN_BuffInitRX_AnyID(MDR_CAN_Type *MDR_CANx, uint32_t bufInd, bool enOverwrite)
{
  return MDR_CAN_BuffInitRX(MDR_CANx, bufInd, enOverwrite, 0, 0);
}

void MDR_CAN_BuffDeInit(MDR_CAN_BufType* CAN_Buff);


void MDR_CAN_BuffSend(MDR_CAN_BufType* CAN_Buff, uint32_t dataLo, uint32_t dataHi);
void MDR_CAN_BuffSendEx(MDR_CAN_BufType* CAN_Buff, MDR_CAN_Data *bufData);
void MDR_CAN_BuffSendEx_ID(MDR_CAN_BufType* CAN_Buff, MDR_CAN_Data *bufData, uint32_t ID);

//  ----  CAN RTR  ----
typedef struct {
  uint32_t            ID;
  uint32_t            filterMask;
  MDR_CAN_BuffCfgTX   answerCfg;
} MDR_CAN_BuffCfgRTR; 


MDR_CAN_BufType* MDR_CAN_BuffInit_AnswerRTR(MDR_CAN_Type *MDR_CANx, uint32_t bufInd, MDR_CAN_BuffCfgRTR *cfgRTR, MDR_CAN_Data *bufData); 
MDR_CAN_BufType* MDR_CAN_BuffInit_RequestRTR(MDR_CAN_Type *MDR_CANx, uint32_t bufInd, uint32_t RTR_ID, bool isExtended, bool lowPrioity);




#endif // MDR_CAN_H

