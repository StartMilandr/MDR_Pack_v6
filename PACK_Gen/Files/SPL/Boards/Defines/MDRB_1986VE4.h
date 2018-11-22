#ifndef _MDRB_1986VE4_H
#define _MDRB_1986VE4_H

#ifdef USE_MDR1986VE4

//===================================    Частота тактирования    ========================================
#define HSE_PLL_MUL_MAX         MDR_x4   //  HSE_max = 8MHz * 4 = 32MHz (36MHz max)
#define HSE_LOW_SELRI_MAX       MDR_LOWRI_le40MHz
#define HSE_EEPROM_DELAY_MAX    EEPROM_Delay_le36MHz

#define MDR_CPU_SetClock_HSE_Max(bypass)  MDR_CPU_SetClock_HSE_PLL((bypass), HSE_PLL_MUL_MAX, HSE_LOW_SELRI_MAX, HSE_EEPROM_DELAY_MAX, MDR_CLK_div1, HSE_TIMEOUT)

//===================================    Заметки по плате    ========================================

//  Переопределение пинов для удобства поиска конфликтов
    #define PIN_PA0       MDR_Pin_0   //          LCD_D0
    #define PIN_PA1       MDR_Pin_1   //          LCD_D1
    #define PIN_PA2       MDR_Pin_2   //          LCD_D2
    #define PIN_PA3       MDR_Pin_3   //          LCD_D3
    #define PIN_PA4       MDR_Pin_4   //          LCD_A0
    #define PIN_PA6       MDR_Pin_6   //                    JTAG_A
    #define PIN_PA7       MDR_Pin_7   //                    JTAG_A    
    #define PIN_PA11      MDR_Pin_11  //  LED_1    
    #define PIN_PA14      MDR_Pin_14  //          LCD_WR1
    #define PIN_PA15      MDR_Pin_15  //          LCD_WR2

    #define PIN_PB6       MDR_Pin_6   //                             ADC_Ch7  - TuneResistor
    #define PIN_PB7       MDR_Pin_7   //                             ADC_Ch6
    #define PIN_PB8       MDR_Pin_8   //                             ADC_Ch5   
    #define PIN_PB9       MDR_Pin_9   //  Down                       ADC_Ch4
    #define PIN_PB10      MDR_Pin_10  //  Right
    #define PIN_PB11      MDR_Pin_11  //  Up
    #define PIN_PB12      MDR_Pin_12  //  Left

    #define PIN_PC1       MDR_Pin_1   //                             ADC_Ch3
    #define PIN_PC2       MDR_Pin_2   //                             ADC_Ch2  - TuneResistor (CMP)
    #define PIN_PC3       MDR_Pin_3   //                             ADC_Ch1/Ref+
    #define PIN_PC4       MDR_Pin_4   //                             ADC_Ch0/Ref-
    
    
//  --------------  ADC Definition  ------------
    #define MDRB_ADC_CH_IN1            ADC_Signal_Ch5   //  PIN_PB8    
    #define MDRB_ADC_CH_IN2            ADC_Signal_Ch7   //  PIN_PB6
    #define MDRB_ADC_CH_IN3            ADC_Signal_Ch2   //  PIN_PC2
    
    #define MDRB_ADC_CH_TUNE           ADC_Signal_Ch2   //  and ADC_Signal_Ch7

    #define MDRB_ADC_PORT_ALL1          MDR_GPIO_C
    #define MDRB_ADC_PINS_ALL1          0x001EUL    
    #define MDRB_ADC_PORT_ALL2          MDR_GPIO_B
    #define MDRB_ADC_PINS_ALL2          0x03C0UL
    
    #define MDRB_ADC_PIN_KEY_PROTECT2   0x01C0UL


//  --------------  Buttons Definition  ------------
    #define MDRB_BTN_PORT_KEY1      MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY1       PIN_PB11   //  Up

    #define MDRB_BTN_PORT_KEY2      MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY2       PIN_PB10   //  Right

    #define MDRB_BTN_PORT_KEY3      MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY3       PIN_PB9    //  Down
	
    #define MDRB_BTN_PORT_KEY4      MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY4       PIN_PB12   //  Left
    
    #define MDRB_BTN_PORT_KEY_P1    MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY_P1     (PIN_PB11 | PIN_PB10)   //  Up + Right

    #define MDRB_BTN_PORT_KEY_P2    MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY_P2     (PIN_PB11 | PIN_PB12)    //  Up + Left

	
    // for Initialization
    #define MDRB_BTN_GPIO           MDR_GPIO_B
    #define MDRB_BTN_PinSel         (MDRB_BTN_PIN_KEY1 | MDRB_BTN_PIN_KEY2 | MDRB_BTN_PIN_KEY3 | MDRB_BTN_PIN_KEY4)

    // Active buttons Level
    #define MDRB_BTNs_PUSH_TO_GND 

//  ----------    LEDs Definition -------------
    #define MDRB_LED_1 	           PIN_PA11    // VD3

    #define MDRB_LED_GPIO          MDR_GPIO_A
    #define MDRB_LED_PinAll        MDRB_LED_1

//  ----------  LCD Definition ---------------
    // Initialization                 //  D0 .. D3, A0, WR1, WR2
    #define MDRB_LCD_PORT             MDR_GPIO_A
    #define MDRB_LCD_PINS            (PIN_PA0 | PIN_PA1 | PIN_PA2 | PIN_PA3 | PIN_PA4 | PIN_PA14 | PIN_PA15)
    
    //  Control Pins
    #define MDRB_LCD_WR1_PORT         MDR_GPIO_A
    #define MDRB_LCD_WR1_PIN          PIN_PA14

    #define MDRB_LCD_WR2_PORT         MDR_GPIO_A
    #define MDRB_LCD_WR2_PIN          PIN_PA15

    #define MDRB_LCD_A0_PORT          MDR_GPIO_A
    #define MDRB_LCD_A0_PIN           PIN_PA4

    
    //  Bus Commands                              
    #define MDRB_LCD_BusWrite(value)    MDR_PORTA->RXTX &= 0xFFF0;          \
                                        MDR_PORTA->RXTX |= ((value) & 0x0FUL);
    
    #define LCD_IS_7SEG_DISPLAY
    
#else
   Please, select board in MDRB_BoardSelect.h!

#endif // USE_MDR1986VE4 

#endif // _MDRB_1986VE4_H
