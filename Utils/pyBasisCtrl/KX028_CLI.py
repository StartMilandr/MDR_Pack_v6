import struct
from ctypes import create_string_buffer
from PyComPortTransf import ByteDataBuff, ComPortTransf
from KX028_ItemMAC import KX028_ItemMAC
from KX028_ItemVLAN import KX028_ItemVLAN
from KX028_KeyEntryMAC import KX028_KeyMAC, KX028_KeyEntryMAC
from KX028_KeyEntryVLAN import KX028_KeyVLAN, KX028_KeyEntryVLAN


#Commands
cliCMD_NONE           = 0
cliCMD_ERROR          = 1
#  User Defs
cliCMD_ReadMAC        = 2
cliCMD_UpdAddMAC      = 3
cliCMD_DelMAC         = 4
cliCMD_ClearMAC       = 5
cliCMD_ReadVLAN       = 6
cliCMD_UpdAddVLAN     = 7
cliCMD_DelVLAN        = 8
cliCMD_ClearVLAN      = 9
cliCMD_ReadStatPort   = 10
cliCMD_ReadStatClass  = 11
cliCMD_ReadAXI        = 12
cliCMD_WriteAXI       = 13

cliACK_MinLen_1       = 1

# Results
cliAck_LenError       = 0
cliAck_Ok             = 1
cliAck_TBL_AddOk      = 2
cliAck_TBL_AddFault   = 3
cliAck_TBL_UpdOk      = 4
cliAck_TBL_RdFault    = 5
cliAck_TBL_Empty      = 6
cliAck_Unknown        = 7

cliAck_Str = ['MessRx Len Error', 
              'OK',
              'Item Added',
              'Item AddFault',
              'Item Updated',
              'Read Fault ',
              'Table Empty']
cliAck_UnknownStr = 'Unknown Error'

#Buffers Size
BUF_TX_LEN = 128
BUF_RX_LEN = 1024

HDR_LEN       = 2
ACK_PARS_OFFS = 2

CFG_MAC_TABLE_ITEMS_COUNT  = 4
CFG_MAC_ITEMS_RD_ITER      = 4
CFG_VLAN_TABLE_ITEMS_COUNT = 2
CFG_VLAN_ITEMS_RD_ITER     = 4

def IsEvenNum(num):
  return (num & 1) != 1


