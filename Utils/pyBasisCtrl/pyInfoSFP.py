from pyBasisRes import _VAL2FLD, _FLD2VAL
import struct
from ctypes import create_string_buffer


class StatusSPF:
  packLen = 20
  def __init__(self):
    self.maskPresence = 0
    self.maskEvents = 0
    self.maskIsCooper = 0
    self.maskIsMarvell = 0
    self.maskIsMarvellOk = 0

  def unpack(self, buff, offs):
    self.maskPresence, self.maskEvents, self.maskIsCooper, self.maskIsMarvell, self.maskIsMarvellOk = struct.unpack_from('LLLLL', buff, offs)


SFP_LEN_ID            = 1
SFP_LEN_IDEX          = 1
SFP_LEN_CONNECTOR     = 1
SFP_LEN_TANSCEIVER    = 8
SFP_LEN_ENCODING      = 1
SFP_LEN_BITRATE       = 1
SFP_LEN_RESERVED_1    = 1
SFP_LEN_LEN9KM        = 1
SFP_LEN_LEN9M         = 1
SFP_LEN_LEN50M        = 1
SFP_LEN_LEN62P5M      = 1
SFP_LEN_COPPER        = 1
SFP_LEN_RESERVED_2    = 1
SFP_LEN_VENDOR_NAME   = 16
SFP_LEN_RESERVED_3    = 1
SFP_LEN_VENDOR_OUI    = 3
SFP_LEN_VENDOR_PN     = 16
SFP_LEN_VENDOR_REV    = 4
SFP_LEN_RESERVED_4    = 3
SFP_LEN_CC_BASE       = 1
SFP_LEN_OPTIONS       = 2
SFP_LEN_BITRATE_MAX   = 1
SFP_LEN_BITRATE_MIN   = 1
SFP_LEN_VENDOR_SN     = 16
SFP_LEN_DATA_CODE     = 8
SFP_LEN_RESERVED_5    = 3
SFP_LEN_CC_EXT        = 1


idSfpID         = 0   
idSfpIDex       = 1
idSfpCONN       = 2
idSfpTRANS      = 3
idSfpENC        = 4
idSfpBITRATE    = 5
idSfpRES_1      = 6
idSfpLEN9KM     = 7
idSfpLEN9M      = 8
idSfpLEN50M     = 9
idSfpLEN62M5    = 10
idSfpCOPPER     = 11 
idSfpRES_2      = 12 
idSfpVEND_NAME  = 13
idSfpRES_3      = 14 
idSfpVEND_OUI   = 15
idSfpVEND_PN    = 16
idSfpVEND_REV   = 17
idSfpRES_4      = 18  
idSfpCC_BASE    = 19
idSfpOPTIONS    = 20
idSfpBR_MAX     = 21 
idSfpBR_MIN     = 22
idSfpVEND_SN    = 23
idSfpDATA_CODE  = 24
idSfpRES_5      = 25  
idSfpCC_EXT     = 26  

SFP_Params = [
      (idSfpID,        "ID",        SFP_LEN_ID),   
      (idSfpIDex,      "IDex",      SFP_LEN_IDEX),   
      (idSfpCONN,      "CONN",      SFP_LEN_CONNECTOR),   
      (idSfpTRANS,     "TRANS",     SFP_LEN_TANSCEIVER),  
      (idSfpENC,       "ENC",       SFP_LEN_ENCODING), 
      (idSfpBITRATE,   "BITRATE",   SFP_LEN_BITRATE), 
      (idSfpRES_1,     "RES_1",     SFP_LEN_RESERVED_1), 
      (idSfpLEN9KM,    "LEN9KM",    SFP_LEN_LEN9KM), 
      (idSfpLEN9M,     "LEN9M",     SFP_LEN_LEN9M), 
      (idSfpLEN50M,    "LEN50M",    SFP_LEN_LEN50M), 
      (idSfpLEN62M5,   "LEN62,5M",  SFP_LEN_LEN62P5M), 
      (idSfpCOPPER,    "COPPER",    SFP_LEN_COPPER), 
      (idSfpRES_2,     "RES_2",     SFP_LEN_RESERVED_2), 
      (idSfpVEND_NAME, "VEND_NAME", SFP_LEN_VENDOR_NAME), 
      (idSfpRES_3,     "RES_3",     SFP_LEN_RESERVED_3), 
      (idSfpVEND_OUI,  "VEND_OUI",  SFP_LEN_VENDOR_OUI), 
      (idSfpVEND_PN,   "VEND_PN",   SFP_LEN_VENDOR_PN), 
      (idSfpVEND_REV,  "VEND_REV",  SFP_LEN_VENDOR_REV), 
      (idSfpRES_4,     "RES_4",     SFP_LEN_RESERVED_4), 
      (idSfpCC_BASE,   "CC_BASE",   SFP_LEN_CC_BASE), 
      (idSfpOPTIONS,   "OPTIONS",   SFP_LEN_OPTIONS), 
      (idSfpBR_MAX,    "BR_MAX",    SFP_LEN_BITRATE_MAX), 
      (idSfpBR_MIN,    "BR_MIN",    SFP_LEN_BITRATE_MIN), 
      (idSfpVEND_SN,   "VEND_SN",   SFP_LEN_VENDOR_SN), 
      (idSfpDATA_CODE, "DATA_CODE", SFP_LEN_DATA_CODE), 
      (idSfpRES_5,     "RES_5",     SFP_LEN_RESERVED_5), 
      (idSfpCC_EXT,    "CC_EXT",    SFP_LEN_CC_EXT), 
    ]

class InfoSPF:  
  def __init__(self):
    self.maskPresence = 0
    self.maskEvents = 0
    self.maskIsCooper = 0
    self.maskIsMarvell = 0
    self.maskIsMarvellOk = 0
    self.packLen = 0
    self.infoText = ''
    for ids, name, lenght in SFP_Params:
      self.packLen += lenght    

  def unpack(self, buff, offs):
    self.infoText = ''
    for ids, name, lenght in SFP_Params:
      hexStr = ''
      for i in range(lenght):
        d, = struct.unpack_from('B', buff, offs)
        offs += 1
        hexStr += '{} '.format(hex(d))
        
      self.infoText += '{}({}) \n'.format(name, hexStr) 
