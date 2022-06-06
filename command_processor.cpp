#include "Arduino.h"
#include "command_processor.h"

bool stop=true;//急停标志位
bool s_print=false;
float paramenters[paramenters_num]={0, 0, 0, 0, 90, 0, 0, 0, 0, 0, 0, 1};
int read_modes[paramenters_num]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
void command_process(String cmd_rec);
bool command_check(String cmd_rec)
{
    int chars=0;
    int ints=0;
    int syms=0;
    int checker=100;
    int idx=cmd_rec.indexOf('~');
    if(idx<0)
    {
        return false;
    }
    for(int i=0;i<idx;i++)
    {
        if(isAlpha(cmd_rec[i]))
        {
            chars++;
            continue;
        }
        if(isAlphaNumeric(cmd_rec[i]))
        {
            ints++;
            continue;
        }
        syms++;
    }
    checker=cmd_rec.substring(idx+1).toInt();
    if(checker==chars-ints+syms*2)
    {
        return true;
    }
    return false;
}