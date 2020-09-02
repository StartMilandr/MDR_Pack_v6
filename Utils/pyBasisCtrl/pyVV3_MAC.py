from PySide2 import QtWidgets, QtGui, QtCore
from PySide2.QtCore import QSettings
from pyVV3_MAC_ui import Ui_Form
from pyWidgetsUtils import *
from pyWidgetsStyles import comboBoxStyles, comboBoxStyles_DropDown, lineEditStyles
from pyVV3_Res import *
from pathlib import Path

from KX028_CLI import KX028_CLI
#from KX028_KeyEntryMAC import KX028_KeyEntryMAC, KX028_KeyMAC
#from KX028_ItemMAC import KX028_ItemMAC
from pyVV3_ItemMAC import VV3_ItemMAC


#  TableRx Colunms
cCOL_RX_SEL      = 0
cCOL_RX_ADDR     = 1
cCOL_RX_HASH     = 2
cCOL_RX_HASH_IND = 3
cCOL_RX_MAC      = 4
cCOL_RX_AGE      = 5
cCOL_RX_PORT     = 6

# AddItem Table
cCTRL_ROW_COUNT = 3
cCOL_ADD_HASH_IND = 0
cCOL_ADD_MAC      = 1
cCOL_ADD_AGE      = 2
cCOL_ADD_PORT     = 3
cCOL_ADD_APPLY    = 4

