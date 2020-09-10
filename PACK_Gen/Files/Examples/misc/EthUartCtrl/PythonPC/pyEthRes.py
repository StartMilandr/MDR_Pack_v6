MAC_T       = 0x02
MAC_M       = 0x04
MAC_H       = 0x06
HASH        = 0x08
HASH0       = 0x08
HASH1       = 0x0A
HASH2       = 0x0C
HASH3       = 0x0E
IPG         = 0x10
PSC         = 0x12
BAG         = 0x14
JitterWnd   = 0x16
R_CFG       = 0x18
X_CFG       = 0x1A
G_CFGl      = 0x1C
G_CFGh      = 0x1E
IMR         = 0x20
IFR         = 0x22
MDIO_CTRL   = 0x24
MDIO_DATA   = 0x26
R_Head      = 0x28
X_Tail      = 0x2A
R_Tail      = 0x2C
X_Head      = 0x2E
STAT        = 0x30
PHY_Control = 0x34
PHY_Status  = 0x36 

VE1_RegsMAC_Phy = { 
                  'MAC_T':       (0,  MAC_T),
                  'MAC_M':       (0,  MAC_M),    
                  'MAC_H':       (0,  MAC_H),    
                  'HASH':        (0,  HASH),
                  'HASH0':       (0,  HASH0),
                  'HASH1':       (0,  HASH1),    
                  'HASH2':       (0,  HASH2),   
                  'HASH3':       (0,  HASH3),   
                  'IPG':         (0,  IPG),                   
                  'PSC':         (0,  PSC),     
                  'BAG':         (0,  BAG),      
                  'JitterWnd':   (0,  JitterWnd),
                  'R_CFG':       (0,  R_CFG),    
                  'X_CFG':       (0,  X_CFG),    
                  'G_CFGl':      (0,  G_CFGl),   
                  'G_CFGh':      (0,  G_CFGh),   
                  'IMR':         (0,  IMR),      
                  'IFR':         (0,  IFR),      
                  'MDIO_CTRL':   (0,  MDIO_CTRL),
                  'MDIO_DATA':   (0,  MDIO_DATA),
                  'R_Head':      (0,  R_Head),   
                  'X_Tail':      (0,  X_Tail),   
                  'R_Tail':      (0,  R_Tail),   
                  'X_Head':      (0,  X_Head),   
                  'STAT':        (0,  STAT),
                  'PHY_Control': (0,  PHY_Control),
                  'PHY_Status':  (0,  PHY_Status),
                  # PhyRegs
                  'Phy0_Ctrl'     : (1,  0),
                  'Phy1_Status'   : (1,  1),
                  'Phy2_Ident'    : (1,  2),
                  'Phy3_Ident'    : (1,  3),
                  'Phy4_Adv'      : (1,  4),
                  'Phy5_OppAdv'   : (1,  5),
                  'Phy6_Auto'     : (1,  6),
                  'Phy18_CtrlEx'  : (1,  18),
                  'Phy29_IrqFlags': (1,  29),
                  'Phy30_IrqMsk'  : (1,  30),
                  'Phy31_EnhCtrl' : (1,  31),
}

