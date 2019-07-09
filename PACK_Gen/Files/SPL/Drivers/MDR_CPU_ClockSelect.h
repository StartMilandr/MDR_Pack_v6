#ifndef _MDR_CPU_CLOCK_SELECT_H
#define _MDR_CPU_CLOCK_SELECT_H

#include <MDR_Config.h>  

#if defined (USE_MDR1986VE8)
  //  PLL from 8MHz 
  //  Удовлетворяют FInt = F*N/(Q+1) в диапазоне [75MHz .. 150MHz]
  #define  MDRB_PLL_8MHz_TO_36MHz     MDR_CPU_CFG_PLL(18, 1, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_38MHz     MDR_CPU_CFG_PLL(19, 1, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_39MHz     MDR_CPU_CFG_PLL(39, 2, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_40MHz     MDR_CPU_CFG_PLL(10, 0, MDR_PLL_DV_div2)
  //  Дробные
  #define  MDRB_PLL_8MHz_TO_37MHz5    MDR_CPU_CFG_PLL(75, 7, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_37MHz6    MDR_CPU_CFG_PLL(47, 4, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_38MHz4    MDR_CPU_CFG_PLL(48, 4, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_39MHz2    MDR_CPU_CFG_PLL(49, 4, MDR_PLL_DV_div2)
  
  //  Настройки зависящие от частоты
  #define  MDRB_CPU_FREQ_SUPP_40MHz   MDR_CPU_FREQ_SUPP(MDR_OTP_Delay_le_62MHz5,  MDR_BKP_LDO_SRILow_lt50MHz)
  #define  MDRB_CPU_FREQ_SUPP_20MHz   MDR_CPU_FREQ_SUPP(MDR_OTP_Delay_le_41MHz66, MDR_BKP_LDO_SRILow_lt30MHz)


  //  Максимальная тастота PLL
  #define  MDRB_PLL_8MHz_TO_MAX       MDRB_PLL_8MHz_TO_40MHz
  #define  MDRB_PLL_8MHz_FSUPP_MAX    MDRB_CPU_FREQ_SUPP_40MHz  
  
  #define  MDRB_PLL_8MHz_TO_MIN       MDRB_PLL_8MHz_TO_37MHz5
  #define  MDRB_PLL_8MHz_FSUPP_MIN    MDRB_CPU_FREQ_SUPP_40MHz

  #define  MDRB_CPU_FREQ_SUPP_MIN     MDR_CPU_FREQ_SUPP(MDR_OTP_Delay_le_20MHz84, MDR_BKP_LDO_SRILow_lt100KHz)  
  #define  MDRB_CPU_FREQ_SUPP_MAX     MDR_CPU_FREQ_SUPP(MDR_OTP_Delay_le_83MHz33, MDR_BKP_LDO_SRILow_lt100MHz)  
  

//  MDR_OTP_Delay_Forbiden    = 0,
//  MDR_OTP_Delay_le_20MHz84  = 1,
//  MDR_OTP_Delay_le_41MHz66  = 2,
//  MDR_OTP_Delay_le_62MHz5   = 3,
//  MDR_OTP_Delay_le_83MHz33  = 4,
//  MDR_OTP_Delay_le_100MHz   = 5,

//  MDR_BKP_LDO_SRILow_lt30MHz  = 0,  /*!< ge10MHz : Extra_I about ~400uA                                            */
//  MDR_BKP_LDO_SRILow_lt50MHz  = 1,  /*!< ge30MHz : Extra_I about ~450uA                                            */
//  MDR_BKP_LDO_SRILow_lt100MHz = 2,  /*!< ge50MHz : Extra_I about ~550uA                                            */
//  MDR_BKP_LDO_SRILow_ge100MHz = 3,  /*!< ge100MHz : Extra_I about ~650uA                                           */
//  MDR_BKP_LDO_SRILow_lt10MHz  = 4,  /*!< ge1MHz : Extra_I about ~300uA                                             */
//  MDR_BKP_LDO_SRILow_lt1MHz   = 5,  /*!< ge500KHz : Extra_I about ~200uA                                           */
//  MDR_BKP_LDO_SRILow_lt500KHz = 6,  /*!< ge100KHz : Extra_I about ~100uA                                           */
//  MDR_BKP_LDO_SRILow_lt100KHz = 7,  /*!< ge10KHz : Extra_I about ~50uA                                             */


