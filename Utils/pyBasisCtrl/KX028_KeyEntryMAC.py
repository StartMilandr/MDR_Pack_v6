from pyBasisRes import _VAL2FLD, _FLD2VAL
import struct
from ctypes import create_string_buffer


#--------------  KX028_KeyMAC ---------------
ItemMAC_REG2_MAC_Hi16_Pos  = 0
ItemMAC_REG2_MAC_Hi16_Msk  = 0x0000FFFF
ItemMAC_REG2_VlanID_Pos    = 16
ItemMAC_REG2_VlanID_Msk    = 0x1FFF0000

class KX028_KeyMAC:
  def __init__(self):
    self.MAC = '01:23:45:67:89:AB'
    self.vlanID = 1

  def pack(self, buff):
    #MAC and VLAN ID
    mac64 = int(self.MAC.translate(self.MAC.maketrans('', '', ':.- ')), 16)
    #print('mac64_TX: ', hex(mac64) )
    #REG1
    REG1 = mac64 & 0xFFFFFFFF
    #REG2
    REG2 =  _VAL2FLD(mac64 >> 32,    ItemMAC_REG2_MAC_Hi16_Pos,  ItemMAC_REG2_MAC_Hi16_Msk) \
          | _VAL2FLD(self.vlanID,    ItemMAC_REG2_VlanID_Pos,    ItemMAC_REG2_VlanID_Msk)
    #PACK to Buff
    struct.pack_into("LL", buff, 0, REG1, REG2)

  def unpack(self, buff):
    REG1, REG2 = struct.unpack_from('LL', buff, 0)
    #print(hex(REG1), hex(REG2), hex(REG3), hex(REG4))
    #MAC
    mac64 = REG1 | (_FLD2VAL(REG2, ItemMAC_REG2_MAC_Hi16_Pos,  ItemMAC_REG2_MAC_Hi16_Msk) << 32)
    self.MAC = ':'.join( ['{:02x}'.format((mac64 >> ele) & 0xff) for ele in range(0,8*6,8)][::-1] )
    #rest
    self.vlanID    = _FLD2VAL(REG2,    ItemMAC_REG2_VlanID_Pos,    ItemMAC_REG2_VlanID_Msk)


#--------------  KX028_KeyEntryMAC ---------------
MAC_ENTRY_FWD_PORT_LIST_Pos   = 0
MAC_ENTRY_FWD_PORT_LIST_Msk   = 0x0000FFFF
MAC_ENTRY_TC_Pos 		          = 20
MAC_ENTRY_TC_Msk 		          = 0x00700000
MAC_ENTRY_FWD_ACT_Pos         = 23
MAC_ENTRY_FWD_ACT_Msk         = 0x03800000
MAC_ENTRY_CUT_THROUGH_Pos     = 26
MAC_ENTRY_CUT_THROUGH_Msk     = 0x04000000
MAC_ENTRY_FRESH_Pos           = 29
MAC_ENTRY_FRESH_Msk           = 0x20000000
MAC_ENTRY_STATIC_Pos          = 30
MAC_ENTRY_STATIC_Msk          = 0x40000000

