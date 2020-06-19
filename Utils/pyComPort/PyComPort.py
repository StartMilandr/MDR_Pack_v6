from PySide2 import QtCore, QtGui, QtWidgets
from PyComPortClass import PyComPortForm
import sys


# Create QApplication
app = QtWidgets.QApplication(sys.argv)
# Create 
PyComPort = PyComPortForm()
# Process EventLoop
sys.exit(app.exec_())