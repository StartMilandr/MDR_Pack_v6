# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'pyBasisStats.ui'
##
## Created by: Qt User Interface Compiler version 5.15.0
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide2.QtCore import (QCoreApplication, QDate, QDateTime, QMetaObject,
    QObject, QPoint, QRect, QSize, QTime, QUrl, Qt)
from PySide2.QtGui import (QBrush, QColor, QConicalGradient, QCursor, QFont,
    QFontDatabase, QIcon, QKeySequence, QLinearGradient, QPalette, QPainter,
    QPixmap, QRadialGradient)
from PySide2.QtWidgets import *


class Ui_Form(object):
    def setupUi(self, Form):
        if not Form.objectName():
            Form.setObjectName(u"Form")
        Form.resize(442, 850)
        self.verticalLayout_4 = QVBoxLayout(Form)
        self.verticalLayout_4.setObjectName(u"verticalLayout_4")
        self.grbxCtrl = QGroupBox(Form)
        self.grbxCtrl.setObjectName(u"grbxCtrl")
        self.horizontalLayout_3 = QHBoxLayout(self.grbxCtrl)
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.btClearAll = QPushButton(self.grbxCtrl)
        self.btClearAll.setObjectName(u"btClearAll")
        self.btClearAll.setMinimumSize(QSize(0, 26))

        self.horizontalLayout_3.addWidget(self.btClearAll)


        self.verticalLayout_4.addWidget(self.grbxCtrl)

        self.splitter_2 = QSplitter(Form)
        self.splitter_2.setObjectName(u"splitter_2")
        self.splitter_2.setOrientation(Qt.Vertical)
        self.grbxPort = QGroupBox(self.splitter_2)
        self.grbxPort.setObjectName(u"grbxPort")
        self.verticalLayout_3 = QVBoxLayout(self.grbxPort)
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.splitter = QSplitter(self.grbxPort)
        self.splitter.setObjectName(u"splitter")
        self.splitter.setOrientation(Qt.Vertical)
        self.widget = QWidget(self.splitter)
        self.widget.setObjectName(u"widget")
        self.verticalLayout = QVBoxLayout(self.widget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.cbxPortSel = QComboBox(self.widget)
        self.cbxPortSel.addItem("")
        self.cbxPortSel.addItem("")
        self.cbxPortSel.addItem("")
        self.cbxPortSel.addItem("")
        self.cbxPortSel.setObjectName(u"cbxPortSel")
        sizePolicy = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.cbxPortSel.sizePolicy().hasHeightForWidth())
        self.cbxPortSel.setSizePolicy(sizePolicy)
        self.cbxPortSel.setMinimumSize(QSize(0, 24))

        self.horizontalLayout.addWidget(self.cbxPortSel)

        self.btPortClear = QPushButton(self.widget)
        self.btPortClear.setObjectName(u"btPortClear")
        sizePolicy1 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Fixed)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.btPortClear.sizePolicy().hasHeightForWidth())
        self.btPortClear.setSizePolicy(sizePolicy1)
        self.btPortClear.setMinimumSize(QSize(0, 26))

        self.horizontalLayout.addWidget(self.btPortClear)

        self.btPortRead = QPushButton(self.widget)
        self.btPortRead.setObjectName(u"btPortRead")
        sizePolicy.setHeightForWidth(self.btPortRead.sizePolicy().hasHeightForWidth())
        self.btPortRead.setSizePolicy(sizePolicy)
        self.btPortRead.setMinimumSize(QSize(0, 26))

        self.horizontalLayout.addWidget(self.btPortRead)


        self.verticalLayout.addLayout(self.horizontalLayout)

        self.tblPortStat = QTableWidget(self.widget)
        if (self.tblPortStat.columnCount() < 2):
            self.tblPortStat.setColumnCount(2)
        __qtablewidgetitem = QTableWidgetItem()
        self.tblPortStat.setHorizontalHeaderItem(0, __qtablewidgetitem)
        __qtablewidgetitem1 = QTableWidgetItem()
        self.tblPortStat.setHorizontalHeaderItem(1, __qtablewidgetitem1)
        if (self.tblPortStat.rowCount() < 11):
            self.tblPortStat.setRowCount(11)
        __qtablewidgetitem2 = QTableWidgetItem()
        self.tblPortStat.setVerticalHeaderItem(0, __qtablewidgetitem2)
        __qtablewidgetitem3 = QTableWidgetItem()
        self.tblPortStat.setVerticalHeaderItem(1, __qtablewidgetitem3)
        __qtablewidgetitem4 = QTableWidgetItem()
        self.tblPortStat.setVerticalHeaderItem(2, __qtablewidgetitem4)
        __qtablewidgetitem5 = QTableWidgetItem()
        self.tblPortStat.setVerticalHeaderItem(3, __qtablewidgetitem5)
        __qtablewidgetitem6 = QTableWidgetItem()
        self.tblPortStat.setVerticalHeaderItem(4, __qtablewidgetitem6)
        __qtablewidgetitem7 = QTableWidgetItem()
        self.tblPortStat.setVerticalHeaderItem(5, __qtablewidgetitem7)
        __qtablewidgetitem8 = QTableWidgetItem()
        self.tblPortStat.setVerticalHeaderItem(6, __qtablewidgetitem8)
        __qtablewidgetitem9 = QTableWidgetItem()
        self.tblPortStat.setVerticalHeaderItem(7, __qtablewidgetitem9)
        __qtablewidgetitem10 = QTableWidgetItem()
        self.tblPortStat.setVerticalHeaderItem(8, __qtablewidgetitem10)
        __qtablewidgetitem11 = QTableWidgetItem()
        self.tblPortStat.setVerticalHeaderItem(9, __qtablewidgetitem11)
        __qtablewidgetitem12 = QTableWidgetItem()
        self.tblPortStat.setVerticalHeaderItem(10, __qtablewidgetitem12)
        self.tblPortStat.setObjectName(u"tblPortStat")
        self.tblPortStat.horizontalHeader().setStretchLastSection(True)

        self.verticalLayout.addWidget(self.tblPortStat)

        self.splitter.addWidget(self.widget)
        self.widget1 = QWidget(self.splitter)
        self.widget1.setObjectName(u"widget1")
        self.horizontalLayout_4 = QHBoxLayout(self.widget1)
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.horizontalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.tblPortTx = QTableWidget(self.widget1)
        if (self.tblPortTx.columnCount() < 1):
            self.tblPortTx.setColumnCount(1)
        __qtablewidgetitem13 = QTableWidgetItem()
        self.tblPortTx.setHorizontalHeaderItem(0, __qtablewidgetitem13)
        if (self.tblPortTx.rowCount() < 6):
            self.tblPortTx.setRowCount(6)
        __qtablewidgetitem14 = QTableWidgetItem()
        self.tblPortTx.setVerticalHeaderItem(0, __qtablewidgetitem14)
        __qtablewidgetitem15 = QTableWidgetItem()
        self.tblPortTx.setVerticalHeaderItem(1, __qtablewidgetitem15)
        __qtablewidgetitem16 = QTableWidgetItem()
        self.tblPortTx.setVerticalHeaderItem(2, __qtablewidgetitem16)
        __qtablewidgetitem17 = QTableWidgetItem()
        self.tblPortTx.setVerticalHeaderItem(3, __qtablewidgetitem17)
        __qtablewidgetitem18 = QTableWidgetItem()
        self.tblPortTx.setVerticalHeaderItem(4, __qtablewidgetitem18)
        __qtablewidgetitem19 = QTableWidgetItem()
        self.tblPortTx.setVerticalHeaderItem(5, __qtablewidgetitem19)
        self.tblPortTx.setObjectName(u"tblPortTx")
        self.tblPortTx.horizontalHeader().setStretchLastSection(True)

        self.horizontalLayout_4.addWidget(self.tblPortTx)

        self.tblPortRx = QTableWidget(self.widget1)
        if (self.tblPortRx.columnCount() < 1):
            self.tblPortRx.setColumnCount(1)
        __qtablewidgetitem20 = QTableWidgetItem()
        self.tblPortRx.setHorizontalHeaderItem(0, __qtablewidgetitem20)
        if (self.tblPortRx.rowCount() < 12):
            self.tblPortRx.setRowCount(12)
        __qtablewidgetitem21 = QTableWidgetItem()
        self.tblPortRx.setVerticalHeaderItem(0, __qtablewidgetitem21)
        __qtablewidgetitem22 = QTableWidgetItem()
        self.tblPortRx.setVerticalHeaderItem(1, __qtablewidgetitem22)
        __qtablewidgetitem23 = QTableWidgetItem()
        self.tblPortRx.setVerticalHeaderItem(2, __qtablewidgetitem23)
        __qtablewidgetitem24 = QTableWidgetItem()
        self.tblPortRx.setVerticalHeaderItem(3, __qtablewidgetitem24)
        __qtablewidgetitem25 = QTableWidgetItem()
        self.tblPortRx.setVerticalHeaderItem(4, __qtablewidgetitem25)
        __qtablewidgetitem26 = QTableWidgetItem()
        self.tblPortRx.setVerticalHeaderItem(5, __qtablewidgetitem26)
        __qtablewidgetitem27 = QTableWidgetItem()
        self.tblPortRx.setVerticalHeaderItem(6, __qtablewidgetitem27)
        __qtablewidgetitem28 = QTableWidgetItem()
        self.tblPortRx.setVerticalHeaderItem(7, __qtablewidgetitem28)
        __qtablewidgetitem29 = QTableWidgetItem()
        self.tblPortRx.setVerticalHeaderItem(8, __qtablewidgetitem29)
        __qtablewidgetitem30 = QTableWidgetItem()
        self.tblPortRx.setVerticalHeaderItem(9, __qtablewidgetitem30)
        __qtablewidgetitem31 = QTableWidgetItem()
        self.tblPortRx.setVerticalHeaderItem(10, __qtablewidgetitem31)
        __qtablewidgetitem32 = QTableWidgetItem()
        self.tblPortRx.setVerticalHeaderItem(11, __qtablewidgetitem32)
        self.tblPortRx.setObjectName(u"tblPortRx")
        self.tblPortRx.horizontalHeader().setStretchLastSection(True)

        self.horizontalLayout_4.addWidget(self.tblPortRx)

        self.splitter.addWidget(self.widget1)

        self.verticalLayout_3.addWidget(self.splitter)

        self.splitter_2.addWidget(self.grbxPort)
        self.grbxClass = QGroupBox(self.splitter_2)
        self.grbxClass.setObjectName(u"grbxClass")
        self.verticalLayout_2 = QVBoxLayout(self.grbxClass)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.cbxClassSel = QComboBox(self.grbxClass)
        self.cbxClassSel.addItem("")
        self.cbxClassSel.addItem("")
        self.cbxClassSel.setObjectName(u"cbxClassSel")
        sizePolicy.setHeightForWidth(self.cbxClassSel.sizePolicy().hasHeightForWidth())
        self.cbxClassSel.setSizePolicy(sizePolicy)
        self.cbxClassSel.setMinimumSize(QSize(0, 24))

        self.horizontalLayout_2.addWidget(self.cbxClassSel)

        self.btClassClear = QPushButton(self.grbxClass)
        self.btClassClear.setObjectName(u"btClassClear")
        sizePolicy1.setHeightForWidth(self.btClassClear.sizePolicy().hasHeightForWidth())
        self.btClassClear.setSizePolicy(sizePolicy1)
        self.btClassClear.setMinimumSize(QSize(0, 26))

        self.horizontalLayout_2.addWidget(self.btClassClear)

        self.btClassRead = QPushButton(self.grbxClass)
        self.btClassRead.setObjectName(u"btClassRead")
        sizePolicy.setHeightForWidth(self.btClassRead.sizePolicy().hasHeightForWidth())
        self.btClassRead.setSizePolicy(sizePolicy)
        self.btClassRead.setMinimumSize(QSize(0, 26))

        self.horizontalLayout_2.addWidget(self.btClassRead)


        self.verticalLayout_2.addLayout(self.horizontalLayout_2)

        self.tblClassStat = QTableWidget(self.grbxClass)
        if (self.tblClassStat.rowCount() < 10):
            self.tblClassStat.setRowCount(10)
        __qtablewidgetitem33 = QTableWidgetItem()
        self.tblClassStat.setVerticalHeaderItem(0, __qtablewidgetitem33)
        __qtablewidgetitem34 = QTableWidgetItem()
        self.tblClassStat.setVerticalHeaderItem(1, __qtablewidgetitem34)
        __qtablewidgetitem35 = QTableWidgetItem()
        self.tblClassStat.setVerticalHeaderItem(2, __qtablewidgetitem35)
        __qtablewidgetitem36 = QTableWidgetItem()
        self.tblClassStat.setVerticalHeaderItem(3, __qtablewidgetitem36)
        __qtablewidgetitem37 = QTableWidgetItem()
        self.tblClassStat.setVerticalHeaderItem(4, __qtablewidgetitem37)
        __qtablewidgetitem38 = QTableWidgetItem()
        self.tblClassStat.setVerticalHeaderItem(5, __qtablewidgetitem38)
        __qtablewidgetitem39 = QTableWidgetItem()
        self.tblClassStat.setVerticalHeaderItem(6, __qtablewidgetitem39)
        __qtablewidgetitem40 = QTableWidgetItem()
        self.tblClassStat.setVerticalHeaderItem(7, __qtablewidgetitem40)
        __qtablewidgetitem41 = QTableWidgetItem()
        self.tblClassStat.setVerticalHeaderItem(8, __qtablewidgetitem41)
        __qtablewidgetitem42 = QTableWidgetItem()
        self.tblClassStat.setVerticalHeaderItem(9, __qtablewidgetitem42)
        self.tblClassStat.setObjectName(u"tblClassStat")
        self.tblClassStat.horizontalHeader().setStretchLastSection(True)

        self.verticalLayout_2.addWidget(self.tblClassStat)

        self.splitter_2.addWidget(self.grbxClass)

        self.verticalLayout_4.addWidget(self.splitter_2)


        self.retranslateUi(Form)

        QMetaObject.connectSlotsByName(Form)
    # setupUi

    def retranslateUi(self, Form):
        Form.setWindowTitle(QCoreApplication.translate("Form", u"Statistics", None))
        self.grbxCtrl.setTitle(QCoreApplication.translate("Form", u"Control", None))
        self.btClearAll.setText(QCoreApplication.translate("Form", u"Clear All Statictics", None))
        self.grbxPort.setTitle(QCoreApplication.translate("Form", u"Port Statistics", None))
        self.cbxPortSel.setItemText(0, QCoreApplication.translate("Form", u"Port 1", None))
        self.cbxPortSel.setItemText(1, QCoreApplication.translate("Form", u"Port 2", None))
        self.cbxPortSel.setItemText(2, QCoreApplication.translate("Form", u"Port 3", None))
        self.cbxPortSel.setItemText(3, QCoreApplication.translate("Form", u"Port 4", None))

        self.btPortClear.setText(QCoreApplication.translate("Form", u"Clear", None))
        self.btPortRead.setText(QCoreApplication.translate("Form", u"Update", None))
        ___qtablewidgetitem = self.tblPortStat.horizontalHeaderItem(0)
        ___qtablewidgetitem.setText(QCoreApplication.translate("Form", u"TX", None));
        ___qtablewidgetitem1 = self.tblPortStat.horizontalHeaderItem(1)
        ___qtablewidgetitem1.setText(QCoreApplication.translate("Form", u"RX", None));
        ___qtablewidgetitem2 = self.tblPortStat.verticalHeaderItem(0)
        ___qtablewidgetitem2.setText(QCoreApplication.translate("Form", u"Bytes", None));
        ___qtablewidgetitem3 = self.tblPortStat.verticalHeaderItem(1)
        ___qtablewidgetitem3.setText(QCoreApplication.translate("Form", u"OK", None));
        ___qtablewidgetitem4 = self.tblPortStat.verticalHeaderItem(2)
        ___qtablewidgetitem4.setText(QCoreApplication.translate("Form", u"Broadcast", None));
        ___qtablewidgetitem5 = self.tblPortStat.verticalHeaderItem(3)
        ___qtablewidgetitem5.setText(QCoreApplication.translate("Form", u"Multicast", None));
        ___qtablewidgetitem6 = self.tblPortStat.verticalHeaderItem(4)
        ___qtablewidgetitem6.setText(QCoreApplication.translate("Form", u"Pause", None));
        ___qtablewidgetitem7 = self.tblPortStat.verticalHeaderItem(5)
        ___qtablewidgetitem7.setText(QCoreApplication.translate("Form", u"64 bytes packets", None));
        ___qtablewidgetitem8 = self.tblPortStat.verticalHeaderItem(6)
        ___qtablewidgetitem8.setText(QCoreApplication.translate("Form", u"65..127 bytes packets", None));
        ___qtablewidgetitem9 = self.tblPortStat.verticalHeaderItem(7)
        ___qtablewidgetitem9.setText(QCoreApplication.translate("Form", u"128..255 bytes packets", None));
        ___qtablewidgetitem10 = self.tblPortStat.verticalHeaderItem(8)
        ___qtablewidgetitem10.setText(QCoreApplication.translate("Form", u"256..511 bytes packets", None));
        ___qtablewidgetitem11 = self.tblPortStat.verticalHeaderItem(9)
        ___qtablewidgetitem11.setText(QCoreApplication.translate("Form", u"512..1023 bytes packets", None));
        ___qtablewidgetitem12 = self.tblPortStat.verticalHeaderItem(10)
        ___qtablewidgetitem12.setText(QCoreApplication.translate("Form", u">1518 bytes packets", None));
        ___qtablewidgetitem13 = self.tblPortTx.horizontalHeaderItem(0)
        ___qtablewidgetitem13.setText(QCoreApplication.translate("Form", u"TX", None));
        ___qtablewidgetitem14 = self.tblPortTx.verticalHeaderItem(0)
        ___qtablewidgetitem14.setText(QCoreApplication.translate("Form", u"Underruns", None));
        ___qtablewidgetitem15 = self.tblPortTx.verticalHeaderItem(1)
        ___qtablewidgetitem15.setText(QCoreApplication.translate("Form", u"Single Collisions", None));
        ___qtablewidgetitem16 = self.tblPortTx.verticalHeaderItem(2)
        ___qtablewidgetitem16.setText(QCoreApplication.translate("Form", u"2-15 Collisions", None));
        ___qtablewidgetitem17 = self.tblPortTx.verticalHeaderItem(3)
        ___qtablewidgetitem17.setText(QCoreApplication.translate("Form", u">15 Collisions", None));
        ___qtablewidgetitem18 = self.tblPortTx.verticalHeaderItem(4)
        ___qtablewidgetitem18.setText(QCoreApplication.translate("Form", u"Late Collisions", None));
        ___qtablewidgetitem19 = self.tblPortTx.verticalHeaderItem(5)
        ___qtablewidgetitem19.setText(QCoreApplication.translate("Form", u"Deffered", None));
        ___qtablewidgetitem20 = self.tblPortRx.horizontalHeaderItem(0)
        ___qtablewidgetitem20.setText(QCoreApplication.translate("Form", u"RX", None));
        ___qtablewidgetitem21 = self.tblPortRx.verticalHeaderItem(0)
        ___qtablewidgetitem21.setText(QCoreApplication.translate("Form", u"Excessive Len", None));
        ___qtablewidgetitem22 = self.tblPortRx.verticalHeaderItem(1)
        ___qtablewidgetitem22.setText(QCoreApplication.translate("Form", u"Jubbers", None));
        ___qtablewidgetitem23 = self.tblPortRx.verticalHeaderItem(2)
        ___qtablewidgetitem23.setText(QCoreApplication.translate("Form", u"FCS Errors", None));
        ___qtablewidgetitem24 = self.tblPortRx.verticalHeaderItem(3)
        ___qtablewidgetitem24.setText(QCoreApplication.translate("Form", u"Len Erorrs", None));
        ___qtablewidgetitem25 = self.tblPortRx.verticalHeaderItem(4)
        ___qtablewidgetitem25.setText(QCoreApplication.translate("Form", u"Symbol Errors", None));
        ___qtablewidgetitem26 = self.tblPortRx.verticalHeaderItem(5)
        ___qtablewidgetitem26.setText(QCoreApplication.translate("Form", u"Aligment Errors", None));
        ___qtablewidgetitem27 = self.tblPortRx.verticalHeaderItem(6)
        ___qtablewidgetitem27.setText(QCoreApplication.translate("Form", u"Resource Errors", None));
        ___qtablewidgetitem28 = self.tblPortRx.verticalHeaderItem(7)
        ___qtablewidgetitem28.setText(QCoreApplication.translate("Form", u"Overruns", None));
        ___qtablewidgetitem29 = self.tblPortRx.verticalHeaderItem(8)
        ___qtablewidgetitem29.setText(QCoreApplication.translate("Form", u"IP CRC Errors", None));
        ___qtablewidgetitem30 = self.tblPortRx.verticalHeaderItem(9)
        ___qtablewidgetitem30.setText(QCoreApplication.translate("Form", u"TCP CRC Errors", None));
        ___qtablewidgetitem31 = self.tblPortRx.verticalHeaderItem(10)
        ___qtablewidgetitem31.setText(QCoreApplication.translate("Form", u"UDP CRC Errors", None));
        ___qtablewidgetitem32 = self.tblPortRx.verticalHeaderItem(11)
        ___qtablewidgetitem32.setText(QCoreApplication.translate("Form", u"Dropped", None));
        self.grbxClass.setTitle(QCoreApplication.translate("Form", u"Classificator Statistics", None))
        self.cbxClassSel.setItemText(0, QCoreApplication.translate("Form", u"Classificator 1", None))
        self.cbxClassSel.setItemText(1, QCoreApplication.translate("Form", u"Classificator 2", None))

        self.btClassClear.setText(QCoreApplication.translate("Form", u"Clear", None))
        self.btClassRead.setText(QCoreApplication.translate("Form", u"Update", None))
        ___qtablewidgetitem33 = self.tblClassStat.verticalHeaderItem(0)
        ___qtablewidgetitem33.setText(QCoreApplication.translate("Form", u"RX", None));
        ___qtablewidgetitem34 = self.tblClassStat.verticalHeaderItem(1)
        ___qtablewidgetitem34.setText(QCoreApplication.translate("Form", u"L3 Fails", None));
        ___qtablewidgetitem35 = self.tblClassStat.verticalHeaderItem(2)
        ___qtablewidgetitem35.setText(QCoreApplication.translate("Form", u"IPV4", None));
        ___qtablewidgetitem36 = self.tblClassStat.verticalHeaderItem(3)
        ___qtablewidgetitem36.setText(QCoreApplication.translate("Form", u"IPV6", None));
        ___qtablewidgetitem37 = self.tblClassStat.verticalHeaderItem(4)
        ___qtablewidgetitem37.setText(QCoreApplication.translate("Form", u"CRC Errors", None));
        ___qtablewidgetitem38 = self.tblClassStat.verticalHeaderItem(5)
        ___qtablewidgetitem38.setText(QCoreApplication.translate("Form", u"TLL Errors", None));
        ___qtablewidgetitem39 = self.tblClassStat.verticalHeaderItem(6)
        ___qtablewidgetitem39.setText(QCoreApplication.translate("Form", u"ICMP", None));
        ___qtablewidgetitem40 = self.tblClassStat.verticalHeaderItem(7)
        ___qtablewidgetitem40.setText(QCoreApplication.translate("Form", u"IGMP", None));
        ___qtablewidgetitem41 = self.tblClassStat.verticalHeaderItem(8)
        ___qtablewidgetitem41.setText(QCoreApplication.translate("Form", u"TCP", None));
        ___qtablewidgetitem42 = self.tblClassStat.verticalHeaderItem(9)
        ___qtablewidgetitem42.setText(QCoreApplication.translate("Form", u"UDP", None));
    # retranslateUi

