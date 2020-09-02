import struct
from ctypes import create_string_buffer
from PyComPortTransf import ByteDataBuff, ComPortTransf
from KX028_ItemMAC import KX028_ItemMAC
from KX028_ItemVLAN import KX028_ItemVLAN
from KX028_KeyEntryMAC import KX028_KeyMAC, KX028_KeyEntryMAC
from KX028_KeyEntryVLAN import KX028_KeyVLAN, KX028_KeyEntryVLAN
from KX028_ItemPort import KX028_ItemPort
from pyVV3_ItemMAC import VV3_ItemMAC
from pyBasisRes import kx028_AddrStruc1, kx028_AddrStruc2, CLASS1_BASE_ADDR


DEBUG_MODE = False

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
cliCMD_ClearStatPort  = 12
cliCMD_ClearStatClass = 13
cliCMD_WritePortCfg   = 14
cliCMD_ReadAXI        = 15
cliCMD_WriteAXI       = 16

cliCMD_VV3_ReadMAC    = 17
cliCMD_VV3_AddMAC     = 18
cliCMD_VV3_DelMAC     = 19
cliCMD_VV3_ReadRegs   = 20
cliCMD_VV3_WriteRegs  = 21

cliCMD_Str = ['cmdNone', 'cmdError', \
              'cmdReadMAC',  'cmdUpdAddMAC',  'cmdDelMAC',  'cmdClearMAC', \
              'cmdReadVLAN', 'cmdUpdAddVLAN', 'cmdDelVLAN', 'cmdClearVLAN', \
              'ReadStatPort', 'ReadStatClass', 'ClearStatPort', 'ClearStatClass', \
              'WritePortCfg', 'ReadAXI', 'WriteAXI', 
              'AddMAC_BB3', 'DelMAC_BB3', 'ReadMAC_VV3',]


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

CFG_MAC_TABLE_ITEMS_COUNT  = 4095 #8192
CFG_MAC_ITEMS_RD_ITER      = 16
CFG_VLAN_TABLE_ITEMS_COUNT = 128
CFG_VLAN_ITEMS_RD_ITER     = 4

