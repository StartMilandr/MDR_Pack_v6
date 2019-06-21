#ifndef CLOCK_ITEMS_H
#define CLOCK_ITEMS_H

#include <MDR_CPU_ClockSelect.h>
#include <MDR_RST_Clock.h>

typedef enum {
  ID_SetLSI,
  ID_SetLSE,
  ID_SetHSI,
  ID_SetHSE,
  ID_SetPLL_HSI,
  ID_SetPLL_HSE
} ID_CLK_SetFunc;

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wpadded"
#endif

  typedef struct {
    ID_CLK_SetFunc setFuncID;
    void          *cfgStruct;
    uint8_t        indHSE;
    uint8_t        indPLL;
    uint32_t       freqHz;
    char           name[20];
  } CLK_Item;

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop  
#endif


#if defined (USE_MDR1986VE8)  || (USE_MDR1923VK014)
  typedef enum {
    iLSI,
    iLSE ,
    iHSI,
    iHSId2,
    iHSE0,
    iHSE0d2,
    iHSE1,
    iHSE1d2,
    iHSI_P0_40,
    iHSI_P1_36,
    iHSI_P2_20,
    iHSE0_P0_40,
    iHSE0_P1_36,
    iHSE0_P2_20,
    iHSE1_P0_40,
    iHSE1_P1_36,
    iHSE1_P2_20,
    _ClockItemsCount,
  } ClockItemsEnum;
  
#elif defined (USE_ESila)  
  
  typedef enum {
    iLSI,
    iLSE ,
    iHSI,
    iHSId2,
    iHSE0,
    iHSE0d2,
    iHSE1,
    iHSE1d2,
    iHSI_P0_120,
    iHSI_P1_100,
    iHSI_P2_80,
    iHSI_P3_40,
    iHSE0_P0_120,
    iHSE0_P1_100,
    iHSE0_P2_80,
    iHSE0_P3_60,
    iHSE1_P0_120,
    iHSE1_P1_100,
    iHSE1_P2_80,
    iHSE1_P3_60,
    _ClockItemsCount,
  } ClockItemsEnum;
  
#else //if defined (USE_MDR1986VE9x)
  typedef enum {
    iLSI,
    iLSE ,
    iHSI,
    iHSId2,
    iHSE,
    iHSEd2,
    iHSI_P_128,
    iHSI_P_64,
    iHSI_P_32,
    iHSE_P_128,
    iHSE_P_80,
    iHSE_P_40,
    _ClockItemsCount,
  } ClockItemsEnum;  
#endif

                         
extern CLK_Item ClockConfigs[_ClockItemsCount];
MDR_CPU_SetClockResult  ChangeClockCPU(const CLK_Item *item);



#endif  // CLOCK_ITEMS_H
