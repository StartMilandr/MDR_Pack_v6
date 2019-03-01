/**************************************************************************//**
 * @file     system_MDR1986VK214.h
 * @brief    CMSIS Cortex-M0 Device Peripheral Access Layer Header File for
 *           Device MDR1986VK214
 * @version  V5.00
 * @date     10. January 2018
 ******************************************************************************/

#ifndef SYSTEM_MDR1986VK214_H
#define SYSTEM_MDR1986VK214_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

extern uint32_t SystemCoreClock;     /*!< System Clock Frequency (Core Clock)  */


/**
  \brief Setup the microcontroller system.

   Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit (void);


/**
  \brief  Update SystemCoreClock variable.

   Updates the SystemCoreClock with current core Clock retrieved from cpu registers.
 */
extern void SystemCoreClockUpdate (void);


#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_MDR1986VK214_H */
