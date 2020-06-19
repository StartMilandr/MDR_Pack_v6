# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'PyComPort.ui'
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
        Form.resize(670, 615)
        self.horizontalLayout_10 = QHBoxLayout(Form)
        self.horizontalLayout_10.setObjectName(u"horizontalLayout_10")
        self.splitter = QSplitter(Form)
        self.splitter.setObjectName(u"splitter")
        self.splitter.setOrientation(Qt.Horizontal)
        self.widget = QWidget(self.splitter)
        self.widget.setObjectName(u"widget")
        self.verticalLayout_2 = QVBoxLayout(self.widget)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.verticalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.gbxTool = QGroupBox(self.widget)
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

        self.groupBox = QGroupBox(self.widget)
        self.groupBox.setObjectName(u"groupBox")
        self.verticalLayout = QVBoxLayout(self.groupBox)
        self.verticalLayout.setSpacing(6)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.leSend1 = QLineEdit(self.groupBox)
        self.leSend1.setObjectName(u"leSend1")

        self.horizontalLayout_2.addWidget(self.leSend1)

        self.chbxSend1 = QCheckBox(self.groupBox)
        self.chbxSend1.setObjectName(u"chbxSend1")

        self.horizontalLayout_2.addWidget(self.chbxSend1)

        self.btSend1 = QPushButton(self.groupBox)
        self.btSend1.setObjectName(u"btSend1")

        self.horizontalLayout_2.addWidget(self.btSend1)


        self.verticalLayout.addLayout(self.horizontalLayout_2)

        self.horizontalLayout_3 = QHBoxLayout()
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.leSend2 = QLineEdit(self.groupBox)
        self.leSend2.setObjectName(u"leSend2")

        self.horizontalLayout_3.addWidget(self.leSend2)

        self.chbxSend2 = QCheckBox(self.groupBox)
        self.chbxSend2.setObjectName(u"chbxSend2")

        self.horizontalLayout_3.addWidget(self.chbxSend2)

        self.btSend2 = QPushButton(self.groupBox)
        self.btSend2.setObjectName(u"btSend2")

        self.horizontalLayout_3.addWidget(self.btSend2)


        self.verticalLayout.addLayout(self.horizontalLayout_3)

        self.horizontalLayout_4 = QHBoxLayout()
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.leSend3 = QLineEdit(self.groupBox)
        self.leSend3.setObjectName(u"leSend3")

        self.horizontalLayout_4.addWidget(self.leSend3)

        self.chbxSend3 = QCheckBox(self.groupBox)
        self.chbxSend3.setObjectName(u"chbxSend3")

        self.horizontalLayout_4.addWidget(self.chbxSend3)

        self.btSend3 = QPushButton(self.groupBox)
        self.btSend3.setObjectName(u"btSend3")

        self.horizontalLayout_4.addWidget(self.btSend3)


        self.verticalLayout.addLayout(self.horizontalLayout_4)

        self.horizontalLayout_5 = QHBoxLayout()
        self.horizontalLayout_5.setObjectName(u"horizontalLayout_5")
        self.leSend4 = QLineEdit(self.groupBox)
        self.leSend4.setObjectName(u"leSend4")

        self.horizontalLayout_5.addWidget(self.leSend4)

        self.chbxSend4 = QCheckBox(self.groupBox)
        self.chbxSend4.setObjectName(u"chbxSend4")

        self.horizontalLayout_5.addWidget(self.chbxSend4)

        self.btSend4 = QPushButton(self.groupBox)
        self.btSend4.setObjectName(u"btSend4")

        self.horizontalLayout_5.addWidget(self.btSend4)


        self.verticalLayout.addLayout(self.horizontalLayout_5)

        self.horizontalLayout_6 = QHBoxLayout()
        self.horizontalLayout_6.setObjectName(u"horizontalLayout_6")
        self.leSend5 = QLineEdit(self.groupBox)
        self.leSend5.setObjectName(u"leSend5")

        self.horizontalLayout_6.addWidget(self.leSend5)

        self.chbxSend5 = QCheckBox(self.groupBox)
        self.chbxSend5.setObjectName(u"chbxSend5")

        self.horizontalLayout_6.addWidget(self.chbxSend5)

        self.btSend5 = QPushButton(self.groupBox)
        self.btSend5.setObjectName(u"btSend5")

        self.horizontalLayout_6.addWidget(self.btSend5)


        self.verticalLayout.addLayout(self.horizontalLayout_6)

        self.horizontalLayout_7 = QHBoxLayout()
        self.horizontalLayout_7.setObjectName(u"horizontalLayout_7")
        self.leSend6 = QLineEdit(self.groupBox)
        self.leSend6.setObjectName(u"leSend6")

        self.horizontalLayout_7.addWidget(self.leSend6)

        self.chbxSend6 = QCheckBox(self.groupBox)
        self.chbxSend6.setObjectName(u"chbxSend6")

        self.horizontalLayout_7.addWidget(self.chbxSend6)

        self.btSend6 = QPushButton(self.groupBox)
        self.btSend6.setObjectName(u"btSend6")

        self.horizontalLayout_7.addWidget(self.btSend6)


        self.verticalLayout.addLayout(self.horizontalLayout_7)

        self.horizontalLayout_8 = QHBoxLayout()
        self.horizontalLayout_8.setObjectName(u"horizontalLayout_8")
        self.leSend7 = QLineEdit(self.groupBox)
        self.leSend7.setObjectName(u"leSend7")

        self.horizontalLayout_8.addWidget(self.leSend7)

        self.chbxSend7 = QCheckBox(self.groupBox)
        self.chbxSend7.setObjectName(u"chbxSend7")

        self.horizontalLayout_8.addWidget(self.chbxSend7)

        self.btSend7 = QPushButton(self.groupBox)
        self.btSend7.setObjectName(u"btSend7")

        self.horizontalLayout_8.addWidget(self.btSend7)


        self.verticalLayout.addLayout(self.horizontalLayout_8)

        self.horizontalLayout_9 = QHBoxLayout()
        self.horizontalLayout_9.setObjectName(u"horizontalLayout_9")
        self.leSend8 = QLineEdit(self.groupBox)
        self.leSend8.setObjectName(u"leSend8")

        self.horizontalLayout_9.addWidget(self.leSend8)

        self.chbxSend8 = QCheckBox(self.groupBox)
        self.chbxSend8.setObjectName(u"chbxSend8")

        self.horizontalLayout_9.addWidget(self.chbxSend8)

        self.btSend8 = QPushButton(self.groupBox)
        self.btSend8.setObjectName(u"btSend8")

        self.horizontalLayout_9.addWidget(self.btSend8)


        self.verticalLayout.addLayout(self.horizontalLayout_9)

        self.verticalSpacer = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout.addItem(self.verticalSpacer)

        self.groupBox_2 = QGroupBox(self.groupBox)
        self.groupBox_2.setObjectName(u"groupBox_2")
        self.groupBox_2.setFlat(False)
        self.gridLayout = QGridLayout(self.groupBox_2)
        self.gridLayout.setObjectName(u"gridLayout")
        self.gridLayout.setHorizontalSpacing(9)
        self.gridLayout.setVerticalSpacing(6)
        self.gridLayout.setContentsMargins(6, 6, 6, 6)
        self.btLogClear = QPushButton(self.groupBox_2)
        self.btLogClear.setObjectName(u"btLogClear")
        self.btLogClear.setMinimumSize(QSize(0, 58))

        self.gridLayout.addWidget(self.btLogClear, 0, 3, 2, 1)

        self.chbxLogTx = QCheckBox(self.groupBox_2)
        self.chbxLogTx.setObjectName(u"chbxLogTx")

        self.gridLayout.addWidget(self.chbxLogTx, 0, 1, 1, 1)

        self.horizontalLayout_11 = QHBoxLayout()
        self.horizontalLayout_11.setObjectName(u"horizontalLayout_11")
        self.label_2 = QLabel(self.groupBox_2)
        self.label_2.setObjectName(u"label_2")
        self.label_2.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)
        self.label_2.setMargin(6)

        self.horizontalLayout_11.addWidget(self.label_2)

        self.cbxConvRx = QComboBox(self.groupBox_2)
        self.cbxConvRx.addItem("")
        self.cbxConvRx.addItem("")
        self.cbxConvRx.addItem("")
        self.cbxConvRx.setObjectName(u"cbxConvRx")
        self.cbxConvRx.setMinimumSize(QSize(0, 24))
        self.cbxConvRx.setFrame(True)

        self.horizontalLayout_11.addWidget(self.cbxConvRx)


        self.gridLayout.addLayout(self.horizontalLayout_11, 0, 2, 1, 1)

        self.horizontalLayout_12 = QHBoxLayout()
        self.horizontalLayout_12.setObjectName(u"horizontalLayout_12")
        self.label = QLabel(self.groupBox_2)
        self.label.setObjectName(u"label")
        self.label.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)
        self.label.setMargin(6)

        self.horizontalLayout_12.addWidget(self.label)

        self.cbxProtocol = QComboBox(self.groupBox_2)
        self.cbxProtocol.addItem("")
        self.cbxProtocol.addItem("")
        self.cbxProtocol.setObjectName(u"cbxProtocol")
        self.cbxProtocol.setMinimumSize(QSize(0, 24))

        self.horizontalLayout_12.addWidget(self.cbxProtocol)


        self.gridLayout.addLayout(self.horizontalLayout_12, 1, 2, 1, 1)

        self.btLogSave = QPushButton(self.groupBox_2)
        self.btLogSave.setObjectName(u"btLogSave")
        self.btLogSave.setMinimumSize(QSize(0, 26))

        self.gridLayout.addWidget(self.btLogSave, 1, 1, 1, 1)


        self.verticalLayout.addWidget(self.groupBox_2)


        self.verticalLayout_2.addWidget(self.groupBox)

        self.splitter.addWidget(self.widget)
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
        self.groupBox.setTitle(QCoreApplication.translate("Form", u"Send", None))
        self.chbxSend1.setText(QCoreApplication.translate("Form", u"Char", None))
        self.btSend1.setText(QCoreApplication.translate("Form", u"Send", None))
        self.chbxSend2.setText(QCoreApplication.translate("Form", u"Char", None))
        self.btSend2.setText(QCoreApplication.translate("Form", u"Send", None))
        self.chbxSend3.setText(QCoreApplication.translate("Form", u"Char", None))
        self.btSend3.setText(QCoreApplication.translate("Form", u"Send", None))
        self.chbxSend4.setText(QCoreApplication.translate("Form", u"Char", None))
        self.btSend4.setText(QCoreApplication.translate("Form", u"Send", None))
        self.chbxSend5.setText(QCoreApplication.translate("Form", u"Char", None))
        self.btSend5.setText(QCoreApplication.translate("Form", u"Send", None))
        self.chbxSend6.setText(QCoreApplication.translate("Form", u"Char", None))
        self.btSend6.setText(QCoreApplication.translate("Form", u"Send", None))
        self.chbxSend7.setText(QCoreApplication.translate("Form", u"Char", None))
        self.btSend7.setText(QCoreApplication.translate("Form", u"Send", None))
        self.chbxSend8.setText(QCoreApplication.translate("Form", u"Char", None))
        self.btSend8.setText(QCoreApplication.translate("Form", u"Send", None))
        self.groupBox_2.setTitle(QCoreApplication.translate("Form", u"Log", None))
        self.btLogClear.setText(QCoreApplication.translate("Form", u"Clear", None))
        self.chbxLogTx.setText(QCoreApplication.translate("Form", u"Show Tx", None))
        self.label_2.setText(QCoreApplication.translate("Form", u"ShowRx", None))
        self.cbxConvRx.setItemText(0, QCoreApplication.translate("Form", u"asChar", None))
        self.cbxConvRx.setItemText(1, QCoreApplication.translate("Form", u"asHex", None))
        self.cbxConvRx.setItemText(2, QCoreApplication.translate("Form", u"asInt", None))

        self.label.setText(QCoreApplication.translate("Form", u"Protocol", None))
        self.cbxProtocol.setItemText(0, QCoreApplication.translate("Form", u"None", None))
        self.cbxProtocol.setItemText(1, QCoreApplication.translate("Form", u"Double", None))

        self.btLogSave.setText(QCoreApplication.translate("Form", u"Save...", None))
    # retranslateUi

