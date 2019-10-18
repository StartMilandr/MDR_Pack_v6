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

#include "MDR_DeviceDefs_VE8.h"


__asm void HardFault_Handler(void)
{
  //  Set Result = 1
  MRS   R0, MSP
  MOV   R1,#1
  STR   R1,[R0]
  //  Modify return address to next instruction
  ADD   R0,#24
  LDR   R1,[R0]
  ADD   R1, #4
  STR   R1,[R0]  
  BX    LR
  ALIGN
}

/*
 *  Initialize Flash Programming Functions
 *    Parameter:      adr:  Device Base Address
 *                    clk:  Clock Frequency (Hz)
 *                    fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */

uint32_t HandlersTable[4] __attribute__((aligned(128)));

int Init (unsigned long adr, unsigned long clk, unsigned long fnc) 
{
  uint32_t HSI_Ready;
  
  //  Clear reset by POR (Errata)
  regBKP_KEY = MDR_KEY_UNLOCK;
  regBKP_REG60_TMR0 |= MDR_BKP_REG60_PORSTn_Dis_Msk;
  regBKP_REG60_TMR1 |= MDR_BKP_REG60_PORSTn_Dis_Msk;
  regBKP_REG60_TMR2 |= MDR_BKP_REG60_PORSTn_Dis_Msk;
  
  // Clock HSI Enable
  regBKP_REG63_TMR0 |= MDR_BKP_REG63_HSI_On_Msk;
  regBKP_REG63_TMR1 |= MDR_BKP_REG63_HSI_On_Msk;
  regBKP_REG63_TMR2 |= MDR_BKP_REG63_HSI_On_Msk;
  //  Wait HSI Ready
  do 
    HSI_Ready = regBKP_REG63_TMR0 & regBKP_REG63_TMR1 & regBKP_REG63_TMR2 & MDR_BKP_REG63_HSI_RDY_Msk;
  while (HSI_Ready == 0);
  //  Switch to HSI
  regCLOCK_MAXCLK = MAXCLK_HSI;
  
  //  Close BKP
  regBKP_KEY = 0;  
  
  //  Set VectorTable and assign HardFault_Handler 
  HandlersTable[VTABLE_IND_HardFault] = (uint32_t)&HardFault_Handler;  
  regVTOR = (uint32_t)HandlersTable;
	
	regOTP_KEY = MDR_KEY_UNLOCK;
	
  return (0);                                  // Finished without Errors
}


/*
 *  De-Initialize Flash Programming Functions
 *    Parameter:      fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */

int UnInit (unsigned long fnc) 
{
	regOTP_KEY = 0;
  return (0);                                  // Finished without Errors
}

/*
 *  Program Page in Flash Memory
 *    Parameter:      adr:  Page Start Address
 *                    sz:   Page Size
 *                    buf:  Page Data
 *    Return Value:   0 - OK,  1 - Failed
 */
const uint32_t H[12] = {
  0x08099264,
  0xC8080992,
  0x38C80809,
  0x0738C808,
  0xFF0738C8,
  0x64FF0738,
  0x9264FF07,
  0x099264FF,
  0x08099264,
  0xC8080992,
  0x38C80809,
  0x0738C808
};

unsigned int GetECC(uint32_t data,  uint32_t adr)
{
  uint32_t* ptr_H;
  int i1;   
  uint32_t res;
  uint32_t ecc;

   ecc = 0;
   ptr_H = (unsigned int*)(&H);
   i1 = 8;
   do
   {
      res = *ptr_H;
      res &= data;
      res ^= *(ptr_H + 4) & adr;
      ptr_H ++;
      res ^= res << 16;
      res ^= res << 8;
      res ^= res << 4;
      res ^= res << 2;
      res ^= res << 1;
      res >>= 31;
      i1--;
      res <<= i1;
      ecc |= res;
   }
   while(i1);
   return ecc;
}

void MDR_EEPROM_Write(uint32_t address, uint32_t data)
{ 
    uint32_t ctrl = GetECC(data, address) << MDR_OTP_CNTR_WECC_Pos;
    ctrl |= MDR_OTP_CNTR_WAITCYCL_SRAM_Min | MDR_OTP_CNTR_CLK_Msk | MDR_OTP_CNTR_REG_ACCESS_Msk; // MDR_OTP_CNTR_CEN_Msk

    regOTP_ADR = address;
    regOTP_WDATA = data;
    regOTP_CNTR = ctrl;
    ctrl |= MDR_OTP_CNTR_WE_ALL_Msk;
    regOTP_CNTR = ctrl;
    ctrl &= ~(MDR_OTP_CNTR_CLK_Msk | MDR_OTP_CNTR_REG_ACCESS_Msk);
    regOTP_CNTR = ctrl;
}

int ProgramPage (unsigned long adr, unsigned long sz, unsigned char *buf) 
{
  uint32_t i;
  uint32_t* pData32 = (uint32_t*)buf;
 
  sz = sz >> 2;
  for (i = 0; i < sz; ++i)
    MDR_EEPROM_Write(adr + (i << 2), pData32[i]);
  
  return (0);
}

/*
 *  Erase complete Flash Memory
 *    Return Value:   0 - OK,  1 - Failed
 */

int EraseChip (void) 
{
	uint32_t addr;
	for (addr = OTPSRAM_START_ADDR; addr <= OTPSRAM_END_ADDR; addr += 4)
		MDR_EEPROM_Write(addr, 0);
  return (0);                                  // Finished without Errors
}


/*
 *  Erase Sector in Flash Memory
 *    Parameter:      adr:  Sector Address
 *    Return Value:   0 - OK,  1 - Failed
 */

int EraseSector (unsigned long adr) 
{
	uint32_t addr;
	for (addr = adr; addr <= (adr + OTPSRAM_PAGE_END_ADDR); addr += 4)
		MDR_EEPROM_Write(addr, 0);  
  
  return (0);                                  // Finished without Errors
}


/*
 *  Program Page in Flash Memory
 *    Parameter:      adr:  Page Start Address
 *                    sz:   Page Size
 *                    pat	Pattern to compare
 *    Return Value:   0 - OK,  1 - Failed
 */

#if READ_BY_REGS
  #define ReadWord(addr)    MDR_EEPROM_Read(addr)
#else
  #define ReadWord(addr)    REG32(addr)
#endif


int BlankCheck (unsigned long adr, unsigned long sz, unsigned char pat)
{
	uint32_t addr;
  
	for (addr = adr; addr <= (adr + OTPSRAM_PAGE_END_ADDR); addr += 4)
		if (ReadWord(addr) != 0UL)
      return 1;
  
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
//   if (pData32[i] != value)
//     value = ReadWord(adr + (i << 2));
//#endif

   if (pData32[i] != value)
     break;
 }
 
 return adr + (i << 2);
  //return 0;
}
