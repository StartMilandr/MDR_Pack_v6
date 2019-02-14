/**************************************************************************//**
 * @file     MDR_1986VE4.h
 * @brief    CMSIS Cortex-M0 Core Peripheral Access Layer Header File for
 *           Device MDR1986VE4
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

#ifndef MDR_1986VE4_H
#define MDR_1986VE4_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Milandr
  * @{
  */


/** @addtogroup MDR1986VE4
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
/* =======================================  ARM Cortex-M0 Specific Interrupt Numbers  ======================================== */

  Reset_IRQn                = -15,              /*!< -15  Reset Vector, invoked on Power up and warm reset                     */
  NonMaskableInt_IRQn       = -14,              /*!< -14  Non maskable Interrupt, cannot be stopped or preempted               */
  HardFault_IRQn            = -13,              /*!< -13  Hard Fault, all classes of Fault                                     */
  SVCall_IRQn               =  -5,              /*!< -5 System Service Call via SVC instruction                                */
  PendSV_IRQn               =  -2,              /*!< -2 Pendable request for system service                                    */
  SysTick_IRQn              =  -1,              /*!< -1 System Tick Timer                                                      */

/* ===========================================  MDR1986VE4 Specific Interrupt Numbers  ========================================= */
	DMA_IRQn                  = 0,                /*!< DMA Interrupt              */
	UART1_IRQn                = 1,                /*!< UART1  Interrupt           */
	UART2_IRQn                = 2,                /*!< UART2  Interrupt           */
	SSP1_IRQn                 = 3,                /*!< SSP1  Interrupt            */
	POWER_IRQn                = 4,                /*!< POWER Interrupt            */
	WWDG_IRQn                 = 5,                /*!< WWDG Interrupt             */
	TIMER1_IRQn               = 6,                /*!< Timer1  Interrupt          */
	TIMER2_IRQn               = 7,                /*!< Timer2  Interrupt          */
	ADC_IRQn                  = 8,                /*!< ADC  Interrupt             */
	COMP_IRQn                 = 9,                /*!< Comparator Interrupt       */
	BKP_IRQn                  = 10,               /*!< Backup and RTC Interrupt   */
	EXT1_IRQn                 = 11,               /*!< EXT_INT0  Interrupt        */
	EXT2_IRQn                 = 12,               /*!< EXT_INT1  Interrupt        */
	EXT3_IRQn                 = 13,               /*!< EXT_INT2  Interrupt        */
	ADCUI_CH1_IRQn            = 14,               /*!< ADCIU_CH1 Interrupt        */
	ADCUI_CH2_IRQn            = 15,               /*!< ADCIU_CH2 Interrupt        */
	ADCUI_CH3_IRQn            = 16,               /*!< ADCIU_CH3 Interrupt        */
	ADCUI_CH4_IRQn            = 17,               /*!< ADCIU_CH4 Interrupt        */
	ADCUI_CH5_IRQn            = 18,               /*!< ADCIU_CH5 Interrupt        */
	ADCUI_CH6_IRQn            = 19,               /*!< ADCIU_CH6 Interrupt        */
	ADCUI_CH7_IRQn            = 20,               /*!< ADCIU_CH7 Interrupt        */
	ADCUI_CH8_IRQn            = 21,               /*!< ADCIU_CH8 Interrupt        */
	ADCUI_IRQn                = 22                /*!< ADCIU Interrupt            */
} IRQn_Type;



/* =========================================================================================================================== */
/* ================                           Processor and Core Peripheral Section                           ================ */
/* =========================================================================================================================== */

/* ===========================  Configuration of the Arm Cortex-M0 Processor and Core Peripherals  =========================== */
#define __CM0_REV                 0x0201    /*!< Core Revision r2p1 */
#define __MPU_PRESENT             0         /*!< Set to 1 if MPU is present */
#define __VTOR_PRESENT            0         /*!< Set to 1 if VTOR is present */
#define __NVIC_PRIO_BITS          2         /*!< Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             0         /*!< Set to 1 if FPU is present */
#define __FPU_DP                  0         /*!< Set to 1 if FPU is double precision FPU (default is single precision FPU) */
#define __ICACHE_PRESENT          0         /*!< Set to 1 if I-Cache is present */
#define __DCACHE_PRESENT          0         /*!< Set to 1 if D-Cache is present */
#define __DTCM_PRESENT            0         /*!< Set to 1 if DTCM is present */


/** @} */ /* End of group Configuration_of_CMSIS */

#include <core_cm0.h>                           /*!< Arm Cortex-M0 processor and core peripherals */
#include "system_MDR1986VE4.h"                  /*!< MDR1986VE4 System */


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
#include "MDR_RST_VE4_defs.h"

/*===============  Backup and RST ==============*/
#include "MDR_BKP_VE4x_defs.h"

/*===============  EEPROM Controller=============*/
#include "MDR_EEPROM_18MHz_defs.h"

/*===============  GPIO Port ===================*/
#include "MDR_GPIO_defs.h"

#define MDR_PORT_Type  MDR_PORT_Type__Base

/*===============  ADC SAR ===================*/
#include "MDR_ADC_VE4VKx_def.h"

/*=========  SSP - Synchronous Serial Port ========*/
#include "MDR_SSP_def.h"

/*=========  WWDT - IWDT ========*/
#include "MDR_WWDT_defs.h"
#include "MDR_IWDT_defs.h"

/*=========  UART ========*/
#include <MDR_UART_Defs.h>

/*@}*/ /* end of group MDR1986VE4_Peripherals */


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
#define ADDR_ADC_BASE         0x40040000UL                              /*!< ADC SAR Base Address        */
#define ADDR_BKP_BASE         0x40060000UL                              /*!< Backup and RTC Base Address */

