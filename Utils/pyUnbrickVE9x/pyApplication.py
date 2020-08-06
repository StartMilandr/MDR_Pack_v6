from PySide2 import QtCore, QtGui, QtWidgets
from pyWindowClass import pyWindowClass
import sys


# Create QApplication
app = QtWidgets.QApplication(sys.argv)
# Create Window
window = pyWindowClass()
# Process EventLoop
sys.exit(app.exec_())