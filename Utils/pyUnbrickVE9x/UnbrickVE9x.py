# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'UnbrickVE9x.ui'
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
        Form.resize(287, 438)
        self.verticalLayout = QVBoxLayout(Form)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.gbxTool = QGroupBox(Form)
        self.gbxTool.setObjectName(u"gbxTool")
        self.horizontalLayout = QHBoxLayout(self.gbxTool)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.cbxComSel = QComboBox(self.gbxTool)
        self.cbxComSel.setObjectName(u"cbxComSel")
        self.cbxComSel.setMinimumSize(QSize(0, 24))
        self.cbxComSel.setMaximumSize(QSize(80, 16777215))

        self.horizontalLayout.addWidget(self.cbxComSel)

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


        self.verticalLayout.addWidget(self.gbxTool)

        self.btClear = QPushButton(Form)
        self.btClear.setObjectName(u"btClear")
        self.btClear.setMinimumSize(QSize(0, 50))

        self.verticalLayout.addWidget(self.btClear)

        self.txtLog = QTextEdit(Form)
        self.txtLog.setObjectName(u"txtLog")

        self.verticalLayout.addWidget(self.txtLog)


        self.retranslateUi(Form)

        QMetaObject.connectSlotsByName(Form)
    # setupUi

    def retranslateUi(self, Form):
        Form.setWindowTitle(QCoreApplication.translate("Form", u"Form", None))
        self.gbxTool.setTitle(QCoreApplication.translate("Form", u"Control", None))
        self.btStatus.setText("")
        self.btConnect.setText(QCoreApplication.translate("Form", u"Connect", None))
        self.btClear.setText(QCoreApplication.translate("Form", u"Clear Flash", None))
    # retranslateUi

