from PySide2 import QtWidgets, QtGui
from pyBasisStats_ui import Ui_Form
from pyWidgetsUtils import *
#from pyWidgetsStyles import *
from pyBasisRes import *
from KX028_PortStatsModel import KX028_PortStatsModel

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
          

    def closeEvent(self, event):
        event.accept()
        
    def ReadStatsFromDevice(self):
        self.statModel.debugIncCounters()

    def ColumnsFit(self):
        header = self.treeView.header()
        header.setSectionResizeMode(0,   QtWidgets.QHeaderView.ResizeToContents)
        header.setSectionResizeMode(1,    QtWidgets.QHeaderView.Stretch)





