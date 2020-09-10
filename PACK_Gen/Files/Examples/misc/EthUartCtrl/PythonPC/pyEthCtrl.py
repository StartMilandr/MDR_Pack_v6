from PySide2 import QtWidgets, QtGui
from PySide2.QtGui import QTextCursor
from pyEthCtrl_ui import Ui_Form

from pyWidgetsUtils import *
#from pyWidgetsStyles import *
from pyEthRes import *
from pathlib import Path
from PyComPortThreadRD import ComPortThreadRD
from PySide2.QtCore import QSettings
from PyComPortConfigs import ComPortConfigs
from PyComPortConfigKeys import *
from PyComUtils import Com_GetSerialPorts, Com_Speeds
 
uiRegSel = 'cbxRegSel'
uiValue = 'edValue'
saveComFileName = str(Path().absolute()) + '\ComPort.ini'

class pyEthCtrlWindow(QtWidgets.QWidget, Ui_Form):
    # Constructor
    def __init__(self, parent=None):
        super(pyEthCtrlWindow, self).__init__(parent)       
        # Setup UI and Show
        self.setupUi(self)
        self.uiCbxRegSel = [self.cbxRegSel1, self.cbxRegSel2, self.cbxRegSel3, self.cbxRegSel4, self.cbxRegSel5,
                            self.cbxRegSel6, self.cbxRegSel7, self.cbxRegSel8, self.cbxRegSel9, self.cbxRegSel10]
        self.uiEdValue = [self.edValue1, self.edValue2, self.edValue3, self.edValue4, self.edValue5,
                          self.edValue6, self.edValue7, self.edValue8, self.edValue9, self.edValue10]
        self.uiBtSet = [self.btSet1, self.btSet2, self.btSet3, self.btSet4, self.btSet5,
                        self.btSet6, self.btSet7, self.btSet8, self.btSet9, self.btSet10]
        self.uiBtGet = [self.btGet1, self.btGet2, self.btGet3, self.btGet4, self.btGet5,
                        self.btGet6, self.btGet7, self.btGet8, self.btGet9, self.btGet10]

        regNames = VE1_RegsMAC_Phy.keys()
        for cbxRegSel in self.uiCbxRegSel:
            cbxRegSel.addItems(regNames)
        for btSet in self.uiBtSet:   
            btSet.clicked.connect(self.WriteReg) 
        for btGet in self.uiBtGet:   
            btGet.clicked.connect(self.ReadReg)

        self.btDebug1.setText('Read Info')
        self.btDebug1.clicked.connect(self.ReadInfo)
        self.btDebug2.setText('Read Frame')
        self.btDebug2.clicked.connect(self.ReadFrame)      

        self.lblWriteValue.setText('Write Hex Value')
        for edValue in self.uiEdValue:   
            edValue.setInputMask("HHHH")
            # hexValidr = QtGui.QRegExpValidator(QtCore.QRegExp("0x[0-9A-Fa-f]{1,8}"))    
            # edValue.setValidator(hexValidr)

        #self.setStyleSheet(tableWidgetPaddingOff)
        self.saveFileName = str(Path().absolute()) + '\Controls.ini'
        self.RestoreWindowAndWidgets()

        self.btConnect.clicked.connect(self.connect)
        self.cbxComSel.currentTextChanged.connect(self.changeComPort)
        self.cbxComBaud.currentTextChanged.connect(self.changeComBaud)
        self.btClearLog.clicked.connect(self.ClearLog) 

        self.comThread = ComPortThreadRD(self.showDataRx)
        self.showConnected()

        self.loadSettings(saveComFileName)        
        self.show()

    def closeEvent(self, event):
        self.SaveWindowAndWidgets()
        self.saveSettings(saveComFileName)
        self.comThread.stop()
        event.accept()
        
    def changeComPort(self, text):  
      self.comThread.comPort = text

    def changeComBaud(self, text):  
      self.comThread.baud = int(text)  

    def LogAddText(self, text):
      self.txtEdit.moveCursor(QTextCursor.End)
      self.txtEdit.insertPlainText(text)
      self.txtEdit.moveCursor(QTextCursor.End)

    def showDataRx(self, data):
      strg = data.decode("ascii")
      #print(data)
      #print(strg)
      if strg != None:
        #self.txtEdit.append(strg)
        self.LogAddText(strg)
      else:
        print(data)

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


    def SaveWindowAndWidgets(self):
        settings = QSettings(self.saveFileName, QSettings.IniFormat)
        WindowSaveGeometry(self, settings)
        for cbxRegSel in self.uiCbxRegSel:
            GuiSaveWidget(cbxRegSel, settings)
        for edValue in self.uiEdValue:
            GuiSaveWidget(edValue, settings)

    def RestoreWindowAndWidgets(self): 
        settings = QSettings(self.saveFileName, QSettings.IniFormat)
        WindowRestoreGeometry(self, settings)
        for cbxRegSel in self.uiCbxRegSel:
            GuiRestoreWidget(cbxRegSel, settings)
        for edValue in self.uiEdValue:
            GuiRestoreWidget(edValue, settings)

    def ClearLog(self):    
      self.txtEdit.clear()


    def GetBtnIndex(self, sender, ctrlList):
        for i in range(len(ctrlList)):
            if ctrlList[i] == sender:
                return i
        return None        

    def WriteReg(self):
        ind = self.GetBtnIndex(self.sender(), self.uiBtSet)
        if ind != None:
            regName = self.uiCbxRegSel[ind].currentText()
            #self.txtEdit.append('{0:10s}'.format(regName))
            self.LogAddText('{0:10s}'.format(regName))
            isPhyReg, addr = VE1_RegsMAC_Phy[regName]
            try:
                value = int(self.uiEdValue[ind].text(), 16)
                if isPhyReg == 1:
                    self.comThread.SendCmdWritePHY(addr, value)
                else:
                    self.comThread.SendCmdWriteMAC(addr, value)
            except Exception:
                print('Convertion error!')
        else:
            print('Wrong SetButton Index')    

    def ReadReg(self):
        ind = self.GetBtnIndex(self.sender(), self.uiBtGet)
        if ind != None:
            regName = self.uiCbxRegSel[ind].currentText()
            #self.txtEdit.append('{0:10s}'.format(regName))
            self.LogAddText('{0:10s}'.format(regName))
            isPhyReg, addr = VE1_RegsMAC_Phy[regName]            
            if isPhyReg == 1:
                self.comThread.SendCmdReadPHY(addr)
            else:
                self.comThread.SendCmdReadMAC(addr)
        else:
            print('Wrong GetButton Index')                

    def ReadInfo(self):
        self.comThread.SendCmdReadInfo()

    def ReadFrame(self):
        self.comThread.SendCmdReadFrame()
   
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

        # Gui Sel
        if sTimeoutRx in values:  
          lastCom = values[sPort]

        comList = Com_GetSerialPorts()
        self.cbxComSel.addItems(comList)
        if lastCom in comList:
            self.cbxComSel.setEditText(lastCom)
            self.comThread.port = lastCom
        elif len(comList) > 0:
          self.comThread.port = comList[0]

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
                                      }
        cfg.saveToFile(fileName)  


