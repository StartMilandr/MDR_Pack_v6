#ifndef __MDR_RTC_CFG1_H__
#define __MDR_RTC_CFG1_H__

#include "MDR_Config.h"
#include <stdint.h>

// ==========  Пользовательские настройки  ==========

// Прерывание по инкременту регистра CNT
// Делителем PRL рабочая частота обычно делится так, чтобы CNT увеличивался раз в секунду.
// Значение PRL загружается в регистр DIV, который декрементируется с каждом тактом рабочей частоты  
// и когда DIV == 0, то происходит CNT++. После этого обновляется значение в DIV = PRL.
#define RTCCFG1_ENA_IRQ_SEC           0

// Прерывание по переполнения счетчика CNT
#define RTCCFG1_ENA_IRQ_SEC_OV        0

// Прерывание по условию равенства регистров CNT == ALARM
#define RTCCFG1_ENA_IRQ_ALARM         0

// Калибровка "хода" CNT - Количество тактов для пропуска в периоде из 2^20 тактов.
// Значение из 0..255
#define RTCCFG1_CNT_CALIBR            0

// Выбор входной частоты, которую делит регистр DIV
// - RTCHSI тактирование от встроенного HSI 8MHz, имеет делитель до 256
// - LSI тактирование от встроенного LSI, 40KHz
// - LSE тактирование от внешнего LSE, 32KHz
// - RTCHSE тактирование от внешнего HSE, 2-16MHz, имеет делитель до 256
// Выбрать только один вариант!
#define RTCCFG1_CLK_SEL_RTCHSI        0
#define RTCCFG1_CLK_SEL_LSI           0
#define RTCCFG1_CLK_SEL_LSE           0
#define RTCCFG1_CLK_SEL_RTCHSE        1

//  Делители для вариантов тактирования RTCHSI / RTCHSE
//  MDR_Div256P_div1,2,4,8,16,32,64,128,256
#if RTCCFG1_CLK_SEL_RTCHSI || RTCCFG1_CLK_SEL_RTCHSE
  #define RTCCFG1_CLK_RTCHSI_DIV      MDR_Div256P_div8
  #define RTCCFG1_CLK_RTCHSE_DIV      MDR_Div256P_div8
  
  #define RTCCFG1_DIV_TO_1HZ          1000000
#else
  #define RTCCFG1_CLK_RTCHSI_DIV      MDR_Div256P_div8
  #define RTCCFG1_CLK_RTCHSE_DIV      MDR_Div256P_div8
  
  #define RTCCFG1_DIV_TO_1HZ          1000000
#endif



// ==========  Заполнение регистров  ==========

//  RTC_CS
#if RTCCFG1_ENA_IRQ_SEC
  #define  RTCCFG1_ENA_IRQ_SEC_Msk          MDR_BKP_RTC_CS_SECF_IE_Msk
#else  
  #define  RTCCFG1_ENA_IRQ_SEC_Msk          0
#endif

#if RTCCFG1_ENA_IRQ_SEC_OV
  #define  RTCCFG1_ENA_IRQ_SEC_OV_Msk       MDR_BKP_RTC_CS_OWF_IE_Msk
#else  
  #define  RTCCFG1_ENA_IRQ_SEC_OV_Msk       0
#endif

#if RTCCFG1_ENA_IRQ_ALARM
  #define  RTCCFG1_ENA_IRQ_ALARM_Msk        MDR_BKP_RTC_CS_ALRF_IE_Msk
#else  
  #define  RTCCFG1_ENA_IRQ_ALARM_Msk        0
#endif


#define RTCCFG1_REG_CS       RTCCFG1_ENA_IRQ_SEC_Msk       \
                          |  RTCCFG1_ENA_IRQ_SEC_OV_Msk    \
                          |  RTCCFG1_ENA_IRQ_ALARM_Msk
                          
                          
//  RTC_CLOCK
#define MDR_RST_RTC_FILL(hseEn, hsiEn, hseSel, hsiSel)  \
                  _VAL2FLD(MDR_RST_RTC__HSE_SEL,    hseSel)  \
                | _VAL2FLD(MDR_RST_RTC__HSI_SEL,    hsiSel)  \
                | _VAL2FLD(MDR_RST_RTC__HSE_RTC_EN, hseEn)  \
                | _VAL2FLD(MDR_RST_RTC__HSI_RTC_EN, hsiEn)

#define RTCCFG1_RTC_CLOCK   MDR_RST_RTC_FILL(RTCCFG1_CLK_SEL_RTCHSE, RTCCFG1_CLK_SEL_RTCHSI, RTCCFG1_CLK_RTCHSE_DIV, RTCCFG1_CLK_RTCHSI_DIV)


//  BKP_REG_0F 
#if   RTCCFG1_CLK_SEL_RTCHSI
  #define RTCCFG1_CLK_SEL_Msk    _VAL2FLD(MDR_BKP_REG_0F_RTC_SEL,    MDR_RTC_RTCHSI)
  
#elif RTCCFG1_CLK_SEL_LSI
  #define RTCCFG1_CLK_SEL_Msk    _VAL2FLD(MDR_BKP_REG_0F_RTC_SEL,    MDR_RTC_LSI)
  
#elif RTCCFG1_CLK_SEL_LSE
  #define RTCCFG1_CLK_SEL_Msk     _VAL2FLD(MDR_BKP_REG_0F_RTC_SEL,    MDR_RTC_LSE)
  
#elif RTCCFG1_CLK_SEL_RTCHSE
  #define RTCCFG1_CLK_SEL_Msk    _VAL2FLD(MDR_BKP_REG_0F_RTC_SEL,    MDR_RTC_RTCHSE)
  
#else
  -Select one of these clock source for RTC!
#endif


#define RTCCFG1_BKP_REG_0F_MaskSet    RTCCFG1_CLK_SEL_Msk | _VAL2FLD(MDR_BKP_REG_0F_RTC_CAL, RTCCFG1_CNT_CALIBR)
#define RTCCFG1_BKP_REG_0F_MaskClr    MDR_BKP_REG_0F_RTC_SEL_Msk | MDR_BKP_REG_0F_RTC_CAL_Msk

#define RTCCFG1_CFG_REGS_FILL   { .regRTC_CS = RTCCFG1_REG_CS, \
                                  .regRTC_Clock = RTCCFG1_RTC_CLOCK, \
                                  .regBKP0F_MaskSet = RTCCFG1_BKP_REG_0F_MaskSet, \
                                  .regBKP0F_MaskClr = RTCCFG1_BKP_REG_0F_MaskClr }



#endif // __MDR_RTC_CFG1_H__
