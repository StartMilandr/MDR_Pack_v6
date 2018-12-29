/**************************************************************************//**
 * @file     MDR_1986VE3.h
 * @brief    CMSIS Cortex-M1 Core Peripheral Access Layer Header File for
 *           Device MDR1986VE3
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

#ifndef MDR_1986VE3_H
#define MDR_1986VE3_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Milandr
  * @{
  */


/** @addtogroup MDR1986VE3
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
/* =======================================  ARM Cortex-M1 Specific Interrupt Numbers  ======================================== */
  Reset_IRQn                = -15,              /*!< -15  Reset Vector, invoked on Power up and warm reset                     */
  NonMaskableInt_IRQn       = -14,              /*!< -14  Non maskable Interrupt, cannot be stopped or preempted               */
  HardFault_IRQn            = -13,              /*!< -13  Hard Fault, all classes of Fault                                     */
  SVCall_IRQn               =  -5,              /*!< -5 System Service Call via SVC instruction                                */
  PendSV_IRQn               =  -2,              /*!< -2 Pendable request for system service                                    */
  SysTick_IRQn              =  -1,              /*!< -1 System Tick Timer                                                      */

/* ===========================================  MDR1986VE3 Specific Interrupt Numbers  ========================================= */
  MIL_1553B2_IRQn             = 0,      /*!< MIL_STD_1553B2 Interrupt                             */
  MIL_1553B1_IRQn             = 1,      /*!< MIL_STD_1553B1 Interrupt                             */
  USB_IRQn                    = 2,      /*!< USB Host Interrupt                                   */
  CAN1_IRQn	                  = 3,	    /*!< CAN1 Interrupt		                  								  */
  CAN2_IRQn		                = 4,	    /*!< CAN2 Interrupt										                    */
  DMA_IRQn                    = 5,      /*!< DMA Interrupt                                        */
  UART1_IRQn                  = 6,      /*!< UART1 Interrupt                                      */
  UART2_IRQn                  = 7,      /*!< UART2 Interrupt                                      */
  SSP1_IRQn                   = 8,      /*!< SSP1 Interrupt                                       */
  NAND_IRQn	                  = 9,	    /*!< NAND Busy Interrupt										              */
  ARINC429R_IRQn              = 10,     /*!< ARINC429 Receivers R1-R4 Interrupt                   */
  POWER_IRQn                  = 11,     /*!< POWER Detector Interrupt                              */
  WWDG_IRQn                   = 12,     /*!< Window Watchdog Interrupt                            */
  TIMER4_IRQn                 = 13,	    /*!< Timer4 Interrupt									                    */
  TIMER1_IRQn                 = 14,     /*!< Timer1 Interrupt                                     */
  TIMER2_IRQn                 = 15,     /*!< Timer2 Interrupt                                     */
  TIMER3_IRQn                 = 16,     /*!< Timer3 Interrupt                                     */
  ADC_IRQn                    = 17,     /*!< ADC Interrupt                                        */
  ETHERNET1_IRQn       	      = 18,     /*!< Ethernet1 Interrupt                                  */
  SSP3_IRQn	                  = 19,     /*!< SSP3 and SSP4 Interrupt                         	    */
  SSP2_IRQn                   = 20,     /*!< SSP2 Interrupt                                       */
  ARINC429T_IRQn              = 21,	    /*!< ARINC429 Transmitters T1-T4 Interrupt					      */
  KEY_IRQn                    = 22,	    /*!< Keyboard Interrupt                       					  */
  LED_IRQn                    = 23,	    /*!< LED Display Interrupt				                    	  */
  UART34_IRQn                 = 24,	    /*!< UART3 and UART4 Interrupt 					                  */
  AUC_IRQn                    = 25,	    /*!< AudioCodec Interrupt					                        */
  ETHERNET2_IRQn              = 26,     /*!< Ethernet2 Interrupt                                  */
  BKP_IRQn                    = 27,     /*!< Backup and RTC Interrupt                             */
  EXT1_IRQn                   = 28,     /*!< EXT_INT1 Interrupt                                   */
  EXT2_IRQn                   = 29,     /*!< EXT_INT2 Interrupt                                   */
  EXT3_IRQn                   = 30,     /*!< EXT_INT3 Interrupt                                   */
  EXT4_IRQn                   = 31      /*!< EXT_INT4 Interrupt                                   */
} IRQn_Type;

