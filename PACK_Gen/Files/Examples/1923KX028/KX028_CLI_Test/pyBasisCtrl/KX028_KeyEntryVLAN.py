from pyBasisRes import _VAL2FLD, _FLD2VAL
import struct
from ctypes import create_string_buffer


#--------------  KX028_KeyVLAN ---------------
ItemVLAN_REG1_VlanID_Msk = 0x1FFF

class KX028_KeyVLAN:
  packLen = 2
  def __init__(self):
    self.vlanID = 1

  def pack(self, buff, offs):
    REG1 = self.vlanID & ItemVLAN_REG1_VlanID_Msk
    struct.pack_into("H", buff, offs, REG1)

  def unpack(self, buff, offs):
    (REG1, ) = struct.unpack_from('H', buff, offs)
    self.vlanID = REG1 & ItemVLAN_REG1_VlanID_Msk


#--------------  KX028_KeyEntryVLAN ---------------
EntryVLAN_REG1_ForwPorts_Pos     = 0
EntryVLAN_REG1_ForwPorts_Msk     = 0x000FFFFF
EntryVLAN_REG1_UntagPortsLo_Pos  = 20
EntryVLAN_REG1_UntagPortsLo_Msk  = 0xFFF00000

EntryVLAN_REG2_UntagPortsHi_Offs   = 12

EntryVLAN_REG2_UntagPortsHi_Pos  = 0
EntryVLAN_REG2_UntagPortsHi_Msk  = 0x000000FF
EntryVLAN_REG2_UCastHit_Pos      = 8
EntryVLAN_REG2_UCastHit_Msk      = 0x00000700
EntryVLAN_REG2_MCastHit_Pos      = 11
EntryVLAN_REG2_MCastHit_Msk      = 0x07003E00
EntryVLAN_REG2_UCastMiss_Pos     = 14
EntryVLAN_REG2_UCastMiss_Msk     = 0x3801C000
EntryVLAN_REG2_MCastMiss_Pos     = 17
EntryVLAN_REG2_MCastMiss_Msk     = 0xC00E0000
EntryVLAN_REG2_MSTP_Pos          = 20
EntryVLAN_REG2_MSTP_Msk          = 0x0070000E

class KX028_KeyEntryVLAN:
  packLen = 10
  def __init__(self):
    self.key = KX028_KeyVLAN()
    #entry
    self.forwPorts = 0 
    self.untaggedPorts = 0
    self.UCastHitAct = 0
    self.UCastMissAct = 0
    self.MCastHitAct = 0
    self.MCastMissAct = 0
    self.MSTPAct = 0

  def pack(self, buff, offs):
    R0 = self.key.vlanID & ItemVLAN_REG1_VlanID_Msk
    R1 =  _VAL2FLD(self.forwPorts,      EntryVLAN_REG1_ForwPorts_Pos,    EntryVLAN_REG1_ForwPorts_Msk)   \
        | _VAL2FLD(self.untaggedPorts,  EntryVLAN_REG1_UntagPortsLo_Pos, EntryVLAN_REG1_UntagPortsLo_Msk)
    R2 =  _VAL2FLD(self.untaggedPorts >> EntryVLAN_REG2_UntagPortsHi_Offs,    EntryVLAN_REG2_UntagPortsHi_Pos,  EntryVLAN_REG2_UntagPortsHi_Msk) \
        | _VAL2FLD(self.UCastHitAct,    EntryVLAN_REG2_UCastHit_Pos,     EntryVLAN_REG2_UCastHit_Msk)   \
        | _VAL2FLD(self.MCastHitAct,    EntryVLAN_REG2_MCastHit_Pos,     EntryVLAN_REG2_MCastHit_Msk)   \
        | _VAL2FLD(self.UCastMissAct,   EntryVLAN_REG2_UCastMiss_Pos,    EntryVLAN_REG2_UCastMiss_Msk)   \
        | _VAL2FLD(self.MCastMissAct,   EntryVLAN_REG2_MCastMiss_Pos,    EntryVLAN_REG2_MCastMiss_Msk)  \
        | _VAL2FLD(self.MSTPAct,        EntryVLAN_REG2_MSTP_Pos,         EntryVLAN_REG2_MSTP_Msk)
    #struct.pack_into("HLL", buff, offs, R0, R1, R2)
    self.key.pack(buff, offs)
    struct.pack_into("LL", buff, offs + KX028_KeyVLAN.packLen, R1, R2)

  def unpack(self, buff, offs):
    #REG0, REG1, REG2 = struct.unpack_from('HLL', buff, offs)
    self.key.unpack(buff, offs)
    REG1, REG2 = struct.unpack_from('LL', buff, offs + KX028_KeyVLAN.packLen)

    #self.key.vlanID = REG0 & ItemVLAN_REG1_VlanID_Msk
    self.forwPorts = _FLD2VAL(REG1,  EntryVLAN_REG1_ForwPorts_Pos, EntryVLAN_REG1_ForwPorts_Msk)
    self.untaggedPorts = _FLD2VAL(REG1,  EntryVLAN_REG1_UntagPortsLo_Pos, EntryVLAN_REG1_UntagPortsLo_Msk) \
                      | (_FLD2VAL(REG2 , EntryVLAN_REG2_UntagPortsHi_Pos, EntryVLAN_REG2_UntagPortsHi_Msk) << EntryVLAN_REG2_UntagPortsHi_Offs)
    self.UCastHitAct   = _FLD2VAL(REG2,  EntryVLAN_REG2_UCastHit_Pos,     EntryVLAN_REG2_UCastHit_Msk)
    self.MCastHitAct   = _FLD2VAL(REG2,  EntryVLAN_REG2_MCastHit_Pos,     EntryVLAN_REG2_MCastHit_Msk)
    self.UCastMissAct  = _FLD2VAL(REG2,  EntryVLAN_REG2_UCastMiss_Pos,    EntryVLAN_REG2_UCastMiss_Msk)
    self.MCastMissAct  = _FLD2VAL(REG2,  EntryVLAN_REG2_MCastMiss_Pos,    EntryVLAN_REG2_MCastMiss_Msk) 
    self.MSTPAct       = _FLD2VAL(REG2,  EntryVLAN_REG2_MSTP_Pos,         EntryVLAN_REG2_MSTP_Msk) 



