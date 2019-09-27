#include "FlashOS.h"
//#include "MDR_DeviceDefs.h"

#include <stdint.h>

#if defined (USE_MDR1986VE4)
  #define PAGE_SIZE          0x200
  #define PAGE_COUNT         256
#else
  #define PAGE_SIZE          0x1000
  #define PAGE_COUNT         32
#endif

#if defined(USE_MDR1986VE9x) || defined(USE_MDR1901VC1)
  #define FLASH_ADDR_0      0x08000000
#elif defined(USE_MDR1986VE81)
  #define FLASH_ADDR_0      0x01000000
#else
  #define FLASH_ADDR_0      0
#endif


#define PAGE_SIZE_32        (PAGE_SIZE / 4)

#define MAIN_PAGES_COUNT    32
#define INFO_PAGES_COUNT    1

#ifdef USE_MDR1986VE9x
  #define FLASH_ADDR_0      0x08000000
#elif defined (USE_MDR1986VE1T)
  #define FLASH_ADDR_0      0
#endif


//---------   Memory selection Main/Info ------
//#define SELECT_INFO_MEM

#ifndef SELECT_INFO_MEM
  //#define PAGE_COUNT  MAIN_PAGES_COUNT
  #define MEM_SIZE    MAIN_PAGES_COUNT * PAGE_SIZE
#else
  //#define PAGE_COUNT  INFO_PAGES_COUNT
  #define MEM_SIZE    INFO_PAGES_COUNT * PAGE_SIZE
#endif

//----------  FLM Defs  -----------------
#define CLOCK       8000000     // not used
#define FUNC_Erase  1
#define FUNC_Prog   2
#define FUNC_Verif  3
#define SIZE        1024

//----------  Test Defs  -----------------
#define TEST_COUNT  1
typedef enum {flmOK, flmErrEraseFull, flmErrErasePage, flmErrProgPage, flmErrBlankCheck} FLM_Result;

uint8_t data[PAGE_SIZE];


uint32_t SwapBytes(uint32_t data)
{
  uint8_t* pData = (uint8_t*)&data;
  return (pData[3] <<24 | pData[2]<<16 | pData[1]<<8 | pData[0]);
}

FLM_Result CheckFuncFLM(void);

int main(void)
{
  uint32_t i;
  uint32_t doTest = 1;
  uint32_t cntOk;
  volatile uint32_t result;
  
  
  // Fill Data
  for (i = 0; i < PAGE_SIZE; ++i)
    data[i] = (uint8_t)i;
  
  while (1)
  {
    if (doTest)
    {
      cntOk = 0;
      for (i = 0; i < TEST_COUNT; ++i)
      {
        result = CheckFuncFLM();
        if (result == 0)
          ++cntOk;
      }  
      doTest = 0;
    }
  }
}

uint32_t CheckNotEmpty (unsigned long adr, unsigned long sz)
{
  uint32_t i;
  volatile uint32_t value;
  for (i = 0; i < sz; i +=4)
  {
    value = *((volatile uint32_t *)(adr + i));
    if (0xFFFFFFFF != value)
      return 0; // Ok
  }
  
  return 1;
}

FLM_Result CheckFuncFLM(void)
{
  uint32_t i, resVerif, addrPage;
  
  // Check HardFault exit
  for (i = 0; i < PAGE_COUNT; ++i)
    addrPage = FLASH_ADDR_0 + i * PAGE_SIZE;  
  
  //  Write start data - for FullClear test
  Init (0, CLOCK, FUNC_Prog);    
  ProgramPage(FLASH_ADDR_0, PAGE_SIZE, data);
  UnInit (FUNC_Prog);
  
  //  Test Clear Full
  Init (0, CLOCK, FUNC_Erase);
  EraseChip ();
  UnInit (FUNC_Erase);
  
  //  Check Full Memory Is Empty
  if (BlankCheck(FLASH_ADDR_0, MEM_SIZE, 0xFF) != 0)
    return flmErrEraseFull;

  // Pages tests
  for (i = 0; i < PAGE_COUNT; ++i)
  {
    addrPage = FLASH_ADDR_0 + i * PAGE_SIZE;
    
    //  Program page
    Init (0, CLOCK, FUNC_Prog);
    ProgramPage(addrPage, PAGE_SIZE, data);
    UnInit (FUNC_Prog);

    //  Verify page
    Init (0, CLOCK, FUNC_Verif);
    resVerif = Verify(addrPage, PAGE_SIZE, data);
    UnInit (FUNC_Verif);
    if (resVerif != (addrPage + PAGE_SIZE))
      return flmErrProgPage;
    
    //  Test BlankCheck(Page) return False
    if (CheckNotEmpty(addrPage, PAGE_SIZE) != 0)
      return flmErrBlankCheck;
    
    //  Clear page
    Init (0, CLOCK, FUNC_Erase);      
    EraseSector(addrPage);
    UnInit (FUNC_Erase);

    //  Test BlankCheck(FullMem) return True
    if (BlankCheck(FLASH_ADDR_0, MEM_SIZE, 0xFF) != 0)
      return flmErrErasePage;
  }
    
  return flmOK;
}


