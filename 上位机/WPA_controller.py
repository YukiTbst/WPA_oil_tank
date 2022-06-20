from distutils import cmd
import sys
from ui_WPA_ui import Ui_MainWindow
import serial.tools
import serial.tools.list_ports
from PySide6 import QtWidgets
from PySide6.QtWidgets import *
from PySide6.QtCore import QTimer
import time
import pandas as  pd
import configparser
import os
from functools import partial
class MainWindow(QMainWindow):
    ser=serial.Serial()
    def __init__(self, parent = None) :
        super().__init__(parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        #初始化串口列表
        port_list = list(serial.tools.list_ports.comports())
        self.ui.comboBox_ser.addItem('none')
        for i in range(0, len(port_list)):
            self.ui.comboBox_ser.addItem(str(port_list[i][0]))
        #串口刷新键
        self.ui.pushButton_ser_refresh.clicked.connect(self.pushButton_ser_refresh_clicked)
        #串口连接
        self.ui.comboBox_ser.activated[int].connect(self.ser_connect)
        #定时器，用于读取串口
        self.timer=QTimer(self)
        self.timer.timeout.connect(self.timer_interrupt)
        self.timer.start(500)
        #发送指令
        self.ui.pushButton_ser_send.clicked.connect(self.ser_send)
        #角度读取选框配置
        self.ui.comboBox_theta.activated.connect(lambda: self.reading_setting(self.ui.comboBox_theta.currentText()))
    def pushButton_ser_refresh_clicked(self):
        self.ui.comboBox_ser.clear()
        port_list = list(serial.tools.list_ports.comports())
        self.ui.comboBox_ser.addItem('none')
        for i in range(0, len(port_list)):
            self.ui.comboBox_ser.addItem(str(port_list[i][0]))
    def ser_connect(self, ser_idx):
        self.ser.close()
        try:
            self.ser=serial.Serial(self.ui.comboBox_ser.itemText(ser_idx), 115200)
            self.ser.open()
        except:
            self.ui.label_ser_status.setText("未连接")
        if(not self.ser.isOpen()):
            self.ser.close()
            self.ser.open()
        if(self.ser.isOpen()):
            self.ui.label_ser_status.setText("已连接"+self.ui.comboBox_ser.itemText(ser_idx))
    def timer_interrupt(self):
        if self.ser.isOpen():
            while self.ser.inWaiting()>0:
                rec=self.ser.read(1).decode()
                self.ui.plainTextEdit_ser_rec.setPlainText(self.ui.plainTextEdit_ser_rec.toPlainText()+rec)
                self.ui.plainTextEdit_ser_rec.moveCursor(self.ui.plainTextEdit_ser_rec.textCursor().End)
    def ser_send(self):
        if self.ser.isOpen():
            cmd_str=self.ui.lineEdit_ser_send.text()+"\n"
            self.ser.write(cmd_str.encode())
            self.ui.plainTextEdit_ser_rec.appendPlainText("<<<"+cmd_str)
            self.ui.lineEdit_ser_send.setText("")
        else:
            self.ui.lineEdit_ser_send.setText("failed")
    def reading_setting(self, idx,):
        self.ui.lineEdit_ser_send.setText(str)
        
    
if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    win = MainWindow()
    win.setWindowTitle("WPA 上位机")
    win.show()
    app.exit(app.exec_())