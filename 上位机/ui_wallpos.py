# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'wallpos.ui'
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
from PySide6.QtWebEngineWidgets import QWebEngineView
from PySide6.QtWidgets import (QApplication, QLabel, QMainWindow, QMenuBar,
    QSizePolicy, QStatusBar, QWidget)

from pyqtgraph import PlotWidget

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(970, 700)
        sizePolicy = QSizePolicy(QSizePolicy.Fixed, QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(MainWindow.sizePolicy().hasHeightForWidth())
        MainWindow.setSizePolicy(sizePolicy)
        MainWindow.setMinimumSize(QSize(970, 700))
        MainWindow.setMaximumSize(QSize(970, 700))
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.left = QLabel(self.centralwidget)
        self.left.setObjectName(u"left")
        self.left.setGeometry(QRect(10, 10, 640, 180))
        self.rs = QLabel(self.centralwidget)
        self.rs.setObjectName(u"rs")
        self.rs.setGeometry(QRect(140, 310, 120, 20))
        self.perc = QLabel(self.centralwidget)
        self.perc.setObjectName(u"perc")
        self.perc.setGeometry(QRect(260, 310, 120, 20))
        self.h = QLabel(self.centralwidget)
        self.h.setObjectName(u"h")
        self.h.setEnabled(True)
        self.h.setGeometry(QRect(380, 310, 120, 20))
        self.plotarea = PlotWidget(self.centralwidget)
        self.plotarea.setObjectName(u"plotarea")
        self.plotarea.setGeometry(QRect(660, 10, 300, 670))
        self.webEngineView = QWebEngineView(self.centralwidget)
        self.webEngineView.setObjectName(u"webEngineView")
        self.webEngineView.setGeometry(QRect(120, 410, 300, 200))
        self.webEngineView.setUrl(QUrl(u"about:blank"))
        self.ls = QLabel(self.centralwidget)
        self.ls.setObjectName(u"ls")
        self.ls.setGeometry(QRect(20, 310, 120, 20))
        MainWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName(u"statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.menubar = QMenuBar(MainWindow)
        self.menubar.setObjectName(u"menubar")
        self.menubar.setGeometry(QRect(0, 0, 970, 22))
        MainWindow.setMenuBar(self.menubar)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"MainWindow", None))
        self.left.setText("")
        self.rs.setText(QCoreApplication.translate("MainWindow", u"\u53f3\u4fa7\u6fc0\u5149\uff1a", None))
        self.perc.setText(QCoreApplication.translate("MainWindow", u"\u5de6\u4fa7\u5360\u6bd4\uff1a", None))
        self.h.setText(QCoreApplication.translate("MainWindow", u"\u9ad8\u5ea6\uff1a", None))
        self.ls.setText(QCoreApplication.translate("MainWindow", u"\u5de6\u4fa7\u6fc0\u5149\uff1a", None))
    # retranslateUi