#elif defined (USE_MDR1923VK014)
  //  PLL from 8MHz 
  //  Удовлетворяют FInt = F*N/(Q+1) в диапазоне [75MHz .. 150MHz]
  #define  MDRB_PLL_8MHz_TO_36MHz     MDR_CPU_CFG_PLL(18, 1, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_38MHz     MDR_CPU_CFG_PLL(19, 1, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_39MHz     MDR_CPU_CFG_PLL(39, 2, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_40MHz     MDR_CPU_CFG_PLL(10, 0, MDR_PLL_DV_div2)
  //  Дробные
  #define  MDRB_PLL_8MHz_TO_37MHz5    MDR_CPU_CFG_PLL(75, 7, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_37MHz6    MDR_CPU_CFG_PLL(47, 4, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_38MHz4    MDR_CPU_CFG_PLL(48, 4, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_39MHz2    MDR_CPU_CFG_PLL(49, 4, MDR_PLL_DV_div2)
  
  //  Настройки зависящие от частоты
  #define  MDRB_CPU_FREQ_SUPP_40MHz   MDR_CPU_FREQ_SUPP(MDR_BKP_LDO_SRILow_lt80MHz)
  #define  MDRB_CPU_FREQ_SUPP_20MHz   MDR_CPU_FREQ_SUPP(MDR_BKP_LDO_SRILow_lt40MHz)


  //  Максимальная тастота PLL
  #define  MDRB_PLL_8MHz_TO_MAX       MDRB_PLL_8MHz_TO_40MHz
  #define  MDRB_PLL_8MHz_FSUPP_MAX    MDRB_CPU_FREQ_SUPP_40MHz  
  
  #define  MDRB_PLL_8MHz_TO_MIN       MDRB_PLL_8MHz_TO_37MHz5
  #define  MDRB_PLL_8MHz_FSUPP_MIN    MDRB_CPU_FREQ_SUPP_40MHz

  #define  MDRB_CPU_FREQ_SUPP_MIN     MDR_CPU_FREQ_SUPP(MDR_BKP_LDO_SRILow_lt200KHz)  
  #define  MDRB_CPU_FREQ_SUPP_MAX     MDR_CPU_FREQ_SUPP(MDR_BKP_LDO_SRILow_lt80MHz)  


//typedef enum {                      /*!< MDR_BKP_REG_61_TMR0_LDO1_SRILow                                           */ 
//  MDR_BKP_LDO_SRILow_lt10MHz  = 0,  /*!< LessThen 10MHz : Extra_I about ~300uA                                            */
//  MDR_BKP_LDO_SRILow_lt200KHz = 1,  /*!< lt200KHz : Extra_I about ~7uA                                             */
//  MDR_BKP_LDO_SRILow_lt500KHz = 2,  /*!< lt500KHz : Extra_I about ~20uA                                            */
//  MDR_BKP_LDO_SRILow_lt1MHz   = 3,  /*!< lt1MHz : Extra_I about ~80uA                                              */
//  MDR_BKP_LDO_SRILow_GensOff  = 4,  /*!< GensOff : Extra_I about ~2uA                                              */
//  MDR_BKP_LDO_SRILow_lt40MHz  = 5,  /*!< lt40MHz : Extra_I about ~900uA                                            */
//  MDR_BKP_LDO_SRILow_lt80MHz  = 6,  /*!< lt80MHz : Extra_I about ~5mA                                              */
//  MDR_BKP_LDO_SRILow_gt80MHz  = 7,  /*!< lt80MHz : Extra_I about ~20mA                                             */  
//} MDR_BKP_LDO_SRILow;


