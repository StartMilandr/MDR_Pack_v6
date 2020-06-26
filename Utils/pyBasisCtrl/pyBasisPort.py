from PySide2 import QtWidgets, QtGui
from pyBasisPort_ui import Ui_Form
from pyWidgetsUtils import *
from pyWidgetsStyles import *
from pyBasisRes import *

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

class PyBasisWindowPort(QtWidgets.QWidget, Ui_Form):
    # Constructor
    def __init__(self, parent=None):
        super(PyBasisWindowPort, self).__init__(parent)       
        # Setup UI and Show
        self.setupUi(self)
        #Tables
        self.setStyleSheet(comboBoxStyles + comboBoxStyles_DropDown_SpinW)
        self.initPortsTable()
        #self.setStyleSheet(tableWidgetPaddingOff)        


    def closeEvent(self, event):
        #self.comThread.stop()
        #self.saveSettings(saveFileName)
        #self.saveGeomerty()
        event.accept()

    def initPortsTable(self):
        colCnt = len(PORTS)
        self.tblPorts.setColumnCount(colCnt)
        # Create Ctrls    
        portNames = BasisGetPortNames()
        for i in range(colCnt):
            tableWidget_AddComboBox(self.tblPorts, ROW_PORT, i, portNames, i)
            tableWidget_PushButton(self.tblPorts,  ROW_READ, i, TEXT_BTN_READ)
            tableWidget_AddItemStr(self.tblPorts,  ROW_STAT, i, TEXT_LINK_DOWN)
            tableWidget_AddComboBox(self.tblPorts, ROW_SHUTDOWN, i, SHUT_DOWN_ITEMS, 0)
            tableWidget_AddLineEdit_0x8FFF(self.tblPorts,  ROW_TPID,  i, '0x8100')
            tableWidget_AddSpinBoxRange(self.tblPorts,  ROW_FALLBACK, i, 0, 15)
            tableWidget_AddComboBox(self.tblPorts, ROW_AFT, i, AFT_ITEMS, 0)
            tableWidget_AddComboBox(self.tblPorts, ROW_BLOCKSTATE, i, BLOCKSTATE_ITEMS, 0)
            tableWidget_AddSpinBoxRange(self.tblPorts,  ROW_UNTAG_BT, i, 0, 127)
            tableWidget_PushButton(self.tblPorts, ROW_WRITE, i, TEXT_BTN_WRITE)
        #rescale
        header = self.tblPorts.horizontalHeader()
        for i in range(colCnt):
            header.setSectionResizeMode(i,   QtWidgets.QHeaderView.Stretch)
        tableWidget_SetRowHeight(self.tblPorts, TABLE_ITEM_HEIGHT)