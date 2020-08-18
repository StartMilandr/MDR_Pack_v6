from pyBasisRes import _VAL2FLD, _FLD2VAL
import struct
from ctypes import create_string_buffer


STRUC1_PORT_TPID_Pos            =  0
STRUC1_PORT_TPID_Msk            =  0x0000FFFF
STRUC1_PORT_FALLBACK_BDID_Pos   =  16
STRUC1_PORT_FALLBACK_BDID_Msk   =  0x1FFF0000
      
STRUC2_PORT_SHUTDOWN_Pos              = 0
STRUC2_PORT_AFT_Pos                   = 4
STRUC2_PORT_BLOCKSTATE_Pos            = 8
STRUC2_PORT_DEF_CFI_Pos               = 12
STRUC2_PORT_DEF_PRI_Pos               = 13
STRUC2_PORT_DEF_TC_Pos                = 16
STRUC2_PORT_TRUSTED_Pos               = 19
STRUC2_PORT_VID_PREFIX_Pos            = 20
STRUC2_PORT_UNTAG_FROM_BTABLE_Pos     = 21

STRUC2_PORT_SHUTDOWN_Msk              = 0x00000001
STRUC2_PORT_AFT_Msk                   = 0x000000F0
STRUC2_PORT_BLOCKSTATE_Msk            = 0x00000F00
STRUC2_PORT_DEF_CFI_Msk               = 0x00001000
STRUC2_PORT_DEF_PRI_Msk               = 0x0000E000
STRUC2_PORT_DEF_TC_Msk                = 0x00070000
STRUC2_PORT_TRUSTED_Msk               = 0x00080000
STRUC2_PORT_VID_PREFIX_Msk            = 0x00100000
STRUC2_PORT_UNTAG_FROM_BTABLE_Msk     = 0x00200000


class KX028_ItemPort:
  packLen = 8
  def __init__(self):
    self.shutDown = 0
    self.TPID = 0x8100
    self.Fallback = 0
    self.AFT = 0         # Acceptable frame type 0: any tagging 1: tagged only 2: untagged only
    self.Blockstate = 0  # blockstate for RSTP protocol: 0: forward,  1: blocked  2: Learnonly
    self.UntagBTable = 0 # Enabling of Untag from Btable
    #not used in GUI
    self.vidPreffix = 0  # vid prefix
    self.trusted   = 0   # indicates the port is trusted
    self.defTC    = 0    # def tc field
    self.defPRI   = 0    # Def prio field (Traffic Control)
    self.defCFI   = 0    #(Canonical frame identificator (VLAN))

  def pack(self, buff, offs):
    REG1 = _VAL2FLD(self.TPID,        STRUC1_PORT_TPID_Pos,           STRUC1_PORT_TPID_Msk) \
          | _VAL2FLD(self.Fallback,   STRUC1_PORT_FALLBACK_BDID_Pos,  STRUC1_PORT_FALLBACK_BDID_Msk)
    REG2 =  _VAL2FLD(self.shutDown,   STRUC2_PORT_SHUTDOWN_Pos,       STRUC2_PORT_SHUTDOWN_Msk) \
          | _VAL2FLD(self.AFT,        STRUC2_PORT_AFT_Pos,            STRUC2_PORT_AFT_Msk,         ) \
          | _VAL2FLD(self.Blockstate, STRUC2_PORT_BLOCKSTATE_Pos,     STRUC2_PORT_BLOCKSTATE_Msk) \
          | _VAL2FLD(self.defCFI,     STRUC2_PORT_DEF_CFI_Pos,        STRUC2_PORT_DEF_CFI_Msk) \
          | _VAL2FLD(self.defPRI,     STRUC2_PORT_DEF_PRI_Pos,        STRUC2_PORT_DEF_PRI_Msk) \
          | _VAL2FLD(self.defTC,      STRUC2_PORT_DEF_TC_Pos,         STRUC2_PORT_DEF_TC_Msk) \
          | _VAL2FLD(self.trusted,    STRUC2_PORT_TRUSTED_Pos,        STRUC2_PORT_TRUSTED_Msk) \
          | _VAL2FLD(self.vidPreffix, STRUC2_PORT_VID_PREFIX_Pos,     STRUC2_PORT_VID_PREFIX_Msk) \
          | _VAL2FLD(self.UntagBTable,STRUC2_PORT_UNTAG_FROM_BTABLE_Pos, STRUC2_PORT_UNTAG_FROM_BTABLE_Msk) 
    #PACK to Buff
    struct.pack_into("LL", buff, offs, REG1, REG2)
    return offs + self.packLen

  def unpackFromRegs(self, REG1, REG2):
    self.TPID       = _FLD2VAL(REG1, STRUC1_PORT_TPID_Pos,           STRUC1_PORT_TPID_Msk) 
    self.Fallback   = _FLD2VAL(REG1, STRUC1_PORT_FALLBACK_BDID_Pos,  STRUC1_PORT_FALLBACK_BDID_Msk)
    self.shutDown   = _FLD2VAL(REG2, STRUC2_PORT_SHUTDOWN_Pos,       STRUC2_PORT_SHUTDOWN_Msk) 
    self.AFT        = _FLD2VAL(REG2, STRUC2_PORT_AFT_Pos,            STRUC2_PORT_AFT_Msk) 
    self.Blockstate = _FLD2VAL(REG2, STRUC2_PORT_BLOCKSTATE_Pos,     STRUC2_PORT_BLOCKSTATE_Msk) 
    self.defCFI     = _FLD2VAL(REG2, STRUC2_PORT_DEF_CFI_Pos,        STRUC2_PORT_DEF_CFI_Msk) 
    self.defPRI     = _FLD2VAL(REG2, STRUC2_PORT_DEF_PRI_Pos,        STRUC2_PORT_DEF_PRI_Msk) 
    self.defTC      = _FLD2VAL(REG2, STRUC2_PORT_DEF_TC_Pos,         STRUC2_PORT_DEF_TC_Msk) 
    self.trusted    = _FLD2VAL(REG2, STRUC2_PORT_TRUSTED_Pos,        STRUC2_PORT_TRUSTED_Msk) 
    self.vidPreffix = _FLD2VAL(REG2, STRUC2_PORT_VID_PREFIX_Pos,     STRUC2_PORT_VID_PREFIX_Msk) 
    self.UntagBTable= _FLD2VAL(REG2, STRUC2_PORT_UNTAG_FROM_BTABLE_Pos, STRUC2_PORT_UNTAG_FROM_BTABLE_Msk) 

  def unpack(self, buff, offs):
    REG1, REG2 = struct.unpack_from('LL', buff, offs)
    self.unpackFromRegs(REG1, REG2)