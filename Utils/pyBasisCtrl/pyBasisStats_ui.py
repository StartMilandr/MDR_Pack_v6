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
        Form.resize(295, 655)
        self.verticalLayout_2 = QVBoxLayout(Form)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.btClearAll = QPushButton(Form)
        self.btClearAll.setObjectName(u"btClearAll")
        self.btClearAll.setMinimumSize(QSize(0, 26))

        self.verticalLayout_2.addWidget(self.btClearAll)

        self.grbxPort = QGroupBox(Form)
        self.grbxPort.setObjectName(u"grbxPort")
        self.verticalLayout = QVBoxLayout(self.grbxPort)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.cbxPortSel = QComboBox(self.grbxPort)
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

        self.btPortRead = QPushButton(self.grbxPort)
        self.btPortRead.setObjectName(u"btPortRead")
        sizePolicy.setHeightForWidth(self.btPortRead.sizePolicy().hasHeightForWidth())
        self.btPortRead.setSizePolicy(sizePolicy)
        self.btPortRead.setMinimumSize(QSize(0, 26))

        self.horizontalLayout.addWidget(self.btPortRead)

        self.btPortClear = QPushButton(self.grbxPort)
        self.btPortClear.setObjectName(u"btPortClear")
        sizePolicy1 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Fixed)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.btPortClear.sizePolicy().hasHeightForWidth())
        self.btPortClear.setSizePolicy(sizePolicy1)
        self.btPortClear.setMinimumSize(QSize(0, 26))

        self.horizontalLayout.addWidget(self.btPortClear)


        self.verticalLayout.addLayout(self.horizontalLayout)

        self.treeView = QTreeView(self.grbxPort)
        self.treeView.setObjectName(u"treeView")

        self.verticalLayout.addWidget(self.treeView)


        self.verticalLayout_2.addWidget(self.grbxPort)


        self.retranslateUi(Form)

        QMetaObject.connectSlotsByName(Form)
    # setupUi

    def retranslateUi(self, Form):
        Form.setWindowTitle(QCoreApplication.translate("Form", u"Statistics", None))
        self.btClearAll.setText(QCoreApplication.translate("Form", u"Clear All Port Statictics", None))
        self.grbxPort.setTitle(QCoreApplication.translate("Form", u"Port Statistics", None))
        self.cbxPortSel.setItemText(0, QCoreApplication.translate("Form", u"Port 1", None))
        self.cbxPortSel.setItemText(1, QCoreApplication.translate("Form", u"Port 2", None))
        self.cbxPortSel.setItemText(2, QCoreApplication.translate("Form", u"Port 3", None))
        self.cbxPortSel.setItemText(3, QCoreApplication.translate("Form", u"Port 4", None))

        self.btPortRead.setText(QCoreApplication.translate("Form", u"Read", None))
        self.btPortClear.setText(QCoreApplication.translate("Form", u"Clear", None))
    # retranslateUi

