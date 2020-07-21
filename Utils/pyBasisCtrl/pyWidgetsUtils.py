from PySide2 import QtWidgets, QtGui, QtCore
import inspect
from distutils.util import strtobool

def tableWidget_AddComboBox(tblWdg, rowInd, colInd, items, index, name):
    wdg = QtWidgets.QComboBox(tblWdg)
    wdg.setObjectName(name)
    wdg.addItems(items)
    wdg.setCurrentIndex(index)
    tblWdg.setCellWidget(rowInd, colInd, wdg)
    return wdg


def tableWidget_AddLineEdit_MAC(tblWdg, rowInd, colInd, name):
    wdg = QtWidgets.QLineEdit(tblWdg)
    wdg.setObjectName(name)
    wdg.setInputMask('HH:HH:HH:HH:HH:HH;_')
    tblWdg.setCellWidget(rowInd, colInd, wdg)
    return wdg

def tableWidget_AddLineEditValid(tblWdg, rowInd, colInd, validator, name):
    wdg = QtWidgets.QLineEdit(tblWdg)
    wdg.setObjectName(name)
    wdg.setValidator(validator)
    tblWdg.setCellWidget(rowInd, colInd, wdg)
    return wdg

def tableWidget_AddLineEdit_0x1FF(tblWdg, rowInd, colInd, strValue, name):
    hexValidr = QtGui.QRegExpValidator(QtCore.QRegExp("0x[1][0-9A-Fa-f]{1,2}"))    
    wdg = tableWidget_AddLineEditValid(tblWdg, rowInd, colInd, hexValidr, name)
    wdg.setText(strValue)
    return wdg

def tableWidget_AddLineEdit_0x8FFF(tblWdg, rowInd, colInd, strValue, name):
    hexValidr = QtGui.QRegExpValidator(QtCore.QRegExp("0x[8][0-9A-Fa-f]{1,3}"))
    wdg = tableWidget_AddLineEditValid(tblWdg, rowInd, colInd, hexValidr, name)
    wdg.setText(strValue)
    return wdg

def tableWidget_AddItemCheck(tblWdg, rowInd, colInd, checked):
    item = QtWidgets.QTableWidgetItem('')
    if checked:
        item.setCheckState(QtCore.Qt.Checked)
    else:    
        item.setCheckState(QtCore.Qt.Unchecked)    
    tblWdg.setItem(rowInd, colInd, item)
    return item

def tableWidget_AddItemStr(tblWdg, rowInd, colInd, text):
    item = QtWidgets.QTableWidgetItem(text)
    tblWdg.setItem(rowInd, colInd, item)
    return item    


def tableWidget_AddSpinBox(tblWdg, rowInd, colInd, name):
    wdg = QtWidgets.QSpinBox(tblWdg)
    wdg.setObjectName(name)    
    tblWdg.setCellWidget(rowInd, colInd, wdg)    
    return wdg

def tableWidget_AddSpinBoxRange(tblWdg, rowInd, colInd, minVal, maxVal, name):
    wdg = tableWidget_AddSpinBox(tblWdg, rowInd, colInd, name)
    wdg.setMinimum(minVal)
    wdg.setMaximum(maxVal)
    return wdg


def tableWidget_AddPushButton(tblWdg, rowInd, colInd, caption, name):
    wdg = QtWidgets.QPushButton(tblWdg)
    wdg.setObjectName(name)
    wdg.setText(caption)
    tblWdg.setCellWidget(rowInd, colInd, wdg)
    return wdg    



def tableWidget_SetRowHeight(tblWdg, height):
    headerV = tblWdg.verticalHeader()
    headerV.setSectionResizeMode(QtWidgets.QHeaderView.Fixed)
    headerV.setDefaultSectionSize(height)


#---------  GetControls ----------
#def tableWidget_GetSpinBox(tblWdg, row, col):
#   tblWdg.item(rowInd, cCOL_ADD_MAC)
def printObj(obj):
  attrs = vars(obj)
  print(', '.join("%s: %s" % item for item in attrs.items()))





def WindowSaveGeometry(window, settings):
    settings.setValue('size', window.size())
    settings.setValue('pos', window.pos())

def WindowRestoreGeometry(window, settings):  
  window.resize(settings.value('size', QtCore.QSize(500, 500)))
  window.move(settings.value('pos', QtCore.QPoint(60, 60)))

