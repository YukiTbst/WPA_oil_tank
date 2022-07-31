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

        delay(10);
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
    controller_PID controller1(paramenters[KP], paramenters[KI], paramenters[KD])
    paramenters[REF]=paramenters[THETA];
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
            controller1.ref_set(paramenters[REF]);
            controller1.p_set(paramenters[KP]);
            controller1.i_set(paramenters[KI]);
            controller1.d_set(paramenters[KD]);
            float vel_ref=controller1.run_one_step(paramenters[THETA], paramenters[OMEGA]);
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
//下面这个函数要并入motor_driver
void MRAC_run(void* paramenter)
{
    while(1)
    {
        while(!timmer_flag)
        {
            delay(1)
        }
        MRAC_for_coder_step();
        timmer_flag=false;
        if(MRAC_for_code_controller_output>100)
        {
            MRAC_for_code_controller_output=100;
        }
        else if(MRAC_for_code_controller_output<-100)
        {
            MRAC_for_code_controller_output=-100;
        }
        Serial2.write('w');
        send_double2(MRAC_for_code_controller_output);
        Serial2.write('\n');
    }
}
//修改代码，把读取IMU数据的功能独立出来？好像不用，这个是用I2C询问式读取的
//setup需要改
void setup() 
{
    Serial.begin(115200);
    Serial2.begin(115200)
    MRAC_for_coder_initialize();
    xTaskCreatePinnedToCore(
        timmer,          
        "timmer",        
        10000,            
        NULL,             
        5,               
        NULL,
        1);
    xTaskCreatePinnedToCore(
        MRAC_run,          
        "MRAC_run",        
        10000,            
        NULL,             
        4,               
        NULL,
        0);
    xTaskCreatePinnedToCore(
        ser2_input,          
        "ser2_input",        
        10000,            
        NULL,             
        3,               
        NULL,
        1);
    xTaskCreatePinnedToCore(
        ser0_input,          
        "ser0_input",        
        10000,            
        NULL,             
        2,               
        NULL,
        1);
    xTaskCreatePinnedToCore(
        ser0_print,          
        "ser0_print",        
        10000,            
        NULL,             
        1,               
        NULL,
        1);
}

void loop() 
{
    delay(1000);
}
