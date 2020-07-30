#include <MDR_SoftI2C_byTimer.h>
#include <MDR_SoftI2C_States.h>


//===================   I2C GPIO pins Init ==========================
static void MDR_I2Cs_InitPinsGPIO(const MDR_I2C_CfgPinsGPIO *pinsCfg, MDR_PIN_PWR pinsPower, bool pullUpPins)
{
  MDR_PinDig_GroupPinCfg pinGroupCfg;
  uint32_t pinSelSDA, pinSelCLK, pinInd;
  MDR_PORT_Type *MDR_Port;
  
#ifdef MDR_GPIO_HAS_KEY  
  MDR_Port_InitDigGroupPinCfg(MDR_On, pinsPower, &pinGroupCfg);
#else
  MDR_Port_InitDigGroupPinCfg(MDR_On, pinsPower, MDR_Off, MDR_Off, &pinGroupCfg);
#endif  
  
  //  pPinSDA
  if (pinsCfg->pPinSDA != NULL)
  {    
    MDR_GPIO_Enable(pinsCfg->pPinSDA->portGPIO);
    
    MDR_Port = pinsCfg->pPinSDA->portGPIO->PORTx;
    pinInd = pinsCfg->pPinSDA->pinIndex;
    
    MDR_Port_InitDigPin(MDR_Port, pinInd, MDR_Pin_Out, pinsCfg->pPinSDA->pinFunc, &pinGroupCfg);
    pinSelSDA = 1 << pinInd;
  } 
    
  //  pPinSCL
  if (pinsCfg->pPinSCL != NULL)
  {
    MDR_GPIO_Enable(pinsCfg->pPinSCL->portGPIO);
    
    MDR_Port = pinsCfg->pPinSCL->portGPIO->PORTx;
    pinInd = pinsCfg->pPinSCL->pinIndex;
    
    MDR_Port_InitDigPin(MDR_Port, pinInd, MDR_Pin_Out, pinsCfg->pPinSCL->pinFunc, &pinGroupCfg);  
    pinSelCLK = 1 << pinInd;
    if (pullUpPins)
      MDR_Port_SetPullUp(MDR_Port, pinSelCLK);
    MDR_Port_SetPins(MDR_Port, pinSelCLK);
  } 
  
  //  Stop Condition
  if (pullUpPins)
    MDR_Port_SetPullUp(MDR_Port, pinSelSDA);
  MDR_Port_SetPins(MDR_Port, pinSelSDA);  
}


//===================   I2C Master   ==========================

static void MDR_I2Cst_Start(void *obj);
static void MDR_I2Cst_Stop(void *obj);

static MDR_I2Cst_MasterObj MDR_I2Cst_InitMaster_loc(MDR_I2Cs_MasterInitCfg *cfgI2C)
{
  //  CLK Timer
  MDR_Timer_InitPeriodDirIRQ(cfgI2C->timerEx, cfgI2C->timClockBRG, cfgI2C->timClockPSG, cfgI2C->timPeriod, TIM_FL_CNT_ZERO | TIM_FL_CNT_ARR, TIM_CountUpDown);  
  MDR_TimerCh_InitPWM(cfgI2C->timerCh_PWM, NULL, MDR_TIM_PWM_RefTgl_eqCCR,   cfgI2C->timPeriod / 2); 
  MDR_TimerCh_InvertPWM_Ch(cfgI2C->timerCh_PWM);
  //  Init Pins
  MDR_I2Cs_InitPinsGPIO(cfgI2C->pinsCfg, cfgI2C->pinsPower, cfgI2C->pullUpPins);
  
  MDR_I2Cst_MasterObj i2cObj;
  //  pinSDA
  const MDR_I2C_CfgPinGPIO *pinCfg = cfgI2C->pinsCfg->pPinSDA;
  i2cObj.portSDA   = pinCfg->portGPIO->PORTx;
  i2cObj.pinSelSDA = 1 << pinCfg->pinIndex;
  //  pinCLK
  pinCfg = cfgI2C->pinsCfg->pPinSCL;
  i2cObj.portCLK   = pinCfg->portGPIO->PORTx;
  i2cObj.pinSelCLK = 1 << pinCfg->pinIndex;  
  //  Timer
  i2cObj.timerEx = cfgI2C->timerEx;
  i2cObj.TimerEventsStart = MDR_I2Cst_Start;
  i2cObj.TimerEventsStop = MDR_I2Cst_Stop;
  i2cObj.timTact = 0;
  i2cObj.started = false;
    
  return i2cObj;
}

