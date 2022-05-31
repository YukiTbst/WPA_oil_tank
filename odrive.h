#ifndef YKOdrive
#define YKOdrive
#include <ODriveArduino.h>
#include <HardwareSerial.h>
class myOdrive
{
private:
    Stream& OdriveSerial;
    ODriveArduino* this_odrive;
    int motor_num;
public:
    myOdrive(Stream& serial_input, int motor_input);
    bool Odrive_init();
    double get_vel();
    bool set_vel(double vel);
    bool reboot();
    bool error_check();
};



#endif