// Одно прерывание на два блока
#define SSP3SSP4_IRQn   SSP3_IRQn
#define SSP4_IRQn       SSP3SSP4_IRQn



/* =========================================================================================================================== */
/* ================                           Processor and Core Peripheral Section                           ================ */
/* =========================================================================================================================== */

/* ===========================  Configuration of the Arm Cortex-M4 Processor and Core Peripherals  =========================== */
#define __CM1_REV                 0x0102    /*!< Core Revision r1p2 */
#define __MPU_PRESENT             0         /*!< Set to 1 if MPU is present */
#define __VTOR_PRESENT            1         /*!< Set to 1 if VTOR is present */
#define __NVIC_PRIO_BITS          2         /*!< Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             0         /*!< Set to 1 if FPU is present */
#define __FPU_DP                  0         /*!< Set to 1 if FPU is double precision FPU (default is single precision FPU) */
#define __ICACHE_PRESENT          0         /*!< Set to 1 if I-Cache is present */
#define __DCACHE_PRESENT          0         /*!< Set to 1 if D-Cache is present */
#define __DTCM_PRESENT            0         /*!< Set to 1 if DTCM is present */


/** @} */ /* End of group Configuration_of_CMSIS */


#include <core_cm1.h>                           /*!< Arm Cortex-M1 processor and core peripherals */
#include "system_MDR1986VE3.h"                  /*!< MDR1986VE3 System */


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

/*===============  RST_Clock ===================*/
#include "MDR_RST_VE3_defs.h"

/*===============  Backup and RST ==============*/
#include "MDR_BKP_VE3_defs.h"

/*===============  EEPROM Controller=============*/
#include "MDR_EEPROM_defs.h"

/*===============  GPIO Port ===================*/
#include "MDR_GPIO_defs.h"

#define MDR_PORT_Type  MDR_PORT_Type__Ext

/*===============  ADC SAR ===================*/
#include "MDR_ADC_VE1VE3_def.h"

/*=========  SSP - Synchronous Serial Port ========*/
#include "MDR_SSP_def.h"

/*=========  WWDT - IWDT ========*/
#include "MDR_WWDT_defs.h"
#include "MDR_IWDT_defs.h"

/*@}*/ /* end of group MDR1986VE3_Peripherals */


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
#define ADDR_FLASH_BASE       0x00000000UL                              /*!< (FLASH     ) Base Address */
#define ADDR_SRAM_BASE        0x20000000UL                              /*!< (SRAM      ) Base Address */
#define ADDR_PERIPH_BASE      0x40000000UL                              /*!< (Peripheral) Base Address */

/* Peripheral memory map */
#define ADDR_EEPROM_BASE      0x40018000UL                              /*!< EEPROM Controller           */
#define ADDR_RST_CLOCK_BASE   0x40020000UL                              /*!< RST_CLOCK Base Address      */
#define ADDR_ADC_BASE         0x40088000UL                              /*!< ADC SAR Base Address        */
#define ADDR_BKP_BASE         0x400D8000UL                              /*!< Backup and RTC Base Address */

#define ADDR_PORTA_BASE       0x400A8000UL                              /*!< GPIO PORT_A Base Address */
#define ADDR_PORTB_BASE       0x400B0000UL                              /*!< GPIO PORT_B Base Address */
#define ADDR_PORTC_BASE       0x400B8000UL                              /*!< GPIO PORT_C Base Address */
#define ADDR_PORTD_BASE       0x400C0000UL                              /*!< GPIO PORT_D Base Address */
#define ADDR_PORTE_BASE       0x400C8000UL                              /*!< GPIO PORT_E Base Address */
#define ADDR_PORTF_BASE       0x400E8000UL                              /*!< GPIO PORT_F Base Address */
#define ADDR_PORTG_BASE       0x40118000UL                              /*!< GPIO PORT_G Base Address */
#define ADDR_PORTH_BASE       0x40138000UL                              /*!< GPIO PORT_H Base Address */
#define ADDR_PORTI_BASE       0x40140000UL                              /*!< GPIO PORT_I Base Address */

