from PySide2 import QtGui

idRx_Bytes      = 0
idRx_OK         = 1
idRx_Broadcast  = 2
idRx_Multicast  = 3
idRx_Pause      = 4
idRx_LenTo64    = 5
idRx_LenTo127   = 6
idRx_LenTo255   = 7
idRx_LenTo512   = 8
idRx_LenTo1023  = 9
idRx_LenOv1518  = 10

idTx_Bytes      = 11
idTx_OK         = 12
idTx_Broadcast  = 13
idTx_Multicast  = 14
idTx_Pause      = 15
idTx_LenTo64    = 16
idTx_LenTo127   = 17
idTx_LenTo255   = 18
idTx_LenTo512   = 19
idTx_LenTo1023  = 20
idTx_LenOv1518  = 21

idRX_ExcLen     = 22
idRX_Jubbers    = 23
idRX_FCSErrs    = 24
idRX_LenErrs    = 25
idRX_SymErrs    = 26
idRX_ResErrs    = 27
idRX_AlignErrs  = 28
idRX_OverErrs   = 29
idRX_IpCrcErrs  = 30
idRX_TcpCrcErrs = 31
idRX_UdpCrcErrs = 32
idRX_Dropped    = 33

idTx_Underruns   = 34
idTx_SingleColls = 35
idTx_Le15Colls   = 36
idTx_Gt15Colls   = 37
idTx_LateColls   = 38
idTx_Deffered    = 39

idCL_RX          = 40
idCL_L3_Fails    = 41
idCL_IPV4        = 42
idCL_IPV6        = 43
idCL_CRC_Errs    = 44
idCL_TLL_Errs    = 45
idCL_ICMP        = 46
idCL_IGMP        = 47
idCL_TCP         = 48
idCL_UDP         = 49


class KX028_PortStatsModel:
  def __init__(self):
    self.model = QtGui.QStandardItemModel()
    self.model.setHorizontalHeaderLabels(['Params', 'Values'])
    self.rootItem = self.model.invisibleRootItem()
    
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
      idRx_LenTo512:  [QtGui.QStandardItem('256..511 bytes packets'),   QtGui.QStandardItem('0') ], \
      idRx_LenTo1023: [QtGui.QStandardItem('512..1023 bytes packets'),  QtGui.QStandardItem('0') ], \
      idRx_LenOv1518: [QtGui.QStandardItem('>1518 bytes packets'),      QtGui.QStandardItem('0') ], \
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
      idTx_LenTo512:  [QtGui.QStandardItem('256..511 bytes packets'),   QtGui.QStandardItem('0') ], \
      idTx_LenTo1023: [QtGui.QStandardItem('512..1023 bytes packets'),  QtGui.QStandardItem('0') ], \
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
    itemRX[0].appendRow(self.itemsList[idRx_LenTo512])
    itemRX[0].appendRow(self.itemsList[idRx_LenTo1023])
    itemRX[0].appendRow(self.itemsList[idRx_LenOv1518])
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
    itemTX[0].appendRow(self.itemsList[idTx_LenTo512])
    itemTX[0].appendRow(self.itemsList[idTx_LenTo1023])
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