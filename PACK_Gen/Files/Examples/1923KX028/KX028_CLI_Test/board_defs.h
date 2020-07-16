#ifndef KX028_CLI_DEFS_H
#define KX028_CLI_DEFS_H

//===================================    Частота тактирования    ========================================
#define HSE_PLL_MUL_MAX         MDR_x12                 //  HSE_max = 8MHz * 12 = 96MHz  (100MHz по спецификации)
#define HSE_LOW_SELRI_MAX       MDR_LOWRI_gt80MHz
#define HSE_EEPROM_DELAY_MAX    EEPROM_Delay_le100MHz

#define MDRB_CLK_PLL_HSE_RES_MAX     MDR_CPU_CFG_PLL_HSE_RES_DEF(HSE_PLL_MUL_MAX, HSE_EEPROM_DELAY_MAX, HSE_LOW_SELRI_MAX)


//===================================    UART CLI Control   ========================================
#define CLI_UART_PORT           MDR_GPIO_F
#define CLI_UART_TX             1
#define CLI_UART_RX             0
#define CLI_UART_TX_FUNC        MDR_PIN_ALT
#define CLI_UART_RX_FUNC        MDR_PIN_ALT


//===================================    1923KX028 Control   ========================================
#define KX028_EMAC_PORT_COUNT    3


#endif

