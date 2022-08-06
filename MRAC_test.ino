#include "MRAC_for_coder.h"
#include "Wire.h"
#include <SPI.h>
#include <TFT_eSPI.h>       // Hardware-specific library
#include <ODriveArduino.h>
#include <HardwareSerial.h>
#include "odrive.h"
#include "YKcontroller.h"
#include "EEPROM.h"
#include "command_processor.h"

//测试标记
bool is_test=false;

//odrive相关变量
template<class T> inline Print& operator <<(Print &obj,     T arg) { obj.print(arg);    return obj; }
template<>        inline Print& operator <<(Print &obj, float arg) { obj.print(arg, 4); return obj; }
HardwareSerial& odrive_serial = Serial2;
Stream& serial_(odrive_serial);
myOdrive odrive1(odrive_serial, 1);
myOdrive odrive2(odrive_serial, 0);
myOdrive *odrive_list[]={&odrive1, &odrive2};
//IMU使用的I2C
const int sda=22;
const int scl=23;

//MRAC控制器输入
double MRAC_for_coder_ref=0;
double MRAC_for_coder_theta=0;
double MRAC_for_coder_omega=0;
//触发MRAC的定时器
bool timmer_flag=false;

//IMU相关函数：
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
void sensor_data_update_once()
{
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
        paramenters[THETA]=aggas[11]/180.0f*3.14159f;
        uint64_t this_time=millis();
        float dt=((float)(this_time-last_time))/1000.0f;
        float last_omega=paramenters[OMEGA];
        paramenters[OMEGA]=aggas[5]/180.0f*3.14159f;
        paramenters[BETA]=(paramenters[OMEGA]-last_omega)/dt;

        return;
    }
}
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
        paramenters[THETA]=aggas[11]/180.0f*3.14159f;
        uint64_t this_time=millis();
        float dt=((float)(this_time-last_time))/1000.0f;
        float last_omega=paramenters[OMEGA];
        paramenters[OMEGA]=aggas[5]/180.0f*3.14159f;
        paramenters[BETA]=(paramenters[OMEGA]-last_omega)/dt;

        delay(5);
    }
    
    
}

//串口信息打印函数
void data_print_serial(void * parameter)//通过串口打印信息
{
    while(1)
    {
        delay(10);
        if(s_print)
        {
            Serial.println("theta: "+String(paramenters[THETA],3)+",\t"+"omega: "+String(paramenters[OMEGA],3)+",\t"+"beta: "+String(paramenters[BETA],3)+",\t"+"dv: "+String(paramenters[U],3)+",\t"+"ref: "+String(paramenters[REF],3)+",\t");
        }
    }
}

