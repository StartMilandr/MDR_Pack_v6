from PySide2 import QtWidgets, QtGui
from pyBasisVLAN_ui import Ui_Form
from pyWidgetsUtils import *
from pyWidgetsStyles import comboBoxStyles, comboBoxStyles_DropDown
from pyBasisRes import *
from KX028_KeyEntryVLAN import KX028_KeyEntryVLAN, KX028_KeyVLAN
from KX028_ItemVLAN import KX028_ItemVLAN

# AddItem Table
cCTRL_RAW_COUNT = 3

cCOL_ADD_VLAN   = 0
cCOL_ADD_FORW   = 1
cCOL_ADD_UNTAG  = 2
cCOL_ADD_UHIT   = 3
cCOL_ADD_UMISS  = 4
cCOL_ADD_MHIT   = 5
cCOL_ADD_MMISS  = 6
cCOL_ADD_MSTP   = 7
cCOL_ADD_APPLY  = 8

#  TableRx Colunms
cCOL_RX_SEL    = 0
cCOL_RX_VLAN   = 1
cCOL_RX_FORW   = 2
cCOL_RX_UNTAG  = 3
cCOL_RX_UHIT   = 4
cCOL_RX_UMISS  = 5
cCOL_RX_MHIT   = 6
cCOL_RX_MMISS  = 7
cCOL_RX_MSTP   = 8
cCOL_RX_APPLY  = 9

cWIDTH_SEL    = 40
cWIDTH_VLAN   = 60

