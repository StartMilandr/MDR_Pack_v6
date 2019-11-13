#ifndef MDRB_BASIS_V2_H
#define MDRB_BASIS_V2_H

#define PIN_PULL_UP(pinSel)   ((pinSel) << 16)
#define PIN_PULL_DOWN(pinSel)  (pinSel)


//  JTAG_B
#define JTAG_B_PORT           MDR_PORTB
#define JTAG_B_PROTECT        0x1FUL

//  I2C Mux Address
#define I2C_ADDR_MUX          0x70

#define SFP_MUX_X1_1          0x1
#define SFP_MUX_X8_1          0x2
#define SFP_MUX_X1_2          0x4
#define SFP_MUX_X8_2          0x8

//  SFP Presence
#define SFP_COUNT             4

#define SFP_PRES_PORT_CLK     MDR_RST_PER__PORTA_CLK_EN_Msk
#define SFP_PRES_PORT         MDR_PORTA
#define SFP_PRES_PIN_X1_1     MDR_Pin_4
#define SFP_PRES_PIN_X1_2     MDR_Pin_5
#define SFP_PRES_PIN_X8_1     MDR_Pin_6
#define SFP_PRES_PIN_X8_2     MDR_Pin_7

#define SFP_PRES_PIN_ALL      ( SFP_PRES_PIN_X1_1 | SFP_PRES_PIN_X1_2 | SFP_PRES_PIN_X8_1 | SFP_PRES_PIN_X8_2 )
#define SFP_PRES_PIN_ALL_POS  4


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

#define SHIFT_REG_PIN_ALL               (SHIFT_REG_PIN_OE | SHIFT_REG_PIN_CLR | SHIFT_REG_PIN_SRCLK | SHIFT_REG_PIN_IN | SHIFT_REG_PIN_RCLK)
#define SHIFT_REG_PIN_PWR(pwr)         (((pwr) << (SHIFT_REG_PIN_IND_OE    << 1))  | \
                                        ((pwr) << (SHIFT_REG_PIN_IND_CLR   << 1))  | \
                                        ((pwr) << (SHIFT_REG_PIN_IND_SRCLK << 1))  | \
                                        ((pwr) << (SHIFT_REG_PIN_IND_IN    << 1))  | \
                                        ((pwr) << (SHIFT_REG_PIN_IND_RCLK  << 1)))

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


//  ---------------  UART2 Pin Definition ----------------
  //  PORT_F: PF0, PF1 - Main
  #define MDRB_UART2_RX_PD0_Ind	      0
  #define MDRB_UART2_TX_PD1_Ind	      1

  #define MDRB_UART2_RX_PD0_Msk	      MDR_Pin_0
	#define MDRB_UART2_TX_PD1_Msk		    MDR_Pin_1

  #define MDRB_UART2_RX_PD0_Port	    MDR_GPIO_D
	#define MDRB_UART2_TX_PD1_Port		  MDR_GPIO_D
  
  #define MDRB_UART2_RX_PD0_Func	    MDR_PIN_ALT
	#define MDRB_UART2_TX_PD1_Func	    MDR_PIN_ALT


#endif  //MDRB_BASIS_V2_H
