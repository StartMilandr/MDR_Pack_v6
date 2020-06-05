#include <MDR_1923KX028_M0_TransferPC.h>

typedef enum {
  CID_NO_CMD      = 0,
  CID_GET_VERSION = 1,
  CID_GET_TEMP    = 2,
  CID_SFP_EVENTS  = 3,
  CID_SFP_DATA    = 4,
  CID_PHY_RESET   = 5,  
  CID_TEST        = 6,  
} DRV_CMD_ID;

#define CMD_REG_CMD_Pos               0x00000000UL
#define CMD_REG_CMD_Msk               0x000000FFUL
#define CMD_REG_PARAM_Pos             0x00000008UL
#define CMD_REG_PARAM_Msk             0xFFFFFF00UL
//  0,1 bits are reserved - pass the byte
#define CMD_REG_DATA2_Pos             0x8UL

#define STAT_REG_RDY_Msk              0x1UL
#define STAT_REG_ERR_Msk              0x2UL
//#define STAT_REG_RESERVED_Msk         0xFFFFFFFC0UL

//#define CMD_MSK                       0xFFUL
#define CmdReg_To_CmdID(reg)           ((reg) & CMD_REG_CMD_Msk)
#define CmdReg_To_Param(reg)          (((reg) & CMD_REG_PARAM_Msk) >> CMD_REG_PARAM_Pos)

//  Get_SFP_DATA
#define CMD_PAR_SFP_IND_Pos           8UL
#define CMD_PAR_SFP_IND_Msk           0x00000300UL
#define CMD_PAR_SFP_CNT_Pos           12UL
#define CMD_PAR_SFP_CNT_Msk           0x0000F000UL
#define CMD_PAR_SFP_OFFS_Pos          16UL
#define CMD_PAR_SFP_OFFS_Msk          0xFFFF0000UL

#define CmdPar_To_IndSFR(par)        ((par & CMD_PAR_SFP_IND_Msk)  >> CMD_PAR_SFP_IND_Pos)
#define CmdPar_To_RdCnt(par)         ((par & CMD_PAR_SFP_CNT_Msk)  >> CMD_PAR_SFP_CNT_Pos)
#define CmdPar_To_Offs(par)          ((par & CMD_PAR_SFP_OFFS_Msk) >> CMD_PAR_SFP_OFFS_Pos)

//  PHY Reset
#define CMD_PAR_PHY_SEL_Pos           8UL
#define CMD_PAR_PHY_SEL_Msk           0x00FFFF00UL
#define CMD_PAR_PHY_VAL_Pos           24UL
#define CMD_PAR_PHY_VAL_Msk           0x01000000UL

#define CmdPar_To_SelPHY(par)        (((par) & CMD_PAR_PHY_SEL_Msk) >> CMD_PAR_PHY_SEL_Pos)
#define CmdPar_To_BoolPHY(par)        ((par) & CMD_PAR_PHY_VAL_Msk)


#define EventsSFP_to_Data(evnt, pres)  ((evnt) | ((pres) << 16));

#define DrvReadCmd()          MDR_KX028_ReadAXI(CFG_KX028_PC_REG_CMD)
#define DrvWriteStatus(st)    MDR_KX028_WriteAXI(CFG_KX028_PC_REG_STATUS, (st))
#define DrvWriteData1(data)   MDR_KX028_WriteAXI(CFG_KX028_PC_REG_DATA1, (data))
#define DrvWriteData2(data)   MDR_KX028_WriteAXI(CFG_KX028_PC_REG_DATA2, (data))


static inline void DrvCmd_GetVersion()
{
  DrvWriteData1((CFG_KX028_PC_MAJOR_FW_VERSION & 0xFF) | (CFG_KX028_PC_MINOR_FW_VERSION << 8));
}

static inline void DrvCmd_GetTemp()
{
  //  Dummy values TODO
  uint8_t _TemprBasis_dummy = 0;
  uint8_t _TemprBoard_dummy = 0;
  
  DrvWriteData1((_TemprBasis_dummy & 0xFF) | (_TemprBoard_dummy << 8));
}
  
static void DrvCmd_GetEventsSFP()
{
  uint32_t events_dummy = 0;
//  uint32_t events = SFP_GetEventsAndClear();
//  events = EventsSFP_to_Data(events, g_PresenceSFP);
  
  DrvWriteData1(events_dummy);
}


static void DrvCmd_GetDataSFP(uint32_t cmdReg)
{
//  uint32_t indSFR = CmdPar_To_IndSFR(cmdReg);
//  uint32_t offs = CmdPar_To_Offs(cmdReg);
//  uint32_t cnt = CmdPar_To_RdCnt(cmdReg);
//  
//  const uint8_t *pBytes = SFP_pInfo[indSFR];
//  pBytes += offs;
//  uint32_t *pUint32 = (uint32_t *)pBytes;
//  
//  if (cnt > 0)
//    DrvWriteData1(__REV(pUint32[0]));
//  if (cnt > 4)
//    DrvWriteData2(__REV(pUint32[1]));
  
  uint16_t dummy1 = 0xAA; 
  uint16_t dummy2 = 0xBB; 
  DrvWriteData1(dummy1);
  DrvWriteData2(dummy2);
}

static void DrvCmd_PhyReset(uint32_t cmdReg)
{
//  uint32_t selPHY = CmdPar_To_SelPHY(cmdReg);
//  
//  if (CmdPar_To_BoolPHY(cmdReg))
//    ShiftSetValue(g_ShiftLastValue | selPHY);
//  else
//    ShiftSetValue(g_ShiftLastValue & (~selPHY));
}

void DrvCmd_SetTest(void)
{
  DrvWriteData1(CFG_KX028_PC_TEST_DATA1);
  DrvWriteData2(CFG_KX028_PC_TEST_DATA2);
}


void MDR_KX028_M0_TransferPC(void)
{
  uint32_t cmdReg;
  uint32_t cmdID;
  uint32_t cmdStatus;
  
  //  Wait Command
  cmdReg = DrvReadCmd();
  cmdID = CmdReg_To_CmdID(cmdReg);
  //  Check Command and Perform
  if (cmdReg != CID_NO_CMD)        
  {
    cmdStatus = STAT_REG_RDY_Msk;
    switch (cmdID) {
    case CID_GET_VERSION: DrvCmd_GetVersion(); break;
    case CID_GET_TEMP:    DrvCmd_GetTemp(); break;
    case CID_SFP_EVENTS:  DrvCmd_GetEventsSFP(); break;
    case CID_SFP_DATA:    DrvCmd_GetDataSFP(cmdReg); break;
    case CID_PHY_RESET:   DrvCmd_PhyReset(cmdReg); break;
    case CID_TEST:        DrvCmd_SetTest(); break;
    default:              {
      DrvWriteData1(cmdReg);
      cmdStatus = STAT_REG_ERR_Msk;
      }
    }        
    //  Set Status
    DrvWriteStatus(cmdStatus);
    //  Wait Command Clear
    do {
      cmdReg = DrvReadCmd();
    } while (cmdReg != CID_NO_CMD);
    //  ClearReady
    DrvWriteStatus(0);
  }
}

