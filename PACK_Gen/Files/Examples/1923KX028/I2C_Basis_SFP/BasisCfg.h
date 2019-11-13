#ifndef BASIS_CFG_H
#define BASIS_CFG_H

#include <MDR_Config.h>
#include <stdint.h>
#include <MDR_GPIO.h>
#include <MDR_I2C.h>
#include "SFP_Defs.h"
#include "MDRB_Basis_v2.h"

void PhyResetPinsInit(void);
void vResetPhys( void );

void SFP_PresencePinsInit(void);

#define SFP_DISCONNECTED_STATUS   0xFUL

__STATIC_INLINE uint32_t SFP_GetPresenceStatus(void)                       { return (SFP_PRES_PORT->RXTX & SFP_PRES_PIN_ALL) >> SFP_PRES_PIN_ALL_POS; }
bool SFP_MuxSetActive(uint8_t selSFP);

//  Info Items Select
typedef struct {
  uint8_t addr;
  uint8_t len;
  char *  name;
} SFP_Info_Item;


#define  SFP_INFO_CNT       27
extern const SFP_Info_Item  InfoItems[SFP_INFO_CNT];

__STATIC_INLINE bool SFP_ReadInfo(uint32_t infoInd, uint8_t *rdData) { return MDR_I2C_ReadAddrData(I2C_ADDR_SFR, InfoItems[infoInd].addr, InfoItems[infoInd].len, rdData); }




#endif    //BASIS_CFG_H

