from PySide2 import QtWidgets, QtGui, QtCore
from pyBasisMAC_ui import Ui_Form
from pyWidgetsUtils import *
from pyWidgetsStyles import comboBoxStyles, comboBoxStyles_DropDown
from pyBasisRes import *

from KX028_CLI import KX028_CLI
from KX028_KeyEntryMAC import KX028_KeyEntryMAC, KX028_KeyMAC
from KX028_ItemMAC import KX028_ItemMAC


#  TableRx Colunms
cCOL_RX_SEL     = 0
cCOL_RX_VLAN    = 1
cCOL_RX_MAC     = 2
cCOL_RX_FRESH   = 3
cCOL_RX_STATIC  = 4
cCOL_RX_TC      = 5
cCOL_RX_FORW    = 6
cCOL_RX_ACTION  = 7

# AddItem Table
cCTRL_ROW_COUNT = 3
cCOL_ADD_VLAN   = 0
cCOL_ADD_MAC    = 1
cCOL_ADD_STATIC = 2
cCOL_ADD_ACTION = 3
cCOL_ADD_TC     = 4
cCOL_ADD_FORW   = 5
cCOL_ADD_APPLY  = 6

class PyBasisWindowMAC(QtWidgets.QWidget, Ui_Form):
    # Constructor
    def __init__(self, parent=None):
        super(PyBasisWindowMAC, self).__init__(parent)       
        # Setup UI and Show
        self.setupUi(self)
        #Tables
        self.setStyleSheet(comboBoxStyles + comboBoxStyles_DropDown)
        self.initTableCtrl()
        self.initTableRx()
        self.DemoAddTableRx()
        self.comCLI = None
        self.tableItems = []
        self.btRead.clicked.connect(self.ReadTableFromDevice)        
        self.btSelTgl.clicked.connect(self.SelectItemsToggle)
        self.btDelSelected.clicked.connect(self.DelSelectedItems)
        

    def closeEvent(self, event):
        event.accept()    

    # ------------- Control Table ---------------
    def initTableCtrl(self):
      self.tblCtrl.setRowCount(cCTRL_ROW_COUNT)
      self.grbxAddItem.setMaximumHeight(170)
      for i in range(cCTRL_ROW_COUNT):
        # Columns Widgets                       
        tableWidget_AddSpinBoxRange(  self.tblCtrl, i, cCOL_ADD_VLAN, 0, 100)
        tableWidget_AddLineEdit_MAC(  self.tblCtrl, i, cCOL_ADD_MAC)
        tableWidget_AddItemCheck(     self.tblCtrl, i, cCOL_ADD_STATIC, False)
        tableWidget_AddComboBox(      self.tblCtrl, i, cCOL_ADD_ACTION, ACT_ACTIIONS, 0)
        tableWidget_AddSpinBoxRange(  self.tblCtrl, i, cCOL_ADD_TC, 0, 7)
        tableWidget_AddLineEdit_0x1FF(self.tblCtrl, i, cCOL_ADD_FORW, '0x00')
        btn = tableWidget_AddPushButton(self.tblCtrl, i, cCOL_ADD_APPLY, sAPPLY_BTN_TEXT)
        btn.clicked.connect(self.writeItemMAC)
      # Resize
      header = self.tblCtrl.horizontalHeader()
      header.setSectionResizeMode(cCOL_ADD_VLAN,   QtWidgets.QHeaderView.ResizeToContents)
      header.setSectionResizeMode(cCOL_ADD_MAC,    QtWidgets.QHeaderView.Stretch)
      header.setSectionResizeMode(cCOL_ADD_STATIC, QtWidgets.QHeaderView.ResizeToContents)
      header.setSectionResizeMode(cCOL_ADD_ACTION, QtWidgets.QHeaderView.Stretch)
      header.setSectionResizeMode(cCOL_ADD_TC,     QtWidgets.QHeaderView.Stretch)
      header.setSectionResizeMode(cCOL_ADD_FORW,   QtWidgets.QHeaderView.Stretch)
      header.setSectionResizeMode(cCOL_ADD_APPLY,  QtWidgets.QHeaderView.ResizeToContents)

    # AddOrUpdateItem:
    def GUI_GetKeyEntry(self, row):
        keyEntry = KX028_KeyEntryMAC()
        keyEntry.key.MAC =  self.tblCtrl.cellWidget(row, cCOL_ADD_MAC).text()
        keyEntry.key.vlanID = self.tblCtrl.cellWidget(row, cCOL_ADD_VLAN).value()
        keyEntry.forwPorts = int(self.tblCtrl.cellWidget(row, cCOL_ADD_FORW).text(), 16)
        keyEntry.tc = self.tblCtrl.cellWidget(row, cCOL_ADD_TC).value()
        keyEntry.action = self.tblCtrl.cellWidget(row, cCOL_ADD_ACTION).currentIndex()
        keyEntry.cutThrough = False 
        keyEntry.isFresh = False
        keyEntry.isStatic = self.tblCtrl.item(row, cCOL_ADD_STATIC).checkState() == QtCore.Qt.Checked
        #printObj(keyEntry)
        #printObj(keyEntry.key)
        return keyEntry

    def writeItemMAC(self):
        button = self.sender()
        index = self.tblCtrl.indexAt(button.pos())
        keyEntry = self.GUI_GetKeyEntry(index.row())
        self.comCLI.UpdateOrAddMAC(keyEntry)
    

    # ------------- Read Table ---------------
    def initTableRx(self):
        #self.tblTableRd.resizeColumnsToContents()
        self.tableRxColumnSetSize()
        tableWidget_SetRowHeight(self.tblTableRd, TABLE_ITEM_HEIGHT)

    def tableRxColumnSetSize(self):
        header = self.tblTableRd.horizontalHeader()
        header.setSectionResizeMode(cCOL_RX_SEL,    QtWidgets.QHeaderView.ResizeToContents)
        header.setSectionResizeMode(cCOL_RX_VLAN,   QtWidgets.QHeaderView.ResizeToContents)
        header.setSectionResizeMode(cCOL_RX_MAC,    QtWidgets.QHeaderView.Stretch)
        header.setSectionResizeMode(cCOL_RX_FRESH,  QtWidgets.QHeaderView.ResizeToContents)
        header.setSectionResizeMode(cCOL_RX_STATIC, QtWidgets.QHeaderView.ResizeToContents)
        header.setSectionResizeMode(cCOL_RX_TC,     QtWidgets.QHeaderView.Stretch)
        header.setSectionResizeMode(cCOL_RX_FORW,   QtWidgets.QHeaderView.Stretch)

    def tableRxAddItem(self, ind, itemMAC):
        # Selected
        tableWidget_AddItemCheck(self.tblTableRd, ind, cCOL_RX_SEL, False)  
        # Others
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_VLAN,   str(itemMAC.vlanID)) 
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_MAC,    itemMAC.MAC) 
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_FRESH,  str(itemMAC.isFresh))
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_STATIC, str(itemMAC.isStatic))
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_TC,     str(itemMAC.tc)) 
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_FORW,   hex(itemMAC.forwPorts))
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_ACTION, ACT_ACTIIONS[itemMAC.action])

    def DemoAddTableRx(self):
        #debug-test
        self.tblTableRd.setRowCount(1)
        self.tableRxAddItem(0, KX028_ItemMAC())

    # Read Table Actions:
    def ReadTableFromDevice(self):
        self.tableItems = self.comCLI.ReadTableMAC()
        self.tblTableRd.setRowCount(len(self.tableItems))
        row = 0
        for item in self.tableItems:
            self.tableRxAddItem(row, item)
            row += 1

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
               key = KX028_KeyMAC()
               key.MAC = self.tableItems[i].MAC
               key.vlanID = self.tableItems[i].vlanID
               self.comCLI.DelItemMAC(key) 
        self.ReadTableFromDevice()       