#elif defined (USE_ESila)
  //  PLL from 8MHz 
  //  Удовлетворяют FInt = F*N/(Q+1) в диапазоне [150MHz .. 300MHz]
  #define  MDRB_PLL_8MHz_TO_38MHz     MDR_CPU_CFG_PLL(19, 0, MDR_PLL_DV_div4)
  #define  MDRB_PLL_8MHz_TO_40MHz     MDR_CPU_CFG_PLL(20, 0, MDR_PLL_DV_div4)
  #define  MDRB_PLL_8MHz_TO_50MHz     MDR_CPU_CFG_PLL(25, 0, MDR_PLL_DV_div4)
  #define  MDRB_PLL_8MHz_TO_60MHz     MDR_CPU_CFG_PLL(30, 0, MDR_PLL_DV_div4)
  #define  MDRB_PLL_8MHz_TO_70MHz     MDR_CPU_CFG_PLL(35, 0, MDR_PLL_DV_div4)
  #define  MDRB_PLL_8MHz_TO_80MHz     MDR_CPU_CFG_PLL(20, 0, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_92MHz     MDR_CPU_CFG_PLL(23, 0, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_100MHz    MDR_CPU_CFG_PLL(25, 0, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_108MHz    MDR_CPU_CFG_PLL(27, 0, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_120MHz    MDR_CPU_CFG_PLL(30, 0, MDR_PLL_DV_div2)
  
#ifdef ERRATA_1001_FIXED  
  #define  MDRB_PLL_8MHz_TO_132MHz    MDR_CPU_CFG_PLL(33, 0, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_140MHz    MDR_CPU_CFG_PLL(35, 0, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_148MHz    MDR_CPU_CFG_PLL(37, 0, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_152MHz    MDR_CPU_CFG_PLL(19, 0, MDR_PLL_DV_div1)
  #define  MDRB_PLL_8MHz_TO_160MHz    MDR_CPU_CFG_PLL(20, 0, MDR_PLL_DV_div1)
#endif
  
  //  Настройки зависящие от частоты
  #define  MDRB_CPU_FREQ_SUPP_38MHz   MDR_CPU_FREQ_SUPP(EEPROM_Delay_le63MHz,  MDR_BKP_LDO_SRILow_lt50MHz)
  #define  MDRB_CPU_FREQ_SUPP_40MHz   MDR_CPU_FREQ_SUPP(EEPROM_Delay_le63MHz,  MDR_BKP_LDO_SRILow_lt50MHz)
  #define  MDRB_CPU_FREQ_SUPP_50MHz   MDR_CPU_FREQ_SUPP(EEPROM_Delay_le63MHz,  MDR_BKP_LDO_SRILow_lt100MHz)
  #define  MDRB_CPU_FREQ_SUPP_60MHz   MDR_CPU_FREQ_SUPP(EEPROM_Delay_le63MHz,  MDR_BKP_LDO_SRILow_lt100MHz)
  #define  MDRB_CPU_FREQ_SUPP_70MHz   MDR_CPU_FREQ_SUPP(EEPROM_Delay_le94MHz,  MDR_BKP_LDO_SRILow_lt100MHz)
  #define  MDRB_CPU_FREQ_SUPP_80MHz   MDR_CPU_FREQ_SUPP(EEPROM_Delay_le94MHz,  MDR_BKP_LDO_SRILow_lt100MHz)
  #define  MDRB_CPU_FREQ_SUPP_92MHz   MDR_CPU_FREQ_SUPP(EEPROM_Delay_le94MHz,  MDR_BKP_LDO_SRILow_lt100MHz)
  #define  MDRB_CPU_FREQ_SUPP_100MHz  MDR_CPU_FREQ_SUPP(EEPROM_Delay_le125MHz, MDR_BKP_LDO_SRILow_ge100MHz)
  #define  MDRB_CPU_FREQ_SUPP_108MHz  MDR_CPU_FREQ_SUPP(EEPROM_Delay_le125MHz, MDR_BKP_LDO_SRILow_ge100MHz)
  #define  MDRB_CPU_FREQ_SUPP_120MHz  MDR_CPU_FREQ_SUPP(EEPROM_Delay_le125MHz, MDR_BKP_LDO_SRILow_ge100MHz)