#define ADDR_PORTA_BASE       0x40080000UL                              /*!< GPIO PORT_A Base Address */
#define ADDR_PORTB_BASE       0x40088000UL                              /*!< GPIO PORT_B Base Address */
#define ADDR_PORTC_BASE       0x40090000UL                              /*!< GPIO PORT_C Base Address */

#define ADDR_SSP1_BASE        0x40000000UL                              /*!< SSP Base Address      */

#define ADDR_WWDT_BASE         0x40048000UL
#define ADDR_IWDT_BASE         0x40050000UL

#define ADDR_UART1_BASE        0x40008000UL
#define ADDR_UART2_BASE        0x40010000UL

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

#define MDR_SSP1                       ((MDR_SSP_Type *)   ADDR_SSP1_BASE)

#define MDR_WWDT                       ((MDR_WWDT_Type*)   ADDR_WWDT_BASE)
#define MDR_IWDT                       ((MDR_IWDT_Type*)   ADDR_IWDT_BASE)

#define MDR_UART1                      ((MDR_UART_Type 	    *) ADDR_UART1_BASE)
#define MDR_UART2                      ((MDR_UART_Type 	    *) ADDR_UART2_BASE)

/* =========================================================================================================================== */
/* ================                                       SPL_Configs                                         ================ */
/* =========================================================================================================================== */

//  Clock Enable bits
#define   MDR_CLK_EN_REG_PER              PER2_CLOCK
#define   MDR_CLK_EN_REG_PER_b            PER2_CLOCK_b

//----------------    EEPROM Definitions  --------------------
#define   MDR_CLK_EN_REG_EEPROM           PER2_CLOCK
#define   MDR_CLK_EN_REG_EEPROM_b         PER2_CLOCK_b
#define   MDR_RST_PER__EEPROM_CLK_EN_Pos  MDR_RST_PER2__EEPROM_CLK_EN_Pos

//----------------    BKP Definitions  --------------------
#define   MDR_CLK_EN_REG_BKP              PER2_CLOCK
#define   MDR_CLK_EN_REG_BKP_b            PER2_CLOCK_b
#define   MDR_RST_PER__BKP_CLK_EN_Pos     MDR_RST_PER2__BKP_CLK_EN_Pos

//----------------    PORT Definitions  --------------------
#define   MDR_CLK_EN_ADDR_PORT_A          &MDR_CLOCK->PER2_CLOCK
#define   MDR_CLK_EN_ADDR_PORT_B          &MDR_CLOCK->PER2_CLOCK
#define   MDR_CLK_EN_ADDR_PORT_C          &MDR_CLOCK->PER2_CLOCK

#define   MDR_CLK_EN_BIT_PORT_A           MDR_RST_PER2__PORTA_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_B           MDR_RST_PER2__PORTB_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_C           MDR_RST_PER2__PORTC_CLK_EN_Pos

#define   MDR_JTAG_A_PORT                 MDR_PORTA
#define   MDR_JTAG_A_PINS                 0x000000C0UL
#define   MDR_JTAG_A_PINS_FUNC            0x0000F000UL
#define   MDR_JTAG_A_PINS_PD              0x00C000C0UL

//----------------    ADC Definitions  --------------------
#define   MDR_ADC_CLK_LIKE_VE4
//  ADC pins in Port_C and Port_B
#define   MDR_ADC_IN_PORTS_CB

//----------------    SSP Definitions  --------------------
//  SSP Block Clock enable
#define   MDR_SSP1_CLK_EN_ADDR          (&MDR_CLOCK->PER2_CLOCK)
#define   MDR_SSP1_CLK_EN_MSK             MDR_RST_PER2__SSP1_CLK_EN_Msk

//  SSP_Clock freq configs
#define   MDR_SSP1_CLOCK_GATE_ADDR      (&MDR_CLOCK->SSP_CLOCK)
#define   MDR_SSP1_CLOCK_GATE_ENA_MSK     MDR_RST_SSP__SSP1_CLK_EN_Msk
#define   MDR_SSP1_CLOCK_GATE_BRG_POS     MDR_RST_SSP__SSP1_BRG_Pos

#define   MDR_SSP_CLOCK_FROM_PER_CLOCK

//----------------    UART Definitions  --------------------
//  UART Block Clock enable
#define   MDR_UART1_CLK_EN_ADDR         (&MDR_CLOCK->PER2_CLOCK)
#define   MDR_UART1_CLK_EN_MSK            MDR_RST_PER2__UART1_CLK_EN_Msk
#define   MDR_UART2_CLK_EN_ADDR         (&MDR_CLOCK->PER2_CLOCK)
#define   MDR_UART2_CLK_EN_MSK            MDR_RST_PER2__UART2_CLK_EN_Msk

//  UART_ClockGate configs
#define   MDR_UART1_CLOCK_GATE_ADDR     (&MDR_CLOCK->UART_CLOCK)
#define   MDR_UART1_CLOCK_GATE_ENA_MSK    MDR_RST_UART__UART1_CLK_EN_Msk
#define   MDR_UART1_CLOCK_GATE_BRG_POS    MDR_RST_UART__UART1_BRG_Pos

#define   MDR_UART2_CLOCK_GATE_ADDR     (&MDR_CLOCK->UART_CLOCK)
#define   MDR_UART2_CLOCK_GATE_ENA_MSK    MDR_RST_UART__UART2_CLK_EN_Msk
#define   MDR_UART2_CLOCK_GATE_BRG_POS    MDR_RST_UART__UART2_BRG_Pos

#define   MDR_UART_CLOCK_FROM_PER_CLOCK


/** @} */ /* End of group MDR1986VE4 */

/** @} */ /* End of group Milandr */

#ifdef __cplusplus
}
#endif

#endif  /* MDR_1986VE4_H */
