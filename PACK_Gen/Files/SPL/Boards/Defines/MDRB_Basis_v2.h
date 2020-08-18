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
#define SFP_MUX_X8_2          0x2
#define SFP_MUX_X1_2          0x4
#define SFP_MUX_X8_1          0x8


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


//  Shift Register - PHY Reset Control
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

//===================================    1923KX028 Control   ========================================
#define KX028_EMAC_PORT_COUNT    16

// SPI Rates
// BitRate = SSP_Clock / (PSR * (1 + SCR)) = 80 MHz / (PSR * (SCR + 1))
//            0 - 255, Serial Clock Rate
//            2 - 254, EVEN ONLY! Clock prescaller
//  8 MHz
#define SPI_DivSCR_80MHZ_TO_8MHz    4
#define SPI_DivPSR_80MHZ_TO_8MHz    2
#define SPI_HALF_PERIOD_8MHz_NS     (1000 / (2 * 8))

//#define SPI_DivSCR_80MHZ_TO_8MHz    40
//#define SPI_DivPSR_80MHZ_TO_8MHz    20
//#define SPI_HALF_PERIOD_8MHz_NS     (10 / (2 * 8))

//  10 MHz
#define SPI_DivSCR_80MHZ_TO_10MHz   3
#define SPI_DivPSR_80MHZ_TO_10MHz   2
#define SPI_HALF_PERIOD_10MHz_NS    (1000 / (2 * 10))
//  20 MHz
#define SPI_DivSCR_80MHZ_TO_20MHz   1
#define SPI_DivPSR_80MHZ_TO_20MHz   2
#define SPI_HALF_PERIOD_18MHz_NS    (1000 / (2 * 20))
//  40 MHz
#define SPI_DivSCR_144MHZ_TO_40MHz  0
#define SPI_DivPSR_144MHZ_TO_40MHz  2
#define SPI_HALF_PERIOD_24MHz_NS    (1000 / (2 * 40))


#define KX028_SPI               MDR_SSP1ex
#define KX028_SPI_DivSCR_0_255  SPI_DivSCR_80MHZ_TO_10MHz
#define KX028_SPI_DivPSR_2_254  SPI_DivPSR_80MHZ_TO_10MHz
#define KX028_SPI_CS_DELAY_NS   SPI_HALF_PERIOD_8MHz_NS

#define KX028_SPI_PORT          MDR_GPIO_F
#define KX028_SPI_TX            0
#define KX028_SPI_RX            3
#define KX028_SPI_SCL           1
#define KX028_SPI_FSS           2
#define KX028_SPI_TX_FUNC       MDR_PIN_ALT
#define KX028_SPI_RX_FUNC       MDR_PIN_ALT
#define KX028_SPI_CLK_FUNC      MDR_PIN_ALT
#define KX028_SPI_FSS_FUNC      MDR_PIN_ALT

#define KX028_SPI_POWER         MDR_PIN_FAST

//  Mode pin defs
#define KX028_MODE_PORT         MDR_GPIO_A
#define KX028_MODE0_PIN         MDR_Pin_0
#define KX028_MODE1_PIN         MDR_Pin_1
#define KX028_MODE2_PIN         MDR_Pin_2
#define KX028_MODE3_PIN         MDR_Pin_3

#define KX028_MODE_PINS_ALL     (KX028_MODE0_PIN | KX028_MODE1_PIN | KX028_MODE2_PIN | KX028_MODE3_PIN)

#define KX028_MODE_PINS_Pos  0
#define KX028_MODE_PINS_Msk  0xFUL


#endif  //MDRB_BASIS_V2_H
