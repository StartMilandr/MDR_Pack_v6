#include <MDR_Config.h>
#include <MDR_GPIO.h>
#include <MDR_RST_Clock.h>
#include <MDR_EBC.h>
#include "MDR_EBC_VE8_Cfg0.h"
#include "MDR_EBC_VE8_Cfg1.h"
#include "MDRB_EBC.h"


#define RGN0_StartAddr        0x10000000
#define RGN0_EndAddr          0x10040000
#define RGN0_EccAddr          0x11000000

#define ADDR_READ_CNT   100

typedef struct {
  uint32_t rdIndex;
  uint32_t rdAddr;
  uint32_t rdDataPrev;
  uint32_t rdData;
} ErrLogStruct;

#define LOG_LEN   100
ErrLogStruct _logArr[LOG_LEN];
uint32_t     _logIndRW = 0;

uint32_t     _rdIndex = 0;
uint32_t     _sumErrCnt = 0;

uint32_t LoopMemTest(void);
uint32_t TestOneAddr(uint32_t addr, uint32_t testCnt);
void fillRAM(void);



int main(void)
{ 
  //  Максимальная скорость тактирования
  MDR_CLK_Enable_RST_BPK();
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX; 
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  
  //  ExtBus
  MDR_EBC_RGN_CfgRegs  cfgRgn0 = EBCCFG0_CFG_REGS(0);  
  MDR_EBC_Enable();
  MDR_EBC_EnableRegion(MDR_EBC_RGN0, &cfgRgn0);

  MDRB_EBC_InitPins_A19_D8();

  _logIndRW = 0;
  _sumErrCnt = 0;  
  while (1)
  {
    _sumErrCnt += LoopMemTest();      
  }
}


uint32_t TestOneAddr(uint32_t addr, uint32_t testCnt)
{  
  uint32_t i, data, pr_data;
  uint32_t err_cnt = 0; 
  
  pr_data = MEM32(addr);
  for (i = 0; i < ADDR_READ_CNT; ++i)
  {
    data = MEM32(addr);
    if (data != pr_data)
    {
      ++err_cnt;
      if (_logIndRW < LOG_LEN)
      {
        _logArr[_logIndRW].rdIndex = _rdIndex;
        _logArr[_logIndRW].rdAddr = addr;
        _logArr[_logIndRW].rdDataPrev = pr_data;
        _logArr[_logIndRW].rdData = data;
        ++_logIndRW;
      }
      else
        _logIndRW = 0;
    }
    pr_data = data;
    ++_rdIndex;
  }
  
  return err_cnt;
}

uint32_t LoopMemTest(void)
{
  uint32_t addr = RGN0_StartAddr;
  uint32_t errCnt = 0;
  
  
  //_rdIndex = 0;
  while (addr < RGN0_EndAddr) 
  {
    errCnt += TestOneAddr(addr, ADDR_READ_CNT);
    addr += 4;
  }    
  return errCnt;
}
