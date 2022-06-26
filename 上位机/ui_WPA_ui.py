# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'WPA_ui.ui'
##
## Created by: Qt User Interface Compiler version 6.3.0
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QApplication, QCheckBox, QComboBox, QDial,
    QGridLayout, QHBoxLayout, QLabel, QLineEdit,
    QMainWindow, QMenuBar, QPlainTextEdit, QPushButton,
    QSizePolicy, QStatusBar, QVBoxLayout, QWidget)

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(815, 426)
        MainWindow.setToolButtonStyle(Qt.ToolButtonIconOnly)
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.plainTextEdit_ser_rec = QPlainTextEdit(self.centralwidget)
        self.plainTextEdit_ser_rec.setObjectName(u"plainTextEdit_ser_rec")
        self.plainTextEdit_ser_rec.setGeometry(QRect(260, 50, 401, 291))
        self.plainTextEdit_ser_rec.viewport().setProperty("cursor", QCursor(Qt.ArrowCursor))
        self.dial_theta = QDial(self.centralwidget)
        self.dial_theta.setObjectName(u"dial_theta")
        self.dial_theta.setGeometry(QRect(670, 230, 131, 131))
        self.dial_theta.setCursor(QCursor(Qt.CrossCursor))
        self.dial_theta.setLayoutDirection(Qt.LeftToRight)
        self.dial_theta.setAutoFillBackground(False)
        self.dial_theta.setLocale(QLocale(QLocale.Chinese, QLocale.China))
        self.dial_theta.setMinimum(-180)
        self.dial_theta.setMaximum(179)
        self.dial_theta.setOrientation(Qt.Vertical)
        self.dial_theta.setInvertedAppearance(False)
        self.dial_theta.setInvertedControls(False)
        self.dial_theta.setWrapping(True)
        self.dial_theta.setNotchTarget(1.000000000000000)
        self.dial_theta.setNotchesVisible(False)
        self.label_ref = QLabel(self.centralwidget)
        self.label_ref.setObjectName(u"label_ref")
        self.label_ref.setGeometry(QRect(680, 350, 54, 21))
        self.label_ref.setLayoutDirection(Qt.LeftToRight)
        self.checkBox_ser_display = QCheckBox(self.centralwidget)
        self.checkBox_ser_display.setObjectName(u"checkBox_ser_display")
        self.checkBox_ser_display.setGeometry(QRect(580, 50, 79, 20))
        self.widget = QWidget(self.centralwidget)
        self.widget.setObjectName(u"widget")
        self.widget.setGeometry(QRect(13, 14, 231, 370))
        self.gridLayout = QGridLayout(self.widget)
        self.gridLayout.setObjectName(u"gridLayout")
        self.gridLayout.setContentsMargins(0, 0, 0, 0)
        self.comboBox_dvel = QComboBox(self.widget)
        self.comboBox_dvel.addItem("")
        self.comboBox_dvel.addItem("")
        self.comboBox_dvel.addItem("")
        self.comboBox_dvel.setObjectName(u"comboBox_dvel")
        self.comboBox_dvel.setEditable(False)

        self.gridLayout.addWidget(self.comboBox_dvel, 1, 2, 1, 1)

        self.text_dvel = QLineEdit(self.widget)
        self.text_dvel.setObjectName(u"text_dvel")

        self.gridLayout.addWidget(self.text_dvel, 1, 1, 1, 1)

        self.text_omega = QLineEdit(self.widget)
        self.text_omega.setObjectName(u"text_omega")

        self.gridLayout.addWidget(self.text_omega, 2, 1, 1, 1)

        self.comboBox_ref = QComboBox(self.widget)
        self.comboBox_ref.addItem("")
        self.comboBox_ref.addItem("")
        self.comboBox_ref.addItem("")
        self.comboBox_ref.setObjectName(u"comboBox_ref")
        self.comboBox_ref.setEditable(False)

        self.gridLayout.addWidget(self.comboBox_ref, 5, 2, 1, 1)

        self.text_freq = QLineEdit(self.widget)
        self.text_freq.setObjectName(u"text_freq")

        self.gridLayout.addWidget(self.text_freq, 12, 1, 1, 1)

        self.comboBox_theta = QComboBox(self.widget)
        self.comboBox_theta.addItem("")
        self.comboBox_theta.addItem("")
        self.comboBox_theta.addItem("")
        self.comboBox_theta.setObjectName(u"comboBox_theta")
        self.comboBox_theta.setEditable(False)

        self.gridLayout.addWidget(self.comboBox_theta, 0, 2, 1, 1)

        self.comboBox_freq = QComboBox(self.widget)
        self.comboBox_freq.addItem("")
        self.comboBox_freq.addItem("")
        self.comboBox_freq.addItem("")
        self.comboBox_freq.setObjectName(u"comboBox_freq")
        self.comboBox_freq.setEditable(False)

        self.gridLayout.addWidget(self.comboBox_freq, 12, 2, 1, 1)

        self.lab_dvel = QLabel(self.widget)
        self.lab_dvel.setObjectName(u"lab_dvel")

        self.gridLayout.addWidget(self.lab_dvel, 1, 0, 1, 1)

        self.lab_ki = QLabel(self.widget)
        self.lab_ki.setObjectName(u"lab_ki")

        self.gridLayout.addWidget(self.lab_ki, 10, 0, 1, 1)

        self.lab_beta = QLabel(self.widget)
        self.lab_beta.setObjectName(u"lab_beta")

        self.gridLayout.addWidget(self.lab_beta, 3, 0, 1, 1)

        self.text_theta = QLineEdit(self.widget)
        self.text_theta.setObjectName(u"text_theta")

        self.gridLayout.addWidget(self.text_theta, 0, 1, 1, 1)

        self.text_ki = QLineEdit(self.widget)
        self.text_ki.setObjectName(u"text_ki")

        self.gridLayout.addWidget(self.text_ki, 10, 1, 1, 1)

        self.text_kp = QLineEdit(self.widget)
        self.text_kp.setObjectName(u"text_kp")

        self.gridLayout.addWidget(self.text_kp, 9, 1, 1, 1)

        self.text_u = QLineEdit(self.widget)
        self.text_u.setObjectName(u"text_u")

        self.gridLayout.addWidget(self.text_u, 7, 1, 1, 1)

        self.comboBox_kp = QComboBox(self.widget)
        self.comboBox_kp.addItem("")
        self.comboBox_kp.addItem("")
        self.comboBox_kp.addItem("")
        self.comboBox_kp.setObjectName(u"comboBox_kp")
        self.comboBox_kp.setEditable(False)

        self.gridLayout.addWidget(self.comboBox_kp, 9, 2, 1, 1)

        self.text_ref = QLineEdit(self.widget)
        self.text_ref.setObjectName(u"text_ref")

        self.gridLayout.addWidget(self.text_ref, 5, 1, 1, 1)

        self.lab_vel_bal = QLabel(self.widget)
        self.lab_vel_bal.setObjectName(u"lab_vel_bal")

        self.gridLayout.addWidget(self.lab_vel_bal, 4, 0, 1, 1)

        self.lab_omega = QLabel(self.widget)
        self.lab_omega.setObjectName(u"lab_omega")

        self.gridLayout.addWidget(self.lab_omega, 2, 0, 1, 1)

        self.comboBox_kd = QComboBox(self.widget)
        self.comboBox_kd.addItem("")
        self.comboBox_kd.addItem("")
        self.comboBox_kd.addItem("")
        self.comboBox_kd.setObjectName(u"comboBox_kd")
        self.comboBox_kd.setEditable(False)

        self.gridLayout.addWidget(self.comboBox_kd, 11, 2, 1, 1)

        self.text_beta = QLineEdit(self.widget)
        self.text_beta.setObjectName(u"text_beta")

        self.gridLayout.addWidget(self.text_beta, 3, 1, 1, 1)

        self.lab_ref = QLabel(self.widget)
        self.lab_ref.setObjectName(u"lab_ref")

        self.gridLayout.addWidget(self.lab_ref, 5, 0, 1, 1)

        self.comboBox_beta = QComboBox(self.widget)
        self.comboBox_beta.addItem("")
        self.comboBox_beta.addItem("")
        self.comboBox_beta.addItem("")
        self.comboBox_beta.setObjectName(u"comboBox_beta")
        self.comboBox_beta.setEditable(False)

        self.gridLayout.addWidget(self.comboBox_beta, 3, 2, 1, 1)

        self.comboBox_u = QComboBox(self.widget)
        self.comboBox_u.addItem("")
        self.comboBox_u.addItem("")
        self.comboBox_u.addItem("")
        self.comboBox_u.setObjectName(u"comboBox_u")
        self.comboBox_u.setEditable(False)

        self.gridLayout.addWidget(self.comboBox_u, 7, 2, 1, 1)

        self.text_vel_bal = QLineEdit(self.widget)
        self.text_vel_bal.setObjectName(u"text_vel_bal")

        self.gridLayout.addWidget(self.text_vel_bal, 4, 1, 1, 1)

        self.comboBox_ki = QComboBox(self.widget)
        self.comboBox_ki.addItem("")
        self.comboBox_ki.addItem("")
        self.comboBox_ki.addItem("")
        self.comboBox_ki.setObjectName(u"comboBox_ki")
        self.comboBox_ki.setEditable(False)

        self.gridLayout.addWidget(self.comboBox_ki, 10, 2, 1, 1)

        self.comboBox_omega = QComboBox(self.widget)
        self.comboBox_omega.addItem("")
        self.comboBox_omega.addItem("")
        self.comboBox_omega.addItem("")
        self.comboBox_omega.setObjectName(u"comboBox_omega")
        self.comboBox_omega.setEditable(False)

        self.gridLayout.addWidget(self.comboBox_omega, 2, 2, 1, 1)

        self.lab_kd = QLabel(self.widget)
        self.lab_kd.setObjectName(u"lab_kd")

        self.gridLayout.addWidget(self.lab_kd, 11, 0, 1, 1)

        self.comboBox_vel_bal = QComboBox(self.widget)
        self.comboBox_vel_bal.addItem("")
        self.comboBox_vel_bal.addItem("")
        self.comboBox_vel_bal.addItem("")
        self.comboBox_vel_bal.setObjectName(u"comboBox_vel_bal")
        self.comboBox_vel_bal.setEditable(False)

        self.gridLayout.addWidget(self.comboBox_vel_bal, 4, 2, 1, 1)

        self.lab_kp = QLabel(self.widget)
        self.lab_kp.setObjectName(u"lab_kp")

        self.gridLayout.addWidget(self.lab_kp, 9, 0, 1, 1)

        self.text_kd = QLineEdit(self.widget)
        self.text_kd.setObjectName(u"text_kd")

        self.gridLayout.addWidget(self.text_kd, 11, 1, 1, 1)

        self.lab_freq = QLabel(self.widget)
        self.lab_freq.setObjectName(u"lab_freq")

        self.gridLayout.addWidget(self.lab_freq, 12, 0, 1, 1)

        self.lab_theta = QLabel(self.widget)
        self.lab_theta.setObjectName(u"lab_theta")

        self.gridLayout.addWidget(self.lab_theta, 0, 0, 1, 1)

        self.lab_u = QLabel(self.widget)
        self.lab_u.setObjectName(u"lab_u")

        self.gridLayout.addWidget(self.lab_u, 7, 0, 1, 1)

        self.widget1 = QWidget(self.centralwidget)
        self.widget1.setObjectName(u"widget1")
        self.widget1.setGeometry(QRect(260, 345, 401, 31))
        self.horizontalLayout_2 = QHBoxLayout(self.widget1)
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.horizontalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.lineEdit_ser_send = QLineEdit(self.widget1)
        self.lineEdit_ser_send.setObjectName(u"lineEdit_ser_send")

        self.horizontalLayout_2.addWidget(self.lineEdit_ser_send)

        self.pushButton_ser_send = QPushButton(self.widget1)
        self.pushButton_ser_send.setObjectName(u"pushButton_ser_send")

        self.horizontalLayout_2.addWidget(self.pushButton_ser_send)

        self.widget2 = QWidget(self.centralwidget)
        self.widget2.setObjectName(u"widget2")
        self.widget2.setGeometry(QRect(260, 10, 255, 41))
        self.horizontalLayout_3 = QHBoxLayout(self.widget2)
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.horizontalLayout_3.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.lab_theta_2 = QLabel(self.widget2)
        self.lab_theta_2.setObjectName(u"lab_theta_2")

        self.horizontalLayout.addWidget(self.lab_theta_2)

        self.comboBox_ser = QComboBox(self.widget2)
        self.comboBox_ser.setObjectName(u"comboBox_ser")

        self.horizontalLayout.addWidget(self.comboBox_ser)

        self.pushButton_ser_refresh = QPushButton(self.widget2)
        self.pushButton_ser_refresh.setObjectName(u"pushButton_ser_refresh")

        self.horizontalLayout.addWidget(self.pushButton_ser_refresh)


        self.horizontalLayout_3.addLayout(self.horizontalLayout)

        self.label_ser_status = QLabel(self.widget2)
        self.label_ser_status.setObjectName(u"label_ser_status")

        self.horizontalLayout_3.addWidget(self.label_ser_status)

        self.widget3 = QWidget(self.centralwidget)
        self.widget3.setObjectName(u"widget3")
        self.widget3.setGeometry(QRect(690, 50, 101, 91))
        self.verticalLayout = QVBoxLayout(self.widget3)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.comboBox_val_set = QComboBox(self.widget3)
        self.comboBox_val_set.addItem("")
        self.comboBox_val_set.addItem("")
        self.comboBox_val_set.addItem("")
        self.comboBox_val_set.addItem("")
        self.comboBox_val_set.setObjectName(u"comboBox_val_set")

        self.verticalLayout.addWidget(self.comboBox_val_set)

        self.lineEdit_val_set = QLineEdit(self.widget3)
        self.lineEdit_val_set.setObjectName(u"lineEdit_val_set")

        self.verticalLayout.addWidget(self.lineEdit_val_set)

        self.pushButton_val_set = QPushButton(self.widget3)
        self.pushButton_val_set.setObjectName(u"pushButton_val_set")

        self.verticalLayout.addWidget(self.pushButton_val_set)

        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QMenuBar(MainWindow)
        self.menubar.setObjectName(u"menubar")
        self.menubar.setGeometry(QRect(0, 0, 815, 22))
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName(u"statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"MainWindow", None))
        self.label_ref.setText(QCoreApplication.translate("MainWindow", u"0", None))
        self.checkBox_ser_display.setText(QCoreApplication.translate("MainWindow", u"\u8fd0\u884c", None))
        self.comboBox_dvel.setItemText(0, QCoreApplication.translate("MainWindow", u"\u505c\u6b62\u8bfb\u53d6", None))
        self.comboBox_dvel.setItemText(1, QCoreApplication.translate("MainWindow", u"\u5355\u6b21\u8bfb\u53d6", None))
        self.comboBox_dvel.setItemText(2, QCoreApplication.translate("MainWindow", u"\u5faa\u73af\u8bfb\u53d6", None))

        self.comboBox_dvel.setCurrentText(QCoreApplication.translate("MainWindow", u"\u505c\u6b62\u8bfb\u53d6", None))
        self.comboBox_ref.setItemText(0, QCoreApplication.translate("MainWindow", u"\u505c\u6b62\u8bfb\u53d6", None))
        self.comboBox_ref.setItemText(1, QCoreApplication.translate("MainWindow", u"\u5355\u6b21\u8bfb\u53d6", None))
        self.comboBox_ref.setItemText(2, QCoreApplication.translate("MainWindow", u"\u5faa\u73af\u8bfb\u53d6", None))

        self.comboBox_ref.setCurrentText(QCoreApplication.translate("MainWindow", u"\u505c\u6b62\u8bfb\u53d6", None))
        self.comboBox_theta.setItemText(0, QCoreApplication.translate("MainWindow", u"\u505c\u6b62\u8bfb\u53d6", None))
        self.comboBox_theta.setItemText(1, QCoreApplication.translate("MainWindow", u"\u5355\u6b21\u8bfb\u53d6", None))
        self.comboBox_theta.setItemText(2, QCoreApplication.translate("MainWindow", u"\u5faa\u73af\u8bfb\u53d6", None))

        self.comboBox_theta.setCurrentText(QCoreApplication.translate("MainWindow", u"\u505c\u6b62\u8bfb\u53d6", None))
        self.comboBox_freq.setItemText(0, QCoreApplication.translate("MainWindow", u"\u505c\u6b62\u8bfb\u53d6", None))
        self.comboBox_freq.setItemText(1, QCoreApplication.translate("MainWindow", u"\u5355\u6b21\u8bfb\u53d6", None))
        self.comboBox_freq.setItemText(2, QCoreApplication.translate("MainWindow", u"\u5faa\u73af\u8bfb\u53d6", None))

        self.comboBox_freq.setCurrentText(QCoreApplication.translate("MainWindow", u"\u505c\u6b62\u8bfb\u53d6", None))
        self.lab_dvel.setText(QCoreApplication.translate("MainWindow", u"\u8f6c\u901f\u5dee\uff1a", None))
        self.lab_ki.setText(QCoreApplication.translate("MainWindow", u"KI\uff1a", None))
        self.lab_beta.setText(QCoreApplication.translate("MainWindow", u"\u89d2\u52a0\u901f\u5ea6\uff1a", None))
        self.comboBox_kp.setItemText(0, QCoreApplication.translate("MainWindow", u"\u505c\u6b62\u8bfb\u53d6", None))
        self.comboBox_kp.setItemText(1, QCoreApplication.translate("MainWindow", u"\u5355\u6b21\u8bfb\u53d6", None))
        self.comboBox_kp.setItemText(2, QCoreApplication.translate("MainWindow", u"\u5faa\u73af\u8bfb\u53d6", None))

        self.comboBox_kp.setCurrentText(QCoreApplication.translate("MainWindow", u"\u505c\u6b62\u8bfb\u53d6", None))
        self.lab_vel_bal.setText(QCoreApplication.translate("MainWindow", u"\u5e73\u8861\u8f6c\u901f\uff1a", None))
        self.lab_omega.setText(QCoreApplication.translate("MainWindow", u"\u89d2\u901f\u5ea6\uff1a", None))
        self.comboBox_kd.setItemText(0, QCoreApplication.translate("MainWindow", u"\u505c\u6b62\u8bfb\u53d6", None))
        self.comboBox_kd.setItemText(1, QCoreApplication.translate("MainWindow", u"\u5355\u6b21\u8bfb\u53d6", None))
        self.comboBox_kd.setItemText(2, QCoreApplication.translate("MainWindow", u"\u5faa\u73af\u8bfb\u53d6", None))

        self.comboBox_kd.setCurrentText(QCoreApplication.translate("MainWindow", u"\u505c\u6b62\u8bfb\u53d6", None))
        self.lab_ref.setText(QCoreApplication.translate("MainWindow", u"\u53c2\u8003\u89d2\u5ea6", None))
        self.comboBox_beta.setItemText(0, QCoreApplication.translate("MainWindow", u"\u505c\u6b62\u8bfb\u53d6", None))
        self.comboBox_beta.setItemText(1, QCoreApplication.translate("MainWindow", u"\u5355\u6b21\u8bfb\u53d6", None))
        self.comboBox_beta.setItemText(2, QCoreApplication.translate("MainWindow", u"\u5faa\u73af\u8bfb\u53d6", None))

        self.comboBox_beta.setCurrentText(QCoreApplication.translate("MainWindow", u"\u505c\u6b62\u8bfb\u53d6", None))
        self.comboBox_u.setItemText(0, QCoreApplication.translate("MainWindow", u"\u505c\u6b62\u8bfb\u53d6", None))
        self.comboBox_u.setItemText(1, QCoreApplication.translate("MainWindow", u"\u5355\u6b21\u8bfb\u53d6", None))
        self.comboBox_u.setItemText(2, QCoreApplication.translate("MainWindow", u"\u5faa\u73af\u8bfb\u53d6", None))

        self.comboBox_u.setCurrentText(QCoreApplication.translate("MainWindow", u"\u505c\u6b62\u8bfb\u53d6", None))
        self.comboBox_ki.setItemText(0, QCoreApplication.translate("MainWindow", u"\u505c\u6b62\u8bfb\u53d6", None))
        self.comboBox_ki.setItemText(1, QCoreApplication.translate("MainWindow", u"\u5355\u6b21\u8bfb\u53d6", None))
        self.comboBox_ki.setItemText(2, QCoreApplication.translate("MainWindow", u"\u5faa\u73af\u8bfb\u53d6", None))

        self.comboBox_ki.setCurrentText(QCoreApplication.translate("MainWindow", u"\u505c\u6b62\u8bfb\u53d6", None))
        self.comboBox_omega.setItemText(0, QCoreApplication.translate("MainWindow", u"\u505c\u6b62\u8bfb\u53d6", None))
        self.comboBox_omega.setItemText(1, QCoreApplication.translate("MainWindow", u"\u5355\u6b21\u8bfb\u53d6", None))
        self.comboBox_omega.setItemText(2, QCoreApplication.translate("MainWindow", u"\u5faa\u73af\u8bfb\u53d6", None))

        self.comboBox_omega.setCurrentText(QCoreApplication.translate("MainWindow", u"\u505c\u6b62\u8bfb\u53d6", None))
        self.lab_kd.setText(QCoreApplication.translate("MainWindow", u"KD\uff1a", None))
        self.comboBox_vel_bal.setItemText(0, QCoreApplication.translate("MainWindow", u"\u505c\u6b62\u8bfb\u53d6", None))
        self.comboBox_vel_bal.setItemText(1, QCoreApplication.translate("MainWindow", u"\u5355\u6b21\u8bfb\u53d6", None))
        self.comboBox_vel_bal.setItemText(2, QCoreApplication.translate("MainWindow", u"\u5faa\u73af\u8bfb\u53d6", None))

        self.comboBox_vel_bal.setCurrentText(QCoreApplication.translate("MainWindow", u"\u505c\u6b62\u8bfb\u53d6", None))
        self.lab_kp.setText(QCoreApplication.translate("MainWindow", u"KP\uff1a", None))
        self.lab_freq.setText(QCoreApplication.translate("MainWindow", u"\u8f93\u51fa\u9891\u7387\uff1a", None))
        self.lab_theta.setText(QCoreApplication.translate("MainWindow", u"\u89d2\u5ea6\uff1a", None))
        self.lab_u.setText(QCoreApplication.translate("MainWindow", u"\u63a7\u5236\u5668\u8f93\u51fa\uff1a", None))
        self.pushButton_ser_send.setText(QCoreApplication.translate("MainWindow", u"\u53d1\u9001", None))
        self.lab_theta_2.setText(QCoreApplication.translate("MainWindow", u"\u4e32\u53e3\uff1a", None))
        self.pushButton_ser_refresh.setText(QCoreApplication.translate("MainWindow", u"\u5237\u65b0", None))
        self.label_ser_status.setText(QCoreApplication.translate("MainWindow", u"   \u672a\u8fde\u63a5", None))
        self.comboBox_val_set.setItemText(0, QCoreApplication.translate("MainWindow", u"KP", None))
        self.comboBox_val_set.setItemText(1, QCoreApplication.translate("MainWindow", u"KI", None))
        self.comboBox_val_set.setItemText(2, QCoreApplication.translate("MainWindow", u"KD", None))
        self.comboBox_val_set.setItemText(3, QCoreApplication.translate("MainWindow", u"\u8f93\u51fa\u9891\u7387", None))

        self.lineEdit_val_set.setText(QCoreApplication.translate("MainWindow", u"0", None))
        self.pushButton_val_set.setText(QCoreApplication.translate("MainWindow", u"\u8bbe\u7f6e", None))
    # retranslateUi

