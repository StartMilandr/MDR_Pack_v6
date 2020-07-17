from PySide2 import QtGui
import struct
from KX028_CLI import KX028_CLI

idTx_OK         = 0
idTx_Broadcast  = 1
idTx_Multicast  = 2
idTx_Pause      = 3
idTx_LenTo64    = 4
idTx_LenTo127   = 5
idTx_LenTo255   = 6
idTx_LenTo511   = 7
idTx_LenTo1023  = 8
idTx_LenTo1517  = 9
idTx_LenOv1518  = 10
idTx_Underruns   = 11
idTx_SingleColls = 12
idTx_Le15Colls   = 13
idTx_Gt15Colls   = 14
idTx_LateColls   = 15
idTx_Deffered    = 16

idRx_OK         = 17
idRx_Broadcast  = 18
idRx_Multicast  = 19
idRx_Pause      = 20
idRx_LenTo64    = 21
idRx_LenTo127   = 22
idRx_LenTo255   = 23
idRx_LenTo511   = 24
idRx_LenTo1023  = 25
idRx_LenTo1517  = 26
idRx_LenOv1518  = 27
idRx_LenLT64    = 28
idRX_ExcLen     = 29
idRX_Jubbers    = 30
idRX_FCSErrs    = 31
idRX_LenErrs    = 32
idRX_SymErrs    = 33
idRX_ResErrs    = 34
idRX_AlignErrs  = 35
idRX_OverErrs   = 36
idRX_IpCrcErrs  = 37
idRX_TcpCrcErrs = 38
idRX_UdpCrcErrs = 39
idRX_Dropped    = 40

idTx_Bytes      = 41
idRx_Bytes      = 42

EMAC_STAT_COUNT    = idRx_Bytes + 1
EMAC_STAT_CNTR_LEN = 8
EMAC_STAT_LEN      = EMAC_STAT_COUNT * EMAC_STAT_CNTR_LEN

idCL_RX          = 43
idCL_L3_Fails    = 44
idCL_IPV4        = 45
idCL_IPV6        = 46
idCL_CRC_Errs    = 47
idCL_TLL_Errs    = 48
idCL_ICMP        = 49
idCL_IGMP        = 50
idCL_TCP         = 51
idCL_UDP         = 52

idCL_LOW  = idCL_RX
idCL_HIGH = idCL_UDP
CLASS_STAT_LEN = idCL_HIGH - idCL_LOW + 1

