#include <MDR_SoftI2C_States.h>


// -------------  Master Write Transfer ------------
static bool MDR_I2Cs_MasterWriteHandler(void *obj, bool isClkDown);
static bool MDR_I2Cs_MasterReadHandler(void *obj, bool isClkDown);
static bool MDR_I2Cs_MasterStopHandler(void *obj, bool isClkDown);
static bool MDR_I2Cs_MasterRestartToReadHandler(void *obj, bool isClkDown);
static bool MDR_I2Cs_MasterStopAndGoReadHandler(void *obj, bool isClkDown);

// Tacts of MDR_I2Cs_MasterWriteHandler:
static bool MDR_I2Cs_MasterWriteDataBits(MDR_I2Cst_MasterObj *i2cObj, bool isClkDown);
static bool MDR_I2Cs_MasterWriteStartNextData(MDR_I2Cst_MasterObj *i2cObj);

static bool MDR_I2Cs_MasterReadStartHandler(void *obj, bool isClkDown);
static bool MDR_I2Cs_MasterReadDataBits(MDR_I2Cst_MasterObj *i2cObj, bool isClkDown);
static bool MDR_I2Cs_MasterReadStartNextData(MDR_I2Cst_MasterObj *i2cObj);


void MDR_I2Cs_MasterStart(MDR_I2Cst_MasterObj *i2cObj, bool writeMode)
{
  //  Write START
  SET_SDA_0(i2cObj);
  
  //  Init Transfer
  if (writeMode)
  {
    i2cObj->activeByte = i2cObj->addr_7bit << 1;
    i2cObj->ProcessFunc = MDR_I2Cs_MasterWriteHandler;
  }
  else
  {
    i2cObj->activeByte = (i2cObj->addr_7bit << 1) | MDR_I2C_RD_Msk;
    i2cObj->ProcessFunc = MDR_I2Cs_MasterReadStartHandler;
  }
  i2cObj->dataInd = 0;
  i2cObj->bitInd = MDR_I2Cs_BIT_CNT;
  //  Run Events
  i2cObj->writeMode = writeMode;
  i2cObj->started = true;
  i2cObj->clkEnable = true;
  i2cObj->TimerEventsStart(i2cObj);
}

#if I2C_STOP_DELAY_EN
  static bool MDR_I2Cs_MasterStopHandler(void *obj, bool isClkDown)
  { 
    MDR_I2Cst_MasterObj *i2cObj = obj;
    if (i2cObj->bitInd == 0)
    {
      if (isClkDown)
        SET_SDA_0(i2cObj); // CLK = 0: Set SDA to 0 before CLK
      else
      {      
        FREE_SDA_1(i2cObj);  // Event0: CLK = 1: Set SDA to 1 for stop 
        i2cObj->bitInd = 99;
        if (i2cObj->TimerEventsStopPWM != NULL)  
          i2cObj->TimerEventsStopPWM(i2cObj);
        i2cObj->clkEnable = false;
        // Stop PWM-?
      }
    }
    else if (!isClkDown)
    {
      i2cObj->started = false;        
      i2cObj->TimerEventsStop(i2cObj);
      return true;    
    }
    return false;
  }
#else
  static bool MDR_I2Cs_MasterStopHandler(void *obj, bool isClkDown)
  { 
    MDR_I2Cst_MasterObj *i2cObj = obj;
    if (isClkDown)
    { // CLK = 0: Set SDA to 0 before CLK
      SET_SDA_0(i2cObj);
      return false;
    }
    else
    { // Event0: CLK = 1: Set SDA to 1 for stop 
      FREE_SDA_1(i2cObj);
      i2cObj->started = false;        
      i2cObj->TimerEventsStop(i2cObj);
      return true;
    }
  }
#endif //I2C_STOP_DELAY_EN

static bool MDR_I2Cs_MasterRestartToReadHandler(void *obj, bool isClkDown)
{
  MDR_I2Cst_MasterObj *i2cObj = obj;
  if (isClkDown)
  { // CLK = 0: Do nothing - Slave release SDA here
    return false;
  }
  else
  { // Event0: CLK = 1: Start Read Transfer    
    i2cObj->pData = i2cObj->regAddrCfg.pData;
    i2cObj->dataCnt = i2cObj->regAddrCfg.dataCnt;
    
    MDR_I2Cs_MasterStart(obj, false);
    return true;
  }
}

static bool MDR_I2Cs_MasterStopAndGoReadHandler(void *obj, bool isClkDown)
{
  MDR_I2Cst_MasterObj *i2cObj = obj;
  if (i2cObj->bitInd == 0)
  {
    if (isClkDown)
      SET_SDA_0(i2cObj);  // CLK = 0: Set SDA to 0 before CLK
    else
    {
      FREE_SDA_1(i2cObj); // Event0: CLK = 1: Set SDA to 1 for stop 
      i2cObj->bitInd = 99;
      if (i2cObj->TimerEventsStopPWM != NULL)  
        i2cObj->TimerEventsStopPWM(i2cObj);
      i2cObj->clkEnable = false;
    }
  }
  else if (!isClkDown)
  {
    //Start Read Transfer
    i2cObj->clkEnable = true;
    i2cObj->pData = i2cObj->regAddrCfg.pData;
    i2cObj->dataCnt = i2cObj->regAddrCfg.dataCnt;
    MDR_I2Cs_MasterStart(obj, false);  
    return true;
  }
  
  return false;
}


