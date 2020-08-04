#include "MDR_SFP_ReadInfo.h"

const SFP_Info_Item MDR_SFP_InfoItems[CFG_SFP_ITEMS_CNT] = CFG_SFP_ITEMS;


static MDR_I2Cst_MasterObj   *_pMasterI2C = NULL;
static uint8_t *_infoBuff;

static bool _started = false;
static uint32_t _infoInd;


static bool StartReadNextItem(void);


bool MDR_ReadSFP_Start(MDR_I2Cst_MasterObj *masterI2C, uint8_t *infoBuff)
{
  if (_started)
    return false;
  
  _pMasterI2C = masterI2C;
  _infoBuff = infoBuff;
  _infoInd = 0;
  _started = StartReadNextItem();
  return true;
}

bool MDR_ReadSFP_ProcessCompleted(void)
{
  if (!_pMasterI2C->started)
    _started = StartReadNextItem();
  return !_started;
}

static bool StartReadNextItem(void)
{
  if (_infoInd < CFG_SFP_ITEMS_CNT)
  {  
    MDR_I2C_StartReadAddrData(_pMasterI2C, I2C_ADDR_SFR, (uint8_t *)&MDR_SFP_InfoItems[_infoInd].addr, MDR_SFP_InfoItems[_infoInd].len, &_infoBuff[_infoInd * SFP_ITEM_LEN_MAX]);  
    _infoInd++;
    return true;
  }
  else
    return false;
}


