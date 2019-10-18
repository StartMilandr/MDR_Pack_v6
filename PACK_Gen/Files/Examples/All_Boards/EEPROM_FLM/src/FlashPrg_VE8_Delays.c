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
#include "MDR_GPIO.h"
#include "MDR_Funcs.h"
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


//  LED1 (VD7)
#define MDRB_FLAG_GPIO            MDR_GPIO_C
#define MDRB_FLAG_PIN             MDR_Pin_16
#define MDRB_FLAG_PIN_Ex          MDR_Pin_17

#define MDRB_FLAG_PIN_ALL         (MDRB_FLAG_PIN | MDRB_FLAG_PIN_Ex)

MDR_OTP_ProgDelays _delaysOTP;

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
                                              .freqSupp            = MDRB_CPU_FREQ_SUPP_LE_62MHz};
                                              
    MDR_CPU_SetClock_HSE0_PLL0(&cfgPll_HSE0_25MHz, true);
  }
  
#else    
  MDR_CPU_CfgHSI  cfgHSI = MDR_CPU_CFG_HSI_DEF;
  MDR_CPU_SetClock_HSI(&cfgHSI, HSI_TIMEOUT, false);  
#endif

  MDR_OTP_Enable();
  if (fnc == PROG_MODE)
  {
    _delaysOTP = MDR_OTP_GetProgDelays(CPU_CLOCK_HZ);
    MDR_OTP_ProgBegin(&_delaysOTP);  
  }

//  GPIO Init
  MDR_GPIO_Enable(MDRB_FLAG_GPIO);
  MDR_GPIO_Init_PortOUT(MDRB_FLAG_GPIO, MDRB_FLAG_PIN_ALL, MDR_PIN_SLOW);    
  MDR_GPIO_SetPins(MDRB_FLAG_GPIO, MDRB_FLAG_PIN_Ex); 	
 
  
  return (0);                                  // Finished without Errors
}


/*
 *  De-Initialize Flash Programming Functions
 *    Parameter:      fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */
int UnInit (unsigned long fnc) 
{
  MDR_GPIO_ClearPins(MDRB_FLAG_GPIO, MDRB_FLAG_PIN_Ex);      
  
	MDR_OTP_ProgEnd();
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
 
  sz = sz >> 2;
  for (i = 0; i < sz; ++i)
  {
    MDR_GPIO_ClearPins(MDRB_FLAG_GPIO, MDRB_FLAG_PIN);
    MDR_Delay(_delaysOTP.delay_HV_PE);
    MDR_GPIO_SetPins(MDRB_FLAG_GPIO, MDRB_FLAG_PIN);
    MDR_Delay(_delaysOTP.delay_A_D);
    MDR_GPIO_ClearPins(MDRB_FLAG_GPIO, MDRB_FLAG_PIN);
    MDR_Delay(_delaysOTP.delay_Prog);
    MDR_GPIO_SetPins(MDRB_FLAG_GPIO, MDRB_FLAG_PIN);
  }
  
  return (0);
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
		if (MDR_OTP_ReadWord(addr) != 0UL)
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
   value = MDR_OTP_ReadWord(adr + (i << 2));  
   if (pData32[i] != value)
     break;
 }
 
 return adr + (i << 2);
}
