#include <MDR_SFP_PresenceCtrl.h>


static MDR_SFP_PresCtrl_Cfg         _presCfg;
static MDR_SFP_PresCtrl_MuxI2C_Cfg  _muxCfg;
static bool _muxCfgEnabled = false;

static uint32_t _activePresence = 0;
static uint32_t _changedPresence;
static uint32_t _indSFP = 0;
static bool     _started;

//  Handlers Def
typedef bool (*pProcessCompletedFunc)(void);
static pProcessCompletedFunc _nextFunc;
//  Presence
static bool SFP_CheckPresenceChanged(void);
static bool SFP_CheckNextSFP(void);
//  Mux
static void SFP_MuxSetActive_Start(uint8_t indSFP);
static bool I2C_SetMux_WaitCompleted(void);
//  Info
static void SFP_ReadInfoSFP_Start(void);
static bool SFP_ReadInfoSFP_WaitCompleted(void);


void MDR_SFP_PresCtrlInit(MDR_SFP_PresCtrl_Cfg *presCfg, MDR_SFP_PresCtrl_MuxI2C_Cfg *muxCfg)
{
  _presCfg = *presCfg;
  _muxCfgEnabled = muxCfg != NULL;
  if (_muxCfgEnabled)
    _muxCfg = *muxCfg;
  
  _activePresence = ~_presCfg.GetPresenceMaskFunc();
  _nextFunc = SFP_CheckPresenceChanged;
}

bool MDR_SFP_PresCtrl_Process(void)
{
  _started = _nextFunc();        
  return _started;
}

// Если маска наличия SFP поменялась - запускаем опрос для изменившихся бит
static bool SFP_CheckPresenceChanged(void)
{
  uint32_t newPresence = _presCfg.GetPresenceMaskFunc();
  _changedPresence = newPresence ^ _activePresence;
  _activePresence = newPresence;
  if (_changedPresence != 0)
  {
    _indSFP = 0;
    _nextFunc = SFP_CheckNextSFP;
    return false;
  }
  else    
    return true;
}


// Перебираем изменившиеся биты:
// Если SPF вынут - SPF_OnDisconnected, 
// если SPF появился - запускаем опрос инфо (или переключаем мультиплексор I2C на конкретный SFP)
static bool SFP_CheckNextSFP(void)
{
  while (_indSFP < _presCfg.countSFP)
  {
    uint32_t selMsk = _presCfg.pPresenceMask[_indSFP];    
    if (_changedPresence & selMsk)
    {
      if (_activePresence & selMsk)
        _presCfg.OnDisconnected(_indSFP);
      else
      {
        if (_muxCfgEnabled)
          SFP_MuxSetActive_Start(_indSFP);
        else
          SFP_ReadInfoSFP_Start();
        
        return false;
      }
    }       
    _indSFP++;
  }
  
  _nextFunc = SFP_CheckPresenceChanged;
  return true; 
}

//  ---  Switch I2C-MUX  ---
static void SFP_MuxSetActive_Start(uint8_t indSFP) 
{  
  _nextFunc = I2C_SetMux_WaitCompleted;
  MDR_I2Cst_MasterStartWrite(_presCfg.pMasterI2C, _muxCfg.muxAddr, (uint8_t *)&_muxCfg.pIndToMux[_indSFP], 1);
}

static bool I2C_SetMux_WaitCompleted(void)
{
  if (MDR_I2Cst_MasterGetCompleted(_presCfg.pMasterI2C))
    SFP_ReadInfoSFP_Start();
  return false;
}


//  ---  Read SFP Info  ---
static void SFP_ReadInfoSFP_Start(void)
{
  _nextFunc = SFP_ReadInfoSFP_WaitCompleted;  
  MDR_ReadSFP_Start(_presCfg.pMasterI2C, _presCfg.pInfoSFP[_indSFP], _presCfg.useRestart);
}

static bool SFP_ReadInfoSFP_WaitCompleted(void)
{
  if (!MDR_ReadSFP_ProcessCompleted())
    return false;    
  
  _presCfg.OnConnected(_indSFP);
  
  _indSFP++;
  _nextFunc = SFP_CheckNextSFP;    
  return false;
}





