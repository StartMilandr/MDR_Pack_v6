from PySide2 import QtCore, QtGui, QtWidgets
from pyBasisMain import PyBasisMainForm
import sys


# Create QApplication
app = QtWidgets.QApplication(sys.argv)
# Create 
PyComPort = PyBasisMainForm()
# Process EventLoop
sys.exit(app.exec_())