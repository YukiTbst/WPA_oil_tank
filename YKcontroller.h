#ifndef YKcontroller
#define YKcontroller
#include "Arduino.h"
class controller_PID
{
private:
    uint64_t last_running_time;
    float kp;
    float ki;
    float kd;
    float last_i;
    float ref;
public:
    controller_PID(float p, float i, float d);
    void ref_set(float input);
    float run_one_step(float x, float x_dot);
    void p_set(float p);
    void i_set(float i);
    void d_set(float d);
};



#endif