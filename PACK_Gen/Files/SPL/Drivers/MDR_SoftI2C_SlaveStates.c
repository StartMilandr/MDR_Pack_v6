#include <MDR_SoftI2C_States.h>
#include <MDR_GPIO.h>

static bool MDR_I2Cs_SlaveWriteHandler(void *obj, bool isClkFall);
static bool MDR_I2Cs_SlaveReadHandler(void *obj, bool isClkFall);

static bool MDR_I2Cs_SlaveReadDataBits(MDR_I2Cst_SlaveObj *i2cObj, bool isClkFall);
static bool MDR_I2Cs_SlaveReadStartNextData(MDR_I2Cst_SlaveObj *i2cObj);

static void MDR_I2Cs_SlaveWriteStart(MDR_I2Cst_SlaveObj *i2cObj);


// -------------  Write Transfer (Slave Read from Master)------------
void MDR_I2Cs_SlaveStart(MDR_I2Cst_SlaveObj *i2cObj)
{ 
  if (i2cObj->started)
    i2cObj->reStarted = true;

  i2cObj->addrMatch = false;
  i2cObj->bitInd = MDR_I2Cs_BIT_CNT;
  i2cObj->activeByte = 0;
  i2cObj->isWriteTransf = false;
  i2cObj->transfDataCnt = 0;
  i2cObj->ProcessFunc = MDR_I2Cs_SlaveReadHandler;  
  
  i2cObj->started = true;
}

void MDR_I2Cs_SlaveStop(MDR_I2Cst_SlaveObj *i2cObj)
{ 
  if (i2cObj->started)
  {
    i2cObj->started = false;
    i2cObj->reStarted = false;
    i2cObj->OnCompleted(i2cObj);
  }
}

static void MDR_I2Cs_SlaveSetACK(MDR_I2Cst_SlaveObj *i2cObj)
{ 
  MDR_GPIO_PinFunc_SetPort(&i2cObj->pinFuncMasks);
  SET_SDA_ACK(i2cObj);  
}

static void MDR_I2Cs_SlaveClearACK(MDR_I2Cst_SlaveObj *i2cObj)
{
  CLR_SDA_ACK(i2cObj);
  MDR_GPIO_PinFunc_SetFunc(&i2cObj->pinFuncMasks);
}

static bool MDR_I2Cs_SlaveReadDataBits(MDR_I2Cst_SlaveObj *i2cObj, bool isClkFall)
{
  bool result = false;
  if (isClkFall)
  { 
    if (i2cObj->addrMatch)
    {     
      if (i2cObj->bitInd == MDR_I2Cs_BIT_CNT)
        MDR_I2Cs_SlaveClearACK(i2cObj);
      else if (i2cObj->bitInd == 0)
        MDR_I2Cs_SlaveSetACK(i2cObj);
    }
  }
  else
  {
    if (i2cObj->bitInd > 0)
    {
      i2cObj->bitInd--;
      if (GET_SDA_1(i2cObj))
        i2cObj->activeByte |= (1 << i2cObj->bitInd);
      
      if ((i2cObj->transfDataCnt + i2cObj->bitInd) == 0)
      {
        // Ask User for fuffers Wr/Rd 
        i2cObj->isWriteTransf = (i2cObj->activeByte & MDR_I2C_RD_Msk) == 0;
        i2cObj->addrMatch = i2cObj->OnCheckAddr(i2cObj->activeByte >> 1, i2cObj->isWriteTransf, i2cObj->reStarted, &i2cObj->pData, &(i2cObj->dataLen));
        i2cObj->dataInd  = 0; 
      }
    }
    else     
      result = true;
  }
  return result;
}

//  Return if read should be completed, may be chaged to Write transfer
static bool MDR_I2Cs_SlaveReadStartNextData(MDR_I2Cst_SlaveObj *i2cObj)
{
  bool result = false;
  if (i2cObj->addrMatch)
  {      
    // First received byte is address
    if (i2cObj->transfDataCnt == 0)
    {
      if (!i2cObj->isWriteTransf)
        result = true;
    }
    else
    { //  Write Transfer - Save Bytes to Buff until buff Length
      if (i2cObj->dataInd == i2cObj->dataLen)
        i2cObj->dataInd = 0;      
      i2cObj->pData[i2cObj->dataInd] = i2cObj->activeByte;
      i2cObj->dataInd++;      
    }    
    i2cObj->transfDataCnt++;
  }
  else
    result = true;
  
  i2cObj->bitInd = MDR_I2Cs_BIT_CNT;
  i2cObj->activeByte = 0;
  return result;
}


static bool MDR_I2Cs_SlaveReadHandler(void *obj, bool isClkFall)
{
  MDR_I2Cst_SlaveObj *i2cObj = obj;
  
  bool result = false;  
  if (MDR_I2Cs_SlaveReadDataBits(i2cObj, isClkFall))
    if (MDR_I2Cs_SlaveReadStartNextData(i2cObj))
    {
      if (!i2cObj->isWriteTransf)
        MDR_I2Cs_SlaveWriteStart(i2cObj);
      else
      {
        //Will processed by Stop Event !
//        i2cObj->started = false;
//        i2cObj->OnCompleted(i2cObj);
        result = true;
      }
    }  
  return result;
}


//------------------    Read Transfer (Slave send to Master)  ---------------
static void MDR_I2Cs_SlaveWriteStart(MDR_I2Cst_SlaveObj *i2cObj)
{
//  i2cObj->pData = i2cObj->pRetBuff;
//  i2cObj->dataLen = i2cObj->retBuffLen;

  i2cObj->activeByte = i2cObj->pData[0];   
  i2cObj->dataInd = 1;
  i2cObj->ProcessFunc = MDR_I2Cs_SlaveWriteHandler;
}

static bool MDR_I2Cs_SlaveWriteDataBits(MDR_I2Cst_SlaveObj *i2cObj, bool isClkFall)
{
  bool result = false;
  if (isClkFall)
  { 
    if (i2cObj->bitInd > 0)
    {
      if (i2cObj->activeByte & (1 << (i2cObj->bitInd - 1)))
        FREE_SDA_1(i2cObj);
      else
        SET_SDA_0(i2cObj);
    }
    else
      FREE_SDA_1(i2cObj);    
  }
  else 
  {  
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

static bool MDR_I2Cs_SlaveWriteStartNextData(MDR_I2Cst_SlaveObj *i2cObj)
{
  if (i2cObj->ackOk)
  {
    if (i2cObj->dataInd == i2cObj->dataLen)
      i2cObj->dataInd = 0;
    
    i2cObj->activeByte = i2cObj->pData[i2cObj->dataInd];
    i2cObj->dataInd++;
    i2cObj->bitInd = MDR_I2Cs_BIT_CNT;    
    return false;
  }
  else
    return true;
}

static bool MDR_I2Cs_SlaveWriteHandler(void *obj, bool isClkFall)
{
  MDR_I2Cst_SlaveObj *i2cObj = obj;
  
  bool result = false;
  if (MDR_I2Cs_SlaveWriteDataBits(i2cObj, isClkFall))
    if (MDR_I2Cs_SlaveWriteStartNextData(i2cObj))
    { 
      //MDR_I2Cs_SlaveClearACK(i2cObj);
      MDR_GPIO_PinFunc_SetFunc(&i2cObj->pinFuncMasks);
      //  NACK from Master
      i2cObj->started = false;
      i2cObj->OnCompleted(i2cObj);
      result = true;
    }
    
  return result;
}




