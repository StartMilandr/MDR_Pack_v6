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

SFP_IdStr = [
    'Unknown or unspecified',
    'GBIC',
    'Module/connector soldered to motherboard',
    'SFP transceiver']

SFP_ConnectorValuesStr = [
    'Unknown or unspecified',
    'SC',
    'Fibre Channel Style 1 copper connector',
    'Fibre Channel Style 2 copper connector',
    'BNC/TNC',
    'Fibre Channel coaxial headers',
    'FiberJack',
    'LC',
    'MT-RJ',
    'MU',
    'SG',
    'Optical pigtail',

    'Reserved',
    'HSSDC II',
    'Copper Pigtail',
    'Reserved',
    'Vendor specific',
    ]

SFP_EncodeStr = [
    'Unspecified',
    '8B10B',
    '4B5B',
    'NRZ',
    'Manchester']

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

  def GetStrFromID(self, strOffs, value):
    if value in range(len(SFP_IdStr)):
      return strOffs + SFP_IdStr[value] + '\n'
    elif value in range(4, 8):  
      return None #'Reserved'
    else:  
      return strOffs + 'Vendor specific' + '\n' 

  def GetStrFromConnectorValues(self, strOffs, value):
    if value in range(len(SFP_ConnectorValuesStr)):    
      return strOffs + SFP_ConnectorValuesStr[value] + '\n'
    elif value in range(0x0C, 0x1F + 1):
      return strOffs + 'Reserved' + '\n'
    elif value == 0x20:
      return strOffs + 'HSSDC II' + '\n'
    elif value == 0x21:
      return strOffs + 'Copper Pigtail' + '\n'
    elif value in range(0x22, 0x7F + 1):
      return None #'Reserved'
    else:
      return strOffs + 'Vendor specific' + '\n'

  def GetStrFromTransiever(self, strOffs, values):
    #Reserved Standard Compliance Codes
    #0 7-0 Reserved 
    #1 7-4 Reserved 
    #SONET Compliance Codes 
    #if values[1] & (1 << 3) != 0: return 'Reserved'
    resStr = ''
    if values[1] & (1 << 2 ) != 0: 
      resStr += strOffs + 'OC 48, long reach \n'
    if values[1] & (1 << 1) != 0: 
      resStr +=  strOffs + 'OC 48, intermediate reach \n'
    if values[1] & (1 << 0) != 0: 
      resStr +=  strOffs + 'OC 48 short reach \n'
    #if values[2] & (1 << 7) != 0: return ' Reserved 
    if values[2] & (1 << 6) != 0: 
      resStr +=  strOffs + 'OC 12, single mode long reach \n'
    if values[2] & (1 << 5) != 0: 
      resStr +=  strOffs + 'OC 12, single mode inter. reach \n'
    if values[2] & (1 << 4) != 0: 
      resStr +=  strOffs + 'OC 12 multi-mode short reach \n'
    #if values[2] & (1 << 3) != 0: return ' Reserved 
    if values[2] & (1 << 2) != 0: 
      resStr +=  strOffs + 'OC 3, single mode long reach \n'
    if values[2] & (1 << 1) != 0: 
      resStr += strOffs + 'OC 3, single mode inter. reach \n'
    if values[2] & (1 << 0) != 0: 
      resStr += strOffs +  'OC 3, multi-mode short reach \n'
    #Gigabit Ethernet Compliance Codes 
    #if values[3] & (1 << 7-4 Reserved 
    if values[3] & (1 << 3) != 0: 
      resStr +=  strOffs + '1000BASE-T \n'
    if values[3] & (1 << 2) != 0: 
      resStr +=  strOffs + '1000BASE-CX \n'
    if values[3] & (1 << 1) != 0: 
      resStr +=  strOffs + '1000BASE-LX \n'
    if values[3] & (1 << 0) != 0: 
      resStr +=  strOffs + '1000BASE-SX \n'
    #Fibre Channel link length
    if values[4] & (1 << 7) != 0: 
      resStr +=  strOffs + 'very long distance (V)\n'
    if values[4] & (1 << 6) != 0: 
      resStr +=  strOffs + 'short distance (S)\n'
    if values[4] & (1 << 5) != 0: 
      resStr +=  strOffs + 'intermediate distance (I)\n'
    if values[4] & (1 << 4) != 0: 
      resStr +=  strOffs + 'long distance (L)\n'
    #Fibre Channel transmitter technology
    #if values[4] & (1 << 3-2 Reserved
    if values[4] & (1 << 1) != 0: 
      resStr += strOffs +  'Longwave laser (LC)\n'
    if values[4] & (1 << 0) != 0: 
      resStr +=  strOffs + 'Electrical inter-enclosure (EL)\n'
    if values[5] & (1 << 7) != 0: 
      resStr +=  strOffs + 'Electrical intra-enclosure (EL)\n'
    if values[5] & (1 << 6) != 0: 
      resStr +=  strOffs + 'Shortwave laser w/o OFC (SN)\n'
    if values[5] & (1 << 5) != 0: 
      resStr +=  strOffs + 'Shortwave laser w/ OFC (SL)\n'
    if values[5] & (1 << 4) != 0: 
      resStr +=  strOffs + 'Longwave laser (LL)\n'
    #if values[5] & (1 << 0-3 Reserved
    #Fibre Channel transmission media
    if values[6] & (1 << 7) != 0: 
      resStr +=  strOffs + 'Twin Axial Pair (TW)\n'
    if values[6] & (1 << 6) != 0: 
      resStr +=  strOffs + 'Shielded Twisted Pair (TP)\n'
    if values[6] & (1 << 5) != 0: 
      resStr +=  strOffs + 'Miniature Coax (MI)\n'
    if values[6] & (1 << 4) != 0: 
      resStr +=  strOffs + 'Video Coax (TV)\n'
    if values[6] & (1 << 3) != 0: 
      resStr +=  strOffs + 'Multi-mode, 62.5m (M6)\n'
    if values[6] & (1 << 2) != 0: 
      resStr +=  strOffs + 'Multi-mode, 50 m (M5)\n'
    #if values[6] & (1 << 1 Reserved
    if values[6] & (1 << 0) != 0: 
      resStr +=  strOffs + 'Single Mode (SM)\n'
    #Fibre Channel speed
    #if values[7] & (1 << 7-5 Reserved
    if values[7] & (1 << 4) != 0: 
      resStr +=  strOffs + '400 MBytes/Sec\n'
    #if values[7] & (1 << 3 Reserved
    if values[7] & (1 << 2) != 0: 
      resStr +=  strOffs + '200 MBytes./Sec\n'
    #if values[7] & (1 << 1 Reserved
    if values[7] & (1 << 0) != 0: 
      resStr +=  strOffs + '100 MBytes/Sec\n'
    return resStr  


  def GetStrFromEncoding(self, strOffs, value):
    if value in range(len(SFP_EncodeStr)):    
      return strOffs + SFP_EncodeStr[value] + '\n'
    else:
      return None #reserved  

  def GetStrFromOptions(self, strOffs, values):
    resStr = ''
    if values[1] & (1 << 1 ) != 0: 
      resStr += strOffs + 'Loss of Signal implemented \n'
    if values[1] & (1 << 2) != 0: 
      resStr += strOffs + 'Loss Signal Inverted \n'
    if values[1] & (1 << 3) != 0: 
      resStr += strOffs + 'TX_FAULT signal implemented \n'  
    if values[1] & (1 << 4) != 0: 
      resStr += strOffs + 'TX_DISABLE signal implemented \n'  
    if values[1] & (1 << 5) != 0: 
      resStr += strOffs + 'RATE_SELECT implemented \n'
    return resStr

  def GetStrFromData(self, strOffs, values):
    return strOffs + '{}:{}:20{}\n'.format(values[2], values[1], values[0])


  def unpack(self, buff, offs):
    self.infoText = ''
    strOffset = '            '
    for ids, name, length in SFP_Params:
      data = struct.unpack_from('{}B'.format(length), buff, offs)  
      #newText = '{} \n'.format(hex(data))
      hexStr = [hex(d) for d in data]
      hexStr = ' '.join(hexStr)

      name = '{0:10s}'.format(name)
      newText = '{}: {} \n'.format(name, hexStr)
      self.infoText += newText

      valStr = None
      if ids == idSfpID:
        valStr = self.GetStrFromID(strOffset, data[0])
      elif ids == idSfpCONN:
        valStr = self.GetStrFromConnectorValues(strOffset, data[0])
      elif ids == idSfpTRANS:  
        valStr = self.GetStrFromTransiever(strOffset, data)
      elif ids == idSfpENC:  
        valStr = self.GetStrFromEncoding(strOffset, data[0])
      elif ids == idSfpDATA_CODE:  
        valStr, = struct.unpack_from('{}s'.format(length), buff, offs)  
        valStrEx = valStr.decode('ascii')
        print(valStrEx)
        print(valStrEx[4:2])
        print(valStrEx[2:2])
        print(valStrEx[0:2])
        valStr = strOffset + '{}:{}:20{}'.format(valStrEx[4:6], valStrEx[2:4], valStrEx[0:2])  + '\n'
      elif ids == idSfpOPTIONS:  
        valStr = self.GetStrFromOptions(strOffset, data)  
      elif ids in (idSfpVEND_NAME, idSfpVEND_PN, idSfpVEND_REV, idSfpVEND_SN):  
        valStr, = struct.unpack_from('{}s'.format(length), buff, offs)  
        valStr = strOffset + valStr.decode('ascii') + '\n'
      # else:
      #   hexStr += '{} '.format(data[0])

      if valStr:
        self.infoText += valStr

      offs += length

  # def unpack(self, buff, offs):
  #   self.infoText = ''
  #   for ids, name, length in SFP_Params:
  #     hexStr = ''
  #     if length == 1:
  #       d, = struct.unpack_from('B', buff, offs)
  #       offs += 1
  #       hexStr += '{} '.format(hex(d))
  #     else:
  #       hexStr, = struct.unpack_from('{}s'.format(length), buff, offs)  
  #       offs += length
  #       hexStrExc = hexStr
  #       try:
  #         hexStrExc = hexStrExc.decode('ascii')
  #       except Exception:
  #         hexStrExc = hexStr

  #       hexStr = hexStrExc


  #     # for i in range(lenght):
  #     #   d, = struct.unpack_from('B', buff, offs)
  #     #   offs += 1
  #     #   hexStr += '{} '.format(hex(d))
  #     name = '{0:10s}'.format(name)
  #     print(name, hexStr)
  #     self.infoText += '{}: {} \n'.format(name, hexStr) 
