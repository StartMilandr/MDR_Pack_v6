from PySide2 import QtCore, QtGui, QtWidgets
from pyEthCtrl import pyEthCtrlWindow
import sys


# Create QApplication
app = QtWidgets.QApplication(sys.argv)
# Create 
window = pyEthCtrlWindow()
# Process EventLoop
sys.exit(app.exec_())