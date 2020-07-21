from PySide2 import QtWidgets, QtGui
from pyBasisPort_ui import Ui_Form
from pyWidgetsUtils import *
from pyWidgetsStyles import *
from pyBasisRes import *
from pathlib import Path
from PySide2.QtCore import QSettings
from KX028_ItemPort import KX028_ItemPort

ROW_PORT        = 0
ROW_READ        = 1
ROW_STAT        = 2
ROW_SHUTDOWN    = 3
ROW_TPID        = 4
ROW_FALLBACK    = 5
ROW_AFT         = 6
ROW_BLOCKSTATE  = 7
ROW_UNTAG_BT    = 8
ROW_WRITE       = 9

LinkState_Str = ['LinkDown', 'LinkUp']        

class PyBasisWindowPort(QtWidgets.QWidget, Ui_Form):
    # Constructor
    def __init__(self, parent=None):
        super(PyBasisWindowPort, self).__init__(parent)       
        # Setup UI and Show
        self.setupUi(self)
        #Tables
        self.setStyleSheet(comboBoxStyles + comboBoxStyles_DropDown_SpinW + lineEditStyles + spinBoxStyles)
        self.initPortsTable()
        #self.setStyleSheet(tableWidgetPaddingOff)
        self.comCLI = None
        self.saveFileName = str(Path().absolute()) + '/saves/Ports.ini'
        self.RestoreWidgets()
        self.btUpdateAll.clicked.connect(self.readAllPorts)        

        
    def __del__(self):
        self.SaveWidgets()

    def SaveWidgets(self):
        settings = QSettings(self.saveFileName, QSettings.IniFormat)
        tableWidget_SaveWidgets(self.tblPorts, settings)

    def RestoreWidgets(self): 
        settings = QSettings(self.saveFileName, QSettings.IniFormat)
        tableWidget_RestoreWidgets(self.tblPorts, settings)

    def initPortsTable(self):
        colCnt = len(PORTS)
        self.tblPorts.setColumnCount(colCnt)
        # Create Ctrls    
        portNames = BasisGetPortNames()
        for i in range(colCnt):
            tableWidget_AddComboBox(self.tblPorts, ROW_PORT, i, portNames, i, 'cbxPort_' + str(i))
            btn = tableWidget_AddPushButton(self.tblPorts,  ROW_READ, i, TEXT_BTN_READ, 'btRead_' + str(i))
            btn.clicked.connect(self.readItemPort)

            tableWidget_AddItemStr(self.tblPorts,  ROW_STAT, i, TEXT_LINK_DOWN)
            tableWidget_AddComboBox(self.tblPorts, ROW_SHUTDOWN, i, SHUT_DOWN_ITEMS, 0, 'cbxShutDown_' + str(i))
            tableWidget_AddLineEdit_0x8FFF(self.tblPorts,  ROW_TPID,  i, '0x8100', 'leTPID_' + str(i))
            tableWidget_AddSpinBoxRange(self.tblPorts,  ROW_FALLBACK, i, 0, 15, 'spbxFallback_' + str(i))
            tableWidget_AddComboBox(self.tblPorts, ROW_AFT, i, AFT_ITEMS, 0, 'cbxAFT_' + str(i))
            tableWidget_AddComboBox(self.tblPorts, ROW_BLOCKSTATE, i, BLOCKSTATE_ITEMS, 0, 'cbxBlockState_' + str(i))
            tableWidget_AddSpinBoxRange(self.tblPorts,  ROW_UNTAG_BT, i, 0, 127, 'spbxUntagBt_' + str(i))
            btn = tableWidget_AddPushButton(self.tblPorts, ROW_WRITE, i, TEXT_BTN_WRITE, 'btWrite_' + str(i))
            btn.clicked.connect(self.writeItemPort)
        #rescale
        header = self.tblPorts.horizontalHeader()
        for i in range(colCnt):
            header.setSectionResizeMode(i,   QtWidgets.QHeaderView.Stretch)
        tableWidget_SetRowHeight(self.tblPorts, TABLE_ITEM_HEIGHT)


    def GUI_GetItemPort(self, col):
        itemPort = KX028_ItemPort()
        itemPort.shutDown   = self.tblPorts.cellWidget(ROW_SHUTDOWN, col).currentIndex()
        itemPort.TPID       = int(self.tblPorts.cellWidget(ROW_TPID, col).text(), 16)
        itemPort.Fallback   = self.tblPorts.cellWidget(ROW_FALLBACK, col).value()
        itemPort.AFT        = self.tblPorts.cellWidget(ROW_AFT, col).currentIndex()
        itemPort.Blockstate = self.tblPorts.cellWidget(ROW_BLOCKSTATE, col).currentIndex()
        itemPort.UntagBTable = self.tblPorts.cellWidget(ROW_UNTAG_BT, col).value()
        return itemPort

    def GUI_SetItemPort(self, col, itemPort):
        self.tblPorts.cellWidget(ROW_SHUTDOWN, col).setCurrentIndex(itemPort.shutDown)
        self.tblPorts.cellWidget(ROW_TPID, col).setText(hex(itemPort.TPID))
        self.tblPorts.cellWidget(ROW_FALLBACK, col).setValue(itemPort.Fallback)
        self.tblPorts.cellWidget(ROW_AFT, col).setCurrentIndex(itemPort.AFT)
        self.tblPorts.cellWidget(ROW_BLOCKSTATE, col).setCurrentIndex(itemPort.Blockstate)
        self.tblPorts.cellWidget(ROW_UNTAG_BT, col).setValue(itemPort.UntagBTable)

    def writeItemPort(self):
        button = self.sender()
        index = self.tblPorts.indexAt(button.pos())
        emac = self.tblPorts.cellWidget(ROW_PORT, index.column()).currentIndex()
        itemPort = self.GUI_GetItemPort(index.column())
        self.comCLI.writePortCfg(emac, itemPort)


    def readPort(self, col):
        emac = self.tblPorts.cellWidget(ROW_PORT, col).currentIndex()
        #Read Config
        itemPort = self.comCLI.readPortCfg(emac)
        self.GUI_SetItemPort(col, itemPort)
        #Read LinkStatus
        netStat = self.comCLI.readAxiRegList([ kx028_EmacAdr[emac] + EMAC_NETSTAT ])
        if netStat != None:
            self.tblPorts.item(ROW_STAT, col).setText(LinkState_Str[netStat[0] & EMAC_NETSTAT_LINK_Msk])
        else:
            self.tblPorts.item(ROW_STAT, col).setText('Error')

    def readItemPort(self):
        button = self.sender()
        index = self.tblPorts.indexAt(button.pos())
        self.readPort(index.column())
        
    def readAllPorts(self):
        for i in range(self.tblPorts.columnCount()):
            self.readPort(i)
        