#ifdef ERRATA_1001_FIXED
  #define  MDRB_CPU_FREQ_SUPP_132MHz  MDR_CPU_FREQ_SUPP(EEPROM_Delay_le157MHz, MDR_BKP_LDO_SRILow_ge100MHz)
  #define  MDRB_CPU_FREQ_SUPP_140MHz  MDR_CPU_FREQ_SUPP(EEPROM_Delay_le157MHz, MDR_BKP_LDO_SRILow_ge100MHz)
  #define  MDRB_CPU_FREQ_SUPP_148MHz  MDR_CPU_FREQ_SUPP(EEPROM_Delay_le157MHz, MDR_BKP_LDO_SRILow_ge100MHz)
  #define  MDRB_CPU_FREQ_SUPP_152MHz  MDR_CPU_FREQ_SUPP(EEPROM_Delay_le157MHz, MDR_BKP_LDO_SRILow_ge100MHz)
  #define  MDRB_CPU_FREQ_SUPP_160MHz  MDR_CPU_FREQ_SUPP(EEPROM_Delay_le188MHz, MDR_BKP_LDO_SRILow_ge100MHz)
  
  //  Максимальная частота PLL
  #define  MDRB_PLL_8MHz_TO_MAX       MDRB_PLL_8MHz_TO_160MHz
  #define  MDRB_PLL_8MHz_FSUPP_MAX    MDRB_CPU_FREQ_SUPP_160MHz  
  #define  MDRB_CPU_FREQ_SUPP_MAX     MDR_CPU_FREQ_SUPP(EEPROM_Delay_le188MHz, MDR_BKP_LDO_SRILow_ge100MHz)   
  
#else
  //  Максимальная частота PLL
  #define  MDRB_PLL_8MHz_TO_MAX       MDRB_PLL_8MHz_TO_120MHz
  #define  MDRB_PLL_8MHz_FSUPP_MAX    MDRB_CPU_FREQ_SUPP_120MHz  
  #define  MDRB_CPU_FREQ_SUPP_MAX     MDR_CPU_FREQ_SUPP(EEPROM_Delay_le125MHz, MDR_BKP_LDO_SRILow_ge100MHz)   
#endif

  //  Минимальная частота PLL
  #define  MDRB_PLL_8MHz_TO_MIN       MDRB_PLL_8MHz_TO_38MHz
  #define  MDRB_PLL_8MHz_FSUPP_MIN    MDRB_CPU_FREQ_SUPP_38MHz
  
  #define  MDRB_CPU_FREQ_SUPP_MIN     MDR_CPU_FREQ_SUPP(EEPROM_Delay_le32MHz,  MDR_BKP_LDO_SRILow_lt100KHz) 
  

//  Поля будут уточняться!
//typedef enum {                     /*!< MDR_BKP_REG_61_TMR0_HLDO_SRILow                                           */
//  MDR_BKP_LDO_SRILow_lt30MHz  = 0,  /*!< ge10MHz : Extra_I about ~400uA                                            */
//  MDR_BKP_LDO_SRILow_lt50MHz  = 1,  /*!< ge30MHz : Extra_I about ~450uA                                            */
//  MDR_BKP_LDO_SRILow_lt100MHz = 2,  /*!< ge50MHz : Extra_I about ~550uA                                            */
//  MDR_BKP_LDO_SRILow_ge100MHz = 3,  /*!< ge100MHz : Extra_I about ~650uA                                           */
//  MDR_BKP_LDO_SRILow_lt10MHz  = 4,  /*!< ge1MHz : Extra_I about ~300uA                                             */
//  MDR_BKP_LDO_SRILow_lt1MHz   = 5,  /*!< ge500KHz : Extra_I about ~200uA                                           */
//  MDR_BKP_LDO_SRILow_lt500KHz = 6,  /*!< ge100KHz : Extra_I about ~100uA                                           */
//  MDR_BKP_LDO_SRILow_lt100KHz = 7,  /*!< ge10KHz : Extra_I about ~50uA                                             */
//} MDR_BKP_LDO_SRILow;

//typedef enum {
//  EEPROM_Delay_Forbiden = 0,     //  
//  EEPROM_Delay_le32MHz  = 1,     //  31,25 MHz
//  EEPROM_Delay_le63MHz  = 2,     //  62,50 MHz
//  EEPROM_Delay_le94MHz  = 3,     //  93,75 MHz
//  EEPROM_Delay_le125MHz = 4,     // 125,00 MHz
//  EEPROM_Delay_le157MHz = 5,     // 156,25 MHz
//  EEPROM_Delay_le188MHz = 6,     // 187,50 MHz
//  EEPROM_Delay_le219MHz = 7,     // 218,75 MHz
//  EEPROM_Delay_le250MHz = 8,     // 250,00 MHz
//  EEPROM_Delay_le282MHz = 9,     // 281,25 MHz
//  EEPROM_Delay_le313MHz = 10,    // 312,50 MHz
//  EEPROM_Delay_le344MHz = 11,    // 343,75 MHz
//  EEPROM_Delay_le374MHz = 12,    // 374,00 MHz
//  EEPROM_Delay_le407MHz = 13,    // 406,25 MHz
//  EEPROM_Delay_le438MHz = 14,    // 437,50 MHz
//  EEPROM_Delay_le469MHz = 15,    // 468,75 MHz
//} MDR_EEPROM_DELAY;

