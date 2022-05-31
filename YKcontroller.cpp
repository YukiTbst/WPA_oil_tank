#include "YKcontroller.h"
#include "Arduino.h"
controller_PID::controller_PID(float p, float i, float d)
{
    kp=p;
    ki=i;
    kd=d;
    last_i=0;
    ref=0;
    last_running_time=0;//标记这是第一次运行，run_one_step时如果发现这个值为0，就暂不启动微分与积分环节
}
void controller_PID::ref_set(float input)
{
    ref=input;
}
float controller_PID::run_one_step(float x, float x_dot)
{
    uint64_t this_time=millis();
    float p_out=0;
    float d_out=0;
    if(last_running_time!=0)
    {
        float dt=((float)(this_time-last_running_time))/1000.0;
        last_i+=dt*(ref-x)*ki;
        d_out=x_dot*kd;
    }
    p_out=(ref-x)*kp;
    last_running_time=this_time;
    return p_out+last_i+d_out;
}
void controller_PID::p_set(float p)
{
    kp=p;
}
void controller_PID::i_set(float i)
{
    ki=i;
}
void controller_PID::d_set(float d)
{
    kd=d;
}