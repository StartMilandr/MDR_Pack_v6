from pyBasisRes import _VAL2FLD, _FLD2VAL
import struct
from ctypes import create_string_buffer


ItemMAC_REG2_MAC_Hi16_Pos  = 0
ItemMAC_REG2_MAC_Hi16_Msk  = 0x0000FFFF
ItemMAC_REG2_VlanID_Pos    = 16
ItemMAC_REG2_VlanID_Msk    = 0x1FFF0000
ItemMAC_REG2_PortListL_Pos = 29
ItemMAC_REG2_PortListL_Msk = 0xE0000000

ItemMAC_REG3_PortListH_Pos   = 0
ItemMAC_REG3_PortListH_Msk   = 0x00001FFF
ItemMAC_REG3_TC_Pos          = 17
ItemMAC_REG3_TC_Msk          = 0x000E0000
ItemMAC_REG3_Actions_Pos     = 20
ItemMAC_REG3_Actions_Msk     = 0x00700000
ItemMAC_REG3_CutThrough_Pos  = 23
ItemMAC_REG3_CutThrough_Msk  = 0x00800000
ItemMAC_REG3_IsFresh_Pos     = 26
ItemMAC_REG3_IsFresh_Msk     = 0x04000000
ItemMAC_REG3_IsStatic_Pos    = 27
ItemMAC_REG3_IsStatic_Msk    = 0x08000000
ItemMAC_REG3_IsValidREG1_Pos = 28
ItemMAC_REG3_IsValidREG1_Msk = 0x10000000
ItemMAC_REG3_IsValidREG2_Pos = 29
ItemMAC_REG3_IsValidREG2_Msk = 0x20000000
ItemMAC_REG3_IsValidREG3_Pos = 30
ItemMAC_REG3_IsValidREG3_Msk = 0x40000000
ItemMAC_REG3_IsValidREG4_Pos = 31
ItemMAC_REG3_IsValidREG4_Msk = 0x80000000

ItemMAC_REG4_IsValidREG5_Pos    = 0
ItemMAC_REG4_IsValidREG5_Msk    = 0x00000001
ItemMAC_REG4_PortNum_Pos        = 4
ItemMAC_REG4_PortNum_Msk        = 0x000000F0
ItemMAC_REG4_CollizPtr_Pos      = 8
ItemMAC_REG4_CollizPtr_Msk      = 0x00FFFF00
ItemMAC_REG4_IsValidCollPtr_Pos = 26
ItemMAC_REG4_IsValidCollPtr_Msk = 0x04000000
ItemMAC_REG4_IsActive_Pos       = 27
ItemMAC_REG4_IsActive_Msk       = 0x08000000


