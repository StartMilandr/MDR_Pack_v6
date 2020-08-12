#include <MDR_SFP_ReadInfo.h>

const SFP_Info_Item   MDR_SFP_InfoItems[CFG_SFP_ITEMS_CNT] = CFG_SFP_ITEMS;
uint16_t MDR_SFP_InfoItem_Offs[CFG_SFP_ITEMS_CNT];

static MDR_I2Cst_MasterObj   *_pMasterI2C = NULL;
static uint8_t *_infoBuff;

static bool _started = false;
static bool _byRestart = false;
static uint32_t _infoInd;


static bool StartReadNextItem(void);

bool MDR_ReadSFP_Init(void)
{
  uint32_t i;
  uint16_t offs = 0;
  for (i = 0; i < CFG_SFP_ITEMS_CNT; i++)
  {
    MDR_SFP_InfoItem_Offs[i] = offs;
    offs += MDR_SFP_InfoItems[i].len;
  }
  
  return (offs == CFG_SFP_ITEMS_TABLE_LEN);
}

uint16_t MDR_ReadSFP_GetInfoItemOffset(uint32_t itemIndex)
{
  return MDR_SFP_InfoItem_Offs[itemIndex];
}

bool MDR_ReadSFP_Start(MDR_I2Cst_MasterObj *masterI2C, uint8_t *infoBuff, bool byRestart)
{
  if (_started)
    return false;
  
  _pMasterI2C = masterI2C;
  _infoBuff = infoBuff;
  _infoInd = 0;
  _started = StartReadNextItem();
  _byRestart = byRestart;
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
     MDR_I2C_StartReadAddrData(_pMasterI2C, I2C_ADDR_SFR, (uint8_t *)&MDR_SFP_InfoItems[_infoInd].addr, MDR_SFP_InfoItems[_infoInd].len, &_infoBuff[MDR_SFP_InfoItem_Offs[_infoInd]], _byRestart);      
    _infoInd++;
    return true;
  }
  else
    return false;
}


