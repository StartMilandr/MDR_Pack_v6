from PySide2 import QtWidgets, QtGui, QtWidgets
from PySide2.QtWidgets import QFileDialog, QToolBar
from PySide2.QtCore import QSettings, Qt
from pyBasisMain_ui import Ui_MainWindow

from pyBasisMAC import PyBasisWindowMAC
from pyBasisVLAN import PyBasisWindowVLAN
from pyBasisPort import PyBasisWindowPort
from pyBasisStats import PyBasisWindowStats
from pyWidgetsStyles import dockWidgetStyles

from PyComUtils import Com_GetSerialPorts, Com_Speeds
#from PyComPortThread import ComPortThread
#from PyComPortConfigs import ComPortConfigs
#from PyComPortConfigKeys import *
from pathlib import Path

from PyComPortTransf import ComPortTransf
from KX028_CLI import KX028_CLI


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

# sPort = 'Port'
# sData = 'Data'
# sIsDataStr = 'IsDataStr'
# sBaud = 'Baud'
# sBaudList = 'BaudList'
# sRates = 'Rates'
# sLastSettings = 'LastSettings'
# sTimeoutRx = 'TimeoutRx'

# sWidth = 'Width'
# sHeight = 'Length'
# sTop = 'Top'
# sLeft = 'Left'


