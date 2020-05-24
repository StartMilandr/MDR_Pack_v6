#ifndef ETH_SWITCH_KX028_BB3_DEFS_H
#define ETH_SWITCH_KX028_BB3_DEFS_H



//===================================    Частота тактирования    ========================================
#define HSE_PLL_MUL_MAX         MDR_x9   //  HSE_max = 16MHz * 9 = 144MHz
#define HSE_LOW_SELRI_MAX       MDR_LOWRI_gt80MHz
#define HSE_EEPROM_DELAY_MAX    EEPROM_Delay_le150MHz

#define MDRB_CLK_PLL_HSE_RES_MAX     MDR_CPU_CFG_PLL_HSE_RES_DEF(HSE_PLL_MUL_MAX, HSE_EEPROM_DELAY_MAX, HSE_LOW_SELRI_MAX)

// SPI Rates
// BitRate = SSP_Clock / (PSR * (1 + SCR)) = 144 MHz / (PSR * (SCR + 1))
//            0 - 255, Serial Clock Rate
//            2 - 254, EVEN ONLY! Clock prescaller
//  12 MHz
#define SPI_DivSCR_144MHZ_TO_12MHz   5
#define SPI_DivPSR_144MHZ_TO_12MHz   2
#define SPI_HALF_PERIOD_12MHz_NS     (1000 / (2 * 12))
//  14.4 MHz
#define SPI_DivSCR_144MHZ_TO_14M4Hz  4
#define SPI_DivPSR_144MHZ_TO_14M4Hz  2
#define SPI_HALF_PERIOD_14M4Hz_NS     (1000 / (2 * 14.4))
//  18 MHz
#define SPI_DivSCR_144MHZ_TO_18MHz   3
#define SPI_DivPSR_144MHZ_TO_18MHz   2
#define SPI_HALF_PERIOD_18MHz_NS     (1000 / (2 * 24))
//  24 MHz
#define SPI_DivSCR_144MHZ_TO_24MHz   2
#define SPI_DivPSR_144MHZ_TO_24MHz   2
#define SPI_HALF_PERIOD_24MHz_NS     (1000 / (2 * 24))


//===================================    Reset Control   ========================================
#define RESET_PORT              MDR_GPIO_B
#define RESET_PIN_BB3           MDR_Pin_7
#define RESET_PIN_KX028         MDR_Pin_8
#define RESET_PIN_EPHY          MDR_Pin_9
// RESETB hold in 0
#define RESETB_PIN_EPHY         MDR_Pin_10

#define RESET_PINS_ALL          (RESET_PIN_BB3 | RESET_PIN_KX028 | RESET_PIN_EPHY | RESETB_PIN_EPHY)

#define RESET_APPLY_DELAY_MS    50

//===================================    5600BB3 SPI Control   ========================================
#define BB3_SPI                 MDR_SSP1ex
#define BB3_SPI_DivSCR_0_255    SPI_DivSCR_144MHZ_TO_12MHz
#define BB3_SPI_DivPSR_2_254    SPI_DivPSR_144MHZ_TO_12MHz

#define BB3_SPI_PORT            MDR_GPIO_D
#define BB3_SPI_TX              2
#define BB3_SPI_RX              3
#define BB3_SPI_SCL             4
#define BB3_SPI_FSS             5
#define BB3_SPI_TX_FUNC         MDR_PIN_ALT
#define BB3_SPI_RX_FUNC         MDR_PIN_ALT
#define BB3_SPI_CLK_FUNC        MDR_PIN_ALT
#define BB3_SPI_FSS_FUNC        MDR_PIN_ALT
#define BB3_SPI_POWER           MDR_PIN_FAST


//===================================    1923KX028 Control   ========================================
#define KX028_SPI               MDR_SSP2ex
#define KX028_SPI_DivSCR_0_255  SPI_DivSCR_144MHZ_TO_24MHz
#define KX028_SPI_DivPSR_2_254  SPI_DivPSR_144MHZ_TO_24MHz
#define KX028_SPI_CS_DELAY_NS   SPI_HALF_PERIOD_24MHz_NS

#define KX028_SPI_PORT          MDR_GPIO_C
#define KX028_SPI_TX            9
#define KX028_SPI_RX            10
#define KX028_SPI_SCL           11
#define KX028_SPI_FSS           12
#define KX028_SPI_TX_FUNC       MDR_PIN_MAIN
#define KX028_SPI_RX_FUNC       MDR_PIN_MAIN
#define KX028_SPI_CLK_FUNC      MDR_PIN_MAIN
#define KX028_SPI_FSS_FUNC      MDR_PIN_MAIN
#define KX028_SPI_POWER         MDR_PIN_FAST

//  Mode pin defs
#define KX028_MODE_PORT         MDR_GPIO_B
#define KX028_MODE0_PIN         MDR_Pin_0
#define KX028_MODE1_PIN         MDR_Pin_1
#define KX028_MODE2_PIN         MDR_Pin_2
#define KX028_MODE3_PIN         MDR_Pin_3

#define KX028_MODE_PINS_ALL     (KX028_MODE0_PIN | KX028_MODE1_PIN | KX028_MODE2_PIN | KX028_MODE3_PIN)

#define KX028_MODE_PINS_Pos  0
#define KX028_MODE_PINS_Msk  0xFUL


//===================================    UART Control   ========================================
#define CLI_UART                MDR_UART1
#define CLI_UART_PORT           MDR_GPIO_C
#define CLI_UART_TX             MDR_Pin_3
#define CLI_UART_RX             MDR_Pin_4
#define CLI_UART_TX_FUNC        MDR_PIN_MAIN
#define CLI_UART_RX_FUNC        MDR_PIN_MAIN


//===================================    SFP Control   ========================================
#define SFP_I2C_PORT            MDR_GPIO_D
#define SFP_I2C_SCL             MDR_PIN_0
#define SFP_I2C_SDA             MDR_PIN_1

#define SFP_PORT                MDR_GPIO_B
#define SFP_PRESENCE            MDR_Pin_4
#define SFP_TX_DIS              MDR_Pin_11
#define SFP_RATE_SEL            MDR_Pin_12


//===================================  VE1 - EPHY(VE1)  Soft Jtag ========================================
#define EPHY_JTAG_PORT          MDR_GPIO_F
#define EPHY_JTAG_TCK           MDR_Pin_0
#define EPHY_JTAG_TDI           MDR_Pin_1
#define EPHY_JTAG_TMS           MDR_Pin_2
#define EPHY_JTAG_TRST          MDR_Pin_3
#define EPHY_JTAG_TDO           MDR_Pin_4

#define EPHY_JTAG_FREQ_HZ       2000
#define MDR_1986VE1_JTAG_OPEN_EthPHY_IR       0x81
#define MDR_1986VE1_JTAG_OPEN_EthPHY_IR_LEN   8


//===================================  VE1 - KX028  Soft Jtag ========================================
#define KX028_JTAG_PORT          MDR_GPIO_E
#define KX028_JTAG_TCK           MDR_Pin_0
#define KX028_JTAG_TDI           MDR_Pin_1
#define KX028_JTAG_TMS           MDR_Pin_2
#define KX028_JTAG_TRST          MDR_Pin_3
#define KX028_JTAG_TDO           MDR_Pin_4



#endif

