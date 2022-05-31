#include "Arduino.h"
#include "odrive.h"
#include <ODriveArduino.h>
#include <HardwareSerial.h>

template<class T> inline Print& operator <<(Print &obj,     T arg) { obj.print(arg);    return obj; }
template<>        inline Print& operator <<(Print &obj, float arg) { obj.print(arg, 4); return obj; }
myOdrive::myOdrive(Stream& serial_input, int motor_input):OdriveSerial(serial_input)
{
    
    this_odrive= new ODriveArduino(OdriveSerial);
    motor_num=motor_input;
}
bool myOdrive::reboot()
{
    OdriveSerial<<"sr\n";
    OdriveSerial<<"sr\n";
    OdriveSerial<<"sr\n";
    //测试一下，可能加了这个就不用delay 8秒了
    do 
    {
        delay(100);
        OdriveSerial << "r axis" << motor_num << ".current_state\n";
    } while (this_odrive->readInt() != AXIS_STATE_IDLE );
}
bool myOdrive::error_check()
{
    OdriveSerial << "r axis" << motor_num << ".error\n";
    if(this_odrive->readInt()==0)
    {
        return false;
    }
    return true;
}
bool myOdrive::Odrive_init()
{
    //Serial.println("rebooting");
    //OdriveSerial<<"sr\n";
    //OdriveSerial<<"sr\n";
    //OdriveSerial<<"sr\n";
    //delay(8000);
    //Serial.println("start calibration");
    int requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE;
    while(!this_odrive->run_state(motor_num, requested_state, true, 25.0f));
    //Serial <<  "done\n";
    //Serial.println("starting closeloop control!");
    requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL;
    this_odrive->run_state(motor_num, requested_state, false) ;
    //Serial <<  "done\n";
    //Serial.println("velocity control mode:");
    int ctr_mode=CONTROL_MODE_VELOCITY_CONTROL;
    OdriveSerial<<"w axis"<<motor_num<<".controller.config.control_mode"<<" "<<ctr_mode<<"\n";
    OdriveSerial<<"w axis"<<motor_num<<".controller.config.vel_ramp_rate"<<" "<<150<<"\n";
    OdriveSerial<<"w axis"<<motor_num<<".controller.config.input_mode"<<" "<<INPUT_MODE_VEL_RAMP<<"\n";
    set_vel(0);
    return true;
}
bool myOdrive::set_vel(double vel)
{
    OdriveSerial<<"v "<<motor_num<<" "<<" "<<vel<<"\n";
    return true;
}
double myOdrive::get_vel()
{
    //研究一下怎么获取当前速度。
    return this_odrive->GetVelocity(motor_num);
}