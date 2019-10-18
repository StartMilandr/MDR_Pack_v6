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

#include "MDR_OTP_VE8x.h"
#include "MDR_RST_Clock_VE8x.h"
#include "MDR_CPU_ClockSelect.h"

#ifdef USE_HSE1_GEN_25MHZ
  #define CPU_CLOCK_HZ  25000000
#elif defined (USE_HSE0_RES_10MHZ)
  #define CPU_CLOCK_HZ  25000000
#else  
  #define CPU_CLOCK_HZ   8000000
#endif


#define REG32(x) (*((volatile uint32_t *)(x)))

//==================  CORE Cortex-M   =================
#define VTOR_ADDR               0xE000ED08UL    
#define regVTOR                 REG32(VTOR_ADDR)
#define VTABLE_IND_SP           0UL
#define VTABLE_IND_Reset        1UL
#define VTABLE_IND_NMI          2UL
#define VTABLE_IND_HardFault    3UL

//==================  OTP  ===============
#define OTP_START_ADDR       0x01000000UL
#define OTP_LAST_ADDR       (0x01020000UL - 4UL)


uint32_t HandlersTable[4] __attribute__((aligned(128)));

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
#define PROG_MODE   2
#define NOP_DOUBLE  0xBF00BF00


int Init (unsigned long adr, unsigned long clk, unsigned long fnc) 
{
  MDR_CLK_Enable_RST_BPK();
  
  MDR_BKP->TMR0.REG_60 |= MDR_BKP_REG60_PORSTn_Dis_Msk;
  MDR_BKP->TMR1.REG_60 |= MDR_BKP_REG60_PORSTn_Dis_Msk;
  MDR_BKP->TMR2.REG_60 |= MDR_BKP_REG60_PORSTn_Dis_Msk;  

  //  Set VectorTable and assign HardFault_Handler 
  HandlersTable[VTABLE_IND_HardFault] = (uint32_t)&HardFault_Handler;  
  regVTOR = (uint32_t)HandlersTable;
  
  //  Set CPU_Clock
#ifdef USE_HSE1_GEN_25MHZ
  if (MDR_CLOCK->MAX_CLK == 0)
    MDR_CPU_SetClock_HSE1_def(MDR_CLK_Generator, true);
  
#elif defined (USE_HSE0_RES_10MHZ)
  //  ТОЛЬКО для ревизии 1986ВЕ8Т начиная с 5-й! (Errata 0051 - Большой джиттер PLL)
  if (MDR_CLOCK->MAX_CLK == 0)
  {
    MDR_CPU_PLL_CfgHSE  cfgPll_HSE0_25MHz = { .freqSource          = MDR_CLK_Resonator,
                                              .selDiv2             = true,
                                              .timeoutCycles_HSE   = HSI_TIMEOUT,
                                              .cfgPLL              = MDRB_PLL_10MHz_TO_50MHz,
                                              .timeoutCycles_PLL   = PLL_TIMEOUT,
                                              .divMaxToCpu_0       = 0,
                                              .freqSupp            = MDRB_PLL_10MHz_FSUPP_MAX};
                                              
    MDR_CPU_SetClock_HSE0_PLL0(&cfgPll_HSE0_25MHz, true);
  }
  
#else    
  MDR_CPU_CfgHSI  cfgHSI = MDR_CPU_CFG_HSI_DEF;
  MDR_CPU_SetClock_HSI(&cfgHSI, HSI_TIMEOUT, false);  
#endif

  MDR_OTP_Enable();
  if (fnc == PROG_MODE)
    MDR_OTP_ProgBegin_ByClockCPU_Hz(CPU_CLOCK_HZ);  
	
  return (0);                                  // Finished without Errors
}


/*
 *  De-Initialize Flash Programming Functions
 *    Parameter:      fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */

uint32_t _OTP_Prog_NextAddr = 0;

