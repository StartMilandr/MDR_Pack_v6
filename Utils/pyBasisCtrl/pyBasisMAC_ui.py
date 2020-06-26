# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'pyBasisMAC.ui'
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
        Form.resize(649, 677)
        self.verticalLayout_4 = QVBoxLayout(Form)
        self.verticalLayout_4.setObjectName(u"verticalLayout_4")
        self.splitter = QSplitter(Form)
        self.splitter.setObjectName(u"splitter")
        self.splitter.setOrientation(Qt.Vertical)
        self.layoutWidget = QWidget(self.splitter)
        self.layoutWidget.setObjectName(u"layoutWidget")
        self.verticalLayout_3 = QVBoxLayout(self.layoutWidget)
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.verticalLayout_3.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_3 = QHBoxLayout()
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.grboxSave = QGroupBox(self.layoutWidget)
        self.grboxSave.setObjectName(u"grboxSave")
        self.horizontalLayout = QHBoxLayout(self.grboxSave)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.btSave = QPushButton(self.grboxSave)
        self.btSave.setObjectName(u"btSave")
        self.btSave.setMinimumSize(QSize(0, 26))

        self.horizontalLayout.addWidget(self.btSave)

        self.btSelTgl = QPushButton(self.grboxSave)
        self.btSelTgl.setObjectName(u"btSelTgl")
        self.btSelTgl.setMinimumSize(QSize(0, 26))

        self.horizontalLayout.addWidget(self.btSelTgl)


        self.horizontalLayout_3.addWidget(self.grboxSave)

        self.gbxDevice = QGroupBox(self.layoutWidget)
        self.gbxDevice.setObjectName(u"gbxDevice")
        self.horizontalLayout_2 = QHBoxLayout(self.gbxDevice)
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.btRead = QPushButton(self.gbxDevice)
        self.btRead.setObjectName(u"btRead")
        self.btRead.setMinimumSize(QSize(0, 26))

        self.horizontalLayout_2.addWidget(self.btRead)

        self.btDelSelected = QPushButton(self.gbxDevice)
        self.btDelSelected.setObjectName(u"btDelSelected")
        self.btDelSelected.setMinimumSize(QSize(0, 26))

        self.horizontalLayout_2.addWidget(self.btDelSelected)


        self.horizontalLayout_3.addWidget(self.gbxDevice)


        self.verticalLayout_3.addLayout(self.horizontalLayout_3)

        self.grBoxTableRd = QGroupBox(self.layoutWidget)
        self.grBoxTableRd.setObjectName(u"grBoxTableRd")
        self.verticalLayout_2 = QVBoxLayout(self.grBoxTableRd)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.tblTableRd = QTableWidget(self.grBoxTableRd)
        if (self.tblTableRd.columnCount() < 8):
            self.tblTableRd.setColumnCount(8)
        __qtablewidgetitem = QTableWidgetItem()
        self.tblTableRd.setHorizontalHeaderItem(0, __qtablewidgetitem)
        __qtablewidgetitem1 = QTableWidgetItem()
        self.tblTableRd.setHorizontalHeaderItem(1, __qtablewidgetitem1)
        __qtablewidgetitem2 = QTableWidgetItem()
        self.tblTableRd.setHorizontalHeaderItem(2, __qtablewidgetitem2)
        __qtablewidgetitem3 = QTableWidgetItem()
        self.tblTableRd.setHorizontalHeaderItem(3, __qtablewidgetitem3)
        __qtablewidgetitem4 = QTableWidgetItem()
        self.tblTableRd.setHorizontalHeaderItem(4, __qtablewidgetitem4)
        __qtablewidgetitem5 = QTableWidgetItem()
        self.tblTableRd.setHorizontalHeaderItem(5, __qtablewidgetitem5)
        __qtablewidgetitem6 = QTableWidgetItem()
        self.tblTableRd.setHorizontalHeaderItem(6, __qtablewidgetitem6)
        __qtablewidgetitem7 = QTableWidgetItem()
        self.tblTableRd.setHorizontalHeaderItem(7, __qtablewidgetitem7)
        self.tblTableRd.setObjectName(u"tblTableRd")
        self.tblTableRd.horizontalHeader().setStretchLastSection(True)

        self.verticalLayout_2.addWidget(self.tblTableRd)


        self.verticalLayout_3.addWidget(self.grBoxTableRd)

        self.splitter.addWidget(self.layoutWidget)
        self.grbxAddItem = QGroupBox(self.splitter)
        self.grbxAddItem.setObjectName(u"grbxAddItem")
        self.grbxAddItem.setMaximumSize(QSize(16777215, 160))
        self.verticalLayout = QVBoxLayout(self.grbxAddItem)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.tblCtrl = QTableWidget(self.grbxAddItem)
        if (self.tblCtrl.columnCount() < 7):
            self.tblCtrl.setColumnCount(7)
        __qtablewidgetitem8 = QTableWidgetItem()
        self.tblCtrl.setHorizontalHeaderItem(0, __qtablewidgetitem8)
        __qtablewidgetitem9 = QTableWidgetItem()
        self.tblCtrl.setHorizontalHeaderItem(1, __qtablewidgetitem9)
        __qtablewidgetitem10 = QTableWidgetItem()
        self.tblCtrl.setHorizontalHeaderItem(2, __qtablewidgetitem10)
        __qtablewidgetitem11 = QTableWidgetItem()
        self.tblCtrl.setHorizontalHeaderItem(3, __qtablewidgetitem11)
        __qtablewidgetitem12 = QTableWidgetItem()
        self.tblCtrl.setHorizontalHeaderItem(4, __qtablewidgetitem12)
        __qtablewidgetitem13 = QTableWidgetItem()
        self.tblCtrl.setHorizontalHeaderItem(5, __qtablewidgetitem13)
        __qtablewidgetitem14 = QTableWidgetItem()
        self.tblCtrl.setHorizontalHeaderItem(6, __qtablewidgetitem14)
        self.tblCtrl.setObjectName(u"tblCtrl")
        self.tblCtrl.horizontalHeader().setStretchLastSection(True)

        self.verticalLayout.addWidget(self.tblCtrl)

        self.splitter.addWidget(self.grbxAddItem)

        self.verticalLayout_4.addWidget(self.splitter)


        self.retranslateUi(Form)

        QMetaObject.connectSlotsByName(Form)
    # setupUi

    def retranslateUi(self, Form):
        Form.setWindowTitle(QCoreApplication.translate("Form", u"MAC Table", None))
        self.grboxSave.setTitle(QCoreApplication.translate("Form", u"View Table", None))
        self.btSave.setText(QCoreApplication.translate("Form", u"Save to File...", None))
        self.btSelTgl.setText(QCoreApplication.translate("Form", u"Select / Unselect All", None))
        self.gbxDevice.setTitle(QCoreApplication.translate("Form", u"Device Table", None))
        self.btRead.setText(QCoreApplication.translate("Form", u"Read", None))
        self.btDelSelected.setText(QCoreApplication.translate("Form", u"Delete Selected", None))
        self.grBoxTableRd.setTitle(QCoreApplication.translate("Form", u"Table", None))
        ___qtablewidgetitem = self.tblTableRd.horizontalHeaderItem(0)
        ___qtablewidgetitem.setText(QCoreApplication.translate("Form", u"sel", None));
        ___qtablewidgetitem1 = self.tblTableRd.horizontalHeaderItem(1)
        ___qtablewidgetitem1.setText(QCoreApplication.translate("Form", u"VLAN_ID", None));
        ___qtablewidgetitem2 = self.tblTableRd.horizontalHeaderItem(2)
        ___qtablewidgetitem2.setText(QCoreApplication.translate("Form", u"MAC", None));
        ___qtablewidgetitem3 = self.tblTableRd.horizontalHeaderItem(3)
        ___qtablewidgetitem3.setText(QCoreApplication.translate("Form", u"isFresh", None));
        ___qtablewidgetitem4 = self.tblTableRd.horizontalHeaderItem(4)
        ___qtablewidgetitem4.setText(QCoreApplication.translate("Form", u"isStatic", None));
        ___qtablewidgetitem5 = self.tblTableRd.horizontalHeaderItem(5)
        ___qtablewidgetitem5.setText(QCoreApplication.translate("Form", u"PortRx", None));
        ___qtablewidgetitem6 = self.tblTableRd.horizontalHeaderItem(6)
        ___qtablewidgetitem6.setText(QCoreApplication.translate("Form", u"ForwPorts", None));
        ___qtablewidgetitem7 = self.tblTableRd.horizontalHeaderItem(7)
        ___qtablewidgetitem7.setText(QCoreApplication.translate("Form", u"Action", None));
        self.grbxAddItem.setTitle(QCoreApplication.translate("Form", u"Add Items", None))
        ___qtablewidgetitem8 = self.tblCtrl.horizontalHeaderItem(0)
        ___qtablewidgetitem8.setText(QCoreApplication.translate("Form", u" VLAN_ID ", None));
        ___qtablewidgetitem9 = self.tblCtrl.horizontalHeaderItem(1)
        ___qtablewidgetitem9.setText(QCoreApplication.translate("Form", u"MAC", None));
        ___qtablewidgetitem10 = self.tblCtrl.horizontalHeaderItem(2)
        ___qtablewidgetitem10.setText(QCoreApplication.translate("Form", u" isStatis ", None));
        ___qtablewidgetitem11 = self.tblCtrl.horizontalHeaderItem(3)
        ___qtablewidgetitem11.setText(QCoreApplication.translate("Form", u"Action", None));
        ___qtablewidgetitem12 = self.tblCtrl.horizontalHeaderItem(4)
        ___qtablewidgetitem12.setText(QCoreApplication.translate("Form", u" Port ", None));
        ___qtablewidgetitem13 = self.tblCtrl.horizontalHeaderItem(5)
        ___qtablewidgetitem13.setText(QCoreApplication.translate("Form", u"ForwPorts", None));
        ___qtablewidgetitem14 = self.tblCtrl.horizontalHeaderItem(6)
        ___qtablewidgetitem14.setText(QCoreApplication.translate("Form", u"Apply", None));
    # retranslateUi

