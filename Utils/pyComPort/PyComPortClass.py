from PySide2 import QtWidgets, QtGui
from PySide2.QtWidgets import QFileDialog
from PySide2.QtCore import QSettings
from PyComPort_ui import Ui_Form
from PyComUtils import Com_GetSerialPorts, Com_Speeds
from PyComPortThread import ComPortThread
from PyComPortConfigs import ComPortConfigs
from PyComPortConfigKeys import *
from pathlib import Path

runPath = str(Path().absolute())
saveFileName = runPath + '/settings.ini'
sGeomertyIniFile = runPath + '/geomerty.ini'
sSplitter = 'Splitter'

uiData  = 'uiData'
uiIsStr = 'uiIsStr'
sSendUI = 'SendUI_'

sGeometry = 'Geometry'
sWindowState = 'WindowState'
sShowTx = 'ShowTx'
sConvRx = 'ConvRx'
sSelProtocol = 'SelProtocol'

sMaxMessageLen = 'MaxMessageLen'
sCheckHash = 'sCheckHash'

rxConvAsChar = 0
rxConvAsHex  = 1
rxConvAsInt  = 2


# sWidth = 'Width'
# sHeight = 'Length'
# sTop = 'Top'
# sLeft = 'Left'


class PyComPortForm(QtWidgets.QWidget, Ui_Form):
    # Constructor
    def __init__(self):
        super().__init__()       
        # Setup UI and Show
        self.setupUi(self)
        self.setWindowTitle('PyComPort Terminal')
        
        self.uiDict = {
          self.btSend1: {uiData: self.leSend1, uiIsStr: self.chbxSend1},
          self.btSend2: {uiData: self.leSend2, uiIsStr: self.chbxSend2},
          self.btSend3: {uiData: self.leSend3, uiIsStr: self.chbxSend3},
          self.btSend4: {uiData: self.leSend4, uiIsStr: self.chbxSend4},
          self.btSend5: {uiData: self.leSend5, uiIsStr: self.chbxSend5},
          self.btSend6: {uiData: self.leSend6, uiIsStr: self.chbxSend6},
          self.btSend7: {uiData: self.leSend7, uiIsStr: self.chbxSend7},
          self.btSend8: {uiData: self.leSend8, uiIsStr: self.chbxSend8},
        }

        # Vars
        self.comThread = ComPortThread(self.showDataRx)
        self.showTx = False
        self.convRx = rxConvAsChar
        # Widgets Init
        self.loadGeomerty()
        self.loadSettings(saveFileName)
        # Form Show
        self.show()
        self.showConnected()

        self.btConnect.clicked.connect(self.connect)
        self.btLogClear.clicked.connect(self.logClear)
        self.btLogSave.clicked.connect(self.saveLog)

        self.btSend1.clicked.connect(self.send)
        self.btSend2.clicked.connect(self.send)
        self.btSend3.clicked.connect(self.send)
        self.btSend4.clicked.connect(self.send)
        self.btSend5.clicked.connect(self.send)
        self.btSend6.clicked.connect(self.send)
        self.btSend7.clicked.connect(self.send)
        self.btSend8.clicked.connect(self.send)

        self.cbxProtocol.currentIndexChanged.connect(self.setProtocol)
        self.cbxConvRx.currentIndexChanged.connect(self.setConvRx)
        self.cbxComSel.currentTextChanged.connect(self.changeComPort)
        self.chbxLogTx.clicked.connect(self.switchLogTx)

    def setProtocol(self, index):
      self.comThread.setProtocol(index)

    def setConvRx(self, index):
      self.convRx = index

    def changeComPort(self, text):  
      self.comThread.comPort = text

    def showDataAsHex(self, data):
      logText = []
      for d in data:
        logText.append(hex(d))
      strr = ' '.join(logText)
      self.txtEdLog.append(strr)

    def showDataAsInt(self, data):
      logText = []
      for d in data:
        logText.append(str(d))
      strr = ' '.join(logText)
      self.txtEdLog.append(strr)

    def showDataAsChar(self, data):
      logText = []
      for d in data:
        logText.append(chr(d))
      strr = ''.join(logText)
      self.txtEdLog.append(strr)  

    def showDataRx(self, data):
      if self.convRx ==  rxConvAsHex:
        self.showDataAsHex(data)
      elif self.convRx ==  rxConvAsInt:
        self.showDataAsInt(data)
      else: # as char
        self.showDataAsChar(data)

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

    def send(self):        
        if self.comThread.started:
            button = self.sender()

            strData = self.uiDict[button][uiData].text()
            if len(strData) == 0:
              return
            isDataStr = self.uiDict[button][uiIsStr].isChecked()

            if isDataStr:
                values = strData.encode('ascii')
            else:
                atrArr = strData.split(' ')
                values = []
                for stri in atrArr:
                  if stri[0] != 'x':
                      values.append(int(stri))
                  else:
                      stri = '0'+ stri
                      values.append(int(stri, 16))

            if self.showTx:
              self.txtEdLog.setTextColor(QtGui.QColor('green'))
              self.txtEdLog.append('>   ' + str(values))
            self.comThread.send(values)
        else:    
            self.txtEdLog.setTextColor(QtGui.QColor('green'))
            self.txtEdLog.append('>   Send something wrong!')

        # New Line for Responce
        self.txtEdLog.setTextColor(QtGui.QColor('black'))

    def logClear(self):    
      self.txtEdLog.clear()

    def switchLogTx(self):  
      self.showTx = self.chbxLogTx.isChecked()

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
          if sSelProtocol in values:  
            self.comThread.setProtocol(int(values[sSelProtocol]))
            self.cbxProtocol.setCurrentIndex(self.comThread.selProtocol)
          if sCheckHash in values:  
            self.comThread.checkHash = values.getboolean(sCheckHash)
            if self.comThread.checkHash:
              print('CheckHash On')
          # Gui Sel
          if sTimeoutRx in values:  
            lastCom = values[sPort]
          if sShowTx in values:  
            self.showTx = values.getboolean(sShowTx)
            self.chbxLogTx.setChecked(self.showTx)
          if sConvRx in values:  
            self.convRx = int(values[sConvRx])
            self.cbxConvRx.setCurrentIndex(self.convRx)

        comList = Com_GetSerialPorts()
        self.cbxComSel.addItems(comList)        
        if lastCom in comList:
            self.cbxComSel.setEditText(lastCom)

        if sBaudList in cfg.config:
          rates = cfg.config[sBaudList][sRates]
          self.cbxComBaud.addItems(rates.split())
        self.cbxComBaud.setEditText(str(self.comThread.baud))

        i = 1
        for item in self.uiDict.values():
          sect = sSendUI  + str(i)
          if sect in cfg.config:
            if sData in cfg.config[sect]:
                item[uiData].setText(cfg.config[sect][sData])
            if sIsDataStr in cfg.config[sect]:  
                item[uiIsStr].setChecked(cfg.config[sect].getboolean(sIsDataStr))
          i += 1

        # if sGeometry in cfg.config:
        #   # size
        #   geometry = cfg.config[sGeometry]
        #   if sWidth in geometry:
        #     if sWidth in geometry:
        #       lSize = self.size()
        #       width = int(geometry[sWidth])  
        #       if width > lSize.width():
        #         lSize.setWidth(width)          
        #       height = int(geometry[sHeight])
        #       if height > lSize.height():
        #         lSize.setHeight(height)
        #       self.resize(lSize)
        #   # pos
        #   if sTop in geometry:
        #     if sLeft in geometry:
        #       lPos = self.pos()
        #       lTop = int(geometry[sTop])
        #       if lTop > 0:
        #         lPos.setY(lTop)
        #       lLeft = int(geometry[sLeft])
        #       if lLeft > 0:
        #         lPos.setX(lLeft)
        #       self.move(lPos)  

    def saveSettings(self, fileName):
        cfg = ComPortConfigs(fileName)

        cfg.config[sLastSettings] = { sPort: self.cbxComSel.currentText(),
                                      sBaud: self.cbxComBaud.currentText(),
                                      sTimeoutRx: str(self.comThread.timeoutRx),
                                      sShowTx: str(self.showTx),
                                      sConvRx: str(self.convRx),
                                      sMaxMessageLen: str(self.comThread.maxMessageLen),
                                      sSelProtocol: str(self.comThread.selProtocol),
                                      sCheckHash: str(self.comThread.checkHash),
                                      }

        i = 1
        for item in self.uiDict.values():
          strData = item[uiData].text()
          isDataStr = str(item[uiIsStr].isChecked())
          sect = sSendUI  + str(i)          
          cfg.config[sect] = {sData: strData, sIsDataStr: isDataStr } 
          i += 1                  

        # cfg.config[sGeometry] = {sWidth: str(self.size().width()), 
        #                          sHeight: str(self.size().height()),
        #                          sTop:    str(self.pos().y()),
        #                          sLeft:   str(self.pos().x())}

        cfg.saveToFile(fileName)  

    def saveLog(self):
        #defDir = self._settings.dirExport + '/Logs'
        fileName, fileFilter = QFileDialog.getSaveFileName(self, "Save Log to File", runPath + '/Logs', "Text (*.txt)")
        if len(fileName) > 0:
          with open(fileName, 'w') as logFile:
            logFile.write(str(self.txtEdLog.toPlainText()))

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