class KX028_ItemMAC:
  packLen = 16
  def __init__(self):
    self.MAC = '01:23:45:67:89:AB'
    self.vlanID = 1
    self.forwPorts = 7 
    self.tc = 0
    self.action = 0
    self.cutThrough = False 
    self.isFresh = False
    self.isStatic = False 
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
    #MAC and VLAN ID
    mac64 = int(self.MAC.translate(self.MAC.maketrans('', '', ':.- ')), 16)
    #print('mac64_TX: ', hex(mac64) )
    #REG1
    REG1 = mac64 & 0xFFFFFFFF
    #REG2
    REG2 =  _VAL2FLD(mac64 >> 32,    ItemMAC_REG2_MAC_Hi16_Pos,  ItemMAC_REG2_MAC_Hi16_Msk) \
          | _VAL2FLD(self.vlanID,    ItemMAC_REG2_VlanID_Pos,    ItemMAC_REG2_VlanID_Msk)   \
          | _VAL2FLD(self.forwPorts, ItemMAC_REG2_PortListL_Pos, ItemMAC_REG2_PortListL_Msk) 
    #REG3
    REG3 =  _VAL2FLD(self.forwPorts,    ItemMAC_REG3_PortListH_Pos,   ItemMAC_REG3_PortListH_Msk) \
          | _VAL2FLD(self.tc,          ItemMAC_REG3_TC_Pos,           ItemMAC_REG3_TC_Msk) \
          | _VAL2FLD(self.action,      ItemMAC_REG3_Actions_Pos,      ItemMAC_REG3_Actions_Msk) \
          | _VAL2FLD(self.cutThrough,  ItemMAC_REG3_CutThrough_Pos,   ItemMAC_REG3_CutThrough_Msk) \
          | _VAL2FLD(self.isFresh,     ItemMAC_REG3_IsFresh_Pos,      ItemMAC_REG3_IsFresh_Msk) \
          | _VAL2FLD(self.isStatic,    ItemMAC_REG3_IsStatic_Pos,     ItemMAC_REG3_IsStatic_Msk) \
          | _VAL2FLD(self.isValidREG1, ItemMAC_REG3_IsValidREG1_Pos,  ItemMAC_REG3_IsValidREG1_Msk) \
          | _VAL2FLD(self.isValidREG2, ItemMAC_REG3_IsValidREG2_Pos,  ItemMAC_REG3_IsValidREG2_Msk) \
          | _VAL2FLD(self.isValidREG3, ItemMAC_REG3_IsValidREG3_Pos,  ItemMAC_REG3_IsValidREG3_Msk) \
          | _VAL2FLD(self.isValidREG4, ItemMAC_REG3_IsValidREG4_Pos,  ItemMAC_REG3_IsValidREG4_Msk)
    #REG4
    REG4 =  _VAL2FLD(self.isValidREG5,  ItemMAC_REG4_IsValidREG5_Pos,    ItemMAC_REG4_IsValidREG5_Msk) \
          | _VAL2FLD(self.port,         ItemMAC_REG4_PortNum_Pos,        ItemMAC_REG4_PortNum_Msk) \
          | _VAL2FLD(self.collizPtr,    ItemMAC_REG4_CollizPtr_Pos,      ItemMAC_REG4_CollizPtr_Msk) \
          | _VAL2FLD(self.isValidColiz, ItemMAC_REG4_IsValidCollPtr_Pos, ItemMAC_REG4_IsValidCollPtr_Msk) \
          | _VAL2FLD(self.isActive,     ItemMAC_REG4_IsActive_Pos,       ItemMAC_REG4_IsActive_Msk)    
    #PACK to Buff
    struct.pack_into("LLLL", buff, offs, REG1, REG2, REG3, REG4)

  def unpack(self, buff, offs):
    REG1, REG2, REG3, REG4 = struct.unpack_from('LLLL', buff, offs)
    #print(hex(REG1), hex(REG2), hex(REG3), hex(REG4))
    #MAC
    mac64 = REG1 | (_FLD2VAL(REG2, ItemMAC_REG2_MAC_Hi16_Pos,  ItemMAC_REG2_MAC_Hi16_Msk) << 32)
    self.MAC = ':'.join( ['{:02x}'.format((mac64 >> ele) & 0xff) for ele in range(0,8*6,8)][::-1] )
    #rest
    self.vlanID    = _FLD2VAL(REG2,    ItemMAC_REG2_VlanID_Pos,    ItemMAC_REG2_VlanID_Msk)
    self.forwPorts = _FLD2VAL(REG2, ItemMAC_REG2_PortListL_Pos, ItemMAC_REG2_PortListL_Msk) 
    #REG3
    self.forwPorts   = _FLD2VAL(REG3, ItemMAC_REG3_PortListH_Pos,    ItemMAC_REG3_PortListH_Msk)
    self.tc          = _FLD2VAL(REG3, ItemMAC_REG3_TC_Pos,           ItemMAC_REG3_TC_Msk)
    self.action      = _FLD2VAL(REG3, ItemMAC_REG3_Actions_Pos,      ItemMAC_REG3_Actions_Msk)
    self.cutThrough  = _FLD2VAL(REG3, ItemMAC_REG3_CutThrough_Pos,   ItemMAC_REG3_CutThrough_Msk) != 0
    self.isFresh     = _FLD2VAL(REG3, ItemMAC_REG3_IsFresh_Pos,      ItemMAC_REG3_IsFresh_Msk) != 0
    self.isStatic    = _FLD2VAL(REG3, ItemMAC_REG3_IsStatic_Pos,     ItemMAC_REG3_IsStatic_Msk) != 0
    self.isValidREG1 = _FLD2VAL(REG3, ItemMAC_REG3_IsValidREG1_Pos,  ItemMAC_REG3_IsValidREG1_Msk) != 0
    self.isValidREG2 = _FLD2VAL(REG3, ItemMAC_REG3_IsValidREG2_Pos,  ItemMAC_REG3_IsValidREG2_Msk) != 0
    self.isValidREG3 = _FLD2VAL(REG3, ItemMAC_REG3_IsValidREG3_Pos,  ItemMAC_REG3_IsValidREG3_Msk) != 0
    self.isValidREG4 = _FLD2VAL(REG3, ItemMAC_REG3_IsValidREG4_Pos,  ItemMAC_REG3_IsValidREG4_Msk) != 0
    #REG4
    self.isValidREG5 = _FLD2VAL(REG4, ItemMAC_REG4_IsValidREG5_Pos,    ItemMAC_REG4_IsValidREG5_Msk) != 0
    self.port        = _FLD2VAL(REG4, ItemMAC_REG4_PortNum_Pos,        ItemMAC_REG4_PortNum_Msk)
    self.collizPtr   = _FLD2VAL(REG4, ItemMAC_REG4_CollizPtr_Pos,      ItemMAC_REG4_CollizPtr_Msk)
    self.isValidColiz= _FLD2VAL(REG4, ItemMAC_REG4_IsValidCollPtr_Pos, ItemMAC_REG4_IsValidCollPtr_Msk) != 0
    self.isActive    = _FLD2VAL(REG4, ItemMAC_REG4_IsActive_Pos,       ItemMAC_REG4_IsActive_Msk) != 0


#--------------  Test ---------------
TEST_OFFS = 0

def TestItemMAC():
    item1 = KX028_ItemMAC()
    item1.MAC = 'AB:89:67:45:23:01'
    item1.vlanID = 0x1FF
    item1.forwPorts = 2 
    item1.tc = 2
    item1.action = 2
    item1.cutThrough = True 
    item1.isFresh = True
    item1.isStatic = True 
    item1.port = 4
    item1.collizPtr = 16
    item1.isActive = False
    item1.isValidREG1 = False
    item1.isValidREG2 = False
    item1.isValidREG3 = False
    item1.isValidREG4 = False
    item1.isValidREG5 = False
    item1.isValidColiz = False

    #refItem
    item2 = KX028_ItemMAC()
    attrs = vars(item2)
    print(', '.join("%s: %s" % item for item in attrs.items()))

    # send ItemMAC
    ITEM_MAC_BUF_LEN = 16
    buff = create_string_buffer(ITEM_MAC_BUF_LEN)
    item1.pack(buff, TEST_OFFS)
    print("Byte chunk: ", repr(buff.raw))
    item2.unpack(buff, TEST_OFFS)

    # Check
    attrs = vars(item2)
    print(', '.join("%s: %s" % item for item in attrs.items()))
    attrs = vars(item1)
    print(', '.join("%s: %s" % item for item in attrs.items()))    


#TestItemMAC()