class PyWindowMAC_VV3(QtWidgets.QWidget, Ui_Form):
    # Constructor
    def __init__(self, parent=None):
        super(PyWindowMAC_VV3, self).__init__(parent)       
        # Setup UI and Show
        self.setupUi(self)
        #Tables
        self.setStyleSheet(comboBoxStyles + comboBoxStyles_DropDown + lineEditStyles)
        self.initTableCtrl()
        self.initTableRx()
        self.DemoAddTableRx()
        self.comCLI = None
        self.tableItems = []
        self.btRead.clicked.connect(self.ReadTableFromDevice)        
        self.btSelTgl.clicked.connect(self.SelectItemsToggle)
        self.btDelSelected.clicked.connect(self.DelSelectedItems)
        self.chbxOldClear.clicked.connect(self.ChangeOldClear)

        self.saveFileName = str(Path().absolute()) + '/saves/TableMAC_VV3.ini'
        self.RestoreWidgets()


    def __del__(self):
        self.SaveWidgets()

    def SaveWidgets(self):
        #print("Save to: " + self.saveFileName)
        settings = QSettings(self.saveFileName, QSettings.IniFormat)
        tableWidget_SaveWidgets(self.tblCtrl, settings)

    def RestoreWidgets(self): 
        #print("Load From: " + self.saveFileName)
        settings = QSettings(self.saveFileName, QSettings.IniFormat)
        tableWidget_RestoreWidgets(self.tblCtrl, settings)

    # ------------- Control Table ---------------
    def initTableCtrl(self):
      self.tblCtrl.setRowCount(cCTRL_ROW_COUNT)
      self.grbxAddItem.setMaximumHeight(170)
      for i in range(cCTRL_ROW_COUNT):
        # Columns Widgets                       
        tableWidget_AddSpinBoxRange(  self.tblCtrl, i, cCOL_ADD_HASH_IND, 0, 7, 'spbHInd_' + str(i))
        tableWidget_AddLineEdit_MAC(  self.tblCtrl, i, cCOL_ADD_MAC, 'leMAC_' + str(i))
        tableWidget_AddLineEdit_0xFFF(self.tblCtrl, i, cCOL_ADD_AGE, '0x000', 'leAge_' + str(i))
        tableWidget_AddSpinBoxRange(  self.tblCtrl, i, cCOL_ADD_PORT, 0, 4, 'spbPort_' + str(i))
        btn = tableWidget_AddPushButton(self.tblCtrl, i, cCOL_ADD_APPLY, 'ADD', 'btApply_' + str(i))
        btn.clicked.connect(self.writeItemMAC)
      # Resize
      header = self.tblCtrl.horizontalHeader()
      header.setSectionResizeMode(cCOL_ADD_HASH_IND, QtWidgets.QHeaderView.ResizeToContents)
      header.setSectionResizeMode(cCOL_ADD_MAC,      QtWidgets.QHeaderView.Stretch)
      header.setSectionResizeMode(cCOL_ADD_AGE,      QtWidgets.QHeaderView.ResizeToContents)
      header.setSectionResizeMode(cCOL_ADD_PORT,     QtWidgets.QHeaderView.ResizeToContents)
      header.setSectionResizeMode(cCOL_ADD_APPLY,    QtWidgets.QHeaderView.Stretch)
      self.grbxAddItem.setMaximumHeight(170)

    # AddItem:
    def GUI_GetItemMac(self, row):
        itemMac = VV3_ItemMAC()
        itemMac.HashInd = self.tblCtrl.cellWidget(row, cCOL_ADD_HASH_IND).value()
        itemMac.MAC = self.tblCtrl.cellWidget(row, cCOL_ADD_MAC).text()
        itemMac.Age = int(self.tblCtrl.cellWidget(row, cCOL_ADD_AGE).text(), 16)
        itemMac.Port = self.tblCtrl.cellWidget(row, cCOL_ADD_PORT).value()        
        itemMac.IsActive = False 
        itemMac.CalcHash()
        #printObj(itemMac)
        return itemMac     

    def writeItemMAC(self):
        button = self.sender()
        index = self.tblCtrl.indexAt(button.pos())
        keyEntry = self.GUI_GetItemMac(index.row())
        self.comCLI.AddMAC_VV3(keyEntry)
    

    # ------------- Read Table ---------------
    def initTableRx(self):
        #self.tblTableRd.resizeColumnsToContents()
        self.tableRxColumnSetSize()
        tableWidget_SetRowHeight(self.tblTableRd, TABLE_ITEM_HEIGHT)

    def tableRxColumnSetSize(self):
        header = self.tblTableRd.horizontalHeader()
        header.setSectionResizeMode(cCOL_RX_SEL,      QtWidgets.QHeaderView.ResizeToContents)
        header.setSectionResizeMode(cCOL_RX_ADDR,     QtWidgets.QHeaderView.Stretch)
        header.setSectionResizeMode(cCOL_RX_HASH,     QtWidgets.QHeaderView.Stretch)
        header.setSectionResizeMode(cCOL_RX_HASH_IND, QtWidgets.QHeaderView.Stretch)
        header.setSectionResizeMode(cCOL_RX_MAC,      QtWidgets.QHeaderView.Stretch)
        header.setSectionResizeMode(cCOL_RX_AGE,      QtWidgets.QHeaderView.Stretch)
        header.setSectionResizeMode(cCOL_RX_PORT,     QtWidgets.QHeaderView.Stretch)

    def tableRxAddItem(self, ind, itemMAC):
        # Selected
        tableWidget_AddItemCheck(self.tblTableRd, ind, cCOL_RX_SEL, False)  
        # Others
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_ADDR,      hex(itemMAC.HashAddr))
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_HASH,      hex(itemMAC.Hash))
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_HASH_IND,  str(itemMAC.HashInd))
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_MAC,       itemMAC.MAC) 
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_AGE,       hex(itemMAC.Age))
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_PORT,      str(itemMAC.Port))

    def DemoAddTableRx(self):
        #debug-test
        self.tblTableRd.setRowCount(1)
        self.tableRxAddItem(0, VV3_ItemMAC())

    # Read Table Actions:
    def ReadTableFromDevice(self):
        self.tblTableRd.setRowCount(0)
        self.tableItems = self.comCLI.ReadTableMAC_VV3()
        self.tblTableRd.setRowCount(len(self.tableItems))
        row = 0
        for item in self.tableItems:
            self.tableRxAddItem(row, item)
            row += 1

        values = self.comCLI.ReadRegList_VV3([MDR_5600BB3_regAgeCtrl0])
        if len(values) > 0:
            self.chbxOldClear.setChecked((values[0] & MDR_5600BB3_AgeCtrl0_MAC_AgeDelEn_Msk) != 0)

    def SelectItemsToggle(self):
        cnt = self.tblTableRd.rowCount()
        if cnt > 0:            
            if self.tblTableRd.item(0, cCOL_RX_SEL).checkState() == QtCore.Qt.Checked:
                checkState = QtCore.Qt.Unchecked
            else:
                checkState = QtCore.Qt.Checked 
            for i in range(cnt):
               self.tblTableRd.item(i, cCOL_RX_SEL).setCheckState(checkState) 

    def DelSelectedItems(self):
        itemsCnt = min(len(self.tableItems), self.tblTableRd.rowCount())
        for i in range(itemsCnt):
            if self.tblTableRd.item(i, cCOL_RX_SEL).checkState() == QtCore.Qt.Checked:
               hashAddr = int(self.tblTableRd.item(i, cCOL_RX_ADDR).text(), 16)
               self.comCLI.DelItemMAC_VV3(hashAddr) 
        self.ReadTableFromDevice()       

    def ChangeOldClear(self):
        values = self.comCLI.ReadRegList_VV3([MDR_5600BB3_regAgeCtrl0])
        if len(values) > 0:
            #print(hex(values[0]))
            if self.chbxOldClear.isChecked():
              self.comCLI.WriteRegList_VV3([MDR_5600BB3_regAgeCtrl0], [values[0] | MDR_5600BB3_AgeCtrl0_MAC_AgeDelEn_Msk])
            else:
              self.comCLI.WriteRegList_VV3([MDR_5600BB3_regAgeCtrl0], [values[0] & ~MDR_5600BB3_AgeCtrl0_MAC_AgeDelEn_Msk])
        else:
            print('Read List Empty!')      
