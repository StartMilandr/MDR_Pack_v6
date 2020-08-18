from pyBasisRes import _VAL2FLD, _FLD2VAL
import struct
from ctypes import create_string_buffer


ItemVLAN_REG1_VlanID_Pos       = 0
ItemVLAN_REG1_VlanID_Msk       = 0x00001FFF
ItemVLAN_REG1_ForwPortsLo_Pos  = 13
ItemVLAN_REG1_ForwPortsLo_Msk  = 0xFFFFE000

ItemVLAN_REG2_ForwPortsHi_Offs = 19

ItemVLAN_REG2_ForwPortsHi_Pos  = 0
ItemVLAN_REG2_ForwPortsHi_Msk  = 0x00000001
ItemVLAN_REG2_UntagPorts_Pos   = 1
ItemVLAN_REG2_UntagPorts_Msk   = 0x001FFFFE
ItemVLAN_REG2_UCastHit_Pos     = 21
ItemVLAN_REG2_UCastHit_Msk     = 0x00E00000
ItemVLAN_REG2_MCastHit_Pos     = 24
ItemVLAN_REG2_MCastHit_Msk     = 0x07000000
ItemVLAN_REG2_UCastMiss_Pos    = 27
ItemVLAN_REG2_UCastMiss_Msk    = 0x38000000
ItemVLAN_REG2_MCastMissLo_Pos  = 30
ItemVLAN_REG2_MCastMissLo_Msk  = 0xC0000000

ItemVLAN_REG2_MCastMissHi_Offs = 2

ItemVLAN_REG3_MCastMissHi_Pos  = 0
ItemVLAN_REG3_MCastMissHi_Msk  = 0x00000001
ItemVLAN_REG3_MSTP_Pos         = 1
ItemVLAN_REG3_MSTP_Msk         = 0x0000000E
ItemVLAN_REG3_IsValidREG1_Pos  = 4
ItemVLAN_REG3_IsValidREG1_Msk  = 0x00000010
ItemVLAN_REG3_IsValidREG2_Pos  = 5
ItemVLAN_REG3_IsValidREG2_Msk  = 0x00000020
ItemVLAN_REG3_IsValidREG3_Pos  = 6
ItemVLAN_REG3_IsValidREG3_Msk  = 0x00000040
ItemVLAN_REG3_IsValidREG4_Pos  = 7
ItemVLAN_REG3_IsValidREG4_Msk  = 0x00000080
ItemVLAN_REG3_IsValidREG5_Pos  = 8
ItemVLAN_REG3_IsValidREG5_Msk  = 0x00000100
ItemVLAN_REG3_PortNum_Pos      = 12
ItemVLAN_REG3_PortNum_Msk      = 0x0000F000
ItemVLAN_REG3_CollizPtr_Pos    = 16
ItemVLAN_REG3_CollizPtr_Msk    = 0xFFFF0000

ItemVLAN_REG4_IsValidCollPtr_Pos  = 2
ItemVLAN_REG4_IsValidCollPtr_Msk  = 0x00000004
ItemVLAN_REG4_IsActive_Pos        = 3
ItemVLAN_REG4_IsActive_Msk        = 0x00000008