MDR_I2Cst_MasterObj MDR_I2Cst_InitMasterPWM(MDR_I2Cs_MasterInitCfg *cfgI2C)
{
  //  CLK Timer
  MDR_Timer_InitPeriodDirIRQ(cfgI2C->timerEx, cfgI2C->timClockBRG, cfgI2C->timClockPSG, cfgI2C->timPeriod, TIM_FL_CNT_ZERO | TIM_FL_CNT_ARR, TIM_CountUpDown);  
  MDR_TimerCh_InitPWM(cfgI2C->timerCh_PWM, NULL, MDR_TIM_PWM_RefTgl_eqCCR,   cfgI2C->timPeriod / 2); 
  
  return MDR_I2Cst_InitMaster_loc(cfgI2C);
}

MDR_I2Cst_MasterObj MDR_I2Cst_InitMasterSoft(MDR_I2Cs_MasterInitCfg *cfgI2C)
{
  //  CLK Timer
  MDR_Timer_InitPeriodDirIRQ(cfgI2C->timerEx, cfgI2C->timClockBRG, cfgI2C->timClockPSG, cfgI2C->timPeriod, TIM_FL_CNT_ZERO | TIM_FL_CNT_ARR, TIM_CountUpDown);    
  return MDR_I2Cst_InitMaster_loc(cfgI2C);
}


static void MDR_I2Cst_Start(void *obj)
{ 
  MDR_I2Cst_MasterObj *i2cObj = obj;
  MDR_Timer_Start(i2cObj->timerEx);
}

static void MDR_I2Cst_Stop(void *obj)
{
  MDR_I2Cst_MasterObj *i2cObj = obj;
  MDR_Timer_Stop(i2cObj->timerEx);  
}


void MDR_I2Cst_MasterHandlerIRQ_PWM(MDR_I2Cst_MasterObj *i2cObj)
{  
  MDR_TIMER_Type *TIMERx = ((const MDR_TIMER_TypeEx*)(i2cObj->timerEx))->TIMERx;
  
  uint32_t status = MDR_Timer_GetStatus(TIMERx);
  MDR_Timer_ClearEvent(TIMERx, status);
  
  MDR_I2Cs_MasterProcessCompleted(i2cObj, status & TIM_FL_CNT_ARR);
}


void MDR_I2Cst_MasterHandlerIRQ_Soft(MDR_I2Cst_MasterObj *i2cObj)
{  
  MDR_TIMER_Type *TIMERx = ((const MDR_TIMER_TypeEx*)(i2cObj->timerEx))->TIMERx;
  
  uint32_t status = MDR_Timer_GetStatus(TIMERx);
  MDR_Timer_ClearEvent(TIMERx, status);
  
  switch (i2cObj->timTact++) {
    case 0: SET_CLK_0(i2cObj); break;
    case 1: MDR_I2Cs_MasterProcessCompleted(i2cObj, true); break;
    case 2: FREE_CLK_1(i2cObj); break;
    case 3: MDR_I2Cs_MasterProcessCompleted(i2cObj, false); i2cObj->timTact = 0; break;
  }
}


void MDR_I2Cst_MasterStartWrite(MDR_I2Cst_MasterObj *i2cObj, uint8_t addr_7bit, uint8_t *data, uint8_t dataLen)
{
  i2cObj->addr_7bit = addr_7bit;
  i2cObj->dataCnt = dataLen;
  i2cObj->pData = data;  
  i2cObj->readRegMode = false;
  MDR_I2Cs_MasterStart(i2cObj, true);
}

void MDR_I2Cst_MasterStartRead(MDR_I2Cst_MasterObj *i2cObj, uint8_t addr_7bit, uint8_t *data, uint8_t dataLen)
{
  i2cObj->addr_7bit = addr_7bit;
  i2cObj->dataCnt = dataLen;
  i2cObj->pData = data;  
  i2cObj->readRegMode = false;
  MDR_I2Cs_MasterStart(i2cObj, false);
}

void MDR_I2Cst_MasterStartReadRegs(MDR_I2Cst_MasterObj *i2cObj, uint8_t addr_7bit, const uint8_t *wrData, uint8_t wrDataLen, uint8_t *rdData, uint8_t rdDataLen)
{
  i2cObj->addr_7bit = addr_7bit;
  i2cObj->dataCnt = wrDataLen;
  i2cObj->pData = wrData;  
  i2cObj->regAddrCfg.dataCnt = rdDataLen;
  i2cObj->regAddrCfg.pData = rdData;
  i2cObj->readRegMode = true;
  MDR_I2Cs_MasterStart(i2cObj, true);
}

