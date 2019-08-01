/**************************************************************************//**
 * @file     MDR_1986VK214.h
 * @brief    CMSIS Cortex-M0 Core Peripheral Access Layer Header File for
 *           Device MDR1986VK214
 * @version  V5.00
 * @date     10. January 2018
 ******************************************************************************/

#ifndef MDR_1986VK214_H
#define MDR_1986VK214_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Milandr
  * @{
  */


/** @addtogroup MDR1986VK214
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

/* ===========================================  MDR1986VK214 Specific Interrupt Numbers  ========================================= */
	_Reserved_0_IRQn          = 0,                /*!< DReserved Interrupt  */
	UART1_IRQn                = 1,                /*!< UART1  Interrupt     */
	UART2_IRQn                = 2,                /*!< UART2  Interrupt     */
	SSP1_IRQn                 = 3,                /*!< SSP1  Interrupt      */
	POWER_IRQn                = 4,                /*!< POWER Interrupt      */
	WWDG_IRQn                 = 5,                /*!< WWDG Interrupt       */
	TIMER1_IRQn               = 6,                /*!< Timer1  Interrupt    */
	TIMER2_IRQn               = 7,                /*!< Timer2  Interrupt    */
	ADC_IRQn                  = 8,                /*!< ADC  Interrupt       */
	I2C_IRQn                  = 9,                /*!< I2C  Interrupt       */
	BKP_IRQn                  = 10,               /*!< BACKUP  Interrupt    */
	EXT1_IRQn                 = 11,               /*!< EXT_INT0  Interrupt  */
	EXT2_IRQn                 = 12,               /*!< EXT_INT1  Interrupt  */
	EXT3_IRQn                 = 13,               /*!< EXT_INT2  Interrupt  */
  ADCUI_F0_IRQn             = 14,               /*!< ADCIU_F0 Interrupt   */
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
#include "system_MDR1986VK214.h"                /*!< MDR1986VK214 System */


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
#include "MDR_RST_VK214_defs.h"

///*===============  Backup and RST ==============*/
#include "MDR_BKP_VE4x_defs.h"

///*===============  EEPROM Controller=============*/
#include "MDR_EEPROM_18MHz_defs.h"

/*===============  GPIO Port ===================*/
#include "MDR_GPIO_defs.h"

#define MDR_PORT_Type  MDR_PORT_Type__Base

///*===============  ADC SAR ===================*/
#include "MDR_ADC_VE4VKx_def.h"

///*=========  SSP - Synchronous Serial Port ========*/
#include "MDR_SSP_def.h"

///*=========  WWDT - IWDT ========*/
#include "MDR_WWDT_defs.h"
#include "MDR_IWDT_defs.h"

///*=========  LCD Controller ========*/
#include "MDR_LCD_VK214_defs.h"

///*=========  ADC IU ========*/
#include "MDR_ADCUI_VK214_defs.h"

/*=========  UART ========*/
#include <MDR_UART_8Bit_defs.h>

///*=========  TIMER ========*/
#include <MDR_TimerVx_defs.h>

///*=========  POWER ========*/
#include <MDR_PowerVx_defs.h>

/*=========  I2C ========*/
#include <MDR_I2C_defs.h>



/*@}*/ /* end of group MDR1986BE4_Peripherals */


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
#define ADDR_FLASH_BASE        0x00000000UL                              /*!< (FLASH     ) Base Address */
#define ADDR_SRAM_BASE         0x20000000UL                              /*!< (SRAM      ) Base Address */
#define ADDR_PERIPH_BASE       0x40000000UL                              /*!< (Peripheral) Base Address */

/* Peripheral memory map */
#define ADDR_EEPROM_BASE       0x40018000UL                              /*!< EEPROM Controller           */
#define ADDR_RST_CLOCK_BASE    0x40020000UL                              /*!< RST_CLOCK Base Address      */
#define ADDR_ADC_BASE          0x40040000UL                              /*!< ADC SAR Base Address        */
#define ADDR_BKP_BASE          0x40060000UL                              /*!< Backup and RTC Base Address */

#define ADDR_PORTA_BASE        0x40080000UL                              /*!< GPIO PORT_A Base Address */
#define ADDR_PORTB_BASE        0x40088000UL                              /*!< GPIO PORT_B Base Address */
#define ADDR_PORTC_BASE        0x40090000UL                              /*!< GPIO PORT_C Base Address */

#define ADDR_SSP1_BASE         0x40000000UL                              /*!< SSP Base Address      */

#define ADDR_WWDT_BASE         0x40048000UL
#define ADDR_IWDT_BASE         0x40050000UL
#define ADDR_LCD_BASE          0x40038000UL

#define ADDR_ADCIU_BASE        0x40068000UL

#define ADDR_UART1_BASE        0x40008000UL
#define ADDR_UART2_BASE        0x40010000UL

#define ADDR_TIMER1_BASE      0x40070000UL
#define ADDR_TIMER2_BASE      0x40078000UL

#define ADDR_POWER_BASE       0x40058000UL
#define ADDR_I2C_BASE         0x40030000UL



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

#define MDR_PORTA                      ((MDR_PORT_Type 	    *) ADDR_PORTA_BASE)
#define MDR_PORTB                      ((MDR_PORT_Type 	    *) ADDR_PORTB_BASE)
#define MDR_PORTC                      ((MDR_PORT_Type 	    *) ADDR_PORTC_BASE)

#define MDR_SSP1                       ((MDR_SSP_Type       *) ADDR_SSP1_BASE)

#define MDR_WWDT                       ((MDR_WWDT_Type      *) ADDR_WWDT_BASE)
#define MDR_IWDT                       ((MDR_IWDT_Type      *) ADDR_IWDT_BASE)

#define MDR_LCD                        ((MDR_LCD_Type       *) ADDR_LCD_BASE)
#define MDR_ADCUI                      ((MDR_ADCUI_TypeDef 	*) ADDR_ADCIU_BASE)

#define MDR_UART1                      ((MDR_UART_Type 	    *) ADDR_UART1_BASE)
#define MDR_UART2                      ((MDR_UART_Type 	    *) ADDR_UART2_BASE)

#define MDR_TIMER1                     ((MDR_TIMER_Type 	  *) ADDR_TIMER1_BASE)
#define MDR_TIMER2                     ((MDR_TIMER_Type 	  *) ADDR_TIMER2_BASE)

//  Timer Channels - there is only one channel in Timer
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #define MDR_TIMER1_CH1                 ((MDR_TIMER_CH_Type 	*) (__IOM uint32_t)(&MDR_TIMER1->CCR1))
  #define MDR_TIMER2_CH1                 ((MDR_TIMER_CH_Type 	*) (__IOM uint32_t)(&MDR_TIMER2->CCR1))    
#else
  #define MDR_TIMER1_CH1                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER1->CCR1))  
  #define MDR_TIMER2_CH1                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER2->CCR1))  
#endif


#define MDR_POWER                      ((MDR_PWR_Type 	    *) ADDR_POWER_BASE)
#define MDR_I2C                        ((MDR_I2C_Type       *) ADDR_I2C_BASE)



/* =========================================================================================================================== */
/* ================                                  SPL_Configs                                   ================ */
/* =========================================================================================================================== */


//----------------    RST Clock Definitions  --------------------
#define   MDR_CLK_EN_REG_RST        PER2_CLOCK
#define   MDR_CLK_EN_BIT_RST        MDR_RST_PER2__RST_CLK_EN_Msk

//----------------    BKP Clock Definitions  --------------------
#define   MDR_CLK_EN_REG_BKP        PER2_CLOCK
#define   MDR_CLK_EN_BIT_BKP        MDR_RST_PER2__BKP_CLK_EN_Msk

//----------------    ADC Clock Definitions  --------------------
#define   MDR_CLK_EN_REG_ADC        PER2_CLOCK
#define   MDR_CLK_EN_BIT_ADC        MDR_RST_PER2__ADC_CLK_EN_Msk

//----------------    EEPROM Definitions  --------------------
#define   MDR_CLK_EN_REG_EEPROM     PER2_CLOCK
#define   MDR_CLK_EN_BIT_EEPROM     MDR_RST_PER2__EEPROM_CLK_EN_Pos
#define   MDR_EEPROM_HAS_TWO_BLOCK_ONLY

//----------------    PORT Definitions  --------------------
#define   MDR_CLK_EN_ADDR_PORT_A          &MDR_CLOCK->PER2_CLOCK
#define   MDR_CLK_EN_ADDR_PORT_B          &MDR_CLOCK->PER2_CLOCK
#define   MDR_CLK_EN_ADDR_PORT_C          &MDR_CLOCK->PER2_CLOCK

#define   MDR_CLK_EN_BIT_PORT_A           MDR_RST_PER2__PORTA_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_B           MDR_RST_PER2__PORTB_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_C           MDR_RST_PER2__PORTC_CLK_EN_Pos

#define   MDR_SWD_A_PORT                 MDR_PORTB
#define   MDR_SWD_A_PINS                 0x0000000CUL
#define   MDR_SWD_A_PINS_FUNC            0x000000F0UL
#define   MDR_SWD_A_PINS_PD              0x000C000CUL

//----------------    ADC Definitions  --------------------
#define   MDR_ADC_CLK_LIKE_VE4
//  ADC pins in Port_C and Port_B
#define   MDR_ADC_IN_PORTS_CB

//----------------    ADCUI Definitions  --------------------
//  ADCUI clock by 
#define   MDR_ADCUI_CLOCK_FROM_PER_CLOCK

//----------------    PER CLOCK  --------------------
//  Только в ВК214, раздельный выбор частот для каждого блока!
#define   MDR_PER_CLOCK_SELF_TIM_UART_SSP
#define   MDR_PER_CLOCK_LIKE_VE4

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
#define   MDR_UART2_CLK_EN_ADDR         (&MDR_CLOCK->PER2_CLOCK)

#define   MDR_UART1_CLK_EN_MSK            MDR_RST_PER2__UART1_CLK_EN_Msk
#define   MDR_UART2_CLK_EN_MSK            MDR_RST_PER2__UART2_CLK_EN_Msk

//  UART_ClockGate configs
#define   MDR_UART1_CLOCK_GATE_ADDR     (&MDR_CLOCK->UART_CLOCK)
#define   MDR_UART1_CLOCK_GATE_ENA_MSK    MDR_RST_UART__UART1_CLK_EN_Msk
#define   MDR_UART1_CLOCK_GATE_BRG_POS    MDR_RST_UART__UART1_BRG_Pos

#define   MDR_UART2_CLOCK_GATE_ADDR     (&MDR_CLOCK->UART_CLOCK)
#define   MDR_UART2_CLOCK_GATE_ENA_MSK    MDR_RST_UART__UART2_CLK_EN_Msk
#define   MDR_UART2_CLOCK_GATE_BRG_POS    MDR_RST_UART__UART2_BRG_Pos


//----------------    TIMER Definitions  --------------------
//  TIMER Block Clock enable
#define   MDR_TIMER1_CLK_EN_ADDR         (&MDR_CLOCK->PER2_CLOCK)
#define   MDR_TIMER2_CLK_EN_ADDR         (&MDR_CLOCK->PER2_CLOCK)

#define   MDR_TIMER1_CLK_EN_MSK            MDR_RST_PER2__TIMER1_CLK_EN_Msk
#define   MDR_TIMER2_CLK_EN_MSK            MDR_RST_PER2__TIMER2_CLK_EN_Msk


//  TIMER_ClockGate configs
#define   MDR_TIMER1_CLOCK_GATE_ADDR     (&MDR_CLOCK->TIM_CLOCK)
#define   MDR_TIMER2_CLOCK_GATE_ADDR     (&MDR_CLOCK->TIM_CLOCK)

#define   MDR_TIMER1_CLOCK_GATE_ENA_MSK    MDR_RST_TIM__TIM1_CLK_EN_Msk
#define   MDR_TIMER2_CLOCK_GATE_ENA_MSK    MDR_RST_TIM__TIM2_CLK_EN_Msk

#define   MDR_TIMER1_CLOCK_GATE_BRG_POS    MDR_RST_TIM__TIM1_BRG_Pos
#define   MDR_TIMER2_CLOCK_GATE_BRG_POS    MDR_RST_TIM__TIM2_BRG_Pos


//  Enable Count UpDown by external events
#define MDR_TIMER_Can_UpDown_ByExtEvents

#define MDR_TIMER_SINGLE_CH

//----------------    Power Definitions  --------------------
#define   MDR_PWR_CLK_EN_ADDR         (&MDR_CLOCK->PER2_CLOCK)
#define   MDR_PWR_CLK_EN_MSK            MDR_RST_PER2__PWR_CLK_EN_Msk

//----------------    I2C Definitions  --------------------
#define   MDR_I2C_CLK_EN_ADDR         (&MDR_CLOCK->PER2_CLOCK)
#define   MDR_I2C_CLK_EN_MSK            MDR_RST_PER2__I2C_CLK_EN_Msk


/** @} */ /* End of group MDR1986VK214 */

/** @} */ /* End of group Milandr */

#ifdef __cplusplus
}
#endif

#endif  /* MDR_1986VK214_H */
