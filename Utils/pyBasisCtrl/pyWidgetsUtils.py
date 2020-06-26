from PySide2 import QtWidgets, QtGui, QtCore


def tableWidget_AddComboBox(tblWdg, rowInd, colInd, items, index):
    wdg = QtWidgets.QComboBox(tblWdg)
    wdg.addItems(items)
    wdg.setCurrentIndex(index)
    tblWdg.setCellWidget(rowInd, colInd, wdg)
    return wdg


def tableWidget_AddLineEdit_MAC(tblWdg, rowInd, colInd):
    wdg = QtWidgets.QLineEdit(tblWdg)
    wdg.setInputMask('HH:HH:HH:HH:HH:HH;_')
    tblWdg.setCellWidget(rowInd, colInd, wdg)
    return wdg

def tableWidget_AddLineEditValid(tblWdg, rowInd, colInd, validator):
    wdg = QtWidgets.QLineEdit(tblWdg)
    wdg.setValidator(validator)
    tblWdg.setCellWidget(rowInd, colInd, wdg)
    return wdg

def tableWidget_AddLineEdit_0x1FF(tblWdg, rowInd, colInd, strValue):
    hexValidr = QtGui.QRegExpValidator(QtCore.QRegExp("0x[1][0-9A-Fa-f]{1,2}"))
    wdg = tableWidget_AddLineEditValid(tblWdg, rowInd, colInd, hexValidr)
    wdg.setText(strValue)
    return wdg

def tableWidget_AddLineEdit_0x8FFF(tblWdg, rowInd, colInd, strValue):
    hexValidr = QtGui.QRegExpValidator(QtCore.QRegExp("0x[8][0-9A-Fa-f]{1,3}"))
    wdg = tableWidget_AddLineEditValid(tblWdg, rowInd, colInd, hexValidr)
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


def tableWidget_AddSpinBox(tblWdg, rowInd, colInd):
    wdg = QtWidgets.QSpinBox(tblWdg)
    tblWdg.setCellWidget(rowInd, colInd, wdg)    
    return wdg

def tableWidget_AddSpinBoxRange(tblWdg, rowInd, colInd, minVal, maxVal):
    wdg = tableWidget_AddSpinBox(tblWdg, rowInd, colInd)
    wdg.setMinimum(minVal)
    wdg.setMaximum(maxVal)
    return wdg


def tableWidget_PushButton(tblWdg, rowInd, colInd, caption):
    wdg = QtWidgets.QPushButton(tblWdg)
    wdg.setText(caption)
    tblWdg.setCellWidget(rowInd, colInd, wdg)
    return wdg    

def tableWidget_SetRowHeight(tblWdg, height):
    headerV = tblWdg.verticalHeader()
    headerV.setSectionResizeMode(QtWidgets.QHeaderView.Fixed)
    headerV.setDefaultSectionSize(height)