class KX028_CLI:
  def __init__(self, comPortTransf):
    self.ComPort = comPortTransf
    self.buffTx = create_string_buffer(BUF_TX_LEN)
    self.buffRx = ByteDataBuff(BUF_RX_LEN)


  def packHeader(self, cmd, paramsLen):
    # Create Buff with desired Len
    buffLen = paramsLen + HDR_LEN
    if buffLen & 1 == 0:
      buffLen += 1
    self.buffTx = create_string_buffer(buffLen)
    # Fill Header
    txBytes = paramsLen + HDR_LEN
    b1 = txBytes & 0xFF
    b2 = cmd | ((txBytes >> 2) & 0xC0)
    struct.pack_into("BB", self.buffTx, 0, b1, b2)
    return HDR_LEN

  # def unpackHeader(self):
  #   b1, b2 = struct.unpack_from('BB', buff, 0)

  #   txBytes = paramsLen + 2
  #   b1 = txBytes & 0xFF
  #   b2 = cmd | ((txBytes >> 2) & 0xC0)
  #   struct.pack_into("BB", self.buffTx, 0, b1, b2)
  #   return 2  

  def packValidateMessLen(self):
    bufLen = len(self.buffTx)
    print('IN buffTx.len = {}'.format(len(self.buffTx)))
    if IsEvenNum(bufLen):
      struct.pack_into("B", self.buffTx, bufLen, 0)
      print('OUT buffTx.len = {}'.format(len(self.buffTx)))

  def transfer(self, cmd, minAckLen):
    #self.packValidateMessLen()
    rxCnt = self.ComPort.transfer(self.buffTx, self.buffRx)
    if rxCnt < 3:
      print('rxCnt Too Small: {}'.format(rxCnt))
      return False
    else:
      b1, b2 = struct.unpack_from('BB', self.buffRx.data, 0)
      #print('b1={}, b2={}'.format(b1, b2))
      messLen = b1 | ((b2 & 0xC0) << 2)
      rxCmd = b2 & 0x3F
      print('cmd={} , messLen={}'.format(rxCmd, messLen))
      dataLen = len(self.buffRx.data)
      if IsEvenNum(messLen):
        protocolOk = dataLen == messLen + 1
      else:
        protocolOk = dataLen == messLen 
      protocolOk = protocolOk and (rxCmd == cmd)
      #print(str(protocolOk))
      if protocolOk and (dataLen - HDR_LEN >= minAckLen):
        return True
      else:
        print('Wrong DataLength = {}'.format(dataLen))
        return False

  def checkAckStatus(self):
    (R1, ) = struct.unpack_from('B', self.buffRx.data, ACK_PARS_OFFS)
    if R1 < cliAck_Unknown:
      print(cliAck_Str[R1])
    else:
      print(cliAck_UnknownStr)        


  # --- Read Items from Tables ---
  def readItemMAC(self, hashAddr, rxItemMAC):
    offs = self.packHeader(cliCMD_ReadMAC, 2)
    struct.pack_into("H", self.buffTx, offs, hashAddr)
    resOK = self.transfer(cliCMD_ReadMAC, KX028_ItemMAC.packLen)
    if resOK:
      rxItemMAC.unpack(self.buffRx.data, offs)
    else:
      print('Fault readItemMAC')
    return resOK  

  def readItemVLAN(self, hashAddr, rxItemVLAN):
    offs = self.packHeader(cliCMD_ReadVLAN, 2)
    struct.pack_into("H", self.buffTx, offs, hashAddr)
    resOK = self.transfer(cliCMD_ReadVLAN, KX028_ItemVLAN.packLen)
    if resOK:
      rxItemVLAN.unpack(self.buffRx.data, offs)
    else:
      print('Fault readItemVLAN')
    return resOK 

  def readActiveItemsMAC(self, fromHashAddr, rdCount, itemsList):
    offs = self.packHeader(cliCMD_ReadMAC, 4)
    struct.pack_into("HH", self.buffTx, offs, fromHashAddr, rdCount)
    resOK = self.transfer(cliCMD_ReadMAC, cliACK_MinLen_1)
    rdItemsCnt = 0    
    if resOK:
      messLenRx = len(self.buffRx.data)
      if messLenRx > KX028_ItemMAC.packLen:
        while offs + KX028_ItemMAC.packLen < messLenRx:
          item = KX028_ItemMAC()
          item.unpack(self.buffRx.data, offs)
          itemsList.append(item)
          offs += KX028_ItemMAC.packLen
          rdItemsCnt += 1
      else:
        self.checkAckStatus()
    else:
      print('Fault readActiveItemsMAC')
    return rdItemsCnt 

  def readActiveItemsVLAN(self, fromHashAddr, rdCount, itemsList):
    offs = self.packHeader(cliCMD_ReadVLAN, 4)
    struct.pack_into("HH", self.buffTx, offs, fromHashAddr, rdCount)
    resOK = self.transfer(cliCMD_ReadVLAN, cliACK_MinLen_1)
    rdItemsCnt = 0
    if resOK:
      messLenRx = len(self.buffRx.data)
      if messLenRx > KX028_ItemVLAN.packLen:
        while offs  + KX028_ItemVLAN.packLen < messLenRx:
          item = KX028_ItemVLAN()
          item.unpack(self.buffRx.data, offs)
          itemsList.append(item)
          offs += KX028_ItemVLAN.packLen
          rdItemsCnt += 1
      else:
        self.checkAckStatus()
    else:
      print('Fault readActiveItemsVLAN')
    return rdItemsCnt 

  def ReadTableMAC(self):
    cntToRead = CFG_MAC_TABLE_ITEMS_COUNT
    itemsList = []
    fromHashAddr = 0
    while cntToRead > 0:
      rdCnt = self.readActiveItemsMAC(fromHashAddr, CFG_MAC_ITEMS_RD_ITER, itemsList)
      if rdCnt < CFG_MAC_ITEMS_RD_ITER:
        break
      else:
        cntToRead -= CFG_MAC_ITEMS_RD_ITER
        fromHashAddr += CFG_MAC_ITEMS_RD_ITER
    return itemsList

  def ReadTableVLAN(self):
    cntToRead = CFG_VLAN_TABLE_ITEMS_COUNT
    itemsList = []
    fromHashAddr = 0
    while cntToRead > 0:
      rdCnt = self.readActiveItemsVLAN(fromHashAddr, CFG_VLAN_ITEMS_RD_ITER, itemsList)
      if rdCnt < CFG_VLAN_ITEMS_RD_ITER:
        break
      else:
        cntToRead -= CFG_VLAN_ITEMS_RD_ITER
        fromHashAddr += CFG_VLAN_ITEMS_RD_ITER
    return itemsList  


  # --- Add Items to Tables ---
  def UpdateOrAddMAC(self, keyEntryMAC):
    offs = self.packHeader(cliCMD_UpdAddMAC, KX028_KeyEntryMAC.packLen)
    keyEntryMAC.pack(self.buffTx, offs)
    resOK = self.transfer(cliCMD_UpdAddMAC, cliACK_MinLen_1)
    if resOK:
      self.checkAckStatus()
    else:
      print('Fault UpdateOrAddMAC')
    return resOK 

  def UpdateOrAddVLAN(self, keyEntryVLAN):
    offs = self.packHeader(cliCMD_UpdAddVLAN, KX028_KeyEntryVLAN.packLen)
    keyEntryVLAN.pack(self.buffTx, offs)    
    resOK = self.transfer(cliCMD_UpdAddVLAN, 1)
    if resOK:
      self.checkAckStatus()
    else:
      print('Fault UpdateOrAddVLAN')
    return resOK 


  # --- Delete Items from Tables ---
  def DelItemMAC(self, keyMAC):
    offs = self.packHeader(cliCMD_DelMAC, KX028_KeyMAC.packLen)
    keyMAC.pack(self.buffTx, offs)
    resOK = self.transfer(cliCMD_DelMAC, cliACK_MinLen_1)
    if resOK:
      self.checkAckStatus()
    else:
      print('Fault DelItemMAC')
    return resOK 

  def DelItemVLAN(self, keyVLAN):
    offs = self.packHeader(cliCMD_DelVLAN, keyVLAN.packLen)
    keyVLAN.pack(self.buffTx, offs)
    resOK = self.transfer(cliCMD_DelVLAN, cliACK_MinLen_1)
    if resOK:
      self.checkAckStatus()
    else:
      print('Fault DelItemVLAN')
    return resOK 

  # --- Clear Tables ---
  def ClearMAC(self, options):
    offs = self.packHeader(cliCMD_ClearMAC, 4)
    struct.pack_into("L", self.buffTx, offs, options)
    # self.packValidateMessLen(offs + 4)
    resOK = self.transfer(cliCMD_ClearMAC, 1)
    if resOK:
      self.checkAckStatus()
    else:
      print('Fault ClearMAC')
    return resOK 

  def ClearVLAN(self, options):
    offs = self.packHeader(cliCMD_ClearVLAN, 4)
    struct.pack_into("L", self.buffTx, offs, options)
    resOK = self.transfer(cliCMD_ClearVLAN, 1)
    if resOK:
      self.checkAckStatus()
    else:
      print('Fault ClearVLAN')
    return resOK

  # --- AXI Registers ---
  def readAxiRegList(self, regAddrList):
    offs = self.packHeader(cliCMD_ReadAXI, len(regAddrList) * 4)
    #TODO
    # txCount = self.packValidateMessLen(offs + len(regAddrList) * 4)

  def writeAxiRegList(self, regAddrList, regDataList):
    offs = self.packHeader(cliCMD_WriteAXI, len(regAddrList) * 4 * 2)
    #TODO
    # txCount = self.packValidateMessLen(offs + len(regAddrList) * 4 * 2)


  # --- Read Statistics ---
  def readStatsEMAC(self, emac, estimLen):
    offs = self.packHeader(cliCMD_ReadStatPort, 1)
    struct.pack_into("B", self.buffTx, offs, emac)
    resOK = self.transfer(cliCMD_ReadStatPort, cliACK_MinLen_1)
    if resOK:
      if len(self.buffRx.data) > estimLen + offs:
        return (self.buffRx.data, ACK_PARS_OFFS)
      else:
        self.checkAckStatus()
    else:
      print('Fault readStatsEMAC')
    return (None, 1)
    

  def readStatClassifEMAC(self, emac, estimLen):
    offs = self.packHeader(cliCMD_ReadStatClass, 1)
    struct.pack_into("B", self.buffTx, offs, emac)
    resOK = self.transfer(cliCMD_ReadStatClass, cliACK_MinLen_1)
    if resOK:
      if len(self.buffRx.data) > estimLen + offs:
        return (self.buffRx.data, ACK_PARS_OFFS)
      else:
        self.checkAckStatus()
    else:
      print('Fault readStatClassifEMAC')
    return (None, 1)
