#include "Wire.h"
#include <SPI.h>
#include <TFT_eSPI.h>       // Hardware-specific library
#include <ODriveArduino.h>
#include <HardwareSerial.h>
#include "odrive.h"
#include "YKcontroller.h"
#include "EEPROM.h"
template<class T> inline Print& operator <<(Print &obj,     T arg) { obj.print(arg);    return obj; }
template<>        inline Print& operator <<(Print &obj, float arg) { obj.print(arg, 4); return obj; }
HardwareSerial& odrive_serial = Serial2;
Stream& serial_(odrive_serial);
myOdrive odrive1(odrive_serial, 1);
myOdrive odrive2(odrive_serial, 0);
myOdrive *odrive_list[]={&odrive1, &odrive2};
const int sda=22;
const int scl=23;
bool stop=true;//急停标志位
bool s_print=false;
float vel=0;
float theta=0;
float omega=0;
float beta=0;
float vel_bal=90;
//TFT_eSPI tft = TFT_eSPI();  // Invoke custom library
float kp, ki, kd, ref, u;
/*
void tft_clear()
{

    tft.setCursor(0, 0, 7);
    tft.print("                                                                                                                                                                                 ");
    tft.setCursor(0, tft.fontHeight(7), 7);
    tft.print("                                                                                                                                                                                 ");
}
void tft_print(String msg, int line)
{
    //tft.setTextSize(2);
    int fh=tft.fontHeight(2);
    int y_s=line*(fh+3)+2;
    tft.setCursor(5, y_s, 2);
    tft.print(msg);
}
*/
uint8_t sensor_finder()
{
    int i, iRetry;
	for(i = 0; i < 0x7F; i++)
	{
		iRetry = 2;
		do
		{
            Wire.beginTransmission(i);
            Wire.write(0x34);
            Wire.endTransmission(false);
            delay(5);
            int val=Wire.requestFrom(i, 24);
            if(val!=0)
            {
                //Serial.print("find 0x");
				//Serial.print(i, HEX);
				//Serial.print(" addr sensor\r\n");
				return i;
            }
			iRetry--;
		}while(iRetry);		
	}
	//Serial.print("can not find sensor\r\n");
	//Serial.print("please check your connection\r\n");
    return 0xff;
}
/*
void display( void * parameter )
{
    tft_clear();
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft_print("From wyq : )", 0);
    while(1)
    {
        tft_print("vel: "+String(vel,3)+"  ",1);
        tft_print("theta: "+String(theta,3)+"  ",2);
        tft_print("omega: "+String(omega,3)+"  ",3);
        tft_print("beta: "+String(beta,3)+"  ",4);
        tft_print(String(kp,0)+", "+String(ki,0)+", "+String(kd,0),5);
        tft_print(String(ref,3)+", "+String(u,0)+", "+String(u/(ref-theta),0),6);
        delay(50);
    }


}
*/
void sensor_read( void * parameter )
{
    uint64_t last_time=millis();
    //sensor_finder();
    while(1)
    {//sensor_finder();
        uint8_t datas[24];
        Wire.beginTransmission(0x50);
        Wire.write(0x34);
        Wire.endTransmission(false);
        int val=Wire.requestFrom(0x50, 24);
        if(val==0)
        {
            Serial.println("Failed");
            continue;
        }
        //Serial.println("Start reading");
        while (Wire.available()<24)
        {
            continue;
        }
        for(int i=0; i<24; i++)
        {
            datas[i]=Wire.read();
        }
        float aggas[12];
        for(int i=0;i<12;i++)
        {
            int16_t t1=datas[2*i];
            int16_t t2=datas[2*i+1];
            t1=(t2<<8)+t1;
            aggas[i]=((float)t1)/ 32768.0f;
            switch((i-(i%3))/3)
            {
                case 0:
                aggas[i]*=16.0f;
                break;
                case 1:
                aggas[i]*=2000.0f;
                break;
                case 3:
                aggas[i]*=180.0f;
                break;
                default:
                break;

            }
            //Serial.print(aggas[i]);
            //Serial.print("\t");
        }
        //Serial.print("\n");
        //delay(500);
        theta=aggas[11]/180.0f*3.14159f;
        uint64_t this_time=millis();
        float dt=((float)(this_time-last_time))/1000.0f;
        float last_omega=omega;
        omega=aggas[5]/180.0f*3.14159f;
        beta=(omega-last_omega)/dt;

        delay(10);
    }
    
    
}
void data_print_serial(void * parameter)//通过串口打印信息
{
    while(1)
    {
        delay(10);
        if(s_print)
        {
            Serial.println("theta: "+String(theta,3)+"\t"+"omega: "+String(omega,3)+"\t"+"beta: "+String(beta,3)+"\t");
        }
    }
}
void motor_driver(void * parameter)
{
    for(int i=0; i<2; i++)
    {
        odrive_list[i]->reboot();
    }
    for(int i=0; i<2; i++)
    {
        odrive_list[i]->Odrive_init();
    }
    for(int i=0; i<2; i++)
    {
        odrive_list[i]->set_vel(1);
    }
    controller_PID controller1(kp, ki, kd);
    ref=theta;
    while(1)
    {
        delay(20);
        if(stop)
        {
            for(int i=0; i<2; i++)
            {
                odrive_list[i]->set_vel(1);
            }
            continue;
        }
        else
        {
            controller1.ref_set(ref);
            controller1.p_set(kp);
            controller1.i_set(ki);
            controller1.d_set(kd);
            float vel_ref=controller1.run_one_step(theta, omega);
            //vel=odrive1.get_vel();
            u=vel_ref;
            float umax=(160-vel_bal)*2;
            if(u>umax)
            {
                u=umax;
            }
            if(u<-umax)
            {
                u=-umax;
            }
            float vels[2];
            vels[0]=vel_bal+u/2;
            vels[1]=2*vel_bal-vels[0];
            for(int i=0;i<2;i++)
            {
                if(vels[i]<0)
                {
                    vels[i]=-vels[i];
                }
                odrive_list[i]->set_vel(vels[i]);
            }
        }
    }
}
void command_reader(void * parameter)
{
    while(1)
    {
        String str=Serial.readStringUntil('\n');
        if(str.length()<2)
        {
            if(str.length()==1)//单个字符的命令
            {
                char c1 = str[0];
                switch(c1)
                {
                    case 's':
                    stop=true;//输入stop急停
                    break;
                    case 'e':
                    stop=false;//输入enable启动
                    break;
                    case 'p':
                    s_print=!s_print;
                    break;
                    default:
                    break;
                }
            }
            continue;
        }
        char c1 = str[0];
        str=str.substring(1);
        float data=str.toFloat();
        switch(c1)
        {
            case 'p':
            kp=data;
            EEPROM.writeFloat(0, kp);
            Serial.println("P="+String(kp,0)+", "+"I="+String(ki,0)+", "+"D="+String(kd,0));
            break;
            case 'i':
            ki=data;
            EEPROM.writeFloat(sizeof(float), ki);
            Serial.println("P="+String(kp,0)+", "+"I="+String(ki,0)+", "+"D="+String(kd,0));
            break;
            case 'd':
            kd=data;
            EEPROM.writeFloat(sizeof(float)*2, kd);
            Serial.println("P="+String(kp,0)+", "+"I="+String(ki,0)+", "+"D="+String(kd,0));
            break;
            
            default:
            break;
        }
        delay(1);
        EEPROM.commit();               
    }

}
void setup() 
{
    odrive_serial.begin(115200);
    Serial.begin(115200);
    Wire.begin(sda, scl, 400000);
    //tft.init();
    //tft.setRotation(4);
    //tft.fillScreen(TFT_BLACK);
    if (!EEPROM.begin(4096)) 
    {
        Serial.println("Failed to initialise EEPROM");
        Serial.println("Restarting...");
        delay(1000);
        ESP.restart();
    }
    kp=EEPROM.readFloat(0);
    ki=EEPROM.readFloat(sizeof(float));
    kd=EEPROM.readFloat(sizeof(float)*2);
    Serial.println("P="+String(kp,0)+", "+"I="+String(ki,0)+", "+"D="+String(kd,0));
    /*
    xTaskCreatePinnedToCore(
              display,          
              "TaskOne",       
              10000,            
              NULL,            
              1,               
              NULL,
              1);  
              */
    xTaskCreatePinnedToCore(
              sensor_read,          /*任务函数*/
              "Tasktwo",        /*带任务名称的字符串*/
              10000,            /*堆栈大小，单位为字节*/
              NULL,             /*作为任务输入传递的参数*/
              3,                /*任务的优先级*/
              NULL,
              0);  
    xTaskCreatePinnedToCore(
              motor_driver,          /*任务函数*/
              "Taskthree",        /*带任务名称的字符串*/
              10000,            /*堆栈大小，单位为字节*/
              NULL,             /*作为任务输入传递的参数*/
              4,                /*任务的优先级*/
              NULL,
              1); 
    xTaskCreatePinnedToCore(
              command_reader,          /*任务函数*/
              "Taskfour",        /*带任务名称的字符串*/
              10000,            /*堆栈大小，单位为字节*/
              NULL,             /*作为任务输入传递的参数*/
              2,                /*任务的优先级*/
              NULL,
              1);       
    xTaskCreatePinnedToCore(
              data_print_serial,          /*任务函数*/
              "Print_data_by_serial",        /*带任务名称的字符串*/
              10000,            /*堆栈大小，单位为字节*/
              NULL,             /*作为任务输入传递的参数*/
              1,                /*任务的优先级*/
              NULL,
              0);               
  // put your setup code here, to run once:

}

void loop() 
{
  // put your main code here, to run repeatedly:
    delay(1000);

}