class PyBasisMainForm(QtWidgets.QMainWindow, Ui_MainWindow):
    # Constructor
    def __init__(self):
        super().__init__()       
        # Setup UI and Show
        self.setupUi(self)
        #Forms
        self.formsMAC = list()
        self.comTransf = ComPortTransf()
        self.comCLI = KX028_CLI(self.comTransf)

        self.setStyleSheet(dockWidgetStyles)
        # Toolbars - Forms
        self.toolBarViews = self.addToolBar('Views')
        self.toolBarViews.addAction('MAC Table', self.CreateViewMAC)
        self.toolBarViews.addAction('VLAN Table', self.CreateViewVLAN)
        self.toolBarViews.addAction('Ports', self.CreateViewPort)
        self.toolBarViews.addAction('Statistics', self.CreateViewStats)
        # Toolbars - Connect
        self.toolBarCom = self.addToolBar('Connect')
        self.actConnect = self.toolBarCom.addAction('Connect', self.ComConnect)
        # DockArea
        self.setDockNestingEnabled(False)
        self.setCorner(Qt.TopLeftCorner, Qt.LeftDockWidgetArea)
        self.setCorner(Qt.TopRightCorner, Qt.RightDockWidgetArea)
        self.setCorner(Qt.BottomLeftCorner, Qt.LeftDockWidgetArea)
        self.setCorner(Qt.BottomRightCorner, Qt.RightDockWidgetArea)
        # Central widget problem
        self.centralwidget.hide()
        #self.centralwidget.setMaximumSize(0, 0)

        # self.addFormMac = QtGui.QAction(self)
        # self.addFormMac.setObjectName("actAddMAC")
        # self.addFormMac.setText('Add MAC')
        # self.toolBar.addAction(self.addFormMac)
        
        # Vars
        # self.comThread = ComPortThread(self.showDataRx)
        # self.showTx = False
        # self.convRx = rxConvAsChar
        # Widgets Init
        #self.loadGeomerty()
        #self.loadSettings(saveFileName)

        # Form Show
        self.show()
        #self.showConnected()
    
    def centralHack1(self):
      secMainWin = QtWidgets.QMainWindow(self)
      secMainWin.setCentralWidget(QtWidgets.QTextEdit(secMainWin))
      secMainWin.setWindowFlag(Qt.Widget)
      self.setCentralWidget(secMainWin)

    def addDockedWidget(self, wigdet, name, dockPlace):
      dockArea = QtWidgets.QDockWidget(name, self)
      dockArea.setAllowedAreas(Qt.LeftDockWidgetArea | Qt.RightDockWidgetArea | Qt.TopDockWidgetArea | Qt.BottomDockWidgetArea)
      dockArea.setWidget(wigdet)
      dockArea.setFloating(False)
      self.addDockWidget(dockPlace, dockArea)
      wigdet.show()

    def CreateViewMAC(self):
      window = PyBasisWindowMAC(self)
      window.comCLI = self.comCLI
      self.addDockedWidget(window, "Table MAC", Qt.LeftDockWidgetArea)
      
    def CreateViewVLAN(self):
      window = PyBasisWindowVLAN(self)
      window.comCLI = self.comCLI
      self.addDockedWidget(window, "Table VLAN", Qt.LeftDockWidgetArea)

    def CreateViewPort(self):
      self.addDockedWidget(PyBasisWindowPort(self), "Ports", Qt.RightDockWidgetArea)

    def CreateViewStats(self):
      window = PyBasisWindowStats(self)
      window.AssighCLI(self.comCLI)
      self.addDockedWidget(window, "Table Statistics", Qt.RightDockWidgetArea)

    def CreateViewStatistic(self):
      print('Create Statistics')

    def ComConnect(self):
      if not self.comTransf.started:
        self.comTransf.start()
      else:
        self.comTransf.stop()
      self.showConnected()             

    def showConnected(self):
      if self.comTransf.started:
        #self.btStatus.setStyleSheet("background-color: green")
        self.actConnect.setText('Connected')
      else:
        #self.btStatus.setStyleSheet("background-color: red")
        self.actConnect.setText('Press to Connect')

    #def changeComPort(self, text):  
      #self.comThread.comPort = text

    def closeEvent(self, event):
      #self.comThread.stop()
      #self.saveSettings(saveFileName)
      #self.saveGeomerty()
      self.comTransf.stop()
      event.accept()



    #def showDataRx(self, data):      
      # if self.convRx ==  rxConvAsHex:
      #   self.showDataAsHex(data)
      # elif self.convRx ==  rxConvAsInt:
      #   self.showDataAsInt(data)
      # else: # as char
      #   self.showDataAsChar(data)

    # def connect(self):
    #     if not self.comThread.started:
    #       self.comThread.start()
    #     else:
    #       self.comThread.stop()
    #     self.showConnected()

    # def showConnected(self):
    #   if self.comThread.started:
    #     self.btStatus.setStyleSheet("background-color: green")
    #     self.btConnect.setText('Connected')
    #   else:
    #     self.btStatus.setStyleSheet("background-color: red")
    #     self.btConnect.setText('Press to Connect')



    # def loadSettings(self, fileName):
    #     cfg = ComPortConfigs(fileName)

    #     lastCom = ''       
    #     if sLastSettings in  cfg.config:
    #       values = cfg.config[sLastSettings]
    #       #Thread
    #       if sBaud in values:
    #         self.comThread.baud = int(values[sBaud])
    #       if sTimeoutRx in values:
    #         self.comThread.timeoutRx = float(values[sTimeoutRx])
    #       if sMaxMessageLen in values:  
    #         self.comThread.maxMessageLen = int(values[sMaxMessageLen])
    #       if sSelProtocol in values:  
    #         self.comThread.setProtocol(int(values[sSelProtocol]))
    #         self.cbxProtocol.setCurrentIndex(self.comThread.selProtocol)
    #       if sCheckHash in values:  
    #         self.comThread.checkHash = values.getboolean(sCheckHash)
    #         if self.comThread.checkHash:
    #           print('CheckHash On')
    #       # Gui Sel
    #       if sTimeoutRx in values:  
    #         lastCom = values[sPort]
    #       if sShowTx in values:  
    #         self.showTx = values.getboolean(sShowTx)
    #         self.chbxLogTx.setChecked(self.showTx)
    #       if sConvRx in values:  
    #         self.convRx = int(values[sConvRx])
    #         self.cbxConvRx.setCurrentIndex(self.convRx)

    #     comList = Com_GetSerialPorts()
    #     self.cbxComSel.addItems(comList)        
    #     if lastCom in comList:
    #         self.cbxComSel.setEditText(lastCom)

    #     if sBaudList in cfg.config:
    #       rates = cfg.config[sBaudList][sRates]
    #       self.cbxComBaud.addItems(rates.split())
    #     self.cbxComBaud.setEditText(str(self.comThread.baud))



    # def saveSettings(self, fileName):
    #     cfg = ComPortConfigs(fileName)

    #     cfg.config[sLastSettings] = { sPort: self.cbxComSel.currentText(),
    #                                   sBaud: self.cbxComBaud.currentText(),
    #                                   sTimeoutRx: str(self.comThread.timeoutRx),
    #                                   sShowTx: str(self.showTx),
    #                                   sConvRx: str(self.convRx),
    #                                   sMaxMessageLen: str(self.comThread.maxMessageLen),
    #                                   sSelProtocol: str(self.comThread.selProtocol),
    #                                   sCheckHash: str(self.comThread.checkHash),
    #                                   }


    #     cfg.saveToFile(fileName)  

    # def saveGeomerty(self):
    #   settings = QSettings(sGeomertyIniFile, QSettings.IniFormat)
    #   settings.setValue(sGeometry, self.saveGeometry())
    #   settings.setValue(sSplitter, self.splitter.saveState()) 

    # def loadGeomerty(self):  
    #   settings = QSettings(sGeomertyIniFile, QSettings.IniFormat)
    #   self.restoreGeometry(settings.value(sGeometry))
    #   splitterSettings=settings.value(sSplitter)
    #   if splitterSettings:
    #     self.splitter.restoreState(splitterSettings)


