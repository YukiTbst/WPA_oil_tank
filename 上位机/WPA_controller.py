
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
from threading import Thread
def check_str_cal(cmd_str: str):
    check_num=0
    for i in range(len(cmd_str)):
        if cmd_str[i]>='A' and cmd_str[i]<='z':
            check_num+=1
        elif cmd_str[i]>='0' and cmd_str[i]<='9':
            check_num-=1
        else:
            check_num+=2
    return "~"+str(check_num)+"\n"
def get_float_from_str(str_data):
    temp=""
    for i in range(len(str_data)):
        if (str_data[i]<="9" and str_data[i]>="0") or str_data[i]==".":
            temp+=str_data[i]
    try:
        return float(temp)
    except:
        return 0.0
        
class MainWindow(QMainWindow):
    ser=serial.Serial()
    rec_temp=""
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
        self.timer.start(50)
        #线程，替换定时器
        #thread=Thread(target=self.ser_process_thread)
        #thread.start()
        #发送指令
        self.ui.pushButton_ser_send.clicked.connect(self.ser_send)
        #把参数显示与参数配置加入list
        self.parameter_texts=[self.ui.text_dvel, self.ui.text_theta, self.ui.text_omega, self.ui.text_beta, self.ui.text_vel_bal, self.ui.text_ref, self.ui.text_u, self.ui.text_kp, self.ui.text_ki, self.ui.text_kd, self.ui.text_freq]
        self.parameter_combos=[self.ui.comboBox_dvel, self.ui.comboBox_theta, self.ui.comboBox_omega, self.ui.comboBox_beta, self.ui.comboBox_vel_bal, self.ui.comboBox_ref, self.ui.comboBox_u, self.ui.comboBox_kp, self.ui.comboBox_ki, self.ui.comboBox_kd, self.ui.comboBox_freq]
        self.parameter_combos[0].activated.connect(lambda: self.reading_setting(0, self.parameter_combos[0].currentIndex()))
        self.parameter_combos[1].activated.connect(lambda: self.reading_setting(1, self.parameter_combos[1].currentIndex()))
        self.parameter_combos[2].activated.connect(lambda: self.reading_setting(2, self.parameter_combos[2].currentIndex()))
        self.parameter_combos[3].activated.connect(lambda: self.reading_setting(3, self.parameter_combos[3].currentIndex()))
        self.parameter_combos[4].activated.connect(lambda: self.reading_setting(4, self.parameter_combos[4].currentIndex()))
        self.parameter_combos[5].activated.connect(lambda: self.reading_setting(5, self.parameter_combos[5].currentIndex()))
        self.parameter_combos[6].activated.connect(lambda: self.reading_setting(6, self.parameter_combos[6].currentIndex()))
        self.parameter_combos[7].activated.connect(lambda: self.reading_setting(7, self.parameter_combos[7].currentIndex()))
        self.parameter_combos[8].activated.connect(lambda: self.reading_setting(8, self.parameter_combos[8].currentIndex()))
        self.parameter_combos[9].activated.connect(lambda: self.reading_setting(9, self.parameter_combos[9].currentIndex()))
        self.parameter_combos[10].activated.connect(lambda: self.reading_setting(10, self.parameter_combos[10].currentIndex()))
        #角度控制旋钮
        self.ui.dial_theta.valueChanged.connect(lambda: self.dail_theta_process(self.ui.dial_theta.value()))
        #参数设置
        self.ui.pushButton_val_set.clicked.connect(self.val_set_button)
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
                self.rec_temp+=rec
                if rec=="\n":
                    self.rec_data_process(self.rec_temp)
                    self.rec_temp=""
                if self.ui.checkBox_ser_display.isChecked():
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
    def ser_send2(self, cmd_str):
        if self.ser.isOpen():
            self.ser.write(cmd_str.encode())
            self.ui.plainTextEdit_ser_rec.appendPlainText("<<<"+cmd_str)
            self.ui.lineEdit_ser_send.setText("")
        else:
            self.ui.lineEdit_ser_send.setText("failed")
    def reading_setting(self, combo_idx, status_idx):
        if status_idx==1:
            status_idx=2
        elif status_idx==2:
            status_idx=1
        cmd_str="wyq"+"N"+str(combo_idx)+"e"+"R"+str(status_idx)+"e"
        cmd_str+=check_str_cal(cmd_str)
        self.ser_send2(cmd_str)
        
    def dail_theta_process(self, theta):
        self.ui.label_ref.setText(str(theta))
        self.val_set(5, theta/180*3.14)
    
    def val_set(self, idx, val):
         cmd_str="wyq"+"N"+str(idx)+"e"+"W"+str(val)+"e"
         cmd_str+=check_str_cal(cmd_str)
         self.ser_send2(cmd_str)
    def val_set_button(self):
        idx=self.ui.comboBox_val_set.currentIndex()
        idx+=7
        val=float(self.ui.lineEdit_val_set.text())
        self.val_set(idx, val)
    def rec_data_process(self, rec_str: str):
        data_and_checker=rec_str.split("~")
        if len(data_and_checker)<2:
            return
        data_and_checker[1]="~"+data_and_checker[1]
        if data_and_checker[1]==check_str_cal(data_and_checker[0]):
            idx_and_val=data_and_checker[0].split("e")
            if(len(idx_and_val)%2==1):
                for i in range(round((len(idx_and_val)-1)/2)):
                    idx=int(get_float_from_str(idx_and_val[2*i]))
                    val=get_float_from_str(idx_and_val[2*i+1])
                    self.val_display(idx, val)
            
    def val_display(self, idx, val):
        if(idx>len(self.parameter_texts)):
            return
        self.parameter_texts[idx].setText(str(val))
    def ser_process_thread(self):
        self.ui.lineEdit_ser_send.setText("hello")
        while 1:   
            if self.ser.isOpen():
                while self.ser.inWaiting()>0:
                    rec=self.ser.read(1).decode()
                    self.rec_temp+=rec
                    if rec=="\n":
                        self.rec_data_process(self.rec_temp)
                        self.rec_temp=""
                    if self.ui.checkBox_ser_display.isChecked():
                        text=self.ui.plainTextEdit_ser_rec.toPlainText()+rec
                        print(len(text))
                        if(len(text)>100):
                            text=text[-100:]
                            print(len(text))
                        #下面两句不能直接加，需要使用信号传递给主线程的函数
                        #self.ui.plainTextEdit_ser_rec.setPlainText(text)
                        #self.ui.plainTextEdit_ser_rec.moveCursor(self.ui.plainTextEdit_ser_rec.textCursor().End)
                        
            time.sleep(0.01)
    
        
if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    win = MainWindow()
    win.setWindowTitle("WPA 上位机")
    win.show()
    app.exit(app.exec_())