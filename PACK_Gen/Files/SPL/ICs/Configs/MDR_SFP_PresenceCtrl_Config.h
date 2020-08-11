#ifndef MDR_SFP_PRESENCE_CTRL_CFG_H
#define MDR_SFP_PRESENCE_CTRL_CFG_H

#include <MDR_Config.h>
#include <MDR_GPIO.h>
#include "MDRB_Basis_v2.h"
#include <MDR_SoftI2C_ByTimer.h>
#include <stdint.h>
#include <stdbool.h>
#include "SFP_Defs.h"


__STATIC_INLINE uint32_t SFP_GetPresenceStatus(void)  { return (SFP_PRES_PORT->RXTX & SFP_PRES_PIN_ALL) >> SFP_PRES_PIN_ALL_POS; }


//  Info Items Select
typedef struct {
  uint8_t addr;
  uint8_t len;
  char *  name;
} SFP_Info_Item;


#define  SFP_INFO_CNT       27
extern const SFP_Info_Item  InfoItems[SFP_INFO_CNT];

typedef bool (*pProcessCompletedFunc)(void);
typedef void (*OnChangedSFP)(uint32_t);

bool SFP_ReadInfoStart(MDR_I2Cst_MasterObj *masterI2C, OnChangedSFP onConnectedSFP, OnChangedSFP  onUpdateInfoSFP, OnChangedSFP  onDisconnectedSFP);
bool SFP_ReadInfoProcessCompleted(void);
  
extern uint8_t infoSFP[SFP_LEN_MAX * SFP_INFO_CNT];

#endif    //MDR_SFP_PRESENCE_CTRL_CFG_H