def GuiSaveWidget(obj, settings):
      # if type(obj) is QComboBox:  # this works similar to isinstance, but missed some field... not sure why?
        if isinstance(obj, QtWidgets.QComboBox):
            name = obj.objectName()  # get combobox name
            index = obj.currentIndex()  # get current index from combobox
            text = obj.itemText(index)  # get the text for current index
            settings.setValue(name, text)  # save combobox selection to registry

        elif isinstance(obj, QtWidgets.QLineEdit):
            name = obj.objectName()
            value = obj.text()
            settings.setValue(name, value)  # save ui values, so they can be restored next time

        elif isinstance(obj, QtWidgets.QCheckBox):
            name = obj.objectName()
            state = obj.isChecked()
            settings.setValue(name, state)

        elif isinstance(obj, QtWidgets.QRadioButton):
            name = obj.objectName()
            value = obj.isChecked()  # get stored value from registry
            settings.setValue(name, value)

        elif isinstance(obj, QtWidgets.QSpinBox):
            name  = obj.objectName()
            value = obj.value()             # get stored value from registry
            settings.setValue(name, value)

        elif isinstance(obj, QtWidgets.QSlider):
            name  = obj.objectName()
            value = obj.value()             # get stored value from registry
            settings.setValue(name, value)            


def GuiRestoreWidget(obj, settings):        
        if isinstance(obj, QtWidgets.QComboBox):
            index = obj.currentIndex()  # get current region from combobox
            # text   = obj.itemText(index)   # get the text for new selected index
            name = obj.objectName()
            value = (settings.value(name))
            if value == None:
                return

            index = obj.findText(value)  # get the corresponding index for specified string in combobox
            if index == -1:  # add to list if not found
                obj.insertItems(0, [value])
                index = obj.findText(value)
                obj.setCurrentIndex(index)
            else:
                obj.setCurrentIndex(index)  # preselect a combobox value by index

        elif isinstance(obj, QtWidgets.QLineEdit):
            name = obj.objectName()
            value = settings.value(name)
            if value != None:
                #value = value.decode('utf-8')  # get stored value from registry
                obj.setText(value)  # restore lineEditFile

        elif isinstance(obj, QtWidgets.QCheckBox):
            name = obj.objectName()
            value = settings.value(name)  # get stored value from registry
            if value != None:
                obj.setChecked(strtobool(value))  # restore checkbox

        elif isinstance(obj, QtWidgets.QRadioButton):
            name = obj.objectName()
            value = settings.value(name)  # get stored value from registry
            if value != None:
                obj.setChecked(strtobool(value))

        elif isinstance(obj, QtWidgets.QSlider):
            name = obj.objectName()
            value = settings.value(name)    # get stored value from registry
            if value != None:           
                obj. setValue(int(value))   # restore value from registry

        elif isinstance(obj, QtWidgets.QSpinBox):
            name = obj.objectName()
            value = settings.value(name)    # get stored value from registry
            if value != None:
                obj. setValue(int(value))   # restore value from registry        


def GuiSaveCtrls(ui, settings):
    for (name, obj) in inspect.getmembers(ui):
        GuiSaveWidget(obj, settings)

def GuiRestoreCtrls(ui, settings):
    for name, obj in inspect.getmembers(ui):
        GuiRestoreWidget(obj, settings)


def tableWidget_SaveWidgets(tblWdg, settings):
    for i in range(tblWdg.rowCount()):
        for j in range(tblWdg.columnCount()):
            wgt = tblWdg.cellWidget(i, j)
            if wgt != None:
                GuiSaveWidget(wgt, settings)
            else:
                item = tblWdg.item(i, j)
                name = 'cell_{}_{}'.format(item.row(), item.column())
                settings.setValue(name, item.checkState() == QtCore.Qt.Checked)

def tableWidget_RestoreWidgets(tblWdg, settings):
    for i in range(tblWdg.rowCount()):
        for j in range(tblWdg.columnCount()):
            wgt = tblWdg.cellWidget(i, j)
            if wgt != None:
                GuiRestoreWidget(wgt, settings)
            else:
                item = tblWdg.item(i, j)
                name = 'cell_{}_{}'.format(item.row(), item.column())
                value = settings.value(name)    # get stored value from registry
                if value != None:
                    if strtobool(value):
                        item.setCheckState(QtCore.Qt.Checked)                
