from PySide2 import QtWidgets, QtGui
from pyBasisVLAN_ui import Ui_Form
from pyWidgetsUtils import *
from pyWidgetsStyles import *
from pyBasisRes import *

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
        self.debugAddTableRx()


    def closeEvent(self, event):
        #self.comThread.stop()
        #self.saveSettings(saveFileName)
        #self.saveGeomerty()
        event.accept()
       

    def initTableCtrl(self):
      self.tblCtrl.setRowCount(cCTRL_RAW_COUNT)
      self.grbxAddItem.setMaximumHeight(170)
      for i in range(cCTRL_RAW_COUNT):
        # Coluns Widgets                       
        tableWidget_AddSpinBoxRange(self.tblCtrl, i, cCOL_ADD_VLAN, 0, 100)
        tableWidget_AddComboBox(self.tblCtrl, i, cCOL_ADD_FORW,  ACT_ACTIIONS, 0)
        tableWidget_AddComboBox(self.tblCtrl, i, cCOL_ADD_UNTAG, ACT_ACTIIONS, 0)
        tableWidget_AddComboBox(self.tblCtrl, i, cCOL_ADD_UHIT,  ACT_ACTIIONS, 0)
        tableWidget_AddComboBox(self.tblCtrl, i, cCOL_ADD_UMISS, ACT_ACTIIONS, 0)
        tableWidget_AddComboBox(self.tblCtrl, i, cCOL_ADD_MHIT,  ACT_ACTIIONS, 0)
        tableWidget_AddComboBox(self.tblCtrl, i, cCOL_ADD_MMISS, ACT_ACTIIONS, 0)
        tableWidget_AddComboBox(self.tblCtrl, i, cCOL_ADD_MSTP,  ACT_ACTIIONS, 0)
        tableWidget_AddPushButton(self.tblCtrl,  i, cCOL_ADD_APPLY, sAPPLY_BTN_TEXT)
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

    def initTableRx(self):
       #self.tblTableRd.resizeColumnsToContents()
       self.tableRxResize()
       tableWidget_SetRowHeight(self.tblTableRd, TABLE_ITEM_HEIGHT)

    def tableRxResize(self):   
      header = self.tblTableRd.horizontalHeader()
      header.setSectionResizeMode(0, QtWidgets.QHeaderView.ResizeToContents)
      for col in range(1, 8):
        header.setSectionResizeMode(col, QtWidgets.QHeaderView.Stretch)


    def debugAddTableRx(self):
        #debug-test
        self.tblTableRd.setRowCount(1)        
        self.tableRxAddItem(0)
        self.tableRxResize()

    def tableRxAddItem(self, ind):
        # Selected
        tableWidget_AddItemCheck(self.tblTableRd, ind, cCOL_RX_SEL, False) 
        # Others
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_VLAN,  ACT_ACTIIONS[0])
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_FORW,  ACT_ACTIIONS[0])
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_UNTAG, ACT_ACTIIONS[0])
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_UHIT,  ACT_ACTIIONS[0])
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_UMISS, ACT_ACTIIONS[0])
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_MHIT,  ACT_ACTIIONS[0])
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_MMISS, ACT_ACTIIONS[0])
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_MSTP,  ACT_ACTIIONS[0])
        tableWidget_AddItemStr(self.tblTableRd, ind, cCOL_RX_VLAN,  ACT_ACTIIONS[0])

