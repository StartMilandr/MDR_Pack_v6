from PySide2 import QtWidgets, QtGui
from PySide2.QtWidgets import QFileDialog
from PySide2.QtCore import QSettings
from UnbrickVE9x import Ui_Form

from PyComUtils import Com_GetSerialPorts, Com_Speeds
from PyComPortThread import ComPortThread
from PyComPortConfigs import ComPortConfigs
from PyComPortConfigKeys import *
from pathlib import Path

runPath = str(Path().absolute())
saveFileName = runPath + '/settings.ini'
sGeomertyIniFile = runPath + '/geomerty.ini'

sBinFileName = runPath + '/FlashClearVE9x.bin'
# for debug
#sBinFileName = runPath + '/LED_Flasher_VC1.bin'

sGeometry = 'Geometry'
sWindowState = 'WindowState'


class pyWindowClass(QtWidgets.QWidget, Ui_Form):
    # Constructor
    def __init__(self):
        super().__init__()       
        # Setup UI and Show
        self.setupUi(self)
        self.setWindowTitle('Unbrick 1986VE9x MCU')
        
        # Vars
        self.comThread = ComPortThread(self.addLog, sBinFileName)
        # Widgets Init
        self.loadGeomerty()
        self.loadSettings(saveFileName)
        # Form Show
        self.show()
        self.showConnected()

        self.btConnect.clicked.connect(self.connect)
        self.btClear.clicked.connect(self.unbrick)

    def changeComPort(self, text):  
      self.comThread.comPort = text

    def closeEvent(self, event):
        self.comThread.stop()
        self.saveSettings(saveFileName)
        self.saveGeomerty()
        event.accept()

    def connect(self):
        if not self.comThread.started:
          self.comThread.start()
        else:
          self.comThread.stop()
        self.showConnected()

    def showConnected(self):
      if self.comThread.started:
        self.btStatus.setStyleSheet("background-color: green")
        self.btConnect.setText('Connected')
      else:
        self.btStatus.setStyleSheet("background-color: red")
        self.btConnect.setText('Press to Connect')

    
    def logClear(self):    
      self.txtLog.clear()     

    def loadSettings(self, fileName):
        cfg = ComPortConfigs(fileName)

        lastCom = ''       
        if sLastSettings in  cfg.config:
          values = cfg.config[sLastSettings]
          #Thread
          if sTimeoutRx in values:
            self.comThread.timeoutRx = float(values[sTimeoutRx])

        comList = Com_GetSerialPorts()
        self.cbxComSel.addItems(comList)        
        if lastCom in comList:
            self.cbxComSel.setEditText(lastCom)
        self.comThread.port = self.cbxComSel.currentText()

    def saveSettings(self, fileName):
        cfg = ComPortConfigs(fileName)

        cfg.config[sLastSettings] = { sPort: self.cbxComSel.currentText(),
                                      sTimeoutRx: str(self.comThread.timeoutRx),
                                    }
        cfg.saveToFile(fileName)  

    def saveGeomerty(self):
      settings = QSettings(sGeomertyIniFile, QSettings.IniFormat)
      settings.setValue(sGeometry, self.saveGeometry())

    def loadGeomerty(self):  
      settings = QSettings(sGeomertyIniFile, QSettings.IniFormat)
      self.restoreGeometry(settings.value(sGeometry))

    def addLog(self, text):
      self.txtLog.append(text)

    def unbrick(self):
      if not self.comThread.threadStarted:
        self.txtLog.clear()
      self.comThread.RunUnbrick()
