#ifndef MDR_SFP_PRESENCE_CTRL_H
#define MDR_SFP_PRESENCE_CTRL_H

#include <MDR_Config.h>
#include <MDR_GPIO.h>
#include <MDR_SoftI2C_ByTimer.h>
#include <MDR_SFP_ReadInfo.h>
#include <stdint.h>
#include <stdbool.h>


typedef uint32_t (*pGetPresenceMaskFunc)(void);
typedef void     (*OnEventSFP)(uint32_t);


typedef struct {
  MDR_I2Cst_MasterObj  *pMasterI2C;
  pGetPresenceMaskFunc  GetPresenceMaskFunc;
  uint32_t             *pPresenceMask;    // Pin masks for every countSFP
  OnEventSFP            OnConnected;
  OnEventSFP            OnDisconnected;
  //  ptr to SFP Info
  uint32_t              countSFP;
  uint8_t             **pInfoSFP;
  bool                  useRestart;
} MDR_SFP_PresCtrl_Cfg;

typedef struct {
  uint32_t              muxAddr;
  const uint8_t        *pIndToMux;
} MDR_SFP_PresCtrl_MuxI2C_Cfg;


void MDR_SFP_PresCtrlInit(MDR_SFP_PresCtrl_Cfg *presCfg, MDR_SFP_PresCtrl_MuxI2C_Cfg *muxCfg);
//  Return true while updating, false - no presence changed
bool MDR_SFP_PresCtrl_Process(void);


#endif    //MDR_SFP_PRESENCE_CTRL_H