static bool MDR_I2Cs_MasterWriteDataBits(MDR_I2Cst_MasterObj *i2cObj, bool isClkDown)
{
  bool result = false;  
  if (isClkDown)
  { // EventARR, CLK = 0: Write bits To SDA
    if (i2cObj->bitInd > 0)
    {
      //i2cObj->bitInd--;
      if (i2cObj->activeByte & (1 << (i2cObj->bitInd - 1)))
        FREE_SDA_1(i2cObj);
      else
        SET_SDA_0(i2cObj);
    }
    else
      FREE_SDA_1(i2cObj);
  }
  else
  { // Event0: CLK = 1: Read ACK from SDA    
    if (i2cObj->bitInd == 0)
    {
      i2cObj->ackOk = GET_SDA_ACK(i2cObj);
      result = true;
    }
    else
      i2cObj->bitInd--;    
  }
  return result;
}

static bool MDR_I2Cs_MasterWriteStartNextData(MDR_I2Cst_MasterObj *i2cObj)
{
  if ((i2cObj->dataInd < i2cObj->dataCnt) && (i2cObj->ackOk))
  {
    i2cObj->activeByte = i2cObj->pData[i2cObj->dataInd];
    i2cObj->dataInd++;
    i2cObj->bitInd = MDR_I2Cs_BIT_CNT;    
    return false;
  }
  else
    return true;
}

static bool MDR_I2Cs_MasterWriteHandler(void *obj, bool isClkDown)
{
  MDR_I2Cst_MasterObj *i2cObj = obj;
  if (MDR_I2Cs_MasterWriteDataBits(i2cObj, isClkDown))
    if (MDR_I2Cs_MasterWriteStartNextData(i2cObj))
    { 
      if (!(i2cObj->ackOk && i2cObj->readRegMode))
      //if (!i2cObj->readRegMode)
        i2cObj->ProcessFunc = MDR_I2Cs_MasterStopHandler;
      else
      { if (i2cObj->regModeByRestart) 
          i2cObj->ProcessFunc = MDR_I2Cs_MasterRestartToReadHandler;
        else
          i2cObj->ProcessFunc = MDR_I2Cs_MasterStopAndGoReadHandler;
      }
    }
    
  return false;
}

// -------------  Master Read Transfer ------------
static bool MDR_I2Cs_MasterReadDataBits(MDR_I2Cst_MasterObj *i2cObj, bool isClkDown)
{
  bool result = false;  
  if (!isClkDown)
  { // Event0, CLK = 1: Read bits To SDA
    if (i2cObj->bitInd > 0)
    {
      i2cObj->bitInd--;
      if (GET_SDA_1(i2cObj))
        i2cObj->activeByte |= (1 << i2cObj->bitInd);           
    }
    else
      result = true;
  }
  else
  { // EventARR: CLK = 0
    if (i2cObj->bitInd == MDR_I2Cs_BIT_CNT)
      FREE_SDA_1(i2cObj);
    else if (i2cObj->bitInd == 0)
    { 
      if (i2cObj->dataCnt - i2cObj->dataInd > 1)
        SET_SDA_ACK(i2cObj);        // Last byte received
    }
  }
  return result;
}

static bool MDR_I2Cs_MasterReadStartNextData(MDR_I2Cst_MasterObj *i2cObj)
{
  i2cObj->pData[i2cObj->dataInd] = i2cObj->activeByte;
  i2cObj->dataInd++;
  
  if (i2cObj->dataInd < i2cObj->dataCnt)
  {
    i2cObj->bitInd = MDR_I2Cs_BIT_CNT;
    i2cObj->activeByte = 0;
    return false;
  }
  else
    return true;
}

static bool MDR_I2Cs_MasterReadHandler(void *obj, bool isClkDown)
{
  MDR_I2Cst_MasterObj *i2cObj = obj;
  if (MDR_I2Cs_MasterReadDataBits(i2cObj, isClkDown))
    if (MDR_I2Cs_MasterReadStartNextData(i2cObj))
      i2cObj->ProcessFunc = MDR_I2Cs_MasterStopHandler;
    
  return false;
}

static bool MDR_I2Cs_MasterReadStartHandler(void *obj, bool isClkDown)
{
  MDR_I2Cst_MasterObj *i2cObj = obj;
  if (MDR_I2Cs_MasterWriteDataBits(i2cObj, isClkDown))
  {
    i2cObj->ProcessFunc = MDR_I2Cs_MasterReadHandler;  
    i2cObj->bitInd = MDR_I2Cs_BIT_CNT;
    i2cObj->activeByte = 0;
  }
    
  return false;
}




