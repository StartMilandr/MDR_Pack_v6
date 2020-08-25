from PySide2 import QtWidgets, QtGui, QtWidgets
from PySide2.QtWidgets import QFileDialog, QToolBar, QSizePolicy
from PySide2.QtCore import QSettings, Qt, QSize
from pyBasisMain_ui import Ui_MainWindow
from pyWidgetsUtils import WindowRestoreGeometry, WindowSaveGeometry

from pyBasisMAC import PyBasisWindowMAC
from pyBasisVLAN import PyBasisWindowVLAN
from pyBasisPort import PyBasisWindowPort
from pyBasisStats import PyBasisWindowStats
from pyBasisDebug import PyBasisWindowDebug
from pyWidgetsStyles import dockWidgetStyles

from PyComUtils import Com_GetSerialPorts, Com_Speeds
#from PyComPortThread import ComPortThread
#from PyComPortConfigs import ComPortConfigs
#from PyComPortConfigKeys import *
from pathlib import Path

from PyComPortConfigs import ComPortConfigs
from PyComPortConfigKeys import *

from PyComPortTransf import ComPortTransf
from KX028_CLI import KX028_CLI


runPath = str(Path().absolute())
#saveFileName = runPath + '/settings.ini'
#sGeomertyIniFile = runPath + '/geomerty.ini'
saveComFileName = runPath + '/saves/ComPort.ini'
#sSplitter = 'Splitter'

# uiData  = 'uiData'
# uiIsStr = 'uiIsStr'
# sSendUI = 'SendUI_'

#sGeometry = 'Geometry'
#sWindowState = 'WindowState'

