# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'pyEthCtrl.ui'
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
        Form.resize(802, 623)
        self.horizontalLayout_2 = QHBoxLayout(Form)
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.splitter = QSplitter(Form)
        self.splitter.setObjectName(u"splitter")
        self.splitter.setOrientation(Qt.Horizontal)
        self.widget = QWidget(self.splitter)
        self.widget.setObjectName(u"widget")
        self.verticalLayout_3 = QVBoxLayout(self.widget)
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.verticalLayout_3.setContentsMargins(0, 0, 0, 0)
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


        self.verticalLayout_3.addWidget(self.gbxTool)

        self.grCtrl = QGroupBox(self.widget)
        self.grCtrl.setObjectName(u"grCtrl")
        sizePolicy1 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Minimum)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.grCtrl.sizePolicy().hasHeightForWidth())
        self.grCtrl.setSizePolicy(sizePolicy1)
        self.grCtrl.setMinimumSize(QSize(0, 340))
        self.gridLayout = QGridLayout(self.grCtrl)
        self.gridLayout.setObjectName(u"gridLayout")
        self.gridLayout.setVerticalSpacing(4)
        self.gridLayout.setContentsMargins(-1, -1, -1, 9)
        self.edValue7 = QLineEdit(self.grCtrl)
        self.edValue7.setObjectName(u"edValue7")
        sizePolicy2 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Preferred)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(self.edValue7.sizePolicy().hasHeightForWidth())
        self.edValue7.setSizePolicy(sizePolicy2)
        self.edValue7.setMaximumSize(QSize(100, 16777215))

        self.gridLayout.addWidget(self.edValue7, 7, 1, 1, 1)

        self.cbxRegSel5 = QComboBox(self.grCtrl)
        self.cbxRegSel5.setObjectName(u"cbxRegSel5")
        sizePolicy3 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Preferred)
        sizePolicy3.setHorizontalStretch(0)
        sizePolicy3.setVerticalStretch(0)
        sizePolicy3.setHeightForWidth(self.cbxRegSel5.sizePolicy().hasHeightForWidth())
        self.cbxRegSel5.setSizePolicy(sizePolicy3)

        self.gridLayout.addWidget(self.cbxRegSel5, 5, 0, 1, 1)

        self.btGet8 = QPushButton(self.grCtrl)
        self.btGet8.setObjectName(u"btGet8")
        sizePolicy4 = QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Preferred)
        sizePolicy4.setHorizontalStretch(0)
        sizePolicy4.setVerticalStretch(0)
        sizePolicy4.setHeightForWidth(self.btGet8.sizePolicy().hasHeightForWidth())
        self.btGet8.setSizePolicy(sizePolicy4)

        self.gridLayout.addWidget(self.btGet8, 8, 3, 1, 1)

        self.cbxRegSel1 = QComboBox(self.grCtrl)
        self.cbxRegSel1.setObjectName(u"cbxRegSel1")
        sizePolicy3.setHeightForWidth(self.cbxRegSel1.sizePolicy().hasHeightForWidth())
        self.cbxRegSel1.setSizePolicy(sizePolicy3)

        self.gridLayout.addWidget(self.cbxRegSel1, 1, 0, 1, 1)

        self.btSet6 = QPushButton(self.grCtrl)
        self.btSet6.setObjectName(u"btSet6")
        sizePolicy4.setHeightForWidth(self.btSet6.sizePolicy().hasHeightForWidth())
        self.btSet6.setSizePolicy(sizePolicy4)

        self.gridLayout.addWidget(self.btSet6, 6, 2, 1, 1)

        self.lblRegister = QLabel(self.grCtrl)
        self.lblRegister.setObjectName(u"lblRegister")
        sizePolicy3.setHeightForWidth(self.lblRegister.sizePolicy().hasHeightForWidth())
        self.lblRegister.setSizePolicy(sizePolicy3)

        self.gridLayout.addWidget(self.lblRegister, 0, 0, 1, 1)

        self.btGet9 = QPushButton(self.grCtrl)
        self.btGet9.setObjectName(u"btGet9")
        sizePolicy4.setHeightForWidth(self.btGet9.sizePolicy().hasHeightForWidth())
        self.btGet9.setSizePolicy(sizePolicy4)

        self.gridLayout.addWidget(self.btGet9, 9, 3, 1, 1)

        self.edValue10 = QLineEdit(self.grCtrl)
        self.edValue10.setObjectName(u"edValue10")
        sizePolicy2.setHeightForWidth(self.edValue10.sizePolicy().hasHeightForWidth())
        self.edValue10.setSizePolicy(sizePolicy2)
        self.edValue10.setMaximumSize(QSize(100, 16777215))

        self.gridLayout.addWidget(self.edValue10, 10, 1, 1, 1)

        self.edValue6 = QLineEdit(self.grCtrl)
        self.edValue6.setObjectName(u"edValue6")
        sizePolicy2.setHeightForWidth(self.edValue6.sizePolicy().hasHeightForWidth())
        self.edValue6.setSizePolicy(sizePolicy2)
        self.edValue6.setMaximumSize(QSize(100, 16777215))

        self.gridLayout.addWidget(self.edValue6, 6, 1, 1, 1)

        self.btGet4 = QPushButton(self.grCtrl)
        self.btGet4.setObjectName(u"btGet4")
        sizePolicy4.setHeightForWidth(self.btGet4.sizePolicy().hasHeightForWidth())
        self.btGet4.setSizePolicy(sizePolicy4)

        self.gridLayout.addWidget(self.btGet4, 4, 3, 1, 1)

        self.cbxRegSel9 = QComboBox(self.grCtrl)
        self.cbxRegSel9.setObjectName(u"cbxRegSel9")
        sizePolicy3.setHeightForWidth(self.cbxRegSel9.sizePolicy().hasHeightForWidth())
        self.cbxRegSel9.setSizePolicy(sizePolicy3)

        self.gridLayout.addWidget(self.cbxRegSel9, 9, 0, 1, 1)

        self.btGet2 = QPushButton(self.grCtrl)
        self.btGet2.setObjectName(u"btGet2")
        sizePolicy4.setHeightForWidth(self.btGet2.sizePolicy().hasHeightForWidth())
        self.btGet2.setSizePolicy(sizePolicy4)

        self.gridLayout.addWidget(self.btGet2, 2, 3, 1, 1)

        self.btGet3 = QPushButton(self.grCtrl)
        self.btGet3.setObjectName(u"btGet3")
        sizePolicy4.setHeightForWidth(self.btGet3.sizePolicy().hasHeightForWidth())
        self.btGet3.setSizePolicy(sizePolicy4)

        self.gridLayout.addWidget(self.btGet3, 3, 3, 1, 1)

        self.cbxRegSel8 = QComboBox(self.grCtrl)
        self.cbxRegSel8.setObjectName(u"cbxRegSel8")
        sizePolicy3.setHeightForWidth(self.cbxRegSel8.sizePolicy().hasHeightForWidth())
        self.cbxRegSel8.setSizePolicy(sizePolicy3)

        self.gridLayout.addWidget(self.cbxRegSel8, 8, 0, 1, 1)

        self.cbxRegSel3 = QComboBox(self.grCtrl)
        self.cbxRegSel3.setObjectName(u"cbxRegSel3")
        sizePolicy3.setHeightForWidth(self.cbxRegSel3.sizePolicy().hasHeightForWidth())
        self.cbxRegSel3.setSizePolicy(sizePolicy3)

        self.gridLayout.addWidget(self.cbxRegSel3, 3, 0, 1, 1)

        self.cbxRegSel6 = QComboBox(self.grCtrl)
        self.cbxRegSel6.setObjectName(u"cbxRegSel6")
        sizePolicy3.setHeightForWidth(self.cbxRegSel6.sizePolicy().hasHeightForWidth())
        self.cbxRegSel6.setSizePolicy(sizePolicy3)

        self.gridLayout.addWidget(self.cbxRegSel6, 6, 0, 1, 1)

        self.btSet8 = QPushButton(self.grCtrl)
        self.btSet8.setObjectName(u"btSet8")
        sizePolicy4.setHeightForWidth(self.btSet8.sizePolicy().hasHeightForWidth())
        self.btSet8.setSizePolicy(sizePolicy4)

        self.gridLayout.addWidget(self.btSet8, 8, 2, 1, 1)

        self.btGet10 = QPushButton(self.grCtrl)
        self.btGet10.setObjectName(u"btGet10")
        sizePolicy4.setHeightForWidth(self.btGet10.sizePolicy().hasHeightForWidth())
        self.btGet10.setSizePolicy(sizePolicy4)

        self.gridLayout.addWidget(self.btGet10, 10, 3, 1, 1)

        self.btSet1 = QPushButton(self.grCtrl)
        self.btSet1.setObjectName(u"btSet1")
        sizePolicy4.setHeightForWidth(self.btSet1.sizePolicy().hasHeightForWidth())
        self.btSet1.setSizePolicy(sizePolicy4)

        self.gridLayout.addWidget(self.btSet1, 1, 2, 1, 1)

        self.btGet6 = QPushButton(self.grCtrl)
        self.btGet6.setObjectName(u"btGet6")
        sizePolicy4.setHeightForWidth(self.btGet6.sizePolicy().hasHeightForWidth())
        self.btGet6.setSizePolicy(sizePolicy4)

        self.gridLayout.addWidget(self.btGet6, 6, 3, 1, 1)

        self.btSet9 = QPushButton(self.grCtrl)
        self.btSet9.setObjectName(u"btSet9")
        sizePolicy4.setHeightForWidth(self.btSet9.sizePolicy().hasHeightForWidth())
        self.btSet9.setSizePolicy(sizePolicy4)

        self.gridLayout.addWidget(self.btSet9, 9, 2, 1, 1)

        self.btSet4 = QPushButton(self.grCtrl)
        self.btSet4.setObjectName(u"btSet4")
        sizePolicy4.setHeightForWidth(self.btSet4.sizePolicy().hasHeightForWidth())
        self.btSet4.setSizePolicy(sizePolicy4)

        self.gridLayout.addWidget(self.btSet4, 4, 2, 1, 1)

        self.edValue4 = QLineEdit(self.grCtrl)
        self.edValue4.setObjectName(u"edValue4")
        sizePolicy2.setHeightForWidth(self.edValue4.sizePolicy().hasHeightForWidth())
        self.edValue4.setSizePolicy(sizePolicy2)
        self.edValue4.setMaximumSize(QSize(100, 16777215))

        self.gridLayout.addWidget(self.edValue4, 4, 1, 1, 1)

        self.cbxRegSel2 = QComboBox(self.grCtrl)
        self.cbxRegSel2.setObjectName(u"cbxRegSel2")
        sizePolicy3.setHeightForWidth(self.cbxRegSel2.sizePolicy().hasHeightForWidth())
        self.cbxRegSel2.setSizePolicy(sizePolicy3)

        self.gridLayout.addWidget(self.cbxRegSel2, 2, 0, 1, 1)

        self.edValue5 = QLineEdit(self.grCtrl)
        self.edValue5.setObjectName(u"edValue5")
        sizePolicy2.setHeightForWidth(self.edValue5.sizePolicy().hasHeightForWidth())
        self.edValue5.setSizePolicy(sizePolicy2)
        self.edValue5.setMaximumSize(QSize(100, 16777215))

        self.gridLayout.addWidget(self.edValue5, 5, 1, 1, 1)

        self.cbxRegSel10 = QComboBox(self.grCtrl)
        self.cbxRegSel10.setObjectName(u"cbxRegSel10")
        sizePolicy3.setHeightForWidth(self.cbxRegSel10.sizePolicy().hasHeightForWidth())
        self.cbxRegSel10.setSizePolicy(sizePolicy3)

        self.gridLayout.addWidget(self.cbxRegSel10, 10, 0, 1, 1)

        self.btGet7 = QPushButton(self.grCtrl)
        self.btGet7.setObjectName(u"btGet7")
        sizePolicy4.setHeightForWidth(self.btGet7.sizePolicy().hasHeightForWidth())
        self.btGet7.setSizePolicy(sizePolicy4)

        self.gridLayout.addWidget(self.btGet7, 7, 3, 1, 1)

        self.cbxRegSel7 = QComboBox(self.grCtrl)
        self.cbxRegSel7.setObjectName(u"cbxRegSel7")
        sizePolicy3.setHeightForWidth(self.cbxRegSel7.sizePolicy().hasHeightForWidth())
        self.cbxRegSel7.setSizePolicy(sizePolicy3)

        self.gridLayout.addWidget(self.cbxRegSel7, 7, 0, 1, 1)

        self.edValue2 = QLineEdit(self.grCtrl)
        self.edValue2.setObjectName(u"edValue2")
        sizePolicy2.setHeightForWidth(self.edValue2.sizePolicy().hasHeightForWidth())
        self.edValue2.setSizePolicy(sizePolicy2)
        self.edValue2.setMaximumSize(QSize(100, 16777215))

        self.gridLayout.addWidget(self.edValue2, 2, 1, 1, 1)

        self.btSet5 = QPushButton(self.grCtrl)
        self.btSet5.setObjectName(u"btSet5")
        sizePolicy4.setHeightForWidth(self.btSet5.sizePolicy().hasHeightForWidth())
        self.btSet5.setSizePolicy(sizePolicy4)

        self.gridLayout.addWidget(self.btSet5, 5, 2, 1, 1)

        self.edValue1 = QLineEdit(self.grCtrl)
        self.edValue1.setObjectName(u"edValue1")
        sizePolicy2.setHeightForWidth(self.edValue1.sizePolicy().hasHeightForWidth())
        self.edValue1.setSizePolicy(sizePolicy2)
        self.edValue1.setMaximumSize(QSize(100, 16777215))

        self.gridLayout.addWidget(self.edValue1, 1, 1, 1, 1)

        self.edValue3 = QLineEdit(self.grCtrl)
        self.edValue3.setObjectName(u"edValue3")
        sizePolicy2.setHeightForWidth(self.edValue3.sizePolicy().hasHeightForWidth())
        self.edValue3.setSizePolicy(sizePolicy2)
        self.edValue3.setMaximumSize(QSize(100, 16777215))

        self.gridLayout.addWidget(self.edValue3, 3, 1, 1, 1)

        self.edValue9 = QLineEdit(self.grCtrl)
        self.edValue9.setObjectName(u"edValue9")
        sizePolicy2.setHeightForWidth(self.edValue9.sizePolicy().hasHeightForWidth())
        self.edValue9.setSizePolicy(sizePolicy2)
        self.edValue9.setMaximumSize(QSize(100, 16777215))

        self.gridLayout.addWidget(self.edValue9, 9, 1, 1, 1)

        self.cbxRegSel4 = QComboBox(self.grCtrl)
        self.cbxRegSel4.setObjectName(u"cbxRegSel4")
        sizePolicy3.setHeightForWidth(self.cbxRegSel4.sizePolicy().hasHeightForWidth())
        self.cbxRegSel4.setSizePolicy(sizePolicy3)

        self.gridLayout.addWidget(self.cbxRegSel4, 4, 0, 1, 1)

        self.btGet1 = QPushButton(self.grCtrl)
        self.btGet1.setObjectName(u"btGet1")
        sizePolicy4.setHeightForWidth(self.btGet1.sizePolicy().hasHeightForWidth())
        self.btGet1.setSizePolicy(sizePolicy4)

        self.gridLayout.addWidget(self.btGet1, 1, 3, 1, 1)

        self.btSet2 = QPushButton(self.grCtrl)
        self.btSet2.setObjectName(u"btSet2")
        sizePolicy4.setHeightForWidth(self.btSet2.sizePolicy().hasHeightForWidth())
        self.btSet2.setSizePolicy(sizePolicy4)

        self.gridLayout.addWidget(self.btSet2, 2, 2, 1, 1)

        self.lblWriteValue = QLabel(self.grCtrl)
        self.lblWriteValue.setObjectName(u"lblWriteValue")
        sizePolicy4.setHeightForWidth(self.lblWriteValue.sizePolicy().hasHeightForWidth())
        self.lblWriteValue.setSizePolicy(sizePolicy4)

        self.gridLayout.addWidget(self.lblWriteValue, 0, 1, 1, 1)

        self.btGet5 = QPushButton(self.grCtrl)
        self.btGet5.setObjectName(u"btGet5")
        sizePolicy4.setHeightForWidth(self.btGet5.sizePolicy().hasHeightForWidth())
        self.btGet5.setSizePolicy(sizePolicy4)

        self.gridLayout.addWidget(self.btGet5, 5, 3, 1, 1)

        self.btSet10 = QPushButton(self.grCtrl)
        self.btSet10.setObjectName(u"btSet10")
        sizePolicy4.setHeightForWidth(self.btSet10.sizePolicy().hasHeightForWidth())
        self.btSet10.setSizePolicy(sizePolicy4)

        self.gridLayout.addWidget(self.btSet10, 10, 2, 1, 1)

        self.edValue8 = QLineEdit(self.grCtrl)
        self.edValue8.setObjectName(u"edValue8")
        sizePolicy2.setHeightForWidth(self.edValue8.sizePolicy().hasHeightForWidth())
        self.edValue8.setSizePolicy(sizePolicy2)
        self.edValue8.setMaximumSize(QSize(100, 16777215))

        self.gridLayout.addWidget(self.edValue8, 8, 1, 1, 1)

        self.btSet3 = QPushButton(self.grCtrl)
        self.btSet3.setObjectName(u"btSet3")
        sizePolicy4.setHeightForWidth(self.btSet3.sizePolicy().hasHeightForWidth())
        self.btSet3.setSizePolicy(sizePolicy4)

        self.gridLayout.addWidget(self.btSet3, 3, 2, 1, 1)

        self.btSet7 = QPushButton(self.grCtrl)
        self.btSet7.setObjectName(u"btSet7")
        sizePolicy4.setHeightForWidth(self.btSet7.sizePolicy().hasHeightForWidth())
        self.btSet7.setSizePolicy(sizePolicy4)

        self.gridLayout.addWidget(self.btSet7, 7, 2, 1, 1)


        self.verticalLayout_3.addWidget(self.grCtrl)

        self.groupBox = QGroupBox(self.widget)
        self.groupBox.setObjectName(u"groupBox")
        sizePolicy5 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Minimum)
        sizePolicy5.setHorizontalStretch(0)
        sizePolicy5.setVerticalStretch(0)
        sizePolicy5.setHeightForWidth(self.groupBox.sizePolicy().hasHeightForWidth())
        self.groupBox.setSizePolicy(sizePolicy5)
        self.gridLayout_2 = QGridLayout(self.groupBox)
        self.gridLayout_2.setObjectName(u"gridLayout_2")
        self.btDebug2 = QPushButton(self.groupBox)
        self.btDebug2.setObjectName(u"btDebug2")
        sizePolicy6 = QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Expanding)
        sizePolicy6.setHorizontalStretch(0)
        sizePolicy6.setVerticalStretch(0)
        sizePolicy6.setHeightForWidth(self.btDebug2.sizePolicy().hasHeightForWidth())
        self.btDebug2.setSizePolicy(sizePolicy6)
        self.btDebug2.setMaximumSize(QSize(16777215, 40))

        self.gridLayout_2.addWidget(self.btDebug2, 0, 1, 1, 1)

        self.btDebug4 = QPushButton(self.groupBox)
        self.btDebug4.setObjectName(u"btDebug4")
        sizePolicy6.setHeightForWidth(self.btDebug4.sizePolicy().hasHeightForWidth())
        self.btDebug4.setSizePolicy(sizePolicy6)
        self.btDebug4.setMaximumSize(QSize(16777215, 40))

        self.gridLayout_2.addWidget(self.btDebug4, 1, 0, 1, 1)

        self.btDebug5 = QPushButton(self.groupBox)
        self.btDebug5.setObjectName(u"btDebug5")
        sizePolicy6.setHeightForWidth(self.btDebug5.sizePolicy().hasHeightForWidth())
        self.btDebug5.setSizePolicy(sizePolicy6)
        self.btDebug5.setMaximumSize(QSize(16777215, 40))

        self.gridLayout_2.addWidget(self.btDebug5, 1, 1, 1, 1)

        self.btDebug6 = QPushButton(self.groupBox)
        self.btDebug6.setObjectName(u"btDebug6")
        sizePolicy6.setHeightForWidth(self.btDebug6.sizePolicy().hasHeightForWidth())
        self.btDebug6.setSizePolicy(sizePolicy6)
        self.btDebug6.setMaximumSize(QSize(16777215, 40))

        self.gridLayout_2.addWidget(self.btDebug6, 1, 2, 1, 1)

        self.verticalSpacer = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.gridLayout_2.addItem(self.verticalSpacer, 2, 1, 1, 1)

        self.btDebug1 = QPushButton(self.groupBox)
        self.btDebug1.setObjectName(u"btDebug1")
        sizePolicy6.setHeightForWidth(self.btDebug1.sizePolicy().hasHeightForWidth())
        self.btDebug1.setSizePolicy(sizePolicy6)
        self.btDebug1.setMaximumSize(QSize(16777215, 40))

        self.gridLayout_2.addWidget(self.btDebug1, 0, 0, 1, 1)

        self.btDebug3 = QPushButton(self.groupBox)
        self.btDebug3.setObjectName(u"btDebug3")
        sizePolicy6.setHeightForWidth(self.btDebug3.sizePolicy().hasHeightForWidth())
        self.btDebug3.setSizePolicy(sizePolicy6)
        self.btDebug3.setMaximumSize(QSize(16777215, 40))

        self.gridLayout_2.addWidget(self.btDebug3, 0, 2, 1, 1)


        self.verticalLayout_3.addWidget(self.groupBox)

        self.splitter.addWidget(self.widget)
        self.layoutWidget = QWidget(self.splitter)
        self.layoutWidget.setObjectName(u"layoutWidget")
        self.verticalLayout_2 = QVBoxLayout(self.layoutWidget)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.verticalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.grLog = QGroupBox(self.layoutWidget)
        self.grLog.setObjectName(u"grLog")
        self.verticalLayout = QVBoxLayout(self.grLog)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.btClearLog = QPushButton(self.grLog)
        self.btClearLog.setObjectName(u"btClearLog")
        self.btClearLog.setMinimumSize(QSize(0, 40))

        self.verticalLayout.addWidget(self.btClearLog)


        self.verticalLayout_2.addWidget(self.grLog)

        self.txtEdit = QTextEdit(self.layoutWidget)
        self.txtEdit.setObjectName(u"txtEdit")
        font = QFont()
        font.setFamily(u"Courier New")
        self.txtEdit.setFont(font)

        self.verticalLayout_2.addWidget(self.txtEdit)

        self.splitter.addWidget(self.layoutWidget)

        self.horizontalLayout_2.addWidget(self.splitter)


        self.retranslateUi(Form)

        QMetaObject.connectSlotsByName(Form)
    # setupUi

    def retranslateUi(self, Form):
        Form.setWindowTitle(QCoreApplication.translate("Form", u"Form", None))
        self.gbxTool.setTitle(QCoreApplication.translate("Form", u"COM port", None))
        self.btStatus.setText("")
        self.btConnect.setText(QCoreApplication.translate("Form", u"Connect", None))
        self.grCtrl.setTitle(QCoreApplication.translate("Form", u"Registers", None))
        self.btGet8.setText(QCoreApplication.translate("Form", u"Get", None))
        self.btSet6.setText(QCoreApplication.translate("Form", u"Set", None))
        self.lblRegister.setText(QCoreApplication.translate("Form", u"Register Names", None))
        self.btGet9.setText(QCoreApplication.translate("Form", u"Get", None))
        self.btGet4.setText(QCoreApplication.translate("Form", u"Get", None))
        self.btGet2.setText(QCoreApplication.translate("Form", u"Get", None))
        self.btGet3.setText(QCoreApplication.translate("Form", u"Get", None))
        self.btSet8.setText(QCoreApplication.translate("Form", u"Set", None))
        self.btGet10.setText(QCoreApplication.translate("Form", u"Get", None))
        self.btSet1.setText(QCoreApplication.translate("Form", u"Set", None))
        self.btGet6.setText(QCoreApplication.translate("Form", u"Get", None))
        self.btSet9.setText(QCoreApplication.translate("Form", u"Set", None))
        self.btSet4.setText(QCoreApplication.translate("Form", u"Set", None))
        self.btGet7.setText(QCoreApplication.translate("Form", u"Get", None))
        self.btSet5.setText(QCoreApplication.translate("Form", u"Set", None))
        self.btGet1.setText(QCoreApplication.translate("Form", u"Get", None))
        self.btSet2.setText(QCoreApplication.translate("Form", u"Set", None))
        self.lblWriteValue.setText(QCoreApplication.translate("Form", u"Wite Value", None))
        self.btGet5.setText(QCoreApplication.translate("Form", u"Get", None))
        self.btSet10.setText(QCoreApplication.translate("Form", u"Set", None))
        self.btSet3.setText(QCoreApplication.translate("Form", u"Set", None))
        self.btSet7.setText(QCoreApplication.translate("Form", u"Set", None))
        self.groupBox.setTitle(QCoreApplication.translate("Form", u"Debug", None))
        self.btDebug2.setText(QCoreApplication.translate("Form", u"Action2", None))
        self.btDebug4.setText(QCoreApplication.translate("Form", u"Action4", None))
        self.btDebug5.setText(QCoreApplication.translate("Form", u"Action5", None))
        self.btDebug6.setText(QCoreApplication.translate("Form", u"Action6", None))
        self.btDebug1.setText(QCoreApplication.translate("Form", u"Action1", None))
        self.btDebug3.setText(QCoreApplication.translate("Form", u"Action3", None))
        self.grLog.setTitle(QCoreApplication.translate("Form", u"Log", None))
        self.btClearLog.setText(QCoreApplication.translate("Form", u"Clear", None))
    # retranslateUi

