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
  ADCIU_F1_IRQn             = 14,               /*!< ADCIU_F0 Interrupt   */
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

/*===============  Backup and RST ==============*/
#include "MDR_BKP_VE4x_defs.h"

/*===============  EEPROM Controller=============*/
#include "MDR_EEPROM_18MHz_defs.h"

/*===============  GPIO Port ===================*/
#include "MDR_GPIO_defs.h"

#define MDR_PORT_Type  MDR_PORT_Type__Base


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
#define ADDR_FLASH_BASE       (0x00000000UL)                              /*!< (FLASH     ) Base Address */
#define ADDR_SRAM_BASE        (0x20000000UL)                              /*!< (SRAM      ) Base Address */
#define ADDR_PERIPH_BASE      (0x40000000UL)                              /*!< (Peripheral) Base Address */

/* Peripheral memory map */
#define ADDR_EEPROM_BASE      (0x40018000UL)                              /*!< EEPROM Controller           */
#define ADDR_RST_CLOCK_BASE   (0x40020000UL)                              /*!< RST_CLOCK Base Address      */
#define ADDR_BKP_BASE         (0x40060000UL)                              /*!< Backup and RTC Base Address */

#define ADDR_PORTA_BASE       (0x40080000UL)                              /*!< GPIO PORT_A Base Address */
#define ADDR_PORTB_BASE       (0x40088000UL)                              /*!< GPIO PORT_B Base Address */
#define ADDR_PORTC_BASE       (0x40090000UL)                              /*!< GPIO PORT_C Base Address */


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

#define MDR_PORTA                      ((MDR_PORT_Type 	*) ADDR_PORTA_BASE)
#define MDR_PORTB                      ((MDR_PORT_Type 	*) ADDR_PORTB_BASE)
#define MDR_PORTC                      ((MDR_PORT_Type 	*) ADDR_PORTC_BASE)


/* =========================================================================================================================== */
/* ================                                  SPL_Configs                                   ================ */
/* =========================================================================================================================== */

//  Clock Enable bits
#define   MDR_CLK_EN_REG_PER              PER2_CLOCK
#define   MDR_CLK_EN_REG_PER_b            PER2_CLOCK_b

#define   MDR_CLK_EN_REG_EEPROM           PER2_CLOCK
#define   MDR_RST_PER__EEPROM_CLK_EN_Pos  MDR_RST_PER2__EEPROM_CLK_EN_Pos

#define   MDR_CLK_EN_REG_BKP              PER2_CLOCK
#define   MDR_CLK_EN_REG_BKP_b            PER2_CLOCK_b
#define   MDR_RST_PER__BKP_CLK_EN_Pos     MDR_RST_PER2__BKP_CLK_EN_Pos

#define   MDR_CLK_EN_ADDR_PORT_A          &MDR_CLOCK->PER2_CLOCK
#define   MDR_CLK_EN_ADDR_PORT_B          &MDR_CLOCK->PER2_CLOCK
#define   MDR_CLK_EN_ADDR_PORT_C          &MDR_CLOCK->PER2_CLOCK

#define   MDR_CLK_EN_BIT_PORT_A           MDR_RST_PER2__PORTA_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_B           MDR_RST_PER2__PORTB_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_C           MDR_RST_PER2__PORTC_CLK_EN_Pos

#define   MDR_JTAG_A_PORT               MDR_PORTB
#define   MDR_JTAG_A_PINS               0x0000000CUL
#define   MDR_JTAG_A_PINS_FUNC          0x000000F0UL
#define   MDR_JTAG_A_PINS_PD            0x000C000CUL


/** @} */ /* End of group MDR1986VK214 */

/** @} */ /* End of group Milandr */

#ifdef __cplusplus
}
#endif

#endif  /* MDR_1986VK214_H */