class KX028_ItemVLAN:
  packLen = 16
  def __init__(self):    
    self.vlanID = 1
    self.forwPorts = 0 
    self.untaggedPorts = 0
    self.UCastHitAct = 0
    self.UCastMissAct = 0
    self.MCastHitAct = 0
    self.MCastMissAct = 0
    self.MSTPAct = 0
    self.port = 0
    self.collizPtr = 0
    self.isActive = True
    self.isValidREG1 = True
    self.isValidREG2 = True
    self.isValidREG3 = True
    self.isValidREG4 = True
    self.isValidREG5 = True
    self.isValidColiz = True


  def pack(self, buff, offs):
    #REG1
    REG1 =  _VAL2FLD(self.vlanID,     ItemVLAN_REG1_VlanID_Pos,      ItemVLAN_REG1_VlanID_Msk) \
          | _VAL2FLD(self.forwPorts, ItemVLAN_REG1_ForwPortsLo_Pos, ItemVLAN_REG1_ForwPortsLo_Msk)   
    #REG2
    REG2 =  _VAL2FLD(self.forwPorts >> ItemVLAN_REG2_ForwPortsHi_Offs,    ItemVLAN_REG2_ForwPortsHi_Pos,  ItemVLAN_REG2_ForwPortsHi_Msk) \
          | _VAL2FLD(self.untaggedPorts,  ItemVLAN_REG2_UntagPorts_Pos,   ItemVLAN_REG2_UntagPorts_Msk)  \
          | _VAL2FLD(self.UCastHitAct,    ItemVLAN_REG2_UCastHit_Pos,     ItemVLAN_REG2_UCastHit_Msk)   \
          | _VAL2FLD(self.MCastHitAct,    ItemVLAN_REG2_MCastHit_Pos,     ItemVLAN_REG2_MCastHit_Msk)   \
          | _VAL2FLD(self.UCastMissAct,   ItemVLAN_REG2_UCastMiss_Pos,    ItemVLAN_REG2_UCastMiss_Msk)   \
          | _VAL2FLD(self.MCastMissAct,   ItemVLAN_REG2_MCastMissLo_Pos,  ItemVLAN_REG2_MCastMissLo_Msk) 
    #REG3
    REG3 =  _VAL2FLD(self.MCastMissAct >> ItemVLAN_REG2_MCastMissHi_Offs, ItemVLAN_REG3_MCastMissHi_Pos, ItemVLAN_REG3_MCastMissHi_Msk) \
          | _VAL2FLD(self.MSTPAct,      ItemVLAN_REG3_MSTP_Pos,        ItemVLAN_REG3_MSTP_Msk) \
          | _VAL2FLD(self.isValidREG1,  ItemVLAN_REG3_IsValidREG1_Pos, ItemVLAN_REG3_IsValidREG1_Msk) \
          | _VAL2FLD(self.isValidREG2,  ItemVLAN_REG3_IsValidREG2_Pos, ItemVLAN_REG3_IsValidREG2_Msk) \
          | _VAL2FLD(self.isValidREG3,  ItemVLAN_REG3_IsValidREG3_Pos, ItemVLAN_REG3_IsValidREG3_Msk) \
          | _VAL2FLD(self.isValidREG4,  ItemVLAN_REG3_IsValidREG4_Pos, ItemVLAN_REG3_IsValidREG4_Msk) \
          | _VAL2FLD(self.isValidREG5,  ItemVLAN_REG3_IsValidREG5_Pos, ItemVLAN_REG3_IsValidREG5_Msk) \
          | _VAL2FLD(self.port,         ItemVLAN_REG3_PortNum_Pos,     ItemVLAN_REG3_PortNum_Msk) \
          | _VAL2FLD(self.collizPtr,    ItemVLAN_REG3_CollizPtr_Pos,   ItemVLAN_REG3_CollizPtr_Msk)

    #REG4
    REG4 =  _VAL2FLD(self.isValidColiz,  ItemVLAN_REG4_IsValidCollPtr_Pos,  ItemVLAN_REG4_IsValidCollPtr_Msk) \
          | _VAL2FLD(self.isActive,      ItemVLAN_REG4_IsActive_Pos,        ItemVLAN_REG4_IsActive_Msk)

    #PACK to Buff
    #print(hex(REG1), hex(REG2), hex(REG3), hex(REG4))
    struct.pack_into("LLLL", buff, offs, REG1, REG2, REG3, REG4)

  def unpack(self, buff, offs):
    REG1, REG2, REG3, REG4 = struct.unpack_from('LLLL', buff, offs)
    print(hex(REG1), hex(REG2), hex(REG3), hex(REG4))
    #REG1
    self.vlanID = _FLD2VAL(REG1,     ItemVLAN_REG1_VlanID_Pos,      ItemVLAN_REG1_VlanID_Msk) 
    self.forwPorts = _FLD2VAL(REG1,  ItemVLAN_REG1_ForwPortsLo_Pos, ItemVLAN_REG1_ForwPortsLo_Msk) \
                   | (_FLD2VAL(REG2 , ItemVLAN_REG2_ForwPortsHi_Pos,  ItemVLAN_REG2_ForwPortsHi_Msk) << ItemVLAN_REG2_ForwPortsHi_Offs)
    #REG2
    self.untaggedPorts = _FLD2VAL(REG2,  ItemVLAN_REG2_UntagPorts_Pos,   ItemVLAN_REG2_UntagPorts_Msk)
    self.UCastHitAct   = _FLD2VAL(REG2,  ItemVLAN_REG2_UCastHit_Pos,     ItemVLAN_REG2_UCastHit_Msk)
    self.MCastHitAct   = _FLD2VAL(REG2,  ItemVLAN_REG2_MCastHit_Pos,     ItemVLAN_REG2_MCastHit_Msk)
    self.UCastMissAct  = _FLD2VAL(REG2,  ItemVLAN_REG2_UCastMiss_Pos,    ItemVLAN_REG2_UCastMiss_Msk)
    self.MCastMissAct  = _FLD2VAL(REG2,  ItemVLAN_REG2_MCastMissLo_Pos,  ItemVLAN_REG2_MCastMissLo_Msk) \
                      | (_FLD2VAL(REG3 , ItemVLAN_REG3_MCastMissHi_Pos,   ItemVLAN_REG3_MCastMissHi_Msk) << ItemVLAN_REG2_MCastMissHi_Offs)
    #REG3
    self.MSTPAct     = _FLD2VAL(REG3,  ItemVLAN_REG3_MSTP_Pos,        ItemVLAN_REG3_MSTP_Msk) 
    self.isValidREG1 = _FLD2VAL(REG3,  ItemVLAN_REG3_IsValidREG1_Pos, ItemVLAN_REG3_IsValidREG1_Msk)  != 0
    self.isValidREG2 = _FLD2VAL(REG3,  ItemVLAN_REG3_IsValidREG2_Pos, ItemVLAN_REG3_IsValidREG2_Msk)  != 0
    self.isValidREG3 = _FLD2VAL(REG3,  ItemVLAN_REG3_IsValidREG3_Pos, ItemVLAN_REG3_IsValidREG3_Msk)  != 0
    self.isValidREG3 = _FLD2VAL(REG3,  ItemVLAN_REG3_IsValidREG4_Pos, ItemVLAN_REG3_IsValidREG4_Msk)  != 0
    self.isValidREG3 = _FLD2VAL(REG3,  ItemVLAN_REG3_IsValidREG5_Pos, ItemVLAN_REG3_IsValidREG5_Msk)  != 0
    self.port        = _FLD2VAL(REG3,  ItemVLAN_REG3_PortNum_Pos,     ItemVLAN_REG3_PortNum_Msk) 
    self.collizPtr   = _FLD2VAL(REG3,  ItemVLAN_REG3_CollizPtr_Pos,   ItemVLAN_REG3_CollizPtr_Msk)
    #REG4
    self.isValidColiz =  _FLD2VAL(REG4,  ItemVLAN_REG4_IsValidCollPtr_Pos,  ItemVLAN_REG4_IsValidCollPtr_Msk)  != 0
    self.isActive     =  _FLD2VAL(REG4,  ItemVLAN_REG4_IsActive_Pos,        ItemVLAN_REG4_IsActive_Msk) != 0


