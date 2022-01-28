#include <p18f4620.h>
//#include "Main.h"
//#include "Fan_Support.h"
#include "stdio.h"
void Monitor_Heater();
int get_RPM();
void Toggle_Heater();
void Turn_Off_Fan();
void Turn_On_Fan();
void do_update_pwm(char) ;
void Increase_Speed();
void Decrease_Speed();
void Set_RPM_RGB(int rpm);
#define FAN_LED         PORTEbits.RE2
#define _XTAL_FREQ      8000000

#define ACK             1
#define NAK             0

#define ACCESS_CFG      0xAC
#define START_CONV      0xEE
#define READ_TEMP       0xAA
#define CONT_CONV       0x02



#define FAN_EN          PORTAbits.RA5
#define FAN_PWM         PORTCbits.RC2
#define RTC_ALARM_NOT   PORTAbits.RA4

#define Ch_Minus        0
#define Channel         1
#define Ch_Plus         2
#define Prev            3
#define Next            4
#define Play_Pause      5
#define Minus           6
#define Plus            7
#define EQ              8






extern char HEATER;
extern char duty_cycle;
extern char heater_set_temp;
extern signed int DS1621_tempF;

int get_duty_cycle(signed int temp, int set_temp)
{
    int dc;
    if(temp > set_temp)
    {
        dc = 0;
    }
    else
    {
        dc = 2 * (set_temp - temp);
    }
    if (dc >= 100)
    {
        dc = 100;
    }
    if ((temp - set_temp) > 50)
        dc = 100;
    return dc;
// add code to check if temp is greater than set_temp. If so, dc = 0. Else dc = 2 times of difference of set_temp and temp
// check if dc is greater than 100. If so, set it to 100
// return dc

}

void Monitor_Heater()
{
    duty_cycle = get_duty_cycle(DS1621_tempF, heater_set_temp);
    do_update_pwm(duty_cycle);
    if (HEATER == 1) 
    {
        FAN_EN = 1;
    }
    else 
    {
        FAN_EN = 0;
    }
}

void Toggle_Heater()
{
    if(HEATER == 0)
    {
        Turn_On_Fan();
        HEATER = 1 ;
       
    }
    else
    {
        Turn_Off_Fan();
    HEATER = 0;
    
    }
// add code just to flip the variable FAN

}

int get_RPM()
{
int RPS = TMR3L / 2;                    // read the count. Since there are 2 pulses per rev 
                                        // then RPS = count /2 
TMR3L = 0;                              // clear out the count 
return (RPS * 60); 
}

void Turn_Off_Fan()
{
    
    FAN_EN = 0;
    //FAN_LED = 0;

}

void Turn_On_Fan()
{
    
    do_update_pwm(duty_cycle);
    FAN_EN = 1;
    //FAN_LED = 1;
}