CFG_VV3_MAC_TABLE_LEN = 0x800

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

  def transfer(self, cmd, minAckLen):
    rxCnt = self.ComPort.transfer(self.buffTx, self.buffRx)
    if rxCnt < 3:
      print('rxCnt Too Small: {}'.format(rxCnt))
      return False
    else:
      b1, b2 = struct.unpack_from('BB', self.buffRx.data, 0)
      #print('b1={}, b2={}'.format(b1, b2))
      messLen = b1 | ((b2 & 0xC0) << 2)
      rxCmd = b2 & 0x3F
      #print('cmd={} , messLen={}'.format(rxCmd, messLen))
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
    #print('RdFrom: {} Count: {}'.format(fromHashAddr, rdCount))
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


  # --- Simplest Commands with single ack (no data) ---
  def SendObjectWithAck(self, cmd, obj):
    offs = self.packHeader(cmd, obj.packLen)
    obj.pack(self.buffTx, offs)
    resOK = self.transfer(cmd, cliACK_MinLen_1)
    if resOK:
      self.checkAckStatus()
    else:
      print('Fault ' + cliCMD_Str[cmd])
    return resOK  

  def UpdateOrAddMAC(self, keyEntryMAC):
    return self.SendObjectWithAck(cliCMD_UpdAddMAC, keyEntryMAC)

  def UpdateOrAddVLAN(self, keyEntryVLAN):
    return self.SendObjectWithAck(cliCMD_UpdAddVLAN, keyEntryVLAN)

  def DelItemMAC(self, keyMAC):
    return self.SendObjectWithAck(cliCMD_DelMAC, keyMAC)  

  def DelItemVLAN(self, keyVLAN):
    return self.SendObjectWithAck(cliCMD_DelVLAN, keyVLAN)      


  # --- Commands with single param (int32) ---
  def SendCmdPar32WithAck(self, cmd, par32):
    offs = self.packHeader(cmd, 4)
    struct.pack_into("L", self.buffTx, offs, par32)
    resOK = self.transfer(cmd, cliACK_MinLen_1)
    if resOK:
      self.checkAckStatus()
    else:
      print('Fault ' + cliCMD_Str[cmd])
    return resOK 

  def ClearMAC(self, options):
    return self.SendCmdPar32WithAck(cliCMD_ClearMAC, options)

  def ClearVLAN(self, options):
    return self.SendCmdPar32WithAck(cliCMD_ClearVLAN, options)


  # --- AXI Registers ---
  def readAxiRegList(self, regAddrList):
    regCnt = len(regAddrList)
    offs = self.packHeader(cliCMD_ReadAXI, regCnt * 4)
    for Reg in regAddrList:
      struct.pack_into("L", self.buffTx, offs, Reg)
      offs += 4
    resOK = self.transfer(cliCMD_ReadAXI, cliACK_MinLen_1)
    valueList = []
    if resOK:
      if len(self.buffRx.data) == (regCnt * 4 + HDR_LEN + 1):
        offs = ACK_PARS_OFFS
        for i in range(regCnt):
          R, = struct.unpack_from('L', self.buffRx.data, offs)
          valueList.append(R)
          offs += 4
      else:
        self.checkAckStatus()
    else:
      print('Fault readAxiRegList')
    return valueList

  def writeAxiRegList(self, regAddrList, regDataList):
    regCnt = len(regAddrList)
    offs = self.packHeader(cliCMD_WriteAXI, regCnt * 8)
    for i in range(regCnt):
      struct.pack_into("LL", self.buffTx, offs, regAddrList[i], regDataList[i])
      offs += 8
    resOK = self.transfer(cliCMD_WriteAXI, cliACK_MinLen_1)
    if resOK:
      self.checkAckStatus()
    else:
      print('Fault writeAxiRegList')
    return resOK 

  # --- Read/Clear Statistics ---
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

  def SendCmdPar8WithAck(self, cmd, par8):
    offs = self.packHeader(cmd, 1)
    struct.pack_into("B", self.buffTx, offs, par8)
    resOK = self.transfer(cmd, cliACK_MinLen_1)
    if resOK:
      self.checkAckStatus()
    else:
      print('Fault ' + cliCMD_Str[cmd])
    return resOK 
  
  
  def clearStatsEMAC(self, emac):
    return self.SendCmdPar8WithAck(cliCMD_ClearStatPort, emac)

  def clearStatClassifEMAC(self, emac):
    return self.SendCmdPar8WithAck(cliCMD_ClearStatClass, emac)


  # --- EMAC Ports Control ---
  def writePortCfg(self, emac, itemPort):
    offs = self.packHeader(cliCMD_WritePortCfg, itemPort.packLen + 1)
    offs = itemPort.pack(self.buffTx, offs)
    struct.pack_into("B", self.buffTx, offs, emac)
    resOK = self.transfer(cliCMD_WritePortCfg, cliACK_MinLen_1)
    if resOK:
      self.checkAckStatus()
    else:
      print('Fault writePortCfg')
    return resOK 


  def readPortCfg(self, emac):
    if not DEBUG_MODE:
      addrs = [CLASS1_BASE_ADDR + kx028_AddrStruc1[emac], CLASS1_BASE_ADDR + kx028_AddrStruc2[emac]]
    else:
      addrs = [kx028_AddrStruc1_dbg[emac], kx028_AddrStruc1_dbg[emac]]
    values = self.readAxiRegList(addrs)
    if len(values) > 1:
      itemPort = KX028_ItemPort()
      itemPort.unpackFromRegs(values[0], values[1])
      return itemPort
    else:
      return None

  #============== VV3 ==============
  def AddMAC_VV3(self, itemMac):
    return self.SendObjectWithAck(cliCMD_VV3_AddMAC, itemMac)

  def readActiveItemsMAC_VV3(self, fromHashAddr, rdCount, itemsList):
    #print('RdFrom: {} Count: {}'.format(fromHashAddr, rdCount))
    offs = self.packHeader(cliCMD_VV3_ReadMAC, 4)
    struct.pack_into("HH", self.buffTx, offs, fromHashAddr, rdCount)
    resOK = self.transfer(cliCMD_VV3_ReadMAC, cliACK_MinLen_1)
    rdItemsCnt = 0    
    if resOK:
      messLenRx = len(self.buffRx.data)
      if messLenRx > VV3_ItemMAC.packLen:
        while offs + VV3_ItemMAC.packLen < messLenRx:
          item = VV3_ItemMAC()
          item.unpack(self.buffRx.data, offs)
          itemsList.append(item)
          offs += VV3_ItemMAC.packLen
          rdItemsCnt += 1
      else:
        self.checkAckStatus()
    else:
      print('Fault readActiveItemsMAC_VV3')
    return rdItemsCnt

  def ReadTableMAC_VV3(self):
    cntToRead = CFG_VV3_MAC_TABLE_LEN
    itemsList = []
    fromHashAddr = 0
    while cntToRead > 0:
      rdCnt = self.readActiveItemsMAC_VV3(fromHashAddr, CFG_MAC_ITEMS_RD_ITER, itemsList)
      if rdCnt < CFG_MAC_ITEMS_RD_ITER:
        break
      else:
        cntToRead -= CFG_MAC_ITEMS_RD_ITER
        fromHashAddr += CFG_MAC_ITEMS_RD_ITER
    return itemsList

  def DelItemMAC_VV3(self, hashAddr):
    offs = self.packHeader(cliCMD_VV3_DelMAC, 2)
    struct.pack_into("H", self.buffTx, offs, hashAddr)
    resOK = self.transfer(cliCMD_VV3_DelMAC, cliACK_MinLen_1)
    if resOK:
      self.checkAckStatus()
    else:
      print('Fault ' + cliCMD_Str[cliCMD_VV3_DelMAC])
    return resOK  

  def ReadRegList_VV3(self, regAddrList):
    regCnt = len(regAddrList)
    offs = self.packHeader(cliCMD_VV3_ReadRegs, regCnt)
    for Reg in regAddrList:
      struct.pack_into("B", self.buffTx, offs, Reg)
      offs += 1
    resOK = self.transfer(cliCMD_VV3_ReadRegs, cliACK_MinLen_1)
    valueList = []
    if resOK:
      if len(self.buffRx.data) >= (regCnt + HDR_LEN):
        offs = ACK_PARS_OFFS
        for i in range(regCnt):
          R, = struct.unpack_from('B', self.buffRx.data, offs)
          valueList.append(R)
          offs += 1
      else:
        self.checkAckStatus()
    else:
      print('Fault readRegList_VV3')
    return valueList

  def WriteRegList_VV3(self, regAddrList, regDataList):
    regCnt = len(regAddrList)
    offs = self.packHeader(cliCMD_VV3_WriteRegs, regCnt * 2)
    for i in range(regCnt):
      struct.pack_into("BB", self.buffTx, offs, regAddrList[i], regDataList[i])
      offs += 2
    resOK = self.transfer(cliCMD_VV3_WriteRegs, cliACK_MinLen_1)
    if resOK:
      self.checkAckStatus()
    else:
      print('Fault writeRegList_VV3')
    return resOK     