class KX028_PortStatsModel:
  def __init__(self):
    self.model = QtGui.QStandardItemModel()
    self.model.setHorizontalHeaderLabels(['Params', 'Values'])
    self.rootItem = self.model.invisibleRootItem()
    self.comCLI = None
    
    # Create ItemsList
    self.itemsList = {  \
      # RX
      idRx_Bytes:     [QtGui.QStandardItem('Bytes'),                    QtGui.QStandardItem('0') ], \
      idRx_OK:        [QtGui.QStandardItem('OK'),                       QtGui.QStandardItem('0') ], \
      idRx_Broadcast: [QtGui.QStandardItem('Broadcast'),                QtGui.QStandardItem('0') ], \
      idRx_Multicast: [QtGui.QStandardItem('Multicast'),                QtGui.QStandardItem('0') ], \
      idRx_Pause:     [QtGui.QStandardItem('Pause'),                    QtGui.QStandardItem('0') ], \
      idRx_LenTo64:   [QtGui.QStandardItem('64 bytes packets'),         QtGui.QStandardItem('0') ], \
      idRx_LenTo127:  [QtGui.QStandardItem('65..127 bytes packets'),    QtGui.QStandardItem('0') ], \
      idRx_LenTo255:  [QtGui.QStandardItem('128..255 bytes packets'),   QtGui.QStandardItem('0') ], \
      idRx_LenTo511:  [QtGui.QStandardItem('256..511 bytes packets'),   QtGui.QStandardItem('0') ], \
      idRx_LenTo1023: [QtGui.QStandardItem('512..1023 bytes packets'),  QtGui.QStandardItem('0') ], \
      idRx_LenTo1517: [QtGui.QStandardItem('1024..1516 bytes packets'), QtGui.QStandardItem('0') ], \
      idRx_LenOv1518: [QtGui.QStandardItem('>1518 bytes packets'),      QtGui.QStandardItem('0') ], \
      idRx_LenLT64:   [QtGui.QStandardItem('<64 bytes packets'),        QtGui.QStandardItem('0') ], \
      #RX_Err
      idRX_ExcLen:     [QtGui.QStandardItem('Excessive Length'), QtGui.QStandardItem('0') ], \
      idRX_Jubbers:    [QtGui.QStandardItem('Jubbers'),          QtGui.QStandardItem('0') ], \
      idRX_FCSErrs:    [QtGui.QStandardItem('FCS Errors'),       QtGui.QStandardItem('0') ], \
      idRX_LenErrs:    [QtGui.QStandardItem('Len Erorrs'),       QtGui.QStandardItem('0') ], \
      idRX_SymErrs:    [QtGui.QStandardItem('Symbol Errors'),    QtGui.QStandardItem('0') ], \
      idRX_AlignErrs:  [QtGui.QStandardItem('Aligment Errors'),  QtGui.QStandardItem('0') ], \
      idRX_ResErrs:    [QtGui.QStandardItem('Resource Errors'),  QtGui.QStandardItem('0') ], \
      idRX_OverErrs:   [QtGui.QStandardItem('Overruns'),         QtGui.QStandardItem('0') ], \
      idRX_IpCrcErrs:  [QtGui.QStandardItem('IP CRC Errors'),    QtGui.QStandardItem('0') ], \
      idRX_TcpCrcErrs: [QtGui.QStandardItem('TCP CRC Errors'),   QtGui.QStandardItem('0') ], \
      idRX_UdpCrcErrs: [QtGui.QStandardItem('UDP CRC Errors'),   QtGui.QStandardItem('0') ], \
      idRX_Dropped:    [QtGui.QStandardItem('UDropped'),         QtGui.QStandardItem('0') ], \
      # TX
      idTx_Bytes:     [QtGui.QStandardItem('Bytes'),                    QtGui.QStandardItem('0') ], \
      idTx_OK:        [QtGui.QStandardItem('OK'),                       QtGui.QStandardItem('0') ], \
      idTx_Broadcast: [QtGui.QStandardItem('Broadcast'),                QtGui.QStandardItem('0') ], \
      idTx_Multicast: [QtGui.QStandardItem('Multicast'),                QtGui.QStandardItem('0') ], \
      idTx_Pause:     [QtGui.QStandardItem('Pause'),                    QtGui.QStandardItem('0') ], \
      idTx_LenTo64:   [QtGui.QStandardItem('64 bytes packets'),         QtGui.QStandardItem('0') ], \
      idTx_LenTo127:  [QtGui.QStandardItem('65..127 bytes packets'),    QtGui.QStandardItem('0') ], \
      idTx_LenTo255:  [QtGui.QStandardItem('128..255 bytes packets'),   QtGui.QStandardItem('0') ], \
      idTx_LenTo511:  [QtGui.QStandardItem('256..511 bytes packets'),   QtGui.QStandardItem('0') ], \
      idTx_LenTo1023: [QtGui.QStandardItem('512..1023 bytes packets'),  QtGui.QStandardItem('0') ], \
      idTx_LenTo1517: [QtGui.QStandardItem('1024..1516 bytes packets'), QtGui.QStandardItem('0') ], \
      idTx_LenOv1518: [QtGui.QStandardItem('>1518 bytes packets'),      QtGui.QStandardItem('0') ], \
      # TX_Err
      idTx_Underruns:   [QtGui.QStandardItem('Underruns'),         QtGui.QStandardItem('0') ], \
      idTx_SingleColls: [QtGui.QStandardItem('Single Collisions'), QtGui.QStandardItem('0') ], \
      idTx_Le15Colls:   [QtGui.QStandardItem('2-15 Collisions'),   QtGui.QStandardItem('0') ], \
      idTx_Gt15Colls:   [QtGui.QStandardItem('>15 Collisions'),    QtGui.QStandardItem('0') ], \
      idTx_LateColls:   [QtGui.QStandardItem('Late Collisions'),   QtGui.QStandardItem('0') ], \
      idTx_Deffered:    [QtGui.QStandardItem('Deffered'),          QtGui.QStandardItem('0') ], \
      #Clissifier
      idCL_RX:       [QtGui.QStandardItem('Received'),      QtGui.QStandardItem('0') ], \
      idCL_L3_Fails: [QtGui.QStandardItem('L3 Faults'),     QtGui.QStandardItem('0') ], \
      idCL_IPV4:     [QtGui.QStandardItem('IPV4 packets'),  QtGui.QStandardItem('0') ], \
      idCL_IPV6:     [QtGui.QStandardItem('IPV6 packets'),  QtGui.QStandardItem('0') ], \
      idCL_CRC_Errs: [QtGui.QStandardItem('CRC Errors'),    QtGui.QStandardItem('0') ], \
      idCL_TLL_Errs: [QtGui.QStandardItem('TLL Errors'),    QtGui.QStandardItem('0') ], \
      idCL_ICMP:     [QtGui.QStandardItem('ICMP packets'),  QtGui.QStandardItem('0') ], \
      idCL_IGMP:     [QtGui.QStandardItem('IGMP packets'),  QtGui.QStandardItem('0') ], \
      idCL_TCP:      [QtGui.QStandardItem('TCP packets'),   QtGui.QStandardItem('0') ], \
      idCL_UDP:      [QtGui.QStandardItem('UDP packets'),   QtGui.QStandardItem('0') ], 
        } 

    # Create TreeNodes
    #RX
    itemRX = [QtGui.QStandardItem('EMAC_RX'), QtGui.QStandardItem('Frame Type Counters')]
    self.rootItem.appendRow(itemRX)
    itemRX[0].appendRow(self.itemsList[idRx_Bytes])
    itemRX[0].appendRow(self.itemsList[idRx_OK])
    itemRX[0].appendRow(self.itemsList[idRx_Broadcast])
    itemRX[0].appendRow(self.itemsList[idRx_Multicast])
    itemRX[0].appendRow(self.itemsList[idRx_Pause])
    itemRX[0].appendRow(self.itemsList[idRx_LenTo64])
    itemRX[0].appendRow(self.itemsList[idRx_LenTo127])
    itemRX[0].appendRow(self.itemsList[idRx_LenTo255])
    itemRX[0].appendRow(self.itemsList[idRx_LenTo511])
    itemRX[0].appendRow(self.itemsList[idRx_LenTo1023])
    itemRX[0].appendRow(self.itemsList[idRx_LenTo1517])
    itemRX[0].appendRow(self.itemsList[idRx_LenOv1518])
    itemRX[0].appendRow(self.itemsList[idRx_LenLT64])
    #TX
    itemTX = [QtGui.QStandardItem('EMAC_TX'), QtGui.QStandardItem('Frame Type Counters')]
    self.rootItem.appendRow(itemTX)
    itemTX[0].appendRow(self.itemsList[idTx_Bytes])
    itemTX[0].appendRow(self.itemsList[idTx_OK])
    itemTX[0].appendRow(self.itemsList[idTx_Broadcast])
    itemTX[0].appendRow(self.itemsList[idTx_Multicast])
    itemTX[0].appendRow(self.itemsList[idTx_Pause])
    itemTX[0].appendRow(self.itemsList[idTx_LenTo64])
    itemTX[0].appendRow(self.itemsList[idTx_LenTo127])
    itemTX[0].appendRow(self.itemsList[idTx_LenTo255])
    itemTX[0].appendRow(self.itemsList[idTx_LenTo511])
    itemTX[0].appendRow(self.itemsList[idTx_LenTo1023])
    itemTX[0].appendRow(self.itemsList[idTx_LenTo1517])
    itemTX[0].appendRow(self.itemsList[idTx_LenOv1518])
    #RX_Errors
    itemErrRX = [QtGui.QStandardItem('RX_Errors'), QtGui.QStandardItem('Error Counters')]
    self.rootItem.appendRow(itemErrRX)
    itemErrRX[0].appendRow(self.itemsList[idRX_ExcLen])
    itemErrRX[0].appendRow(self.itemsList[idRX_Jubbers])
    itemErrRX[0].appendRow(self.itemsList[idRX_FCSErrs])
    itemErrRX[0].appendRow(self.itemsList[idRX_LenErrs])
    itemErrRX[0].appendRow(self.itemsList[idRX_SymErrs])
    itemErrRX[0].appendRow(self.itemsList[idRX_ResErrs])
    itemErrRX[0].appendRow(self.itemsList[idRX_AlignErrs])
    itemErrRX[0].appendRow(self.itemsList[idRX_OverErrs])
    itemErrRX[0].appendRow(self.itemsList[idRX_IpCrcErrs])
    itemErrRX[0].appendRow(self.itemsList[idRX_TcpCrcErrs])
    itemErrRX[0].appendRow(self.itemsList[idRX_UdpCrcErrs])    
    itemErrRX[0].appendRow(self.itemsList[idRX_Dropped])    
    #TX_Errors
    itemErrTX = [QtGui.QStandardItem('TX_Errors'), QtGui.QStandardItem('Error Counters')]
    self.rootItem.appendRow(itemErrTX)
    itemErrTX[0].appendRow(self.itemsList[idTx_Underruns])
    itemErrTX[0].appendRow(self.itemsList[idTx_SingleColls])
    itemErrTX[0].appendRow(self.itemsList[idTx_Le15Colls])
    itemErrTX[0].appendRow(self.itemsList[idTx_Gt15Colls])
    itemErrTX[0].appendRow(self.itemsList[idTx_LateColls])
    itemErrTX[0].appendRow(self.itemsList[idTx_Deffered])    
    #Classifier
    itemCL = [QtGui.QStandardItem('Classificator'), QtGui.QStandardItem('Counters')]
    self.rootItem.appendRow(itemCL)
    itemCL[0].appendRow(self.itemsList[idCL_RX])
    itemCL[0].appendRow(self.itemsList[idCL_L3_Fails])
    itemCL[0].appendRow(self.itemsList[idCL_IPV4])
    itemCL[0].appendRow(self.itemsList[idCL_IPV6])
    itemCL[0].appendRow(self.itemsList[idCL_CRC_Errs])
    itemCL[0].appendRow(self.itemsList[idCL_TLL_Errs])
    itemCL[0].appendRow(self.itemsList[idCL_ICMP])
    itemCL[0].appendRow(self.itemsList[idCL_IGMP])
    itemCL[0].appendRow(self.itemsList[idCL_TCP])
    itemCL[0].appendRow(self.itemsList[idCL_UDP])
   

  def debugIncCounters(self):      
      for value in self.itemsList.values():
        val = int(value[1].text())
        value[1].setText(str(val + 1))

  def unpackStatEMAC(self, buff, offs):
    for i in range(EMAC_STAT_COUNT):
      (R64, ) = struct.unpack_from('Q', buff, offs)
      offs += EMAC_STAT_CNTR_LEN
      self.itemsList[i][1].setText(str(R64))

  def unpackStatClass(self, buff, offs):
    for i in range(idCL_LOW, idCL_HIGH + 1):
      (R64, ) = struct.unpack_from('Q', buff, offs)
      offs += EMAC_STAT_CNTR_LEN
      self.itemsList[i][1].setText(str(R64))

  def UpdateModelFromDevice(self, selEmac):
    #EMAC
    (buff, offs) = self.comCLI.readStatsEMAC(selEmac, EMAC_STAT_LEN)
    if buff != None:
      self.unpackStatEMAC(buff, offs)
    else:
      print('readStatsEMAC Faults')  
    #CLASS
    (buff, offs) = self.comCLI.readStatClassifEMAC(selEmac, CLASS_STAT_LEN)
    if buff != None:
      self.unpackStatClass(buff, offs)
    else:
      print('readStatClassifEMAC Faults')        
      