class KX028_KeyEntryMAC:
  def __init__(self):
    self.key = KX028_KeyMAC()
    #entry
    self.forwPorts = 0
    self.tc = 0
    self.action = 0
    self.cutThrough = False 
    self.isFresh = False
    self.isStatic = False 


  def pack(self, buff):
    REG3 =  _VAL2FLD(self.forwPorts,   MAC_ENTRY_FWD_PORT_LIST_Pos, MAC_ENTRY_FWD_PORT_LIST_Msk) \
          | _VAL2FLD(self.tc,          MAC_ENTRY_TC_Pos,            MAC_ENTRY_TC_Msk) \
          | _VAL2FLD(self.action,      MAC_ENTRY_FWD_ACT_Pos,       MAC_ENTRY_FWD_ACT_Msk) \
          | _VAL2FLD(self.cutThrough,  MAC_ENTRY_CUT_THROUGH_Pos,   MAC_ENTRY_CUT_THROUGH_Msk) \
          | _VAL2FLD(self.isFresh,     MAC_ENTRY_FRESH_Pos,         MAC_ENTRY_FRESH_Msk) \
          | _VAL2FLD(self.isStatic,    MAC_ENTRY_STATIC_Pos,        MAC_ENTRY_STATIC_Msk) \
    #PACK to Buff
    self.key.pack(buff)
    struct.pack_into("L", buff, 8, REG3)

  def unpack(self, buff):
    self.key.unpack(buff)
    (REG3, ) = struct.unpack_from('L', buff, 8)
    print(hex(REG3))
    #REG3
    self.forwPorts   = _FLD2VAL(REG3, MAC_ENTRY_FWD_PORT_LIST_Pos,  MAC_ENTRY_FWD_PORT_LIST_Msk)
    self.tc          = _FLD2VAL(REG3, MAC_ENTRY_TC_Pos,             MAC_ENTRY_TC_Msk)
    self.action      = _FLD2VAL(REG3, MAC_ENTRY_FWD_ACT_Pos,        MAC_ENTRY_FWD_ACT_Msk)
    self.cutThrough  = _FLD2VAL(REG3, MAC_ENTRY_CUT_THROUGH_Pos,    MAC_ENTRY_CUT_THROUGH_Msk) != 0
    self.isFresh     = _FLD2VAL(REG3, MAC_ENTRY_FRESH_Pos,          MAC_ENTRY_FRESH_Msk) != 0
    self.isStatic    = _FLD2VAL(REG3, MAC_ENTRY_STATIC_Pos,         MAC_ENTRY_STATIC_Msk) != 0



#--------------  Tests ---------------
def TestKeyMAC():
    item1 = KX028_KeyMAC()
    item1.MAC = 'AB:89:67:45:23:01'
    item1.vlanID = 0x1FF

    #refItem
    item2 = KX028_KeyMAC()
    attrs = vars(item2)
    print(', '.join("%s: %s" % item for item in attrs.items()))

    # send ItemMAC
    ITEM_MAC_BUF_LEN = 8
    buff = create_string_buffer(ITEM_MAC_BUF_LEN)
    item1.pack(buff)
    print("Byte chunk: ", repr(buff.raw))
    item2.unpack(buff)

    # Check
    attrs = vars(item2)
    print(', '.join("%s: %s" % item for item in attrs.items()))
    attrs = vars(item1)
    print(', '.join("%s: %s" % item for item in attrs.items()))    


def TestKeyEntryMAC():
    item1 = KX028_KeyEntryMAC()
    item1.key.MAC = 'AB:89:67:45:23:01'
    item1.key.vlanID = 0x1FF
    item1.forwPorts = 2 
    item1.tc = 2
    item1.action = 2
    item1.cutThrough = True 
    item1.isFresh = True
    item1.isStatic = True 

    #refItem
    item2 = KX028_KeyEntryMAC()
    attrs = vars(item2.key)
    print(', '.join("%s: %s" % item for item in attrs.items()))
    attrs = vars(item2)
    print(', '.join("%s: %s" % item for item in attrs.items()))

    # send ItemMAC
    ITEM_MAC_BUF_LEN = 20
    buff = create_string_buffer(ITEM_MAC_BUF_LEN)
    item1.pack(buff)
    print("Byte chunk: ", repr(buff.raw))
    item2.unpack(buff)

    # Check
    attrs = vars(item2.key)
    print(', '.join("%s: %s" % item for item in attrs.items()))    
    attrs = vars(item2)    
    print(', '.join("%s: %s" % item for item in attrs.items()))
    attrs = vars(item1)
    print(', '.join("%s: %s" % item for item in attrs.items()))    



#TestKeyMAC()
TestKeyEntryMAC()