#--------------  Tests ---------------
TEST_OFFS = 0

def TestKeyVLAN():
    print('TestKeyVLAN:')
    item1 = KX028_KeyVLAN()    
    item1.vlanID = 0x1FF
    
    #refItem
    item2 = KX028_KeyVLAN()
    attrs = vars(item2)
    print(', '.join("%s: %s" % item for item in attrs.items()))

    # send ItemMAC
    ITEM_MAC_BUF_LEN = 20
    buff = create_string_buffer(ITEM_MAC_BUF_LEN)
    item1.pack(buff, TEST_OFFS)
    print("Byte chunk: ", repr(buff.raw))
    item2.unpack(buff, TEST_OFFS)

    # Check
    attrs = vars(item2)    
    print(', '.join("%s: %s" % item for item in attrs.items()))
    attrs = vars(item1)
    print(', '.join("%s: %s" % item for item in attrs.items()))   


def TestKeyEntryVLAN():
    print('TestKeyEntryVLAN:')
    item1 = KX028_KeyEntryVLAN()    
    item1.key.vlanID = 0x1FF
    item1.forwPorts = 15 
    item1.untaggedPorts = 15
    item1.UCastHitAct = 3
    item1.UCastMissAct = 3
    item1.MCastHitAct = 3
    item1.MCastMissAct = 3
    item1.MSTPAct = 3

    #refItem
    item2 = KX028_KeyEntryVLAN()
    attrs = vars(item2.key)
    print(', '.join("%s: %s" % item for item in attrs.items()))
    attrs = vars(item2)
    print(', '.join("%s: %s" % item for item in attrs.items()))

    # send ItemMAC
    ITEM_MAC_BUF_LEN = 20
    buff = create_string_buffer(ITEM_MAC_BUF_LEN)
    item1.pack(buff, TEST_OFFS)
    print("Byte chunk: ", repr(buff.raw))
    item2.unpack(buff, TEST_OFFS)

    # Check
    attrs = vars(item2.key)
    print(', '.join("%s: %s" % item for item in attrs.items()))    
    attrs = vars(item2)    
    print(', '.join("%s: %s" % item for item in attrs.items()))
    attrs = vars(item1)
    print(', '.join("%s: %s" % item for item in attrs.items()))    



#TestKeyVLAN()
#TestKeyEntryVLAN()    