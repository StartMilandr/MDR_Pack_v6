from PySide2 import QtWidgets, QtGui
from PySide2.QtCore import QSettings
from PyComTransf_ui import Ui_Form
from PyComUtils import Com_GetSerialPorts, Com_Speeds
from PyComPortThread import *
from PyComPortConfigs import ComPortConfigs
from PyComPortConfigKeys import *
from pathlib import Path
from PyTransfTest import TransfTest
import time

runPath = str(Path().absolute())
saveFileName = runPath + '/settings.ini'
sGeomertyIniFile = runPath + '/geomerty.ini'
sSplitter = 'Splitter'

uiData  = 'uiData'
uiIsStr = 'uiIsStr'
sSendUI = 'SendUI_'

sGeometry = 'Geometry'
sWindowState = 'WindowState'
# sSelProtocol = 'SelProtocol'

sMaxMessageLen = 'MaxMessageLen'
sCheckHash = 'sCheckHash'

cMaxMessLen = 128

class ComPortTransf(QtWidgets.QWidget, Ui_Form):
    # Constructor
    def __init__(self):
        super().__init__()       
        # Setup UI and Show
        self.setupUi(self)
        self.setWindowTitle('PyComPort Transfer Test')
        
        # Vars
        self.comThread = ComPortThread(self.receiveComData)
        self.comThread.selProtocol = selProtHdrLen
        # Widgets Init
        self.loadGeomerty()
        self.loadSettings(saveFileName)

        self.transfTest = TransfTest(cMaxMessLen, self.comThread.send, self.testUpdateStats)
        # Form Show
        self.show()
        self.showConnected()

        self.btConnect.clicked.connect(self.connect)
        self.btLogClear.clicked.connect(self.logClear)
        self.btTestStart.clicked.connect(self.testStartStop)        
        self.cbxComSel.currentTextChanged.connect(self.changeComPort)

    def receiveComData(self, dataRx):
      self.transfTest.dataReceived(dataRx)

    def testStartStop(self):        
        if self.comThread.started:
          if self.btTestStart.isChecked():
            # StartTest
            self.btTestStart.setText('Executing...')
            self.txtEdLog.append('Test Started: {}'.format(time.ctime()))
            self.transfTest.start()
          else:  
            # StopTest
            self.btTestStart.setText('Start Test')
            self.txtEdLog.append('Test Started: {}'.format(time.ctime()))            
            self.transfTest.stop()
            #show result
            self.lbCycles.setText('Cycles: {}'.format(self.transfTest.CyclesCount))
            self.lbTranstCount.setText('SentCount: {}'.format(self.transfTest.SentCount))
            self.lbErrCount.setText('ErrorCount: {}'.format(self.transfTest.DataError))

            #self.comThread.send(values)
        else:    
            self.btTestStart.setChecked(False)
            self.txtEdLog.append('Please, Open COM port first!')

    def testUpdateStats(self):
      self.lbCycles.setText('Cycles: {}'.format(self.transfTest.CyclesCount))
      self.lbTranstCount.setText('SentCount: {}'.format(self.transfTest.SentCount))
      self.lbErrCount.setText('ErrorCount: {}'.format(self.transfTest.DataError))
     

    def changeComPort(self, text):  
      self.comThread.comPort = text

    def showDataAsHex(self, data):
      logText = []
      for d in data:
        logText.append(hex(d))
      strr = ' '.join(logText)
      self.txtEdLog.append(strr)

    def closeEvent(self, event):
        self.transfTest.stop()
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
      self.txtEdLog.clear()

    def loadSettings(self, fileName):
        cfg = ComPortConfigs(fileName)

        lastCom = ''       
        if sLastSettings in  cfg.config:
          values = cfg.config[sLastSettings]
          #Thread
          if sBaud in values:
            self.comThread.baud = int(values[sBaud])
          if sTimeoutRx in values:
            self.comThread.timeoutRx = float(values[sTimeoutRx])
          if sMaxMessageLen in values:  
            self.comThread.maxMessageLen = int(values[sMaxMessageLen])
          # if sSelProtocol in values:  
          #   self.comThread.setProtocol(int(values[sSelProtocol]))
          if sCheckHash in values:  
            self.comThread.checkHash = values.getboolean(sCheckHash)
            if self.comThread.checkHash:
              print('CheckHash On')
          # Gui Sel
          if sTimeoutRx in values:  
            lastCom = values[sPort]

        comList = Com_GetSerialPorts()
        self.cbxComSel.addItems(comList)        
        if lastCom in comList:
            self.cbxComSel.setEditText(lastCom)

        if sBaudList in cfg.config:
          rates = cfg.config[sBaudList][sRates]
          self.cbxComBaud.addItems(rates.split())
        self.cbxComBaud.setEditText(str(self.comThread.baud))

    def saveSettings(self, fileName):
        cfg = ComPortConfigs(fileName)

        cfg.config[sLastSettings] = { sPort: self.cbxComSel.currentText(),
                                      sBaud: self.cbxComBaud.currentText(),
                                      sTimeoutRx: str(self.comThread.timeoutRx),
                                      sMaxMessageLen: str(self.comThread.maxMessageLen),
                                      # sSelProtocol: str(self.comThread.selProtocol),
                                      sCheckHash: str(self.comThread.checkHash),
                                      }

        cfg.saveToFile(fileName)  

    def saveGeomerty(self):
      settings = QSettings(sGeomertyIniFile, QSettings.IniFormat)
      settings.setValue(sGeometry, self.saveGeometry())
      settings.setValue(sSplitter, self.splitter.saveState()) 

    def loadGeomerty(self):  
      settings = QSettings(sGeomertyIniFile, QSettings.IniFormat)
      self.restoreGeometry(settings.value(sGeometry))
      splitterSettings=settings.value(sSplitter)
      if splitterSettings:
        self.splitter.restoreState(splitterSettings)


