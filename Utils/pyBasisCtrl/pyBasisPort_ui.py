# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'pyBasisPort.ui'
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
        Form.resize(422, 464)
        self.verticalLayout = QVBoxLayout(Form)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.btUpdateAll = QPushButton(Form)
        self.btUpdateAll.setObjectName(u"btUpdateAll")
        self.btUpdateAll.setMinimumSize(QSize(0, 26))

        self.verticalLayout.addWidget(self.btUpdateAll)

        self.tblPorts = QTableWidget(Form)
        if (self.tblPorts.rowCount() < 10):
            self.tblPorts.setRowCount(10)
        __qtablewidgetitem = QTableWidgetItem()
        self.tblPorts.setVerticalHeaderItem(0, __qtablewidgetitem)
        __qtablewidgetitem1 = QTableWidgetItem()
        self.tblPorts.setVerticalHeaderItem(1, __qtablewidgetitem1)
        __qtablewidgetitem2 = QTableWidgetItem()
        self.tblPorts.setVerticalHeaderItem(2, __qtablewidgetitem2)
        __qtablewidgetitem3 = QTableWidgetItem()
        self.tblPorts.setVerticalHeaderItem(3, __qtablewidgetitem3)
        __qtablewidgetitem4 = QTableWidgetItem()
        self.tblPorts.setVerticalHeaderItem(4, __qtablewidgetitem4)
        __qtablewidgetitem5 = QTableWidgetItem()
        self.tblPorts.setVerticalHeaderItem(5, __qtablewidgetitem5)
        __qtablewidgetitem6 = QTableWidgetItem()
        self.tblPorts.setVerticalHeaderItem(6, __qtablewidgetitem6)
        __qtablewidgetitem7 = QTableWidgetItem()
        self.tblPorts.setVerticalHeaderItem(7, __qtablewidgetitem7)
        __qtablewidgetitem8 = QTableWidgetItem()
        self.tblPorts.setVerticalHeaderItem(8, __qtablewidgetitem8)
        __qtablewidgetitem9 = QTableWidgetItem()
        self.tblPorts.setVerticalHeaderItem(9, __qtablewidgetitem9)
        self.tblPorts.setObjectName(u"tblPorts")
        self.tblPorts.horizontalHeader().setVisible(False)

        self.verticalLayout.addWidget(self.tblPorts)


        self.retranslateUi(Form)

        QMetaObject.connectSlotsByName(Form)
    # setupUi

    def retranslateUi(self, Form):
        Form.setWindowTitle(QCoreApplication.translate("Form", u"Form", None))
        self.btUpdateAll.setText(QCoreApplication.translate("Form", u"Read All", None))
        ___qtablewidgetitem = self.tblPorts.verticalHeaderItem(2)
        ___qtablewidgetitem.setText(QCoreApplication.translate("Form", u"State", None));
        ___qtablewidgetitem1 = self.tblPorts.verticalHeaderItem(3)
        ___qtablewidgetitem1.setText(QCoreApplication.translate("Form", u"ShutDown", None));
        ___qtablewidgetitem2 = self.tblPorts.verticalHeaderItem(4)
        ___qtablewidgetitem2.setText(QCoreApplication.translate("Form", u"TPID", None));
        ___qtablewidgetitem3 = self.tblPorts.verticalHeaderItem(5)
        ___qtablewidgetitem3.setText(QCoreApplication.translate("Form", u"Fallback", None));
        ___qtablewidgetitem4 = self.tblPorts.verticalHeaderItem(6)
        ___qtablewidgetitem4.setText(QCoreApplication.translate("Form", u"AFT", None));
        ___qtablewidgetitem5 = self.tblPorts.verticalHeaderItem(7)
        ___qtablewidgetitem5.setText(QCoreApplication.translate("Form", u"Blockstate", None));
        ___qtablewidgetitem6 = self.tblPorts.verticalHeaderItem(8)
        ___qtablewidgetitem6.setText(QCoreApplication.translate("Form", u"UntagBTable", None));
    # retranslateUi

