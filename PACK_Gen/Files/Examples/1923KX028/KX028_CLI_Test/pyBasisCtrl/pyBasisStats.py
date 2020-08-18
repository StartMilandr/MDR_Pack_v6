from PySide2 import QtWidgets, QtGui
from pyBasisStats_ui import Ui_Form
from pyWidgetsUtils import *
#from pyWidgetsStyles import *
from pyBasisRes import *
from KX028_CLI import KX028_CLI
from KX028_PortStatsModel import KX028_PortStatsModel
import struct

class PyBasisWindowStats(QtWidgets.QWidget, Ui_Form):
    # Constructor
    def __init__(self, parent=None):
        super(PyBasisWindowStats, self).__init__(parent)       
        # Setup UI and Show
        self.setupUi(self)
        self.statModel = KX028_PortStatsModel()
        self.treeView.setModel(self.statModel.model)
        self.ColumnsFit()
        self.btPortRead.clicked.connect(self.ReadStatsFromDevice)
        self.btPortClear.clicked.connect(self.ClearStats)
        self.btClearAll.clicked.connect(self.ClearStatsAll)

    def closeEvent(self, event):
        event.accept()
        
    def ColumnsFit(self):
        header = self.treeView.header()
        header.setSectionResizeMode(0,   QtWidgets.QHeaderView.ResizeToContents)
        header.setSectionResizeMode(1,   QtWidgets.QHeaderView.Stretch)

    def AssighCLI(self, comCLI):
        self.statModel.comCLI = comCLI

    def ReadStatsFromDevice(self):
        self.statModel.UpdateModelFromDevice(self.cbxPortSel.currentIndex())

    def ClearStats(self):
        self.statModel.ClearStats(self.cbxPortSel.currentIndex())

    def ClearStatsAll(self):
        for i in range(self.cbxPortSel.count()):
            self.statModel.ClearStats(i)
        self.ReadStatsFromDevice()    





