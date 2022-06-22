#include "Arduino.h"
#include "command_processor.h"

bool stop=true;//急停标志位
bool s_print=false;
bool is_test;
float paramenters[paramenters_num]={0, 0, 0, 0, 90, 0, 0, 0, 0, 0, 1, 0};
int read_modes[paramenters_num]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
void command_process(String cmd_rec)
{
    if(!command_check(cmd_rec))
    {
        if(is_test)
        {
            Serial.println("fuck");
        }
        
        return;
    }
    int idx_N=cmd_rec.indexOf('N', 0);
    int idx_Ne=cmd_rec.indexOf('e', idx_N+1);
    int idx_op=idx_Ne+1;
    int idx_ope=cmd_rec.indexOf('e', idx_op+1);
    int op_type=0;//0:read, 1:write
    while((idx_N>=0)&&(idx_ope>idx_Ne)&&(idx_Ne>idx_N))
    {
        int par_idx=cmd_rec.substring(idx_N+1, idx_Ne).toInt();
        float par_val=cmd_rec.substring(idx_op+1, idx_ope).toFloat();
        if(is_test)
        {
            Serial.println(cmd_rec.substring(idx_N+1, idx_Ne));
            Serial.println(par_idx);
            Serial.println(cmd_rec.substring(idx_op+1, idx_ope));
            Serial.println(par_val);
        }
        if(par_idx>=paramenters_num)
        {
            return;
        }
        switch(cmd_rec[idx_op])
        {
            case 'W':
                paramenters[par_idx]=par_val;
                break;
            case 'R':
                read_modes[par_idx]=(int) par_val;
                break;
            default:
                return;
        }
        
        idx_N=cmd_rec.indexOf('N', idx_ope+1);
        idx_Ne=cmd_rec.indexOf('e', idx_N+1);
        idx_op=idx_N+1;
        idx_ope=cmd_rec.indexOf('N', idx_op+1);
    }

}
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
    if(cmd_rec.substring(0,3)!=String("wyq"))
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
String check_bytes_cal(String cmd_str)
{
    int chars=0;
    int ints=0;
    int syms=0;
    for(int i=0;i<cmd_str.length();i++)
    {
        if(isAlpha(cmd_str[i]))
        {
            chars++;
            continue;
        }
        if(isAlphaNumeric(cmd_str[i]))
        {
            ints++;
            continue;
        }
        syms++;
    }
    return String("~")+String(chars-ints+syms*2)+String("\n");
}