#else
  //  Множитель PLL
  #define  MDRB_PLL_8MHz_TO_8MHz       MDR_x1
  #define  MDRB_PLL_8MHz_TO_16MHz      MDR_x2
  #define  MDRB_PLL_8MHz_TO_24MHz      MDR_x3
  #define  MDRB_PLL_8MHz_TO_32MHz      MDR_x4
  #define  MDRB_PLL_8MHz_TO_40MHz      MDR_x5
  #define  MDRB_PLL_8MHz_TO_48MHz      MDR_x6
  #define  MDRB_PLL_8MHz_TO_56MHz      MDR_x7
  #define  MDRB_PLL_8MHz_TO_64MHz      MDR_x8
  #define  MDRB_PLL_8MHz_TO_72MHz      MDR_x9
  #define  MDRB_PLL_8MHz_TO_80MHz      MDR_x10
  #define  MDRB_PLL_8MHz_TO_88MHz      MDR_x11
  #define  MDRB_PLL_8MHz_TO_96MHz      MDR_x12
  #define  MDRB_PLL_8MHz_TO_104MHz     MDR_x13
  #define  MDRB_PLL_8MHz_TO_112MHz     MDR_x14
  #define  MDRB_PLL_8MHz_TO_120MHz     MDR_x15
  #define  MDRB_PLL_8MHz_TO_128MHz     MDR_x16

  //  Настройки зависящие от частоты
  #define  MDRB_CPU_FREQ_SUPP_8MHz     MDR_CPU_FREQ_SUPP(EEPROM_Delay_le25MHz,   MDR_LOWRI_le10MHz)
  #define  MDRB_CPU_FREQ_SUPP_16MHz    MDR_CPU_FREQ_SUPP(EEPROM_Delay_le25MHz,   MDR_LOWRI_le40MHz)
  #define  MDRB_CPU_FREQ_SUPP_24MHz    MDR_CPU_FREQ_SUPP(EEPROM_Delay_le25MHz,   MDR_LOWRI_le40MHz)
  #define  MDRB_CPU_FREQ_SUPP_32MHz    MDR_CPU_FREQ_SUPP(EEPROM_Delay_le50MHz,   MDR_LOWRI_le40MHz)
  #define  MDRB_CPU_FREQ_SUPP_40MHz    MDR_CPU_FREQ_SUPP(EEPROM_Delay_le50MHz,   MDR_LOWRI_le80MHz)
  #define  MDRB_CPU_FREQ_SUPP_48MHz    MDR_CPU_FREQ_SUPP(EEPROM_Delay_le50MHz,   MDR_LOWRI_le80MHz)
  #define  MDRB_CPU_FREQ_SUPP_56MHz    MDR_CPU_FREQ_SUPP(EEPROM_Delay_le75MHz,   MDR_LOWRI_le80MHz)
  #define  MDRB_CPU_FREQ_SUPP_64MHz    MDR_CPU_FREQ_SUPP(EEPROM_Delay_le75MHz,   MDR_LOWRI_le80MHz)
  #define  MDRB_CPU_FREQ_SUPP_72MHz    MDR_CPU_FREQ_SUPP(EEPROM_Delay_le75MHz,   MDR_LOWRI_le80MHz)
  #define  MDRB_CPU_FREQ_SUPP_80MHz    MDR_CPU_FREQ_SUPP(EEPROM_Delay_le100MHz,  MDR_LOWRI_gt80MHz)
  #define  MDRB_CPU_FREQ_SUPP_88MHz    MDR_CPU_FREQ_SUPP(EEPROM_Delay_le100MHz,  MDR_LOWRI_gt80MHz)
  #define  MDRB_CPU_FREQ_SUPP_96MHz    MDR_CPU_FREQ_SUPP(EEPROM_Delay_le100MHz,  MDR_LOWRI_gt80MHz)
  #define  MDRB_CPU_FREQ_SUPP_104MHz   MDR_CPU_FREQ_SUPP(EEPROM_Delay_le125MHz,  MDR_LOWRI_gt80MHz)
  #define  MDRB_CPU_FREQ_SUPP_112MHz   MDR_CPU_FREQ_SUPP(EEPROM_Delay_le125MHz,  MDR_LOWRI_gt80MHz)
  #define  MDRB_CPU_FREQ_SUPP_120MHz   MDR_CPU_FREQ_SUPP(EEPROM_Delay_le125MHz,  MDR_LOWRI_gt80MHz)
  #define  MDRB_CPU_FREQ_SUPP_128MHz   MDR_CPU_FREQ_SUPP(EEPROM_Delay_le150MHz,  MDR_LOWRI_gt80MHz)

