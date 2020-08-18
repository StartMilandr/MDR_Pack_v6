
#ifndef __SHIFT_FUNCTIONS_H
#define __SHIFT_FUNCTIONS_H

#include "config.h"
#include "MDR32Fx.h"
#include "MDR32F9Qx_rst_clk.h"

#define SHIFT_LEN   16
#define SHIFT_DELAY_TICKS     PAUSE_10_US_IN_SYS_TICK


//  JTAG_B
#define JTAG_B_PORT           MDR_PORTB
#define JTAG_B_PROTECT        0x1FUL

//  Shift Register
#define SHIFT_REG_PORT_CLK     MDR_RST_PER__PORTB_CLK_EN_Msk
#define SHIFT_REG_PORT         MDR_PORTB

#define SHIFT_REG_PIN_IND_OE       6
#define SHIFT_REG_PIN_IND_CLR      7
#define SHIFT_REG_PIN_IND_SRCLK    8
#define SHIFT_REG_PIN_IND_IN       9
#define SHIFT_REG_PIN_IND_RCLK     10

#define SHIFT_REG_PIN_OE                (1UL << SHIFT_REG_PIN_IND_OE)
#define SHIFT_REG_PIN_CLR               (1UL << SHIFT_REG_PIN_IND_CLR)
#define SHIFT_REG_PIN_SRCLK             (1UL << SHIFT_REG_PIN_IND_SRCLK)
#define SHIFT_REG_PIN_IN                (1UL << SHIFT_REG_PIN_IND_IN)
#define SHIFT_REG_PIN_RCLK              (1UL << SHIFT_REG_PIN_IND_RCLK)

#define SHIFT_REG_SET_0(mask)           SHIFT_REG_PORT->RXTX &= ~((mask) | JTAG_B_PROTECT )
#define SHIFT_REG_SET_1(mask)           SHIFT_REG_PORT->RXTX  =   (mask) | ( SHIFT_REG_PORT->RXTX & ( ~JTAG_B_PROTECT ) )

#define SHIFT_REG_OE_0                  SHIFT_REG_SET_0(SHIFT_REG_PIN_OE)
#define SHIFT_REG_OE_1                  SHIFT_REG_SET_1(SHIFT_REG_PIN_OE)
#define SHIFT_REG_CLR_0                 SHIFT_REG_SET_0(SHIFT_REG_PIN_CLR)
#define SHIFT_REG_CLR_1                 SHIFT_REG_SET_1(SHIFT_REG_PIN_CLR)
#define SHIFT_REG_SRCLK_0               SHIFT_REG_SET_0(SHIFT_REG_PIN_SRCLK)
#define SHIFT_REG_SRCLK_1               SHIFT_REG_SET_1(SHIFT_REG_PIN_SRCLK)
#define SHIFT_REG_IN_0                  SHIFT_REG_SET_0(SHIFT_REG_PIN_IN)
#define SHIFT_REG_IN_1                  SHIFT_REG_SET_1(SHIFT_REG_PIN_IN)
#define SHIFT_REG_RCLK_0                SHIFT_REG_SET_0(SHIFT_REG_PIN_RCLK)
#define SHIFT_REG_RCLK_1                SHIFT_REG_SET_1(SHIFT_REG_PIN_RCLK)


#define ShiftOutEnable()      SHIFT_REG_OE_0
#define ShiftOutDisable()     SHIFT_REG_OE_1

extern uint32_t g_ShiftLastValue;
void ShiftSetValue(uint16_t value);
void ShiftClear(void);



#endif	//__SHIFT_FUNCTIONS_H
