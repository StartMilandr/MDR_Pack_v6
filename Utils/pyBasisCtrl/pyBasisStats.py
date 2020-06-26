from PySide2 import QtWidgets, QtGui
from pyBasisStats_ui import Ui_Form
from pyWidgetsUtils import *
#from pyWidgetsStyles import *
from pyBasisRes import *


class PyBasisWindowStats(QtWidgets.QWidget, Ui_Form):
    # Constructor
    def __init__(self, parent=None):
        super(PyBasisWindowStats, self).__init__(parent)       
        # Setup UI and Show
        self.setupUi(self)
        # Init
        self.initTablePort()
        tableWidget_SetRowHeight(self.tblPortStat, TABLE_ITEM_HEIGHT)
        tableWidget_SetRowHeight(self.tblPortTx, TABLE_ITEM_HEIGHT)
        tableWidget_SetRowHeight(self.tblPortRx, TABLE_ITEM_HEIGHT)
        tableWidget_SetRowHeight(self.tblClassStat, TABLE_ITEM_HEIGHT)
        


    def closeEvent(self, event):
        #self.comThread.stop()
        #self.saveSettings(saveFileName)
        #self.saveGeomerty()
        event.accept()

    def initTablePort(self):
        header = self.tblPortStat.horizontalHeader()
        header.setSectionResizeMode(0, QtWidgets.QHeaderView.Stretch)
        header.setSectionResizeMode(1, QtWidgets.QHeaderView.Stretch)        
        