//===================   I2C Slave   ==========================
MDR_I2Cst_SlaveObj MDR_I2Cst_InitSlave(MDR_I2Cs_InitSlaveCfg *cfgI2C)
{
  //  Timer counter
  uint32_t selIRQ = cfgI2C->timCapCh_CLK.selIRQ_CCR_Rise | cfgI2C->timCapCh_CLK.selIRQ_CCR1_Fall
  | cfgI2C->timCapCh_SDA.selIRQ_CCR_Rise | cfgI2C->timCapCh_SDA.selIRQ_CCR1_Fall;
  
  MDR_Timer_InitPeriodDirIRQ(cfgI2C->timerEx, cfgI2C->timClockBRG, cfgI2C->timClockPSG, TIM_MAX_VALUE, selIRQ, TIM_CountUp);  
  //  CLK TimerChannel
  MDR_TimerCh_CfgCAP cfgCAP = {
    .Filter = cfgI2C->timCapCh_CLK.filter,
    .EventPSC = MDR_Div8P_div1,             //  div1, div2, div4, div8
    .EventCAP = MDR_TIM_CAP_RiseOnPin,      //  Event to capture to CCR    
    .enableCAP1 = true,
    .EventCAP1 = MDR_TIM_CAP1_FallOnPin     //  Event to capture to CCR1
  };  
  MDR_TimerCh_InitCAP(cfgI2C->timCapCh_CLK.timerCh, &cfgCAP);  
  //  SDA TimerChannel
  cfgCAP.Filter = cfgI2C->timCapCh_SDA.filter;
  MDR_TimerCh_InitCAP(cfgI2C->timCapCh_SDA.timerCh, &cfgCAP);  
  
  //  Init Pins
  MDR_I2Cs_InitPinsGPIO(cfgI2C->pinsCfg, cfgI2C->pinsPower, cfgI2C->pullUpPins);
  
  MDR_I2Cst_SlaveObj i2cObj;
  //  pinSDA
  const MDR_I2C_CfgPinGPIO *pinCfg = cfgI2C->pinsCfg->pPinSDA;
  i2cObj.portSDA   = pinCfg->portGPIO->PORTx;
  i2cObj.pinSelSDA = 1 << pinCfg->pinIndex;
  
  // SDA PinFunc control. Uses for switch SDA to Port for set ACK
  i2cObj.pinFuncMasks = MDR_GPIO_GetPinFuncMasks(i2cObj.portSDA, pinCfg->pinIndex, pinCfg->pinFunc);  
  
  //  pinCLK
  pinCfg = cfgI2C->pinsCfg->pPinSCL;
  i2cObj.portCLK   = pinCfg->portGPIO->PORTx;
  i2cObj.pinSelCLK = 1 << pinCfg->pinIndex;  
  //  Timer
  i2cObj.timerEx = cfgI2C->timerEx;
  i2cObj.eventFallCLK = cfgI2C->timCapCh_CLK.selIRQ_CCR1_Fall;
  i2cObj.eventRiseCLK = cfgI2C->timCapCh_CLK.selIRQ_CCR_Rise;
  i2cObj.eventFallSDA = cfgI2C->timCapCh_SDA.selIRQ_CCR1_Fall;
  i2cObj.eventRiseSDA = cfgI2C->timCapCh_SDA.selIRQ_CCR_Rise;
  i2cObj.OnCheckAddr = cfgI2C->OnCheckAddr;
  i2cObj.OnCompleted = cfgI2C->OnCompleted;
  
  
  
//  i2cObj.TimerEventsStart = MDR_I2Cst_Start;
//  i2cObj.TimerEventsStop = MDR_I2Cst_Stop;
//  i2cObj.timTact = 0;
  i2cObj.started = false;
    
  return i2cObj;
}


void MDR_I2Cst_SlaveHandlerIRQ(MDR_I2Cst_SlaveObj *i2cObj)
{  
  MDR_TIMER_Type *TIMERx = ((const MDR_TIMER_TypeEx*)(i2cObj->timerEx))->TIMERx;  
  uint32_t status = MDR_Timer_GetStatus(TIMERx);
  MDR_Timer_ClearEvent(TIMERx, status);
  
  if (status & i2cObj->eventFallCLK)
    MDR_I2Cs_SlaveProcessCompleted(i2cObj, true);
  else if (status & i2cObj->eventRiseCLK)
    MDR_I2Cs_SlaveProcessCompleted(i2cObj, false);
  else if (status & i2cObj->eventFallSDA)
  {
    if (GET_CLK_1(i2cObj))
      MDR_I2Cs_SlaveStart(i2cObj);
  }
  else if (status & i2cObj->eventRiseSDA)
  {
    if (GET_CLK_1(i2cObj))
      MDR_I2Cs_SlaveStop(i2cObj);
  }
}



