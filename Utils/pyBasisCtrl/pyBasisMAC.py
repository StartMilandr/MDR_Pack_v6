from PySide2 import QtWidgets, QtGui, QtCore
from pyBasisMAC_ui import Ui_Form
from pyWidgetsUtils import *
from pyWidgetsStyles import *
from pyBasisRes import *

#  TableRx Colunms
cCOL_RX_SEL     = 0
cCOL_RX_VLAN    = 1
cCOL_RX_MAC     = 2
cCOL_RX_FRESH   = 3
cCOL_RX_STATIC  = 4
cCOL_RX_PORT    = 5
cCOL_RX_FORW    = 6
cCOL_RX_ACTION  = 7

# AddItem Table
cCTRL_RAW_COUNT = 3
cCOL_ADD_VLAN   = 0
cCOL_ADD_MAC    = 1
cCOL_ADD_STATIC = 2
cCOL_ADD_ACTION = 3
cCOL_ADD_PORT   = 4
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
        self.debugAddTableRx()


    def closeEvent(self, event):
        #self.comThread.stop()
        #self.saveSettings(saveFileName)
        #self.saveGeomerty()
        event.accept()

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
        header.setSectionResizeMode(cCOL_RX_PORT,   QtWidgets.QHeaderView.Stretch)
        header.setSectionResizeMode(cCOL_RX_FORW,   QtWidgets.QHeaderView.Stretch)

    def debugAddTableRx(self):
        #debug-test
        self.tblTableRd.setRowCount(1)        
        self.tableRxAddItem(0)

    def tableRxAddItem(self, ind):
        # Selected
        item = QtWidgets.QTableWidgetItem('')
        item.setCheckState(QtCore.Qt.Unchecked)
        self.tblTableRd.setItem(ind, cCOL_RX_SEL, item) 
        # Others
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_VLAN,   '1') 
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_MAC,    '00:00:00:00:00:00') 
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_FRESH,  '1')
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_STATIC, '0') 
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_PORT,   '1') 
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_FORW,   'x01')
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_ACTION, 'ACT_FORWARD')

    def initTableCtrl(self):
      self.tblCtrl.setRowCount(cCTRL_RAW_COUNT)
      self.grbxAddItem.setMaximumHeight(170)
      for i in range(cCTRL_RAW_COUNT):
        # Coluns Widgets                       
        tableWidget_AddSpinBoxRange(  self.tblCtrl, i, cCOL_ADD_VLAN, 0, 100)
        tableWidget_AddLineEdit_MAC(  self.tblCtrl, i, cCOL_ADD_MAC)
        tableWidget_AddItemCheck(     self.tblCtrl, i, cCOL_ADD_STATIC, False)
        tableWidget_AddComboBox(      self.tblCtrl, i, cCOL_ADD_ACTION, ACT_ACTIIONS, 0)
        tableWidget_AddSpinBoxRange(  self.tblCtrl, i, cCOL_ADD_PORT, 0, 15)
        tableWidget_AddLineEdit_0x1FF(self.tblCtrl, i, cCOL_ADD_FORW, '0x00')
        tableWidget_PushButton(       self.tblCtrl, i, cCOL_ADD_APPLY, sAPPLY_BTN_TEXT)
      # Resize
      header = self.tblCtrl.horizontalHeader()
      header.setSectionResizeMode(cCOL_ADD_VLAN,   QtWidgets.QHeaderView.ResizeToContents)
      header.setSectionResizeMode(cCOL_ADD_MAC,    QtWidgets.QHeaderView.Stretch)
      header.setSectionResizeMode(cCOL_ADD_STATIC, QtWidgets.QHeaderView.ResizeToContents)
      header.setSectionResizeMode(cCOL_ADD_ACTION, QtWidgets.QHeaderView.Stretch)
      header.setSectionResizeMode(cCOL_ADD_PORT,   QtWidgets.QHeaderView.Stretch)
      header.setSectionResizeMode(cCOL_ADD_FORW,   QtWidgets.QHeaderView.Stretch)
      header.setSectionResizeMode(cCOL_ADD_APPLY,  QtWidgets.QHeaderView.ResizeToContents)



