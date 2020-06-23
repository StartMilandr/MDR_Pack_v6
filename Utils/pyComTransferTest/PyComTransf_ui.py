# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'PyComTransf.ui'
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
        Form.resize(670, 459)
        self.horizontalLayout_10 = QHBoxLayout(Form)
        self.horizontalLayout_10.setObjectName(u"horizontalLayout_10")
        self.splitter = QSplitter(Form)
        self.splitter.setObjectName(u"splitter")
        self.splitter.setOrientation(Qt.Horizontal)
        self.layoutWidget = QWidget(self.splitter)
        self.layoutWidget.setObjectName(u"layoutWidget")
        self.verticalLayout_2 = QVBoxLayout(self.layoutWidget)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.verticalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.gbxTool = QGroupBox(self.layoutWidget)
        self.gbxTool.setObjectName(u"gbxTool")
        self.horizontalLayout = QHBoxLayout(self.gbxTool)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.cbxComSel = QComboBox(self.gbxTool)
        self.cbxComSel.setObjectName(u"cbxComSel")
        self.cbxComSel.setMinimumSize(QSize(0, 24))
        self.cbxComSel.setMaximumSize(QSize(80, 16777215))

        self.horizontalLayout.addWidget(self.cbxComSel)

        self.cbxComBaud = QComboBox(self.gbxTool)
        self.cbxComBaud.setObjectName(u"cbxComBaud")
        self.cbxComBaud.setMinimumSize(QSize(0, 24))
        self.cbxComBaud.setEditable(True)

        self.horizontalLayout.addWidget(self.cbxComBaud)

        self.btStatus = QPushButton(self.gbxTool)
        self.btStatus.setObjectName(u"btStatus")
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

        self.horizontalLayout.addWidget(self.btStatus)

        self.btConnect = QPushButton(self.gbxTool)
        self.btConnect.setObjectName(u"btConnect")
        self.btConnect.setMinimumSize(QSize(0, 26))

        self.horizontalLayout.addWidget(self.btConnect)


        self.verticalLayout_2.addWidget(self.gbxTool)

        self.groupBox = QGroupBox(self.layoutWidget)
        self.groupBox.setObjectName(u"groupBox")
        self.horizontalLayout_2 = QHBoxLayout(self.groupBox)
        self.horizontalLayout_2.setSpacing(6)
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.btTestStart = QPushButton(self.groupBox)
        self.btTestStart.setObjectName(u"btTestStart")
        self.btTestStart.setMinimumSize(QSize(0, 30))
        self.btTestStart.setCheckable(True)

        self.horizontalLayout_2.addWidget(self.btTestStart)

        self.btLogClear = QPushButton(self.groupBox)
        self.btLogClear.setObjectName(u"btLogClear")
        self.btLogClear.setMinimumSize(QSize(0, 30))

        self.horizontalLayout_2.addWidget(self.btLogClear)

        self.horizontalLayout_2.setStretch(0, 1)

        self.verticalLayout_2.addWidget(self.groupBox)

        self.groupBox_2 = QGroupBox(self.layoutWidget)
        self.groupBox_2.setObjectName(u"groupBox_2")
        self.groupBox_2.setMinimumSize(QSize(0, 0))
        self.groupBox_2.setMaximumSize(QSize(16777215, 16777215))
        self.horizontalLayout_3 = QHBoxLayout(self.groupBox_2)
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.lbCycles = QLabel(self.groupBox_2)
        self.lbCycles.setObjectName(u"lbCycles")

        self.horizontalLayout_3.addWidget(self.lbCycles)

        self.lbTranstCount = QLabel(self.groupBox_2)
        self.lbTranstCount.setObjectName(u"lbTranstCount")

        self.horizontalLayout_3.addWidget(self.lbTranstCount)

        self.lbErrCount = QLabel(self.groupBox_2)
        self.lbErrCount.setObjectName(u"lbErrCount")

        self.horizontalLayout_3.addWidget(self.lbErrCount)


        self.verticalLayout_2.addWidget(self.groupBox_2)

        self.verticalSpacer = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_2.addItem(self.verticalSpacer)

        self.splitter.addWidget(self.layoutWidget)
        self.txtEdLog = QTextEdit(self.splitter)
        self.txtEdLog.setObjectName(u"txtEdLog")
        self.splitter.addWidget(self.txtEdLog)

        self.horizontalLayout_10.addWidget(self.splitter)


        self.retranslateUi(Form)

        QMetaObject.connectSlotsByName(Form)
    # setupUi

    def retranslateUi(self, Form):
        Form.setWindowTitle(QCoreApplication.translate("Form", u"Form", None))
        self.gbxTool.setTitle(QCoreApplication.translate("Form", u"Control", None))
        self.btStatus.setText("")
        self.btConnect.setText(QCoreApplication.translate("Form", u"Connect", None))
        self.groupBox.setTitle(QCoreApplication.translate("Form", u"Test", None))
        self.btTestStart.setText(QCoreApplication.translate("Form", u"Start Test", None))
        self.btLogClear.setText(QCoreApplication.translate("Form", u"Log Clear", None))
        self.groupBox_2.setTitle(QCoreApplication.translate("Form", u"Status", None))
        self.lbCycles.setText(QCoreApplication.translate("Form", u"Cycles: 0", None))
        self.lbTranstCount.setText(QCoreApplication.translate("Form", u"TransfCount: 0", None))
        self.lbErrCount.setText(QCoreApplication.translate("Form", u"Error Count: 0", None))
    # retranslateUi