sMaxMessageLen = 'MaxMessageLen'
#sCheckHash = 'sCheckHash'


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
        self.toolBarViews.addAction('Debug', self.CreateViewDebug)
        # Toolbars - Connect
        self.toolBarCom = self.addToolBar('Connect')

        self.cbxComSel = QtWidgets.QComboBox(self.toolBarCom)
        self.toolBarCom.addWidget(self.cbxComSel)
        self.cbxComSel.setObjectName(u"cbxComSel")
        self.cbxComSel.setMinimumSize(QSize(70, 24))
        self.cbxComSel.setMaximumSize(QSize(80, 16777215))
        self.cbxComSel.currentTextChanged.connect(self.changeComPort)

        self.cbxComBaud = QtWidgets.QComboBox(self.toolBarCom)
        self.cbxComBaud.setObjectName(u"cbxComBaud")        
        self.toolBarCom.addWidget(self.cbxComBaud)
        self.cbxComBaud.setMinimumSize(QSize(100, 24))
        self.cbxComBaud.setEditable(True)        
        self.cbxComBaud.currentTextChanged.connect(self.changeComBaud)

        self.btStatus = QtWidgets.QPushButton(self.toolBarCom)
        self.btStatus.setObjectName(u"btStatus")
        self.toolBarCom.addWidget(self.btStatus)
        sizePolicy = QSizePolicy(QSizePolicy.Fixed, QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(24)
        sizePolicy.setVerticalStretch(24)
        sizePolicy.setHeightForWidth(self.btStatus.sizePolicy().hasHeightForWidth())
        self.btStatus.setSizePolicy(sizePolicy)
        self.btStatus.setMinimumSize(QSize(24, 24))
        self.btStatus.setMaximumSize(QSize(24, 24))
        self.btStatus.setContextMenuPolicy(Qt.NoContextMenu)
        self.btStatus.setStyleSheet(u"")
        self.btStatus.setFlat(False)
        

        #self.actConnect = self.toolBarCom.addAction('Connect', self.ComConnect)
        self.btConnect = QtWidgets.QPushButton(self.toolBarCom)
        self.btConnect.setObjectName(u"btConnect")
        self.toolBarCom.addWidget(self.btConnect)        
        self.btConnect.setMinimumSize(QSize(80, 26))   
        self.btConnect.clicked.connect(self.ComConnect)     
        self.showConnected()

        # DockArea
        self.setDockNestingEnabled(False)
        self.setCorner(Qt.TopLeftCorner, Qt.LeftDockWidgetArea)
        self.setCorner(Qt.TopRightCorner, Qt.RightDockWidgetArea)
        self.setCorner(Qt.BottomLeftCorner, Qt.LeftDockWidgetArea)
        self.setCorner(Qt.BottomRightCorner, Qt.RightDockWidgetArea)
        # Central widget problem
        self.centralwidget.hide()
        #self.centralwidget.setMaximumSize(0, 0)

        self.saveFileName = str(Path().absolute()) + '/saves/Main.ini'
        settings = QSettings(self.saveFileName, QSettings.IniFormat)
        WindowRestoreGeometry(self, settings)
        self.loadSettings(saveComFileName)
        # Form Show
        self.show()

    def closeEvent(self, event):
      settings = QSettings(self.saveFileName, QSettings.IniFormat)
      WindowSaveGeometry(self, settings)
      self.saveSettings(saveComFileName)
      self.comTransf.stop()
      event.accept()

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
      window = PyBasisWindowPort(self)
      window.comCLI = self.comCLI
      self.addDockedWidget(window, "Ports", Qt.RightDockWidgetArea)

    def CreateViewStats(self):
      window = PyBasisWindowStats(self)
      window.AssighCLI(self.comCLI)
      self.addDockedWidget(window, "Table Statistics", Qt.RightDockWidgetArea)

    def CreateViewDebug(self):
      window = PyBasisWindowDebug(self)
      window.comCLI = self.comCLI
      self.addDockedWidget(window, "Debug", Qt.LeftDockWidgetArea)


    def ComConnect(self):
      if not self.comTransf.started:
        self.comTransf.start()
      else:
        self.comTransf.stop()
      self.showConnected()             

    def showConnected(self):
      if self.comTransf.started:
        self.btStatus.setStyleSheet("background-color: green")
        self.btConnect.setText('Connected')
      else:
        self.btStatus.setStyleSheet("background-color: red")
        self.btConnect.setText('Press to Connect')

    def changeComPort(self, text):  
      self.comTransf.portName = text

    def changeComBaud(self, text):  
      self.comTransf.baud = int(text)

    def loadSettings(self, fileName):
        cfg = ComPortConfigs(fileName)

        lastCom = ''       
        if sLastSettings in  cfg.config:
          values = cfg.config[sLastSettings]
          #Thread
          if sBaud in values:
            self.comTransf.baud = int(values[sBaud])
          if sTimeoutRx in values:
            self.comTransf.timeoutRx = float(values[sTimeoutRx])
          if sMaxMessageLen in values:  
            self.comTransf.maxMessageLen = int(values[sMaxMessageLen])

        # Gui Sel
        if sTimeoutRx in values:  
          lastCom = values[sPort]

        comList = Com_GetSerialPorts()
        self.cbxComSel.addItems(comList)
        if lastCom in comList:
            self.cbxComSel.setEditText(lastCom)
            self.comTransf.port = lastCom
        elif len(comList) > 0:
          self.comTransf.port = comList[0]

        if sBaudList in cfg.config:
          rates = cfg.config[sBaudList][sRates]
          self.cbxComBaud.addItems(rates.split())
        self.cbxComBaud.setEditText(str(self.comTransf.baud))

    def saveSettings(self, fileName):
        cfg = ComPortConfigs(fileName)
        cfg.config[sLastSettings] = { sPort: self.cbxComSel.currentText(),
                                      sBaud: self.cbxComBaud.currentText(),
                                      sTimeoutRx: str(self.comTransf.timeoutRx),
                                      sMaxMessageLen: str(self.comTransf.maxMessageLen),
                                      }
        cfg.saveToFile(fileName)  