'''
ACT_ACTIIONS = ['ACT_FORWARD', 'ACT_FLOOD', 'ACT_PUNT', 'ACT_DISCARD', 'ACT_OVERRIDE', 'ACT_FWD_MASK', 'ACT_COS_DISCARD']
sAPPLY_BTN_TEXT = 'Write To Device'
#PORTS_ORDER = [1, 2, 3, 4]
PORTS_ORDER = range(1, 17)

TEXT_BTN_READ  = 'Read'
TEXT_BTN_WRITE = 'Write'
TEXT_LINK_DOWN = 'Down'

SHUT_DOWN_ITEMS = ['PowerOn', 'PowerOff']
AFT_ITEMS = ['AnyTagged', 'Tagged', 'Untagged']
BLOCKSTATE_ITEMS = ['Forwarding', 'Blocked', 'LearnOnly']

_PortNames = []
def BasisGetPortNames():
  if len(_PortNames) != len(PORTS_ORDER):
    _PortNames.clear()
    for d in PORTS_ORDER:
      _PortNames.append('Port {}'.format(d))

  return _PortNames


def _VAL2FLD(value, valPos, ValMsk):
  return (value << valPos) & ValMsk

def _FLD2VAL(value, valPos, ValMsk):
  return (value & ValMsk) >> valPos



#--- for EMac DefConfig ---
PORT0_STRUC1  = 0x46c 
PORT1_STRUC1  = 0x474 
PORT2_STRUC1  = 0x47c
PORT3_STRUC1  = 0x484
PORT4_STRUC1  = 0x48c
PORT5_STRUC1  = 0x494
PORT6_STRUC1  = 0x49c
PORT7_STRUC1  = 0x4a4
PORT8_STRUC1  = 0x548
PORT9_STRUC1  = 0x550
PORT10_STRUC1 = 0x558
PORT11_STRUC1 = 0x560
PORT12_STRUC1 = 0x568
PORT13_STRUC1 = 0x570
PORT14_STRUC1 = 0x578
PORT15_STRUC1 = 0x580
PORT16_STRUC1 = 0x588

PORT0_STRUC2  = 0x470 
PORT1_STRUC2  = 0x478
PORT2_STRUC2  = 0x480
PORT3_STRUC2  = 0x488
PORT4_STRUC2  = 0x490
PORT5_STRUC2  = 0x498
PORT6_STRUC2  = 0x4a0
PORT7_STRUC2  = 0x4a8
PORT8_STRUC2  = 0x54c
PORT9_STRUC2  = 0x554
PORT10_STRUC2 = 0x55c
PORT11_STRUC2 = 0x564
PORT12_STRUC2 = 0x56c
PORT13_STRUC2 = 0x574
PORT14_STRUC2 = 0x57c
PORT15_STRUC2 = 0x584
PORT16_STRUC2 = 0x58c

CLASS1_BASE_ADDR = 0x620000
CLASS2_BASE_ADDR = 0x770000

kx028_AddrStruc1 = [PORT0_STRUC1,  PORT1_STRUC1,  PORT2_STRUC1,  PORT3_STRUC1,  PORT4_STRUC1, \
                    PORT5_STRUC1,  PORT6_STRUC1,  PORT7_STRUC1,  PORT8_STRUC1,  PORT9_STRUC1, \
                    PORT10_STRUC1, PORT11_STRUC1, PORT12_STRUC1, PORT13_STRUC1, PORT14_STRUC1, \
                    PORT15_STRUC1, PORT16_STRUC1]

kx028_AddrStruc2 = [PORT0_STRUC2,  PORT1_STRUC2,  PORT2_STRUC2,  PORT3_STRUC2,  PORT4_STRUC2, \
                    PORT5_STRUC2,  PORT6_STRUC2,  PORT7_STRUC2,  PORT8_STRUC2,  PORT9_STRUC2, \
                    PORT10_STRUC2, PORT11_STRUC2, PORT12_STRUC2, PORT13_STRUC2, PORT14_STRUC2, \
                    PORT15_STRUC2, PORT16_STRUC2]


#---  for EMAC Status ---
EMAC_NETSTAT		        = 0x0008 
EMAC_NETSTAT_LINK_Msk	  = 0x0001

EMAC1_BASE_ADDR  = 0x660000
EMAC2_BASE_ADDR  = 0x670000
EMAC3_BASE_ADDR  = 0x680000
EMAC4_BASE_ADDR  = 0x690000
EMAC5_BASE_ADDR  = 0x6A0000
EMAC6_BASE_ADDR  = 0x6B0000
EMAC7_BASE_ADDR  = 0x6C0000
EMAC8_BASE_ADDR  = 0x6D0000
EMAC9_BASE_ADDR  = 0x6E0000
EMAC10_BASE_ADDR = 0x6F0000
EMAC11_BASE_ADDR = 0x760000
EMAC12_BASE_ADDR = 0x710000
EMAC13_BASE_ADDR = 0x720000
EMAC14_BASE_ADDR = 0x730000
EMAC15_BASE_ADDR = 0x740000
EMAC16_BASE_ADDR = 0x750000

kx028_EmacAdr = [EMAC1_BASE_ADDR,  EMAC2_BASE_ADDR,  EMAC3_BASE_ADDR,  EMAC4_BASE_ADDR,  EMAC5_BASE_ADDR, \
                 EMAC6_BASE_ADDR,  EMAC7_BASE_ADDR,  EMAC8_BASE_ADDR,  EMAC9_BASE_ADDR,  EMAC10_BASE_ADDR, \
                 EMAC11_BASE_ADDR, EMAC12_BASE_ADDR, EMAC13_BASE_ADDR, EMAC14_BASE_ADDR, EMAC15_BASE_ADDR, \
                 EMAC16_BASE_ADDR]

#--- for Debug ---
dbg_PORT0_STRUC1  = 0 
dbg_PORT1_STRUC1  = 1 
dbg_PORT2_STRUC1  = 2
dbg_PORT3_STRUC1  = 3
dbg_PORT4_STRUC1  = 4
dbg_PORT5_STRUC1  = 5
dbg_PORT6_STRUC1  = 6
dbg_PORT7_STRUC1  = 7
dbg_PORT8_STRUC1  = 8
dbg_PORT9_STRUC1  = 9
dbg_PORT10_STRUC1 = 10
dbg_PORT11_STRUC1 = 11
dbg_PORT12_STRUC1 = 12
dbg_PORT13_STRUC1 = 13
dbg_PORT14_STRUC1 = 14
dbg_PORT15_STRUC1 = 15
dbg_PORT16_STRUC1 = 16

dbg_PORT0_STRUC2  = 17
dbg_PORT1_STRUC2  = 18
dbg_PORT2_STRUC2  = 19
dbg_PORT3_STRUC2  = 20
dbg_PORT4_STRUC2  = 21
dbg_PORT5_STRUC2  = 22
dbg_PORT6_STRUC2  = 23
dbg_PORT7_STRUC2  = 24
dbg_PORT8_STRUC2  = 25
dbg_PORT9_STRUC2  = 26
dbg_PORT10_STRUC2 = 27
dbg_PORT11_STRUC2 = 28
dbg_PORT12_STRUC2 = 29
dbg_PORT13_STRUC2 = 30
dbg_PORT14_STRUC2 = 31
dbg_PORT15_STRUC2 = 32
dbg_PORT16_STRUC2 = 33

kx028_AddrStruc1_dbg = [dbg_PORT0_STRUC1,  dbg_PORT1_STRUC1,  dbg_PORT2_STRUC1,  dbg_PORT3_STRUC1,  dbg_PORT4_STRUC1, \
                        dbg_PORT5_STRUC1,  dbg_PORT6_STRUC1,  dbg_PORT7_STRUC1,  dbg_PORT8_STRUC1,  dbg_PORT9_STRUC1, \
                        dbg_PORT10_STRUC1, dbg_PORT11_STRUC1, dbg_PORT12_STRUC1, dbg_PORT13_STRUC1, dbg_PORT14_STRUC1, \
                        dbg_PORT15_STRUC1, dbg_PORT16_STRUC1]

kx028_AddrStruc2_dbg = [dbg_PORT0_STRUC2,  dbg_PORT1_STRUC2,  dbg_PORT2_STRUC2,  dbg_PORT3_STRUC2,  dbg_PORT4_STRUC2, \
                        dbg_PORT5_STRUC2,  dbg_PORT6_STRUC2,  dbg_PORT7_STRUC2,  dbg_PORT8_STRUC2,  dbg_PORT9_STRUC2, \
                        dbg_PORT10_STRUC2, dbg_PORT11_STRUC2, dbg_PORT12_STRUC2, dbg_PORT13_STRUC2, dbg_PORT14_STRUC2, \
                        dbg_PORT15_STRUC2, dbg_PORT16_STRUC2]

EMAC_PCS_CONTROL = 0x200
EMAC_PCS_STATUS  = 0x204
EMAC_PCS_ADV     = 0x210
EMAC_PCS_BASE    = 0x214


kxo28_RegsEMAC = { 'emac1_pcs_control': EMAC1_BASE_ADDR + EMAC_PCS_CONTROL,
                  'emac2_pcs_control': EMAC2_BASE_ADDR + EMAC_PCS_CONTROL,
                  'emac3_pcs_control': EMAC3_BASE_ADDR + EMAC_PCS_CONTROL,
                  'emac4_pcs_control': EMAC4_BASE_ADDR + EMAC_PCS_CONTROL,
                  'emac5_pcs_control': EMAC5_BASE_ADDR + EMAC_PCS_CONTROL,
                  'emac6_pcs_control': EMAC6_BASE_ADDR + EMAC_PCS_CONTROL,
                  'emac7_pcs_control': EMAC7_BASE_ADDR + EMAC_PCS_CONTROL,
                  #
                  'emac1_pcs_status':  EMAC1_BASE_ADDR + EMAC_PCS_STATUS,
                  'emac2_pcs_status':  EMAC2_BASE_ADDR + EMAC_PCS_STATUS,
                  'emac3_pcs_status':  EMAC3_BASE_ADDR + EMAC_PCS_STATUS,
                  'emac4_pcs_status':  EMAC4_BASE_ADDR + EMAC_PCS_STATUS,
                  'emac5_pcs_status':  EMAC5_BASE_ADDR + EMAC_PCS_STATUS,
                  'emac6_pcs_status':  EMAC6_BASE_ADDR + EMAC_PCS_STATUS,
                  'emac7_pcs_status':  EMAC7_BASE_ADDR + EMAC_PCS_STATUS,
                  # adv
                  'emac1_pcs_adv':  EMAC1_BASE_ADDR + EMAC_PCS_ADV,
                  'emac2_pcs_adv':  EMAC2_BASE_ADDR + EMAC_PCS_ADV,
                  'emac3_pcs_adv':  EMAC3_BASE_ADDR + EMAC_PCS_ADV,
                  'emac4_pcs_adv':  EMAC4_BASE_ADDR + EMAC_PCS_ADV,
                  'emac5_pcs_adv':  EMAC5_BASE_ADDR + EMAC_PCS_ADV,
                  'emac6_pcs_adv':  EMAC6_BASE_ADDR + EMAC_PCS_ADV,
                  'emac7_pcs_adv':  EMAC7_BASE_ADDR + EMAC_PCS_ADV,
                  # adv
                  'emac1_pcs_base':  EMAC1_BASE_ADDR + EMAC_PCS_BASE,
                  'emac2_pcs_base':  EMAC2_BASE_ADDR + EMAC_PCS_BASE,
                  'emac3_pcs_base':  EMAC3_BASE_ADDR + EMAC_PCS_BASE,
                  'emac4_pcs_base':  EMAC4_BASE_ADDR + EMAC_PCS_BASE,
                  'emac5_pcs_base':  EMAC5_BASE_ADDR + EMAC_PCS_BASE,
                  'emac6_pcs_base':  EMAC6_BASE_ADDR + EMAC_PCS_BASE,
                  'emac7_pcs_base':  EMAC7_BASE_ADDR + EMAC_PCS_BASE,
}


#--------  EMAC  ------------
AXI_EMAC_NETCTRL		   = 0x0000
AXI_EMAC_NETCFG		     = 0x0004 
AXI_EMAC_CTRL          = 0x08A0 
AXI_EMAC_NETSTAT		   = 0x0008 
AXI_EMAC_TXSTAT		     = 0x0014 
AXI_EMAC_RXSTAT		     = 0x0020 

kxo28_RegsOffs_EMAC = { 
                  'AXI_EMAC_NETCTRL':    AXI_EMAC_NETCTRL,
                  'AXI_EMAC_NETCFG':     AXI_EMAC_NETCFG,
                  'AXI_EMAC_CTRL':       AXI_EMAC_CTRL,
                  'AXI_EMAC_NETSTAT':    AXI_EMAC_NETSTAT,
                  'AXI_EMAC_TXSTAT':     AXI_EMAC_TXSTAT,
                  'AXI_EMAC_TXSTAT':     AXI_EMAC_TXSTAT,
                  'AXI_EMAC_RXSTAT':     AXI_EMAC_RXSTAT,
}


#--------  BMU  ---------------
AXI_BMU1_BASE_ADDR          = 0x100000
AXI_BMU2_BASE_ADDR          = 0x700000

AXI_BMU_CTRL                = 0x04
AXI_BMU_UCAST_CONFIG        = 0x08
AXI_BMU_UCAST_BASEADDR      = 0x0c
AXI_BMU_BUF_SIZE            = 0x10 
AXI_BMU_BUF_CNT             = 0x14 
AXI_BMU_THRES               = 0x18
AXI_BMU_INT_SRC             = 0x20
AXI_BMU_INT_ENABLE          = 0x24 

AXI_TMU_BASE_ADDR           = 0x600000
AXI_TMU_PHY16_INQ_ADDR      = 0x240

kxo28_RegsBMU = { 
                  'TMU16_INQADDR':      AXI_TMU_BASE_ADDR + AXI_TMU_PHY16_INQ_ADDR,
  #define AXI_TMU_PHY16_INQ_ADDR      0x240
                  'BMU1_CTRL':      AXI_BMU1_BASE_ADDR + AXI_BMU_CTRL,
                  'BMU1_CFG':       AXI_BMU1_BASE_ADDR + AXI_BMU_UCAST_CONFIG,
                  'BMU1_BASE_ADDR': AXI_BMU1_BASE_ADDR + AXI_BMU_UCAST_BASEADDR,
                  'BMU1_BUF_SIZE':  AXI_BMU1_BASE_ADDR + AXI_BMU_BUF_SIZE,
                  'BMU1_BUF_CNT':   AXI_BMU1_BASE_ADDR + AXI_BMU_BUF_CNT,
                  'BMU1_THRES':     AXI_BMU1_BASE_ADDR + AXI_BMU_THRES,
                  'BMU1_INT_SRC':   AXI_BMU1_BASE_ADDR + AXI_BMU_INT_SRC,
                  'BMU1_INT_ENA':   AXI_BMU1_BASE_ADDR + AXI_BMU_INT_ENABLE,                  
                  # BMU2
                  'BMU2_CTRL':      AXI_BMU2_BASE_ADDR + AXI_BMU_CTRL,
                  'BMU2_CFG':       AXI_BMU2_BASE_ADDR + AXI_BMU_UCAST_CONFIG,
                  'BMU2_BASE_ADDR': AXI_BMU2_BASE_ADDR + AXI_BMU_UCAST_BASEADDR,
                  'BMU2_BUF_SIZE':  AXI_BMU2_BASE_ADDR + AXI_BMU_BUF_SIZE,
                  'BMU2_BUF_CNT':   AXI_BMU2_BASE_ADDR + AXI_BMU_BUF_CNT,
                  'BMU2_THRES':     AXI_BMU2_BASE_ADDR + AXI_BMU_THRES,
                  'BMU2_INT_SRC':   AXI_BMU2_BASE_ADDR + AXI_BMU_INT_SRC,
                  'BMU2_INT_ENA':   AXI_BMU2_BASE_ADDR + AXI_BMU_INT_ENABLE,
}

#--------  GPI  ---------------
EGPI1 = 0
EGPI2 = 1
EGPI3 = 2
EGPI4 = 3
EGPI5 = 4
EGPI6 = 5
EGPI7 = 6
EGPI8 = 7
EGPI9 = 8
EGPI10 = 9
EGPI11 = 10
EGPI12 = 11
EGPI13 = 12
EGPI14 = 13
EGPI15 = 14
EGPI16 = 15
HGPI = 16

AXI_EGPI1_BASE_ADDR         = 0x780000
AXI_EGPI2_BASE_ADDR         = 0x790000
AXI_EGPI3_BASE_ADDR         = 0x7A0000
AXI_EGPI4_BASE_ADDR         = 0x7B0000
AXI_EGPI5_BASE_ADDR         = 0x7C0000
AXI_EGPI6_BASE_ADDR         = 0x7D0000
AXI_EGPI7_BASE_ADDR         = 0x7E0000
AXI_EGPI8_BASE_ADDR         = 0x7F0000
AXI_EGPI9_BASE_ADDR         = 0x800000
AXI_EGPI10_BASE_ADDR        = 0x810000
AXI_EGPI11_BASE_ADDR        = 0x820000
AXI_EGPI12_BASE_ADDR        = 0x830000
AXI_EGPI13_BASE_ADDR        = 0x840000
AXI_EGPI14_BASE_ADDR        = 0x850000
AXI_EGPI15_BASE_ADDR        = 0x860000
AXI_EGPI16_BASE_ADDR        = 0x870000
AXI_HGPI_BASE_ADDR          = 0x650000

kxo28_Addr_GPI = [
  AXI_EGPI1_BASE_ADDR,
  AXI_EGPI2_BASE_ADDR,
  AXI_EGPI3_BASE_ADDR,
  AXI_EGPI4_BASE_ADDR,
  AXI_EGPI5_BASE_ADDR,
  AXI_EGPI6_BASE_ADDR,
  AXI_EGPI7_BASE_ADDR,
  AXI_EGPI8_BASE_ADDR,
  AXI_EGPI9_BASE_ADDR,
  AXI_EGPI10_BASE_ADDR,
  AXI_EGPI11_BASE_ADDR,
  AXI_EGPI12_BASE_ADDR,
  AXI_EGPI13_BASE_ADDR,
  AXI_EGPI14_BASE_ADDR,
  AXI_EGPI15_BASE_ADDR,
  AXI_EGPI16_BASE_ADDR,
  AXI_HGPI_BASE_ADDR
]

AXI_GPI_CTRL               = 0x04
AXI_GPI_RX_CONFIG          = 0x08
AXI_GPI_HDR_SIZE           = 0x0c
AXI_GPI_BUF_SIZE           = 0x10 
AXI_GPI_LMEM_ALLOC_ADDR    = 0x14
AXI_GPI_LMEM_FREE_ADDR     = 0x18
AXI_GPI_CLASS_ADDR         = 0x24 
AXI_GPI_LMEM_SEC_BUF_DATA_OFFSET  = 0x60 
AXI_GPI_TMLF_TX             = 0x4C
AXI_GPI_DTX_ASEQ            = 0X50 
AXI_GPI_LMEM2_FREE_ADDR     = 0x148 
AXI_GPI_LMEM_DATA_OFFSET    = 0x38 

kxo28_RegsOffs_GPI = { 
                  'GPI_CTRL':                 AXI_GPI_CTRL,
                  'GPI_RX_CONFIG':            AXI_GPI_RX_CONFIG,
                  'GPI_HDR_SIZE':             AXI_GPI_HDR_SIZE,
                  'GPI_BUF_SIZE':             AXI_GPI_BUF_SIZE,
                  'GPI_LMEM_ALLOC_ADDR':      AXI_GPI_LMEM_ALLOC_ADDR,
                  'GPI_LMEM_FREE_ADDR':       AXI_GPI_LMEM_FREE_ADDR,
                  'GPI_CLASS_ADDR':           AXI_GPI_CLASS_ADDR,
                  'GPI_LMEM_SEC_BUF_DATA_OFFSET': AXI_GPI_LMEM_SEC_BUF_DATA_OFFSET,
                  'GPI_TMLF_TX':              AXI_GPI_TMLF_TX,
                  'GPI_DTX_ASEQ':             AXI_GPI_DTX_ASEQ,
                  'GPI_LMEM2_FREE_ADDR':      AXI_GPI_LMEM2_FREE_ADDR,
                  'GPI_LMEM_DATA_OFFSET':     AXI_GPI_LMEM_DATA_OFFSET,
}

#--------  Classif  ---------------
AXI_CLASS_HW1_BASE_ADDR             = 0x620000
AXI_CLASS_HW2_BASE_ADDR             = 0x770000

kxo28_Addr_CLASS = [AXI_CLASS_HW1_BASE_ADDR, AXI_CLASS_HW2_BASE_ADDR]

AXI_CLASS_TX_CTRL                   = 0x04 
AXI_CLASS_HDR_SIZE                  = 0x14
AXI_CLASS_TM_INQ_ADDR               = 0x114 
AXI_CLASS_BMU1_BUF_FREE             = 0x24c 
AXI_CLASS_BUS_ACCESS_BASE_ADDR      = 0x258
AXI_CLASS_GLOBAL_CFG                = 0x4ac
AXI_CLASS_GLOBAL_CFG1               = 0x7e8  
AXI_CLASS_SNOOP_SPL_MCAST_MASK1_LSB = 0x378 
AXI_CLASS_SNOOP_SPL_MCAST_MASK1_MSB = 0x37C 
AXI_CLASS_SNOOP_SPL_MCAST_ADDR1_LSB = 0x368 
AXI_CLASS_SNOOP_SPL_MCAST_ADDR1_MSB = 0x36C 
AXI_CLASS_PUNT_COS                  = 0x4c0 
AXI_CLASS_NPU_CTRL                  = 0x4fc 
AXI_CLASS_NPU_CTRL1                 = 0x7f0 
AXI_CLASS_INQ_AFULL_THRES           = 0x290 
AXI_CLASS_USE_TMU_INQ               = 0x250 

kxo28_RegsOffs_CLASS = { 
                  'CLASS_TX_CTRL':                AXI_CLASS_TX_CTRL,
                  'CLASS_HDR_SIZE':               AXI_CLASS_HDR_SIZE,
                  'CLASS_TM_INQ_ADDR':            AXI_CLASS_TM_INQ_ADDR,
                  'CLASS_BMU1_BUF_FREE':          AXI_CLASS_BMU1_BUF_FREE,
                  'CLASS_BUS_ACCESS_BASE_ADDR':   AXI_CLASS_BUS_ACCESS_BASE_ADDR,
                  'CLASS_GLOBAL_CFG':             AXI_CLASS_GLOBAL_CFG,
                  'CLASS_GLOBAL_CFG1':            AXI_CLASS_GLOBAL_CFG1,
                  'CLASS_SNOOP_MCAST_MASK1_LSB':  AXI_CLASS_SNOOP_SPL_MCAST_MASK1_LSB,
                  'CLASS_SNOOP_MCAST_MASK1_MSB':  AXI_CLASS_SNOOP_SPL_MCAST_MASK1_MSB,
                  'CLASS_SNOOP_MCAST_ADDR1_LSB':  AXI_CLASS_SNOOP_SPL_MCAST_ADDR1_LSB,
                  'CLASS_SNOOP_MCAST_ADDR1_MSB':  AXI_CLASS_SNOOP_SPL_MCAST_ADDR1_MSB,
                  'CLASS_PUNT_COS':               AXI_CLASS_PUNT_COS,
                  'CLASS_NPU_CTRL':               AXI_CLASS_NPU_CTRL,
                  'CLASS_NPU_CTRL1':              AXI_CLASS_NPU_CTRL1,
                  'CLASS_INQ_AFULL_THRES':        AXI_CLASS_INQ_AFULL_THRES,
                  'CLASS_USE_TMU_INQ':            AXI_CLASS_USE_TMU_INQ,
}

kxo28_RegsAXI = kxo28_RegsBMU

'''
