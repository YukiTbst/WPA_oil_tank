#ifndef command_processor
#define command_processor
#include "Arduino.h"
#define VEL 0
#define THETA 1
#define OMEGA 2
#define BETA 3
#define VEL_BAL 4
#define REF 5
#define U 6
#define KP 7
#define KI 8
#define KD 9
#define COMMAND_RECEIVED 10
#define PUBLISH_FREQ 11
const int paramenters_num=12;
extern bool stop;//急停标志位
extern bool s_print;
extern float paramenters[paramenters_num];
extern int read_modes[paramenters_num];
//vel_bal=90时，一组比较好的PD值为p=110，d=30
void command_process(String cmd_rec);
bool command_check(String cmd_rec);
#endif