#define ADDR_SSP1_BASE        0x40040000UL                              /*!< SSP Base Address      */
#define ADDR_SSP2_BASE        0x400A0000UL
#define ADDR_SSP3_BASE        0x400F8000UL
#define ADDR_SSP4_BASE        0x40130000UL

#define ADDR_WWDT_BASE         0x40060000UL
#define ADDR_IWDT_BASE         0x40068000UL



/** @} */ /* End of group Device_Peripheral_peripheralAddr */


/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_declaration
  * @{
  */

#define MDR_EEPROM                     ((MDR_EEPROM_Type    *) ADDR_EEPROM_BASE)
#define MDR_CLOCK                      ((MDR_RST_CLOCK_Type *) ADDR_RST_CLOCK_BASE)
#define MDR_BKP                        ((MDR_BKP_Type       *) ADDR_BKP_BASE)

#define MDR_ADC                        ((MDR_ADC_Type       *) ADDR_ADC_BASE)
#define MDR_ADC1                       ((MDR_ADCx_ItemType  *) ADDR_ADC_BASE)

#define MDR_PORTA                      ((MDR_PORT_Type 	*) ADDR_PORTA_BASE)
#define MDR_PORTB                      ((MDR_PORT_Type 	*) ADDR_PORTB_BASE)
#define MDR_PORTC                      ((MDR_PORT_Type 	*) ADDR_PORTC_BASE)
#define MDR_PORTD                      ((MDR_PORT_Type 	*) ADDR_PORTD_BASE)
#define MDR_PORTE                      ((MDR_PORT_Type 	*) ADDR_PORTE_BASE)
#define MDR_PORTF                      ((MDR_PORT_Type 	*) ADDR_PORTF_BASE)
#define MDR_PORTG                      ((MDR_PORT_Type 	*) ADDR_PORTG_BASE)
#define MDR_PORTH                      ((MDR_PORT_Type 	*) ADDR_PORTH_BASE)
#define MDR_PORTI                      ((MDR_PORT_Type 	*) ADDR_PORTI_BASE)

#define MDR_SSP1                       ((MDR_SSP_Type *)   ADDR_SSP1_BASE)
#define MDR_SSP2                       ((MDR_SSP_Type *)   ADDR_SSP2_BASE)
#define MDR_SSP3                       ((MDR_SSP_Type *)   ADDR_SSP3_BASE)
#define MDR_SSP4                       ((MDR_SSP_Type *)   ADDR_SSP4_BASE)

#define MDR_WWDT                       ((MDR_WWDT_Type*)   ADDR_WWDT_BASE)
#define MDR_IWDT                       ((MDR_IWDT_Type*)   ADDR_IWDT_BASE)

/* =========================================================================================================================== */
/* ================                                  SPL_Configs                                   ================ */
/* =========================================================================================================================== */

#define   MDR_EXIST_HSE2

//  Clock Enable bits
#define   MDR_CLK_EN_REG_EEPROM     PER_CLOCK
#define   MDR_CLK_EN_REG_EEPROM_b   PER_CLOCK_b

#define   MDR_CLK_EN_REG_PER        PER_CLOCK
#define   MDR_CLK_EN_REG_PER_b      PER_CLOCK_b

#define   MDR_CLK_EN_REG_BKP        PER_CLOCK
#define   MDR_CLK_EN_REG_BKP_b      PER_CLOCK_b

#define   MDR_CLK_EN_ADDR_PORT_A    &MDR_CLOCK->PER_CLOCK
#define   MDR_CLK_EN_ADDR_PORT_B    &MDR_CLOCK->PER_CLOCK
#define   MDR_CLK_EN_ADDR_PORT_C    &MDR_CLOCK->PER_CLOCK
#define   MDR_CLK_EN_ADDR_PORT_D    &MDR_CLOCK->PER_CLOCK
#define   MDR_CLK_EN_ADDR_PORT_E    &MDR_CLOCK->PER_CLOCK
#define   MDR_CLK_EN_ADDR_PORT_F    &MDR_CLOCK->PER_CLOCK
#define   MDR_CLK_EN_ADDR_PORT_G    &MDR_CLOCK->PER2_CLOCK
#define   MDR_CLK_EN_ADDR_PORT_H    &MDR_CLOCK->PER2_CLOCK
#define   MDR_CLK_EN_ADDR_PORT_I    &MDR_CLOCK->PER2_CLOCK

#define   MDR_CLK_EN_BIT_PORT_A     MDR_RST_PER__PORTA_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_B     MDR_RST_PER__PORTB_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_C     MDR_RST_PER__PORTC_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_D     MDR_RST_PER__PORTD_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_E     MDR_RST_PER__PORTE_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_F     MDR_RST_PER__PORTF_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_G     MDR_RST_PER2__PORTG_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_H     MDR_RST_PER2__PORTH_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_I     MDR_RST_PER2__PORTI_CLK_EN_Pos

#define   MDR_ADC_IN_PORTD

//  SSP Block Clock enable
#define   MDR_CLK_EN_ADDR_SSP1        (&MDR_CLOCK->PER_CLOCK)
#define   MDR_CLK_EN_ADDR_SSP2        (&MDR_CLOCK->PER_CLOCK)
#define   MDR_CLK_EN_ADDR_SSP3        (&MDR_CLOCK->PER_CLOCK)
#define   MDR_CLK_EN_ADDR_SSP4        (&MDR_CLOCK->PER2_CLOCK)

#define   MDR_CLK_EN_MASK_SSP1          MDR_RST_PER__SSP1_CLK_EN_Msk
#define   MDR_CLK_EN_MASK_SSP2          MDR_RST_PER__SSP2_CLK_EN_Msk
#define   MDR_CLK_EN_MASK_SSP3          MDR_RST_PER__SSP3_CLK_EN_Msk
#define   MDR_CLK_EN_MASK_SSP4          MDR_RST_PER2__SSP4_CLK_EN_Msk

//  SSP_Clock freq configs
#define   MDR_SSP_CLOCK_ADDR_SSP1     (&MDR_CLOCK->SSP_CLOCK)
#define   MDR_SSP_CLOCK_ADDR_SSP2     (&MDR_CLOCK->SSP_CLOCK)
#define   MDR_SSP_CLOCK_ADDR_SSP3     (&MDR_CLOCK->SSP_CLOCK)
#define   MDR_SSP_CLOCK_ADDR_SSP4     (&MDR_CLOCK->UART_SSP_CLOCK)


#define   MDR_SSP_CLOCK_ENA_MSK_SSP1    MDR_RST_SSP__SSP1_CLK_EN_Msk
#define   MDR_SSP_CLOCK_ENA_MSK_SSP2    MDR_RST_SSP__SSP2_CLK_EN_Msk
#define   MDR_SSP_CLOCK_ENA_MSK_SSP3    MDR_RST_SSP__SSP3_CLK_EN_Msk
#define   MDR_SSP_CLOCK_ENA_MSK_SSP4    MDR_RST_UARTSSP__SSP4_CLK_EN_Msk

#define   MDR_SSP_CLOCK_BRG_POS_SSP1    MDR_RST_SSP__SSP1_BRG_Pos
#define   MDR_SSP_CLOCK_BRG_POS_SSP2    MDR_RST_SSP__SSP2_BRG_Pos
#define   MDR_SSP_CLOCK_BRG_POS_SSP3    MDR_RST_SSP__SSP3_BRG_Pos
#define   MDR_SSP_CLOCK_BRG_POS_SSP4    MDR_RST_UARTSSP__SSP4_BRG_Pos

#define   MDR_SSP_CLOCK_BRG_CLR_Mask    0x7UL


/** @} */ /* End of group MDR1986VE3 */

/** @} */ /* End of group Milandr */

#ifdef __cplusplus
}
#endif

#endif  /* MDR_1986VE3_H */