//typedef enum {
//  MDR_LOWRI_le10MHz   = 0,                  /*!< 10MHz   : CPU Clock less then 10MHz  : +I ~ 300uA                             */
//  MDR_LOWRI_le200KHz  = 1,                  /*!< 200KHz  : CPU Clock less then 200KHz : +I ~ 6.6uA                             */
//  MDR_LOWRI_le500KHz  = 2,                  /*!< 500KHz  : CPU Clock less then 500KHz : +I ~ 20A                               */
//  MDR_LOWRI_le1MHz    = 3,                  /*!< 1MHz    : CPU Clock less then 1MHz   : +I ~ 80uA                              */
//  MDR_LOWRI_GensOff   = 4,                  /*!< GensOffz: Generators Off             : +I ~ 2uA                               */
//  MDR_LOWRI_le40MHz   = 5,                  /*!< 40MHz   : CPU Clock less then 40MHz  : +I ~ 900uA                             */
//  MDR_LOWRI_le80MHz   = 6,                  /*!< 80MHz   : CPU Clock less then 80MHz  : +I ~ 4.4mA                             */
//  MDR_LOWRI_gt80MHz   = 7,                  /*!< above_80MHz : CPU Clock above 10MHz  : +I ~ 19mA                              */
//} MDR_BKP_LOW_RI;

//typedef enum {                                            /*!< MDR_EEPROM_CMD_DELAY                                          */
//  EEPROM_Delay_le25MHz       = 0,                         /*!< le25MHz : CPU freq is up to 25MHz                             */
//  EEPROM_Delay_le50MHz       = 1,                         /*!< le50MHz : CPU freq is up to 50MHz                             */
//  EEPROM_Delay_le75MHz       = 2,                         /*!< le75MHz : CPU freq is up to 75MHz                             */
//  EEPROM_Delay_le100MHz      = 3,                         /*!< le100MHz : CPU freq is up to 100MHz                           */
//  EEPROM_Delay_le125MHz      = 4,                         /*!< le125MHz : CPU freq is up to 125MHz                           */
//  EEPROM_Delay_le150MHz      = 5,                         /*!< le150MHz : CPU freq is up to 150MHz                           */
//  EEPROM_Delay_le175MHz      = 6,                         /*!< le175MHz : CPU freq is up to 175MHz                           */
//  EEPROM_Delay_le200MHz      = 7,                         /*!< le200MHz : CPU freq is up to 200MHz                           */
//} MDR_EEPROM_DELAY;


#endif

#define MDR_CLK_PLL_HSI_DEF(pllCfg, suppFreq)     {.freqTrim            = HSI_FREQ_TRIM,            \
                                                   .selDiv2             = false,                    \
                                                   .timeoutCycles_HSI   = HSI_TIMEOUT,              \
                                                   .cfgPLL              = pllCfg,                   \
                                                   .timeoutCycles_PLL   = PLL_TIMEOUT,              \
                                                   .divMaxToCpu_0       = 0,                        \
                                                   .freqSupp            = suppFreq}

#define MDR_CLK_PLL_HSE_RES_DEF(pllCfg, suppFreq) {.freqSource          = MDR_CLK_Resonator,        \
                                                   .selDiv2             = false,                    \
                                                   .timeoutCycles_HSE   = HSI_TIMEOUT,              \
                                                   .cfgPLL              = pllCfg,                   \
                                                   .timeoutCycles_PLL   = PLL_TIMEOUT,              \
                                                   .divMaxToCpu_0       = 0,                        \
                                                   .freqSupp            = suppFreq};

#endif //_MDR_CPU_CLOCK_SELECT_H
