from PySide2 import QtWidgets, QtGui
from pyBasisDebug_ui import Ui_Form
from pyWidgetsUtils import *
from pyWidgetsStyles import *
from pyBasisRes import *
from pathlib import Path
from PySide2.QtCore import QSettings
 

uiRegSel = 'cbxRegSel'
uiValue = 'edValue'

class PyBasisWindowDebug(QtWidgets.QWidget, Ui_Form):
    # Constructor
    def __init__(self, parent=None):
        super(PyBasisWindowDebug, self).__init__(parent)       
        # Setup UI and Show
        self.setupUi(self)
        #Tables
        #self.setStyleSheet(comboBoxStyles + comboBoxStyles_DropDown_SpinW + lineEditStyles + spinBoxStyles)

        self.uiCbxRegSel = [self.cbxRegSel1, self.cbxRegSel2, self.cbxRegSel3, self.cbxRegSel4, self.cbxRegSel5,
                            self.cbxRegSel6, self.cbxRegSel7, self.cbxRegSel8, self.cbxRegSel9, self.cbxRegSel10]
        self.uiEdValue = [self.edValue1, self.edValue2, self.edValue3, self.edValue4, self.edValue5,
                          self.edValue6, self.edValue7, self.edValue8, self.edValue9, self.edValue10]
        self.uiBtSet = [self.btSet1, self.btSet2, self.btSet3, self.btSet4, self.btSet5,
                        self.btSet6, self.btSet7, self.btSet8, self.btSet9, self.btSet10]
        self.uiBtGet = [self.btGet1, self.btGet2, self.btGet3, self.btGet4, self.btGet5,
                        self.btGet6, self.btGet7, self.btGet8, self.btGet9, self.btGet10]

        regNames = kxo28_RegsAXI.keys()
        for cbxRegSel in self.uiCbxRegSel:
            cbxRegSel.addItems(regNames)
        for btSet in self.uiBtSet:   
            btSet.clicked.connect(self.WriteReg) 
        for btGet in self.uiBtGet:   
            btGet.clicked.connect(self.ReadReg)

        self.btDebug1.setText('EGPI Regs')
        self.btDebug1.clicked.connect(self.ReadEGPI)
        self.btDebug2.setText('CLASS Regs')
        self.btDebug2.clicked.connect(self.ReadCLASS)
        self.btDebug3.setText('EMAC Regs')
        self.btDebug3.clicked.connect(self.ReadEMAC)
        

        self.lblWriteValue.setText('Write Hex Value')
        for edValue in self.uiEdValue:   
            edValue.setInputMask("HHHHHHHH")
            # hexValidr = QtGui.QRegExpValidator(QtCore.QRegExp("0x[0-9A-Fa-f]{1,8}"))    
            # edValue.setValidator(hexValidr)


        #self.setStyleSheet(tableWidgetPaddingOff)
        self.comCLI = None
        self.saveFileName = str(Path().absolute()) + '/saves/Debug.ini'
        self.RestoreWidgets()
        self.btClearLog.clicked.connect(self.ClearLog) 

        
    def __del__(self):
        self.SaveWidgets()

    def ClearLog(self):    
      self.txtEdit.clear()

    def SaveWidgets(self):
        settings = QSettings(self.saveFileName, QSettings.IniFormat)
        for cbxRegSel in self.uiCbxRegSel:
            GuiSaveWidget(cbxRegSel, settings)
        for edValue in self.uiEdValue:
            GuiSaveWidget(edValue, settings)

    def RestoreWidgets(self): 
        settings = QSettings(self.saveFileName, QSettings.IniFormat)
        for cbxRegSel in self.uiCbxRegSel:
            GuiRestoreWidget(cbxRegSel, settings)
        for edValue in self.uiEdValue:
            GuiRestoreWidget(edValue, settings)

    def GetBtnIndex(self, sender, ctrlList):
        for i in range(len(ctrlList)):
            if ctrlList[i] == sender:
                return i
        return None        

    def WriteReg(self):
        ind = self.GetBtnIndex(self.sender(), self.uiBtSet)
        if ind != None:
            regName = self.uiCbxRegSel[ind].currentText()
            addr = int(kxo28_RegsAXI[regName])
            try:
                value = int(self.uiEdValue[ind].text(), 16)
                self.comCLI.writeAxiRegList([addr], [value])
                self.txtEdit.append('{}({}) = {}'.format(regName, hex(addr), hex(value)))
            except Exception:
                print('Convertion error!')
        else:
            print('Wrong SetButton Index')    

    def ReadReg(self):
        ind = self.GetBtnIndex(self.sender(), self.uiBtGet)
        if ind != None:
            regName = self.uiCbxRegSel[ind].currentText()
            addr = int(kxo28_RegsAXI[regName])
            self.ReadRegAndShow(regName, addr)
        else:
            print('Wrong GetButton Index')                

    def ReadRegAndShow(self, regName, addr):
        try:
            values = self.comCLI.readAxiRegList([addr])
            if len(values) > 0:
                self.txtEdit.append('{0:30s}({1:8s}): {2:10s}'.format(regName, hex(addr), hex(values[0])))
                #self.txtEdit.append('{}: {}({})'.format(hex(values[0]), regName, hex(addr)))
            else:
                print('readAxiRegList empty')
        except Exception:
            print('Convertion error!')

    def ReadEGPI(self):
        self.ReadRegsEGPI(EGPI2)
        self.ReadRegsEGPI(EGPI3)
        self.ReadRegsEGPI(EGPI4)
        self.ReadRegsEGPI(EGPI7)
        self.ReadRegsEGPI(HGPI)

    def ReadRegsEGPI(self, indEGPI):
        baseAddr = kxo28_Addr_GPI[indEGPI]
        self.txtEdit.append('   EGPI_{} Registers:'.format(indEGPI + 1))
        for regName, addr in kxo28_RegsOffs_GPI.items():
            addr += baseAddr
            self.ReadRegAndShow(regName, addr)

    def ReadEMAC(self):
        self.ReadRegsEMAC(EGPI2)
        self.ReadRegsEMAC(EGPI3)
        self.ReadRegsEMAC(EGPI4)
        self.ReadRegsEMAC(EGPI7)
        #self.ReadRegsEMAC(HGPI)

    def ReadRegsEMAC(self, indEMAC):
        baseAddr = kx028_EmacAdr[indEMAC]
        self.txtEdit.append('   EMAC_{} Registers:'.format(indEMAC + 1))
        for regName, addr in kxo28_RegsOffs_EMAC.items():
            addr += baseAddr
            self.ReadRegAndShow(regName, addr)        

    def ReadCLASS(self):
        self.ReadRegsCLASS(0)
        self.ReadRegsCLASS(1)

    def ReadRegsCLASS(self, ind):
        baseAddr = kxo28_Addr_CLASS[ind]
        self.txtEdit.append('   SLASSIFICATOR_{} Registers:'.format(ind))
        for regName, addr in kxo28_RegsOffs_CLASS.items():
            addr += baseAddr
            self.ReadRegAndShow(regName, addr)            

