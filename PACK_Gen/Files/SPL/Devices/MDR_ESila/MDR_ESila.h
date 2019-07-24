/**************************************************************************//**
 * @file     MDR_ESila.h
 * @brief    CMSIS Cortex-M4 Core Peripheral Access Layer Header File for
 *           Device MDR_ESila
 * @version  V5.00
 * @date     10. January 2018
 ******************************************************************************/
/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MDR_ESILA_H
#define MDR_ESILA_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Milandr
  * @{
  */


/** @addtogroup ESila
  * @{
  */


/** @addtogroup Configuration_of_CMSIS
  * @{
  */



/* =========================================================================================================================== */
/* ================                                Interrupt Number Definition                                ================ */
/* =========================================================================================================================== */

typedef enum IRQn
{
/******  Cortex-M4 Processor Exceptions Numbers ***************************************/
  NonMaskableInt_IRQn     = -14,    /*!< 2 Non Maskable Interrupt                     */
  HardFault_IRQn          = -13,    /*!< 3 Cortex-M4 Hard Fault Interrupt             */
  MemoryManagement_IRQn		=	-12,		/*!< 4 Cortex-M4 Memory Management Interrupt      */
  BusFault_IRQn				    =	-11,		/*!< 5 Cortex-M4 Bus Fault Interrupt			        */
  UsageFault_IRQn		      = -10,		/*!< 6 Cortex-M4 Usage Fault Interrupt			      */
  SVCall_IRQn             = -5,     /*!< 11 Cortex-M4 SV Call Interrupt               */
  PendSV_IRQn             = -2,     /*!< 14 Cortex-M4 Pend SV Interrupt               */
  SysTick_IRQn            = -1,     /*!< 15 Cortex-M4 System Tick Interrupt           */

/******  ESila specific Interrupt Numbers *******************************************/                                       
  FT_RESET0_4_IRQn        = 32,
  FT_EVENT0_4_IRQn        = 33,
  FT_EVENT5_8_IRQn        = 34,
  FT_EVENT9_12_IRQn       = 35,
  CLK_IRQn                = 36,
  //POWER_IRQn              = 37,
  RTC_IRQn                = 38,
  BKP_IRQn                = 39,
  EBC_ERROR0_IRQn         = 40,
  EBC_ERROR1_IRQn         = 41,
  EBC_ERROR2_IRQn         = 42,
  EBC_ERROR3_IRQn         = 43,
  EBC_ERROR4_IRQn         = 44,
  EBC_ERROR5_IRQn         = 45,
  EBC_ERROR6_IRQn         = 46,
  EBC_ERROR7_IRQn         = 47,
  SCRB_ERR_IRQn           = 48,
  SCRB_DONE_IRQn          = 49,
  DMA_ERR_IRQn            = 50,
  DMA_DONE0_IRQn          = 51,
  DMA_DONE1_IRQn          = 52,
  DMA_DONE2_IRQn          = 53,
  DMA_DONE3_IRQn          = 54,
  DMA_DONE4_IRQn          = 55,
  DMA_DONE5_IRQn          = 56,
  DMA_DONE6_IRQn          = 57,
  DMA_DONE7_IRQn          = 58,
  DMA_DONE8_IRQn          = 59,
  DMA_DONE9_IRQn          = 60,
  DMA_DONE10_IRQn         = 61,
  DMA_DONE11_IRQn         = 62,
  DMA_DONE12_IRQn         = 63,
  DMA_DONE13_IRQn         = 64,
  DMA_DONE14_IRQn         = 65,
  DMA_DONE15_IRQn         = 66,  
  DMA_DONE16_IRQn         = 67,
  DMA_DONE17_IRQn         = 68,
  DMA_DONE18_IRQn         = 69,
  DMA_DONE19_IRQn         = 70,
  DMA_DONE20_IRQn         = 71,
  DMA_DONE21_IRQn         = 72,
  DMA_DONE22_IRQn         = 73,
  DMA_DONE23_IRQn         = 74,
  DMA_DONE24_IRQn         = 75,
  DMA_DONE25_IRQn         = 76,  
  DMA_DONE26_IRQn         = 77,
  DMA_DONE27_IRQn         = 78,
  DMA_DONE28_IRQn         = 79,
  DMA_DONE29_IRQn         = 80,
  DMA_DONE30_IRQn         = 81,
  DMA_DONE31_IRQn         = 82,  
  PORTA_IRQn         	    = 83,
  PORTB_IRQn         	    = 84,
  PORTC_IRQn         	    = 85,
  PORTD_IRQn         	    = 86,

  ETH1_IRQn     	        = 89,
  CAN1_IRQn         	    = 90,
  CAN2_IRQn         	    = 91,

  SSP1_IRQn         	    = 92,
  SSP1_RX_IRQn       	    = 93,
  SSP1_TX_IRQn       	    = 94,
  SSP1_ROR_IRQn      	    = 95,
  SSP1_RT_IRQn      	    = 96,
  SSP1_RX_FIFO_IRQn       = 97,
  SSP1_TX_FIFO_IRQn       = 98,
  SSP1_BUSY_IRQn     	    = 99,
  SSP2_IRQn         	    = 100,
  SSP2_RX_IRQn       	    = 101,
  SSP2_TX_IRQn       	    = 102,
  SSP2_ROR_IRQn      	    = 103,
  SSP2_RT_IRQn      	    = 104,
  SSP2_RX_FIFO_IRQn       = 105,
  SSP2_TX_FIFO_IRQn       = 106,
  SSP2_BUSY_IRQn     	    = 107,

  UART1_IRQn         	    = 108,
  UART1_BUSY_IRQn    	    = 109,
  UART1_TX_FIFO_IRQn 	    = 110,
  UART1_RX_FIFO_IRQn 	    = 111,
  UART1_ERR_IRQn 	        = 112,
  UART1_RT_IRQn 	        = 113,
  UART1_TX_IRQn 	        = 114,
  UART1_RX_IRQn 	        = 115,
  UART1_MS_IRQn 	        = 116,
  UART2_IRQn         	    = 117,
  UART2_BUSY_IRQn    	    = 118,
  UART2_TX_FIFO_IRQn 	    = 119,
  UART2_RX_FIFO_IRQn 	    = 120,
  UART2_ERR_IRQn 	        = 121,
  UART2_RT_IRQn 	        = 122,
  UART2_TX_IRQn 	        = 123,
  UART2_RX_IRQn 	        = 124,
  UART2_MS_IRQn 	        = 125,
  UART3_IRQn         	    = 126,
  UART3_BUSY_IRQn    	    = 127,
  UART3_TX_FIFO_IRQn 	    = 128,
  UART3_RX_FIFO_IRQn 	    = 129,
  UART3_ERR_IRQn 	        = 130,
  UART3_RT_IRQn 	        = 131,
  UART3_TX_IRQn 	        = 132,
  UART3_RX_IRQn 	        = 133,
  UART3_MS_IRQn 	        = 134,
  UART4_IRQn         	    = 135,
  UART4_BUSY_IRQn    	    = 136,
  UART4_TX_FIFO_IRQn 	    = 137,
  UART4_RX_FIFO_IRQn 	    = 138,
  UART4_ERR_IRQn 	        = 139,
  UART4_RT_IRQn 	        = 140,
  UART4_TX_IRQn 	        = 141,
  UART4_RX_IRQn 	        = 142,
  UART4_MS_IRQn 	        = 143,  

  USB_IRQn        		    = 144,
  MIL1_IRQn               = 145,
  DAC1_IRQn         	    = 146,
  DAC2_IRQn         	    = 147,
  DAC3_IRQn         	    = 148,
  DAC4_IRQn         	    = 149,
  DAC1_FIFO_IRQn         	= 150,
  DAC2_FIFO_IRQn         	= 151,
  DAC3_FIFO_IRQn         	= 152,
  DAC4_FIFO_IRQn         	= 153,  

  TIMER1_IRQn        	    = 154,
  TIMER2_IRQn             = 155,
  TIMER3_IRQn        	    = 156,
  TIMER4_IRQn        	    = 157,
  QENC1_IRQn       	      = 158,
  QENC2_IRQn       	      = 159,
  
  CAP1_IRQn        	      = 162,
  CAP2_IRQn               = 163,
  CAP3_IRQn        	      = 164,
  CAP4_IRQn        	      = 165,

  PWM1_IRQn        	      = 166,
  PWM2_IRQn        	      = 167,
  PWM3_IRQn        	      = 168,
  PWM4_IRQn        	      = 169,
  PWM5_IRQn        	      = 170,
  PWM6_IRQn        	      = 171,
  PWM7_IRQn        	      = 172,
  PWM8_IRQn        	      = 173,
  PWM9_IRQn        	      = 174,
  PWM1_TZ_IRQn        	  = 175,
  PWM2_TZ_IRQn        	  = 176,
  PWM3_TZ_IRQn        	  = 177,
  PWM4_TZ_IRQn        	  = 178,
  PWM5_TZ_IRQn        	  = 179,
  PWM6_TZ_IRQn        	  = 180,
  PWM7_TZ_IRQn        	  = 181,
  PWM8_TZ_IRQn        	  = 182,
  PWM9_TZ_IRQn        	  = 183,
  PWM1_FIFO_IRQn        	= 184,
  PWM2_FIFO_IRQn        	= 185,
  PWM3_FIFO_IRQn        	= 186,
  PWM4_FIFO_IRQn        	= 187,
  PWM5_FIFO_IRQn        	= 188,
  PWM6_FIFO_IRQn        	= 189,
  PWM7_FIFO_IRQn        	= 190,
  PWM8_FIFO_IRQn        	= 191,
  PWM9_FIFO_IRQn        	= 192,

  CMP1_IRQn        	      = 193,
  CMP2_IRQn        	      = 194,
  CMP3_IRQn        	      = 195,
  CMP4_IRQn        	      = 196,

  ADC_A1_IRQn         	  = 197,
  ADC_A1_FIFO_IRQn     	  = 198,
  ADC_B1_IRQn         	  = 199,
  ADC_B1_FIFO_IRQn     	  = 200,
  ADC_C1_IRQn         	  = 201,
  ADC_C1_FIFO_IRQn     	  = 202,
  ADC_A2_IRQn         	  = 203,
  ADC_A2_FIFO_IRQn     	  = 204,
  ADC_B2_IRQn         	  = 205,
  ADC_B2_FIFO_IRQn     	  = 206,
  ADC_C2_IRQn         	  = 207,
  ADC_C2_FIFO_IRQn     	  = 208,  

  CORDIC_IRQn     	      = 209,

  MIL2_IRQn               = 211,
} IRQn_Type;




/* =========================================================================================================================== */
/* ================                           Processor and Core Peripheral Section                           ================ */
/* =========================================================================================================================== */

/* --------  Configuration of the Cortex-M4 Processor and Core Peripherals  ------- */
#define __CM4_REV                 0x0001U   /* Core revision r0p1 */
#define __MPU_PRESENT             1U        /* MPU present */
#define __VTOR_PRESENT            1U        /* VTOR present */
#define __NVIC_PRIO_BITS          3U        /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0U        /* Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             1U        /* FPU present */



/** @} */ /* End of group Configuration_of_CMSIS */


#include <core_cm4.h>                          /*!< Arm Cortex-M4 processor and core peripherals */
#include "system_ESila.h"                 /*!< ESila System */


/* ========================================  Start of section using anonymous unions  ======================================== */
#if   defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


/* =========================================================================================================================== */
/* ================                            Device Specific Peripheral Section                             ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripherals
  * @{
  */

#define MDR_KEY_UNLOCK    0x8555AAA1UL

/*===============  RST_Clock ===================*/
#include <MDR_RST_VE8x_defs.h>
#include <MDR_RST_ESila_defs.h>

/*===============  BKP ===================*/
#include <MDR_BKP_ESila_defs.h>


/*===============  EEPROM Controller=============*/
typedef struct
{
  __IO  uint32_t KEY;
  __IO  uint32_t CNTR;
  __IO  uint32_t ADR;
  __IO  uint32_t WDATA3;
  __IO  uint32_t WDATA2;
  __IO  uint32_t WDATA1;
  __IO  uint32_t WDATA0;
  __IO  uint32_t WECC0;
  __IO  uint32_t WECC1;
  __IO  uint32_t RDATA3;
  __IO  uint32_t RDATA2;
  __IO  uint32_t RDATA1;
  __IO  uint32_t RDATA0;
  __IO  uint32_t RECC0;
  __IO  uint32_t RECC1;
  __IO  uint32_t ECCCS;
  __IO  uint32_t ECCADR;
  __IO  uint32_t ECCDATA;
  __IO  uint32_t ECCECC;
  __IO  uint32_t BLOCK;
} MDR_EEPROM_Type;

#define MDR_EEPROM_CMD_DELAY_Msk  0xFUL 
#define MDR_EEPROM_CMD_DELAY_Pos  0x0

typedef enum {
  EEPROM_Delay_Forbiden = 0,     //  
  EEPROM_Delay_le32MHz  = 1,     //  31,25 MHz
  EEPROM_Delay_le63MHz  = 2,     //  62,50 MHz
  EEPROM_Delay_le94MHz  = 3,     //  93,75 MHz
  EEPROM_Delay_le125MHz = 4,     // 125,00 MHz
  EEPROM_Delay_le157MHz = 5,     // 156,25 MHz
  EEPROM_Delay_le188MHz = 6,     // 187,50 MHz
  EEPROM_Delay_le219MHz = 7,     // 218,75 MHz
  EEPROM_Delay_le250MHz = 8,     // 250,00 MHz
  EEPROM_Delay_le282MHz = 9,     // 281,25 MHz
  EEPROM_Delay_le313MHz = 10,    // 312,50 MHz
  EEPROM_Delay_le344MHz = 11,    // 343,75 MHz
  EEPROM_Delay_le374MHz = 12,    // 374,00 MHz
  EEPROM_Delay_le407MHz = 13,    // 406,25 MHz
  EEPROM_Delay_le438MHz = 14,    // 437,50 MHz
  EEPROM_Delay_le469MHz = 15,    // 468,75 MHz
} MDR_EEPROM_DELAY;


/* ==============  Coparators =================== */
typedef struct
{
  __IO  uint32_t COMP_CNTR;
  __IO  uint32_t COMP_EVNT;
  __IO  uint32_t ANABG_CTRL;
} MDR_COMP_Type;

#define MDR_COMP_ANABG_IREFEN_Pos     0x0UL   
#define MDR_COMP_ANABG_IREFEN_Msk     0x1UL   
#define MDR_COMP_ANABG_BGEN_Pos       0x7UL   
#define MDR_COMP_ANABG_BGEN_Msk       0x80UL   


/*===============  GPIO Port ===================*/
#include <MDR_GPIO_VE8x_defs.h>


/*=========  SSP - Synchronous Serial Port ========*/
#include "MDR_SSP_def.h"

/*=========  UART ========*/
#include <MDR_UART_defs.h>

/*=========  TIMER ========*/
#include <MDR_TimerVE13_defs.h>




/*@}*/ /* end of group ESila_Peripherals */


/* =========================================  End of section using anonymous unions  ========================================= */
#if   defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */

/** @addtogroup Device_Peripheral_peripheralAddr
  * @{
  */


/* Peripheral and SRAM base address */
//#define ADDR_FLASH_BASE       (0x01000000UL)                              /*!< (FLASH     ) Base Address */
#define ADDR_SRAM_BASE        (0x20000000UL)                              /*!< (SRAM      ) Base Address */
#define ADDR_PERIPH_BASE      (0x40000000UL)                              /*!< (Peripheral) Base Address */

/* Peripheral memory map */

#define ADDR_RST_CLOCK_BASE   0x40000000UL                              /*!< RST_CLOCK Base Address      */
#define ADDR_BKP_BASE         0x40001000UL                              /*!< Backup and RTC Base Address */
#define ADDR_EEPROM_BASE      0x40006000UL                              /*!< FLASH Controller           */

#define ADDR_COMP1_BASE       0x400AE000UL
#define ADDR_COMP2_BASE       0x400AF000UL
#define ADDR_COMP3_BASE       0x400B0000UL
#define ADDR_COMP4_BASE       0x400B1000UL


#define ADDR_PORTA_BASE       0x40080000UL                              /*!< GPIO PORT_A Base Address */
#define ADDR_PORTB_BASE       0x40081000UL                              /*!< GPIO PORT_B Base Address */
#define ADDR_PORTC_BASE       0x40082000UL                              /*!< GPIO PORT_C Base Address */
#define ADDR_PORTD_BASE       0x40083000UL                              /*!< GPIO PORT_D Base Address */



#define ADDR_SSP1_BASE        0x40089000UL
#define ADDR_SSP2_BASE        0x4008A000UL

#define ADDR_UART1_BASE       0x4008D000UL
#define ADDR_UART2_BASE       0x4008E000UL
#define ADDR_UART3_BASE       0x4008F000UL
#define ADDR_UART4_BASE       0x40090000UL

#define ADDR_TIMER1_BASE      0x40094000UL
#define ADDR_TIMER2_BASE      0x40095000UL
#define ADDR_TIMER3_BASE      0x40096000UL
#define ADDR_TIMER4_BASE      0x40097000UL



/** @} */ /* End of group Device_Peripheral_peripheralAddr */


/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */

/** @addtogroup Device_Peripheral_declaration
  * @{
  */

#define MDR_CLOCK                      ((MDR_RST_CLOCK_Type *) ADDR_RST_CLOCK_BASE)
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #define MDR_CLOCK_HSE0                 ((MDR_RST_HSE_Type   *) (__IOM uint32_t)(&MDR_CLOCK->HSE0_CLK))
  #define MDR_CLOCK_HSE1                 ((MDR_RST_HSE_Type   *) (__IOM uint32_t)(&MDR_CLOCK->HSE1_CLK))
  #define MDR_CLOCK_PLL0                 ((MDR_RST_PLL_Type   *) (__IOM uint32_t)(&MDR_CLOCK->PLL0_CLK))
  #define MDR_CLOCK_PLL1                 ((MDR_RST_PLL_Type   *) (__IOM uint32_t)(&MDR_CLOCK->PLL1_CLK))
  #define MDR_CLOCK_PLL2                 ((MDR_RST_PLL_Type   *) (__IOM uint32_t)(&MDR_CLOCK->PLL2_CLK))
  #define MDR_CLOCK_PLL3                 ((MDR_RST_PLL_Type   *) (__IOM uint32_t)(&MDR_CLOCK->PLL3_CLK))
#else
  #define MDR_CLOCK_HSE0                 ((MDR_RST_HSE_Type   *) (&MDR_CLOCK->HSE0_CLK))
  #define MDR_CLOCK_HSE1                 ((MDR_RST_HSE_Type   *) (&MDR_CLOCK->HSE1_CLK))
  #define MDR_CLOCK_PLL0                 ((MDR_RST_PLL_Type   *) (&MDR_CLOCK->PLL0_CLK))
  #define MDR_CLOCK_PLL1                 ((MDR_RST_PLL_Type   *) (&MDR_CLOCK->PLL1_CLK))
  #define MDR_CLOCK_PLL2                 ((MDR_RST_PLL_Type   *) (&MDR_CLOCK->PLL2_CLK))
  #define MDR_CLOCK_PLL3                 ((MDR_RST_PLL_Type   *) (&MDR_CLOCK->PLL3_CLK))
#endif

#define MDR_BKP                        ((MDR_BKP_Type       *) ADDR_BKP_BASE)
#define MDR_EEPROM                     ((MDR_EEPROM_Type    *) ADDR_EEPROM_BASE)

#define MDR_PORTA                      ((MDR_PORT_Type 	    *) ADDR_PORTA_BASE)
#define MDR_PORTB                      ((MDR_PORT_Type 	    *) ADDR_PORTB_BASE)
#define MDR_PORTC                      ((MDR_PORT_Type 	    *) ADDR_PORTC_BASE)
#define MDR_PORTD                      ((MDR_PORT_Type 	    *) ADDR_PORTD_BASE)

#define MDR_SSP1                       ((MDR_SSP_Type       *) ADDR_SSP1_BASE)
#define MDR_SSP2                       ((MDR_SSP_Type       *) ADDR_SSP2_BASE)

#define MDR_UART1                      ((MDR_UART_Type 	    *) ADDR_UART1_BASE)
#define MDR_UART2                      ((MDR_UART_Type 	    *) ADDR_UART2_BASE)
#define MDR_UART3                      ((MDR_UART_Type 	    *) ADDR_UART3_BASE)
#define MDR_UART4                      ((MDR_UART_Type 	    *) ADDR_UART4_BASE)

#define MDR_TIMER1                     ((MDR_TIMER_Type 	  *) ADDR_TIMER1_BASE)
#define MDR_TIMER2                     ((MDR_TIMER_Type 	  *) ADDR_TIMER2_BASE)
#define MDR_TIMER3                     ((MDR_TIMER_Type 	  *) ADDR_TIMER3_BASE)
#define MDR_TIMER4                     ((MDR_TIMER_Type 	  *) ADDR_TIMER4_BASE)

//  Timer Channels
#define MDR_TIMER1_CH1                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER1->CCR1))
#define MDR_TIMER1_CH2                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER1->CCR2))
#define MDR_TIMER1_CH3                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER1->CCR3))
#define MDR_TIMER1_CH4                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER1->CCR4))

#define MDR_TIMER2_CH1                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER2->CCR1))
#define MDR_TIMER2_CH2                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER2->CCR2))
#define MDR_TIMER2_CH3                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER2->CCR3))
#define MDR_TIMER2_CH4                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER2->CCR4))

#define MDR_TIMER3_CH1                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER3->CCR1))
#define MDR_TIMER3_CH2                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER3->CCR2))
#define MDR_TIMER3_CH3                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER3->CCR3))
#define MDR_TIMER3_CH4                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER3->CCR4))

#define MDR_TIMER4_CH1                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER4->CCR1))
#define MDR_TIMER4_CH2                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER4->CCR2))
#define MDR_TIMER4_CH3                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER4->CCR3))
#define MDR_TIMER4_CH4                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER4->CCR4))

#define MDR_COMP1                      ((MDR_COMP_Type *) ADDR_COMP1_BASE)
#define MDR_COMP2                      ((MDR_COMP_Type *) ADDR_COMP2_BASE)
#define MDR_COMP3                      ((MDR_COMP_Type *) ADDR_COMP3_BASE)
#define MDR_COMP4                      ((MDR_COMP_Type *) ADDR_COMP4_BASE)



/* =========================================================================================================================== */
/* ================                                  SPL_Configs                                   ================ */
/* =========================================================================================================================== */

//  Clock Enable bits
//----------------    EEPROM Definitions  --------------------
//#define   MDR_CLK_EN_REG_EEPROM     PER_CLOCK
//#define   MDR_CLK_EN_BIT_EEPROM     MDR_RST_PER__EEPROM_CLK_EN_Pos


//----------------    PORT Definitions  --------------------
#define   MDR_CLK_EN_ADDR_PORT_A    &MDR_CLOCK->PER0_CLK
#define   MDR_CLK_EN_ADDR_PORT_B    &MDR_CLOCK->PER0_CLK
#define   MDR_CLK_EN_ADDR_PORT_C    &MDR_CLOCK->PER0_CLK
#define   MDR_CLK_EN_ADDR_PORT_D    &MDR_CLOCK->PER0_CLK

#define   MDR_CLK_EN_BIT_PORT_A     MDR_RST_PER0_PORTA_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_B     MDR_RST_PER0_PORTB_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_C     MDR_RST_PER0_PORTC_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_D     MDR_RST_PER0_PORTD_CLK_EN_Pos

//  Jtag_A: PA[0..4] nTRST, TCK, TMS, TDI, TDO
#define   MDR_JTAG_A_PORT           MDR_PORTA
#define   MDR_JTAG_A_PINS           0x0000001FUL
#define   MDR_JTAG_A_PINS_FUNC      0x000FFFFFUL
#define   MDR_JTAG_A_PINS_PD        0x001F001FUL

//  Jtag_A: PA[1,2] TCK, TMS
#define   MDR_SWD_A_PORT            MDR_PORTA
#define   MDR_SWD_A_PINS            0x00000006UL
#define   MDR_SWD_A_PINS_FUNC       0x00000FF0UL
#define   MDR_SWD_A_PINS_PD         0x00000006UL

//  Jtag_B: PB[4..8] nTRST, TCK, TMS, TDI, TDO
#define   MDR_JTAG_B_PORT           MDR_PORTD
#define   MDR_JTAG_B_PINS           0x00001F00UL
#define   MDR_JTAG_B_PINS_FUNC      0x0FFFFF00UL
#define   MDR_JTAG_B_PINS_PD        0x00001F00UL

#define   MDR_SWD_B_PORT            MDR_PORTD
#define   MDR_SWD_B_PINS            0x00000060UL
#define   MDR_SWD_B_PINS_FUNC       0x0FF00000UL
#define   MDR_SWD_B_PINS_PD         0x00000060UL


// //----------------    SSP Definitions  --------------------
// //  SSP Block Clock enable
// #define   MDR_SSP1_CLK_EN_ADDR          (&MDR_CLOCK->PER_CLOCK)
// #define   MDR_SSP2_CLK_EN_ADDR          (&MDR_CLOCK->PER_CLOCK)

// #define   MDR_SSP1_CLK_EN_MSK             MDR_RST_PER__SSP1_CLK_EN_Msk
// #define   MDR_SSP2_CLK_EN_MSK             MDR_RST_PER__SSP2_CLK_EN_Msk

// //  SSP_Clock freq configs
// #define   MDR_SSP1_CLOCK_GATE_ADDR      (&MDR_CLOCK->SSP_CLOCK)
// #define   MDR_SSP2_CLOCK_GATE_ADDR      (&MDR_CLOCK->SSP_CLOCK)

// #define   MDR_SSP1_CLOCK_GATE_ENA_MSK     MDR_RST_SSP__SSP1_CLK_EN_Msk
// #define   MDR_SSP2_CLOCK_GATE_ENA_MSK     MDR_RST_SSP__SSP2_CLK_EN_Msk

// #define   MDR_SSP1_CLOCK_GATE_BRG_POS     MDR_RST_SSP__SSP1_BRG_Pos
// #define   MDR_SSP2_CLOCK_GATE_BRG_POS     MDR_RST_SSP__SSP2_BRG_Pos


 //----------------    UART Definitions  --------------------
 //  UART Block Clock enable
 //  UART Block Clock enable
 #define   MDR_UART1_CLK_EN_ADDR         (&MDR_CLOCK->PER0_CLK)
 #define   MDR_UART2_CLK_EN_ADDR         (&MDR_CLOCK->PER0_CLK)
 #define   MDR_UART3_CLK_EN_ADDR         (&MDR_CLOCK->PER0_CLK)
 #define   MDR_UART4_CLK_EN_ADDR         (&MDR_CLOCK->PER0_CLK)

 #define   MDR_UART1_CLK_EN_MSK            MDR_RST_PER0_UART1_CLK_EN_Msk
 #define   MDR_UART2_CLK_EN_MSK            MDR_RST_PER0_UART2_CLK_EN_Msk
 #define   MDR_UART3_CLK_EN_MSK            MDR_RST_PER0_UART3_CLK_EN_Msk
 #define   MDR_UART4_CLK_EN_MSK            MDR_RST_PER0_UART4_CLK_EN_Msk

 //  UART_ClockGate configs
 #define   MDR_UART1_CLOCK_GATE_ADDR     (&MDR_CLOCK->UART1_CLK)
 #define   MDR_UART2_CLOCK_GATE_ADDR     (&MDR_CLOCK->UART2_CLK)
 #define   MDR_UART3_CLOCK_GATE_ADDR     (&MDR_CLOCK->UART3_CLK)
 #define   MDR_UART4_CLOCK_GATE_ADDR     (&MDR_CLOCK->UART4_CLK)


// //----------------    TIMER Definitions  --------------------
// //  UART Block Clock enable
// #define   MDR_TIMER1_CLK_EN_ADDR         (&MDR_CLOCK->PER_CLOCK)
// #define   MDR_TIMER2_CLK_EN_ADDR         (&MDR_CLOCK->PER_CLOCK)
// #define   MDR_TIMER3_CLK_EN_ADDR         (&MDR_CLOCK->PER_CLOCK)

// #define   MDR_TIMER1_CLK_EN_MSK            MDR_RST_PER__TIMER1_CLK_EN_Msk
// #define   MDR_TIMER2_CLK_EN_MSK            MDR_RST_PER__TIMER2_CLK_EN_Msk
// #define   MDR_TIMER3_CLK_EN_MSK            MDR_RST_PER__TIMER3_CLK_EN_Msk


// //  UART_ClockGate configs
// #define   MDR_TIMER1_CLOCK_GATE_ADDR     (&MDR_CLOCK->TIM_CLOCK)
// #define   MDR_TIMER2_CLOCK_GATE_ADDR     (&MDR_CLOCK->TIM_CLOCK)
// #define   MDR_TIMER3_CLOCK_GATE_ADDR     (&MDR_CLOCK->TIM_CLOCK)

// #define   MDR_TIMER1_CLOCK_GATE_ENA_MSK    MDR_RST_TIM__TIM1_CLK_EN_Msk
// #define   MDR_TIMER2_CLOCK_GATE_ENA_MSK    MDR_RST_TIM__TIM2_CLK_EN_Msk
// #define   MDR_TIMER3_CLOCK_GATE_ENA_MSK    MDR_RST_TIM__TIM3_CLK_EN_Msk

// #define   MDR_TIMER1_CLOCK_GATE_BRG_POS    MDR_RST_TIM__TIM1_BRG_Pos
// #define   MDR_TIMER2_CLOCK_GATE_BRG_POS    MDR_RST_TIM__TIM2_BRG_Pos
// #define   MDR_TIMER3_CLOCK_GATE_BRG_POS    MDR_RST_TIM__TIM3_BRG_Pos

// //  Enable Count UpDown by external events
// #define MDR_TIMER_Can_UpDown_ByExtEvents



/** @} */ /* End of group ESila */

/** @} */ /* End of group Milandr */

#ifdef __cplusplus
}
#endif

#endif  /* MDR_ESILA_H */
