#include "FlashOS.h"
#include <stdint.h>

//  Байт под данные
#define PAGE_SIZE                  (4 * 4)
//  8 слов после данных для конвейера
#define OTP_TAIL_SIZE              (8 * 4)
//  Оставить неинициализированными, чтобы убедиться что предвыборка до них не доходит
#define OTP_EMPTY_GAP              (2 * 4)
//  Итого байт для одного теста - 56 байт
#define OTP_WRITE_BLOCK            (PAGE_SIZE + OTP_TAIL_SIZE + OTP_EMPTY_GAP)

#define OTP_ADDR_NEXT_BUSY_ADDR    0x01020000

#define TEST_INDEX                 6
#define OTP_ADDR_0                 OTP_ADDR_NEXT_BUSY_ADDR - (OTP_WRITE_BLOCK * TEST_INDEX)

//----------  FLM Defs  -----------------
#define CLOCK       8000000     // not used
#define FUNC_Erase  1
#define FUNC_Prog   2
#define FUNC_Verif  3
#define SIZE        1024

uint8_t data[PAGE_SIZE];
#define NO_RESULT   7

int main(void)
{
  uint32_t i;
  uint32_t doTest = 1;
  
  volatile uint32_t resCheckBlank;
  volatile uint32_t resProg;
  volatile uint32_t resVerif;
  
  // Fill Data
  for (i = 0; i < PAGE_SIZE; ++i)
  {
    data[i] = (uint8_t)i;
    __nop();
  }
  
  
  while (1)
  {
    if (doTest)
    {
      resCheckBlank = NO_RESULT;
      resProg       = NO_RESULT;
      resVerif      = NO_RESULT;
      
      // Check Memory blank
      Init (0, CLOCK, FUNC_Verif);
      resCheckBlank = BlankCheck(OTP_ADDR_0, PAGE_SIZE + OTP_TAIL_SIZE, 0);
      UnInit (FUNC_Verif);
      
      //  Write start data
      if (resCheckBlank == 0)
      {
        Init (0, CLOCK, FUNC_Prog);
        resProg = ProgramPage(OTP_ADDR_0, PAGE_SIZE, data);
        UnInit (FUNC_Prog);
      }
       
      //  Verify page
      //     OK: resVerif == OTP_ADDR_0 + PAGE_SIZE
      //  Fault: resVerif == Error Address 
      Init (0, CLOCK, FUNC_Verif);
      resVerif = Verify(OTP_ADDR_0, PAGE_SIZE, data);
      UnInit (FUNC_Verif);
      
      doTest = 0;
    }
  }
}