class PyBasisWindowVLAN(QtWidgets.QWidget, Ui_Form):
    # Constructor
    def __init__(self, parent=None):
        super(PyBasisWindowVLAN, self).__init__(parent)       
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
      self.tblCtrl.setRowCount(cCTRL_RAW_COUNT)
      self.grbxAddItem.setMaximumHeight(170)
      for i in range(cCTRL_RAW_COUNT):
        # Column Widgets                       
        tableWidget_AddSpinBoxRange(self.tblCtrl, i, cCOL_ADD_VLAN, 0, 100)
        tableWidget_AddLineEdit_0x1FF(self.tblCtrl, i, cCOL_ADD_FORW, '0x00')
        tableWidget_AddLineEdit_0x1FF(self.tblCtrl, i, cCOL_ADD_UNTAG, '0x00')
        tableWidget_AddComboBox(self.tblCtrl, i, cCOL_ADD_UHIT,  ACT_ACTIIONS, 0)
        tableWidget_AddComboBox(self.tblCtrl, i, cCOL_ADD_UMISS, ACT_ACTIIONS, 0)
        tableWidget_AddComboBox(self.tblCtrl, i, cCOL_ADD_MHIT,  ACT_ACTIIONS, 0)
        tableWidget_AddComboBox(self.tblCtrl, i, cCOL_ADD_MMISS, ACT_ACTIIONS, 0)
        tableWidget_AddComboBox(self.tblCtrl, i, cCOL_ADD_MSTP,  ACT_ACTIIONS, 0)
        btn = tableWidget_AddPushButton(self.tblCtrl, i, cCOL_ADD_APPLY, sAPPLY_BTN_TEXT)
        btn.clicked.connect(self.writeItemVLAN)
      # Resize
      header = self.tblCtrl.horizontalHeader()
      header.setSectionResizeMode(cCOL_ADD_VLAN,   QtWidgets.QHeaderView.ResizeToContents)
      header.setSectionResizeMode(cCOL_ADD_FORW,   QtWidgets.QHeaderView.Stretch)
      header.setSectionResizeMode(cCOL_ADD_UNTAG,  QtWidgets.QHeaderView.Stretch)
      header.setSectionResizeMode(cCOL_ADD_UHIT,   QtWidgets.QHeaderView.Stretch)
      header.setSectionResizeMode(cCOL_ADD_UMISS,  QtWidgets.QHeaderView.Stretch)
      header.setSectionResizeMode(cCOL_ADD_MHIT,   QtWidgets.QHeaderView.Stretch)
      header.setSectionResizeMode(cCOL_ADD_MMISS,  QtWidgets.QHeaderView.Stretch)
      header.setSectionResizeMode(cCOL_ADD_MSTP,   QtWidgets.QHeaderView.Stretch)
      header.setSectionResizeMode(cCOL_ADD_APPLY,  QtWidgets.QHeaderView.ResizeToContents)
    #   self.tblCtrl.resizeColumnsToContents()
    #   self.tblCtrl.setColumnWidth(cCOL_ADD_VLAN, cWIDTH_VLAN)

    # ControlTable Actions:
    def GUI_GetKeyEntry(self, row):
        keyEntry = KX028_KeyEntryVLAN()
        keyEntry.key.vlanID = self.tblCtrl.cellWidget(row, cCOL_ADD_VLAN).value()
        keyEntry.forwPorts = int(self.tblCtrl.cellWidget(row, cCOL_ADD_FORW).text(), 16)
        keyEntry.untaggedPorts = int(self.tblCtrl.cellWidget(row, cCOL_ADD_UNTAG).text(), 16)
        keyEntry.UCastHitAct = self.tblCtrl.cellWidget(row, cCOL_ADD_UHIT).currentIndex()
        keyEntry.UCastMissAct = self.tblCtrl.cellWidget(row, cCOL_ADD_UMISS).currentIndex()
        keyEntry.MCastHitAct = self.tblCtrl.cellWidget(row, cCOL_ADD_MHIT).currentIndex()
        keyEntry.MCastMissAct = self.tblCtrl.cellWidget(row, cCOL_ADD_MMISS).currentIndex()
        keyEntry.MSTPAct = self.tblCtrl.cellWidget(row, cCOL_ADD_MSTP).currentIndex()
        return keyEntry

    def writeItemVLAN(self):
        button = self.sender()
        index = self.tblCtrl.indexAt(button.pos())
        keyEntry = self.GUI_GetKeyEntry(index.row())
        self.comCLI.UpdateOrAddVLAN(keyEntry)        

    # ------------- Read Table ---------------
    def initTableRx(self):
       #self.tblTableRd.resizeColumnsToContents()
       self.tableRxResize()
       tableWidget_SetRowHeight(self.tblTableRd, TABLE_ITEM_HEIGHT)

    def tableRxResize(self):   
      header = self.tblTableRd.horizontalHeader()
      header.setSectionResizeMode(cCOL_RX_SEL, QtWidgets.QHeaderView.ResizeToContents)
      header.setSectionResizeMode(cCOL_RX_VLAN, QtWidgets.QHeaderView.ResizeToContents)
      header.setSectionResizeMode(cCOL_RX_FORW, QtWidgets.QHeaderView.ResizeToContents)
      header.setSectionResizeMode(cCOL_RX_UNTAG, QtWidgets.QHeaderView.ResizeToContents)
      header.setSectionResizeMode(cCOL_RX_UHIT, QtWidgets.QHeaderView.Stretch)
      header.setSectionResizeMode(cCOL_RX_UMISS, QtWidgets.QHeaderView.Stretch)
      header.setSectionResizeMode(cCOL_RX_MHIT, QtWidgets.QHeaderView.Stretch)
      header.setSectionResizeMode(cCOL_RX_MMISS, QtWidgets.QHeaderView.Stretch)
      header.setSectionResizeMode(cCOL_RX_MSTP, QtWidgets.QHeaderView.Stretch)

    def tableRxAddItem(self, ind, itemVLAN):
        tableWidget_AddItemCheck(self.tblTableRd, ind, cCOL_RX_SEL, False) 
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_VLAN,  str(itemVLAN.vlanID))
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_FORW,  hex(itemVLAN.forwPorts))        
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_UNTAG, hex(itemVLAN.untaggedPorts))
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_UHIT,  ACT_ACTIIONS[itemVLAN.UCastHitAct])
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_UMISS, ACT_ACTIIONS[itemVLAN.UCastMissAct])
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_MHIT,  ACT_ACTIIONS[itemVLAN.MCastHitAct])
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_MMISS, ACT_ACTIIONS[itemVLAN.MCastMissAct])
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_MSTP,  ACT_ACTIIONS[itemVLAN.MSTPAct])

    def DemoAddTableRx(self):
        self.tblTableRd.setRowCount(1)        
        self.tableRxAddItem(0, KX028_ItemVLAN())

    # Read Table Actions:
    def ReadTableFromDevice(self):
        self.tableItems = self.comCLI.ReadTableVLAN()
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
               key = KX028_KeyVLAN()
               key.vlanID = self.tableItems[i].vlanID
               self.comCLI.DelItemVLAN(key) 
        self.ReadTableFromDevice()  

    