#--------------  Test ---------------
TEST_OFFS = 0

def TestItemVLAN():
    item1 = KX028_ItemVLAN()
    item1.vlanID = 15
    item1.forwPorts = 15 
    item1.untaggedPorts = 15
    item1.UCastHitAct = 2
    item1.UCastMissAct = 2 
    item1.MCastHitAct = 2
    item1.MCastMissAct = 2 
    item1.MSTPAct = 2
    item1.port = 2
    item1.collizPtr = 2
    item1.isActive = False
    item1.isValidREG1 = False
    item1.isValidREG2 = False
    item1.isValidREG3 = False
    item1.isValidREG4 = False
    item1.isValidREG5 = False
    item1.isValidColiz = False

    #refItem
    item2 = KX028_ItemVLAN()
    attrs = vars(item2)
    print(', '.join("%s: %s" % item for item in attrs.items()))

    # send ItemMAC
    buff = create_string_buffer(16)
    item1.pack(buff, TEST_OFFS)
    print("Byte chunk: ", repr(buff.raw))
    item2.unpack(buff, TEST_OFFS)

    # Check
    attrs = vars(item2)
    print(', '.join("%s: %s" % item for item in attrs.items()))
    attrs = vars(item1)
    print(', '.join("%s: %s" % item for item in attrs.items()))    


#TestItemVLAN()