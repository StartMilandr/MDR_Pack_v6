/***********************************************************************/
/*  This file is part of the ARM Toolchain package                     */
/*  Copyright (c) 2010 Keil - An ARM Company. All rights reserved.     */
/***********************************************************************/
/*                                                                     */
/*  FlashDev.C:  Flash Programming Functions adapted                   */
/*               for New Device 256kB Flash                            */
/*                                                                     */
/***********************************************************************/

#include "FlashOS.H"        // FlashOS Structures

#include "MDR_DeviceDefs.h"


int Init (unsigned long adr, unsigned long clk, unsigned long fnc) 
{
  uint32_t regVal;
  __disable_irq();
  
  // Включение тактирования BKP
  regPER_CLOCK |= bClockOn_RST | bClockOn_BKP;
  
  //  Включение генератора HSI
  regVal = regBKP_REG_0F & (~bHSI_TRIM_Msk);
  regBKP_REG_0F = regVal | bHSI_ON | bHSI_Trim8MHz;
  while ((regBKP_REG_0F & bHSI_RDY) == 0);
  
  //  Тактирование от HSI
  regCPU_CLOCK = 0;
  
  //  Выключение тактирования остальных блоков - чтобы не мешали.
  //  BKP нужен для проверки наличия начального загрузчика!
  regPER_CLOCK = bClockOn_RST | bClockOn_EEPROM | bClockOn_BKP;  
  
  return (0);                                  // Finished without Errors
}


/*
 *  De-Initialize Flash Programming Functions
 *    Parameter:      fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */

int UnInit (unsigned long fnc) 
{
  uint32_t addr;
  volatile uint32_t d;  
  
  regCMD = 0;
  regKEY = 0;
  regPER_CLOCK = bClockOn_RST;

  //  Update page cache  
  for (addr = FLASH_ADDR_0; addr < (PAGE_COUNT * PAGE_SIZE); addr += PAGE_SIZE)
    d = REG32(addr);
 
  return (0);                                  // Finished without Errors
}


/*
 *  Erase complete Flash Memory
 *    Return Value:   0 - OK,  1 - Failed
 */

int EraseChip (void) 
{
  MDR_EEPROM_EraseFull();
  return (0);                                  // Finished without Errors
}


/*
 *  Erase Sector in Flash Memory
 *    Parameter:      adr:  Sector Address
 *    Return Value:   0 - OK,  1 - Failed
 */

int EraseSector (unsigned long adr) 
{
  MDR_EEPROM_ErasePage(adr);
  return (0);                                  // Finished without Errors
}


/*
 *  Program Page in Flash Memory
 *    Parameter:      adr:  Page Start Address
 *                    sz:   Page Size
 *                    buf:  Page Data
 *    Return Value:   0 - OK,  1 - Failed
 */

int ProgramPage (unsigned long adr, unsigned long sz, unsigned char *buf) 
{
 uint32_t i;
 uint32_t* pData32 = (uint32_t*)buf;
 
 sz = sz >> 2;
 for (i = 0; i < sz; ++i)
   MDR_EEPROM_Write(adr + (i << 2), pData32[i], 0);
  
  return (0);
}


/*
 *  Program Page in Flash Memory
 *    Parameter:      adr:  Page Start Address
 *                    sz:   Page Size
 *                    pat	Pattern to compare
 *    Return Value:   0 - OK,  1 - Failed
 */

#if READ_BY_EEPROM
  #define ReadWord(addr)    MDR_EEPROM_Read(addr)
#else
  #define ReadWord(addr)    REG32(addr);
#endif

int BlankCheck (unsigned long adr, unsigned long sz, unsigned char pat)
{
 uint32_t i;
 volatile uint32_t value;
 
 for (i = 0; i < sz; i +=4)
 {
   value = ReadWord(adr + i);
   
//#if FIX_DBL_READ    
   if (0xFFFFFFFF != value)
     value = ReadWord(adr + i);
//#endif
   
   if (0xFFFFFFFF != value)
     return 1;
 }
 
  return 0;
}

/*
 *  Program Page in Flash Memory
 *    Parameter:      adr:  Page Start Address
 *                    sz:   Page Size
 *                    buf:  Page Data
 *    Return Value:   0 - OK,  1 - Failed
 */

unsigned long Verify (unsigned long adr, unsigned long sz, unsigned char *buf)
{
 uint32_t i;
 uint32_t* pData32 = (uint32_t*)buf;
 volatile uint32_t value;
 
 //  Loop by Int
 sz = sz >> 2;
 for (i = 0; i < sz; ++i)
 {
   value = ReadWord(adr + (i << 2));
   
//#if FIX_DBL_READ
   if (pData32[i] != value)
     value = ReadWord(adr + (i << 2));
//#endif

   if (pData32[i] != value)
     break;
 }
 
 return adr + (i << 2);
  //return 0;
}