int UnInit (unsigned long fnc) 
{
  //  Программирование 8-ми последующих слов нулями
  if (fnc == PROG_MODE)
  {
    uint32_t i;
    //  Программирование
    for (i = 0; i < 32; i += 4)
    {
      if ((_OTP_Prog_NextAddr + i) < OTP_LAST_ADDR)
      {
        if (!MDR_OTP_ProgWord(_OTP_Prog_NextAddr + i, NOP_DOUBLE))
          break;
      }
      else
        break;
    }
    
#ifndef PASS_REP_PROG    
    //  До-Программирование 8 слов
    for (i = 0; i < 8; ++i)    
    {
      if ((_OTP_Prog_NextAddr + i) < OTP_LAST_ADDR)
      {  
        if (!MDR_OTP_RepProgWord(_OTP_Prog_NextAddr + i, NOP_DOUBLE))
          break;
      }
      else
        break;
    }
#endif

    MDR_OTP_ProgEnd();
  }
  MDR_OTP_Disable();      
  
  MDR_CLK_Disable_BKP();
  MDR_CLK_Disable_RST();
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
  uint32_t result = 0; // OK
  uint32_t* pData32 = (uint32_t*)buf;
 
  _OTP_Prog_NextAddr = adr + sz;  
  sz = sz >> 2;
  //  Программирование
  for (i = 0; i < sz; ++i)
    if (!MDR_OTP_ProgWord(adr + (i << 2), pData32[i]))
    {
      result = 1;  // Fault
      break;
    }
    
#ifndef PASS_REP_PROG     
  //  Допрограммирование
  if (result)
    for (i = 0; i < sz; ++i)
      if (!MDR_OTP_RepProgWord(adr + (i << 2), pData32[i]))
      {
        result = 1; // Fault
        break;
      };
#endif  
    
  return result;
}

/*
 *  Erase complete Flash Memory
 *    Return Value:   0 - OK,  1 - Failed
 */

int EraseChip (void) 
{
  return (0);                                  // Finished without Errors
}


/*
 *  Erase Sector in Flash Memory
 *    Parameter:      adr:  Sector Address
 *    Return Value:   0 - OK,  1 - Failed
 */
int EraseSector (unsigned long adr) 
{ 
  return (0);                                  // Finished without Errors
}


/*
 *  Program Page in Flash Memory
 *    Parameter:      adr:  Page Start Address
 *                    sz:   Page Size
 *                    pat	Pattern to compare
 *    Return Value:   0 - OK,  1 - Failed
 */

int BlankCheck (unsigned long adr, unsigned long sz, unsigned char pat)
{
	uint32_t addr;
	for (addr = adr; addr <= (adr + sz); addr += 4)
		if (!MDR_OTP_CheckWordEmpty(addr))
      return 1;
  
  return 0;
}

/*
 *  Verify Page in Flash Memory
 *    Parameter:      adr:  Start Address
 *                    sz:   Size in bytes
 *                    buf:  Data to be verified
 *    Return Value:   (adr+sz) - OK,  other number - Failed
 */


#if READ_BY_REGS
  #define ReadWord(addr)    MDR_OTP_ReadWord(addr)
#else
  #define ReadWord(addr)    REG32(addr)
#endif

unsigned long Verify (unsigned long adr, unsigned long sz, unsigned char *buf)
{
  uint32_t i;
  uint32_t* pData32 = (uint32_t*)buf;
  uint32_t result = adr + sz;

  //  Loop by Int
  sz = sz >> 2;
  for (i = 0; i < sz; ++i)
  {
    if (ReadWord(adr + (i << 2)) != pData32[i])
    {
      result = adr + (i << 2);
      break;
    }
  }

  //  Конечные 8 слов
  if ((adr + sz) == _OTP_Prog_NextAddr)
    for (i = 0; i < 32; i += 4)
      if (ReadWord(_OTP_Prog_NextAddr + i) != NOP_DOUBLE) 
      {
        result = _OTP_Prog_NextAddr + i;
        break;
      }
 
 return result;
}
