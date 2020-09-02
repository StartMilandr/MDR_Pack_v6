from pyBasisRes import _VAL2FLD, _FLD2VAL
import struct
from ctypes import create_string_buffer


ItemMAC_R2_MAC_Lo16_Pos  = 0
ItemMAC_R2_MAC_Lo16_Msk  = 0xFFFF
ItemMAC_R2_AGE_Pos       = 0
ItemMAC_R2_AGE_Msk       = 0x0FFF
ItemMAC_R2_ACT_Pos       = 12
ItemMAC_R2_ACT_Msk       = 0x1000
ItemMAC_R2_PORT_Pos      = 13
ItemMAC_R2_PORT_Msk      = 0xE000

VV3_HashToAddr_Pos = 3
VV3_HashToAddr_Msk = 0x7FF8
VV3_HashInd_Mask   = 0x0007


class VV3_ItemMAC:
  packLen = 10
  def __init__(self):
    self.HashAddr = 0
    self.Hash = 0
    self.HashInd = 0
    self.MAC = '01:23:45:67:89:AB'
    self.Port = 0
    self.Age = 0
    self.IsActive = True

  def CalcHash(self):
    self.Hash = 0
    strMAC = self.MAC.split(':')
    for s in strMAC:
      self.Hash ^= int(s, 16)

  def pack(self, buff, offs):
    mac64 = int(self.MAC.translate(self.MAC.maketrans('', '', ':.- ')), 16)
    # #print('mac64_TX: ', hex(mac64) )
    REG1 = (mac64 >> 16) & 0xFFFFFFFF
    REG2 =  _VAL2FLD(mac64,     ItemMAC_R2_MAC_Lo16_Pos,  ItemMAC_R2_MAC_Lo16_Msk)
    REG3 =   _VAL2FLD(self.Age,  ItemMAC_R2_AGE_Pos,       ItemMAC_R2_AGE_Msk)   \
           | _VAL2FLD(self.Port, ItemMAC_R2_PORT_Pos,      ItemMAC_R2_PORT_Msk) \
           | ItemMAC_R2_ACT_Msk
    hashAddr = (self.Hash << VV3_HashToAddr_Pos) | (self.HashInd & VV3_HashInd_Mask)
    struct.pack_into(">LH", buff, offs, REG1, REG2)
    struct.pack_into("HH", buff, offs + 6, REG3, hashAddr)
    

  def unpack(self, buff, offs):
    #R1, R2, hashAddr = struct.unpack_from('>LLH', buff, offs)
    R1, R2 = struct.unpack_from('>LH', buff, offs)
    R3, self.HashAddr = struct.unpack_from('HH', buff, offs + 6)
    #print(hex(REG1), hex(REG2), hex(REG3), hex(REG4))
    #MAC
    mac64 = (R1 << 16) | (_FLD2VAL(R2, ItemMAC_R2_MAC_Lo16_Pos,  ItemMAC_R2_MAC_Lo16_Msk))
    self.MAC = ':'.join( ['{:02x}'.format((mac64 >> ele) & 0xff) for ele in range(0,8*6,8)][::-1] )
    #rest
    self.Age    = _FLD2VAL(R3,    ItemMAC_R2_AGE_Pos,    ItemMAC_R2_AGE_Msk)
    self.Port   = _FLD2VAL(R3,    ItemMAC_R2_PORT_Pos,   ItemMAC_R2_PORT_Msk)
    self.IsActive = (R3 & ItemMAC_R2_ACT_Msk) != 0
    self.Hash = _FLD2VAL(self.HashAddr,    VV3_HashToAddr_Pos,   VV3_HashToAddr_Msk)
    self.HashInd = self.HashAddr & VV3_HashInd_Mask


