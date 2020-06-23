from PySide2 import QtCore, QtGui, QtWidgets
from PyComPortTransf import ComPortTransf
import sys


# Create QApplication
app = QtWidgets.QApplication(sys.argv)
# Create 
PyComTransf = ComPortTransf()
# Process EventLoop
sys.exit(app.exec_())