//控制器，此处需要修改
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
    sensor_data_update_once();
    paramenters[REF]=paramenters[THETA];
    while(1)
    {
        while(!timmer_flag)
        {
            delay(1)
        }
        timmer_flag=false;
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
            sensor_data_update_once();
            MRAC_for_coder_ref=(double) paramenters[REF];
            MRAC_for_coder_theta=(double) paramenters[THETA];
            MRAC_for_coder_omega=(double) paramenters[OMEGA];
            MRAC_for_coder_step();
            float vel_ref=(float) MRAC_for_code_controller_output;
            //vel=odrive1.get_vel();
            paramenters[U]=vel_ref;
            float umax=(160-paramenters[VEL_BAL])*2;
            if(paramenters[U]>umax)
            {
                paramenters[U]=umax;
            }
            if(paramenters[U]<-umax)
            {
                paramenters[U]=-umax;
            }
            float vels[2];
            vels[0]=paramenters[VEL_BAL]+paramenters[U]/2;
            vels[1]=2*paramenters[VEL_BAL]-vels[0];
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

//带校验位的指令收发
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
        else
        {
            if(command_check(str))
                {
                    float p=paramenters[KP];
                    float i=paramenters[KI];
                    float d=paramenters[KD];
                    command_process(str);
                    if(p!=paramenters[KP])
                    {
                        EEPROM.writeFloat(0, paramenters[KP]);
                        delay(1);
                        EEPROM.commit();      
                    }
                    if(i!=paramenters[KI])
                    {
                        EEPROM.writeFloat(sizeof(float), paramenters[KI]);
                        delay(1);
                        EEPROM.commit();     
                    }
                    if(i!=paramenters[KD])
                    {
                        EEPROM.writeFloat(sizeof(float)*2, paramenters[KD]);
                        delay(1);
                        EEPROM.commit();     
                    }
                }
        }
        /*
        char c1 = str[0];
        str=str.substring(1);
        float data=str.toFloat();
        switch(c1)
        {
            case 'p':
            paramenters[KP]=data;
            EEPROM.writeFloat(0, paramenters[KP]);
            Serial.println("P="+String(paramenters[KP],0)+", "+"I="+String(paramenters[KI],0)+", "+"D="+String(paramenters[KD],0));
            break;
            case 'i':
            paramenters[KI]=data;
            EEPROM.writeFloat(sizeof(float), paramenters[KI]);
            Serial.println("P="+String(paramenters[KP],0)+", "+"I="+String(paramenters[KI],0)+", "+"D="+String(paramenters[KD],0));
            break;
            case 'd':
            paramenters[KD]=data;
            EEPROM.writeFloat(sizeof(float)*2, paramenters[KD]);
            Serial.println("P="+String(paramenters[KP],0)+", "+"I="+String(paramenters[KI],0)+", "+"D="+String(paramenters[KD],0));
            break;
            
            default:
            break;
        }
        delay(1);
        EEPROM.commit();      
        */         
    }

}
void data_publisher(void * parameter)
{
    while(1)
    {
        if(((int) paramenters[PUBLISH_FREQ])<=0)
        {
            paramenters[PUBLISH_FREQ]=1;
        }
        delay(1000/((int) paramenters[PUBLISH_FREQ]));
        String pub_str="wyq";
        for(int i=0;i<paramenters_num;i++)
        {
            if(read_modes[i]!=0)
            {
                read_modes[i]%=2;
                pub_str+='N'+String(i)+'e'+'R'+String(paramenters[i], 3)+'e';
            }
        }
        if(pub_str=="wyq")
        {
            continue;
        }
        pub_str+=check_bytes_cal(pub_str);
        Serial.print(pub_str);
        
    }
    
}
void timmer(void* paramenter)
{
    while(1)
    {
        delay(20);
        timmer_flag=true;
    }
}
//测试用的任务
void task_for_test(void * parameter)
{
    while(1)
    {
        if(Serial.available())
        {
            String str=Serial.readStringUntil('\n');
            if(str.length()>0)
            {
                if(command_check(str))
                {
                    Serial.println("ok");
                    command_process(str);
                }
                else
                {
                    Serial.println("fuck");
                }
            }
        }
        delay(10);
    }
    
}
void setup() 
{
    odrive_serial.begin(115200);
    Serial.begin(115200);
    MRAC_for_coder_initialize();
    if(!Wire.begin(sda, scl, 400000))
    {
        Serial.println("Failed to initialise I2C");
        Serial.println("Restarting...");
        delay(1000);
        ESP.restart();
    }
    //EEPROM和PID这段其实没用，但数据收发那里可能会用到EEPROM，就把这段copy过来了
    if (!EEPROM.begin(4096)) 
    {
        Serial.println("Failed to initialise EEPROM");
        Serial.println("Restarting...");
        delay(1000);
        ESP.restart();
    }
    paramenters[KP]=EEPROM.readFloat(0);
    if(!(paramenters[KP]==paramenters[KP]))//如果EEPROM里没写过初值，读到的PID都是nan，nan==nan返回false
    {
        paramenters[KP]=110;
    }
    paramenters[KI]=EEPROM.readFloat(sizeof(float));
    if(!(paramenters[KI]==paramenters[KI]))
    {
        paramenters[KI]=0;
    }
    paramenters[KD]=EEPROM.readFloat(sizeof(float)*2);
    if(!(paramenters[KD]==paramenters[KD]))
    {
        paramenters[KD]=30;
    }
    if(is_test)
    {
        Serial.println("it's a test");
        xTaskCreatePinnedToCore(
            task_for_test,          
            "task_for_test",        
            10000,            
            NULL,             
            5,               
            NULL,
            0);
        xTaskCreatePinnedToCore(
            data_publisher,          
            "data_publisher",        
            10000,            
            NULL,             
            4,               
            NULL,
            0);          
    }
    else
    {
        xTaskCreatePinnedToCore(
            motor_driver,          /*任务函数*/
            "motor driver and controller",        /*带任务名称的字符串*/
            10000,            /*堆栈大小，单位为字节*/
            NULL,             /*作为任务输入传递的参数*/
            4,                /*任务的优先级*/
            NULL,
            0); 
        xTaskCreatePinnedToCore(
            command_reader,          /*任务函数*/
            "command reader",        /*带任务名称的字符串*/
            10000,            /*堆栈大小，单位为字节*/
            NULL,             /*作为任务输入传递的参数*/
            2,                /*任务的优先级*/
            NULL,
            1);       
        xTaskCreatePinnedToCore(
            data_publisher,          
            "data publisher",        
            10000,            
            NULL,             
            1,               
            NULL,
            1);    
        xTaskCreatePinnedToCore(
            timmer,          
            "timmer",        
            10000,            
            NULL,             
            5,               
            NULL,
            1);     
    }
}

void loop() 
{
    delay(1000);
}
