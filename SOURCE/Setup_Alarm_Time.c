#include <xc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//#include "I2C_Support.h"
//#include "Setup_Alarm_Time.h"
//#include "Setup_Time.h"
//#include "Main_Screen.h"
//#include "Main.h"
//#include "ST7735_TFT.h"
char check_for_button_input();
char bcd_2_dec (char);
int dec_2_bcd (char);
void Do_Beep();
void Do_Beep_Good();
void Do_Beep_Bad();
void Activate_Buzzer();
void Activate_Buzzer_4KHz();
void Activate_Buzzer_2KHz();
void Activate_Buzzer_500Hz();
void Deactivate_Buzzer();
void Wait_One_Sec();
void do_update_pwm(char);
void Set_RGB_Color(char);
float read_volt();
unsigned int get_full_ADC();
void Init_ADC();



//#include "utils.h"
#define _XTAL_FREQ  	8000000             // Set operation for 8 Mhz
#define TFT_DC      	PORTDbits.RD3       // Location of TFT D/C
#define TFT_CS     	 	PORTDbits.RD4       // Location of TFT Chip Select
#define TFT_RST     	PORTDbits.RD5       // Location of TFT Reset

#define RD               ST7735_RED
#define BU               ST7735_BLUE
#define GR               ST7735_GREEN
#define MA               ST7735_MAGENTA
#define BK               ST7735_BLACK

#define Circle_Size     20              	// Size of Circle for Light
#define Circle_X        60              	// Location of Circle
#define Circle_Y        80              	// Location of Circle
#define Text_X          52
#define Text_Y          77
#define TS_1            1               	// Size of Normal Text
#define TS_2            2               	// Size of Big Text

#define _swap(a, b) { signed int t; t = a; a = b; b = t;}
#define _width         128
#define _height        160
#define ST7735_NOP     0x00
#define ST7735_SWRESET 0x01
#define ST7735_RDDID   0x04
#define ST7735_RDDST   0x09
#define ST7735_SLPIN   0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON   0x12
#define ST7735_NORON   0x13
#define ST7735_INVOFF  0x20
#define ST7735_INVON   0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_RAMRD   0x2E
#define ST7735_PTLAR   0x30
#define ST7735_VSCRDEF 0x33
#define ST7735_COLMOD  0x3A
#define ST7735_MADCTL  0x36
#define ST7735_VSCRSADD 0x37
#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4
#define ST7735_DISSET5 0xB6
#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5
#define ST7735_RDID1   0xDA
#define ST7735_RDID2   0xDB
#define ST7735_RDID3   0xDC
#define ST7735_RDID4   0xDD
#define ST7735_PWCTR6  0xFC
#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

// Color definitions
#define   ST7735_BLACK   0x0000
#define   ST7735_BLUE    0x001F
#define   ST7735_RED     0xF800
#define   ST7735_GREEN   0x07E0
#define   ST7735_CYAN    0x07FF
#define   ST7735_MAGENTA 0xF81F
#define   ST7735_YELLOW  0xFFE0
#define   ST7735_WHITE   0xFFFF


void drawRoundRect(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char r, unsigned int color);
void fillRoundRect(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char r, unsigned int color);
void drawTriangle(signed int x0, signed int y0, signed int x1, signed int y1, signed int x2, signed int y2, unsigned int color);
void fillTriangle(signed int x0, signed int y0, signed int x1, signed int y1, signed int x2, signed int y2, unsigned int color);
void setTextWrap(BOOL w);
void invertDisplay(BOOL i);
void NormalDisplay();
int Color565(int r, int g, int b);
void spiwrite(unsigned char spidata);
void write_command(unsigned char cmd_);
void write_data(unsigned char data_);
void Rcmd1();
void Rcmd2red();
void Rcmd2green();
void Rcmd3();
void setScrollDefinition(unsigned char top_fix_height, unsigned char bottom_fix_height, BOOL _scroll_direction);
void setAddrWindow(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1);
void drawPixel(unsigned char x, unsigned char y, unsigned int color);
void drawFastVLine(unsigned char x, unsigned char y, unsigned char h, unsigned int color);
void fillRect(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned int color);
void drawtext(unsigned char x, unsigned char y, char *_text, unsigned int color, unsigned int bg, unsigned char size);
void drawChar(unsigned char x, unsigned char y, unsigned char c, unsigned int color, unsigned int bg,  unsigned char size);
void fillRectangle(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned int color);
void drawCircle(signed int x0, signed int y0, signed int r, unsigned int color);
void drawCircleHelper(signed int x0, signed int y0, signed int r, unsigned int cornername, unsigned int color);
void fillCircle(signed int x0, signed int y0, signed int r, unsigned int color);
void fillCircleHelper(signed int x0, signed int y0, signed int r, unsigned int cornername, signed int delta, unsigned int color);
void fillScreen(unsigned int color) ;
void drawFastHLine(unsigned char x, unsigned char y, unsigned char w, unsigned int color);
void VerticalScroll(unsigned char _vsp);
void TFT_BlackTab_Initialize();
void TFT_GreenTab_Initialize();
void TFT_RedTab_Initialize(void);
void TFT_ST7735B_Initialize(void);
void LCD_Reset(void);
void drawRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int color);



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






void Initialize_Screen(void) ;
void Update_Screen(void);

#define start_x             1
#define start_y             1
#define temp_x              24
#define temp_y              11
#define circ_x              40
#define circ_y              23
#define data_tempc_x        1
#define data_tempc_y        23
#define tempc_x             45
#define tempc_y             23
#define cirf_x              110
#define cirf_y              23
#define data_tempf_x        70
#define data_tempf_y        23
#define tempf_x             115
#define tempf_y             23
#define time_x              50
#define time_y              40
#define data_time_x         15
#define data_time_y         52
#define date_x              50
#define date_y              71
#define data_date_x         15
#define data_date_y         82

#define alarm_time_x        4
#define alarm_time_y        100
#define data_alarm_time_x   10
#define data_alarm_time_y   110

#define alarm_sw_x          77
#define alarm_sw_y          100
#define data_alarm_sw_x     95
#define data_alarm_sw_y     110

#define heater_set_temp_x      6
#define heater_set_temp_y      120
#define data_heater_set_temp_x 35
#define data_heater_set_temp_y 130

#define heater_sw_x            85
#define heater_sw_y            120
#define data_heater_sw_x       95
#define data_heater_sw_y       130

#define dc_x                12
#define dc_y                140
#define data_dc_x           10
#define data_dc_y           150

#define rtc_x               33
#define rtc_y               140
#define data_rtc_x          35
#define data_rtc_y          150

#define volt_x              50
#define volt_y              140
#define data_volt_x         50
#define data_volt_y         150

#define rpm_x               95
#define rpm_y               140
#define data_rpm_x          93
#define data_rpm_y          150


#define TS_1                1               // Size of Normal Text
#define TS_2                2               // Size of Number Text 


void Do_Setup_Time(void);
void Increase_Time(void);
void Decrease_Time(void);
void Go_Next_Field(void);
void Go_Prev_Field(void);
void Do_Save_New_Time(void);
void Initialize_Setup_Time_Screen(void);
void Update_Setup_Time_Screen(void);
void Update_Setup_Screen_Cursor_Forward(char);
void Update_Setup_Screen_Cursor_Backward(char field);
void Do_Save_New_Time();
void Exit_Time_Setup();


void DS1621_Init(void);
void DS3231_Read_Time(void);
void DS3231_Write_Time(void);
void DS3231_Read_Alarm_Time(void);
void DS3231_Write_Alarm_Time(void);
int DS3231_Read_Temp(void);
int DS1621_Read_Temp(void);
void DS3231_Turn_On_Alarm();
void DS3231_Turn_Off_Alarm();
void DS3231_Init();
void DS3231_Write_Initial_Alarm_Time(void);


void Setup_Alarm_Time(void);
void Increase_Alarm_Time(void);
void Decrease_Alarm_Time(void);
void Go_Next_Alarm_Field(void);
void Go_Prev_Alarm_Field(void);
void Exit_Setup_Alarm_Time(void);
void Do_Save_New_Alarm_Time(void);
void Initialize_Setup_Alarm_Time_Screen(void);
void Update_Setup_Alarm_Time_Screen(void);

extern char setup_alarm_time[]; 
extern unsigned char alarm_second, alarm_minute, alarm_hour, alarm_date;
extern unsigned char setup_alarm_second, setup_alarm_minute, setup_alarm_hour;
extern char found;
extern char *txt;
extern short nec_ok;

char Select_Alarm_Field;  
char In_Alarm_Time_Setup;

void Do_Setup_Alarm_Time(void)
{
    Select_Alarm_Field = 0;
    In_Alarm_Time_Setup = 1;
    DS3231_Read_Alarm_Time();                   // Read alarm time
    alarm_second = bcd_2_dec(alarm_second);     // convert to dec for use
    alarm_minute = bcd_2_dec(alarm_minute);
    alarm_hour   = bcd_2_dec(alarm_hour);
    setup_alarm_second = alarm_second;          // Beginning setup alarm time as current set alarm time
    setup_alarm_minute = alarm_minute;
    setup_alarm_hour = alarm_hour;
    Initialize_Setup_Alarm_Time_Screen();       // Initialize the alarm setup screen
    Update_Setup_Alarm_Time_Screen();           // Update the alarm screen with latest info
    while (In_Alarm_Time_Setup == 1)
    {   
         if (check_for_button_input() == 1)
         {
             if (found >= Prev && found <= EQ)
             {
                Do_Beep_Good(); 
                if (found == Prev) Go_Prev_Alarm_Field();
                if (found == Next) Go_Next_Alarm_Field();      
                if (found == Play_Pause) Do_Save_New_Alarm_Time();            
                if (found == Minus) Decrease_Alarm_Time();
                if (found == Plus) Increase_Alarm_Time();
                if (found == EQ) Exit_Setup_Alarm_Time();
                found = 0xff;
             }
             else
             {
                 Do_Beep_Bad();
             }
        }                   
    }
}

void Increase_Alarm_Time()
{
            switch (Select_Alarm_Field)             // Increment the proper field
            {
                case 0:
                    setup_alarm_hour++;
                    if (setup_alarm_hour == 24) setup_alarm_hour = 0; 
                    break;

                case 1:
                    setup_alarm_minute++;
                    if (setup_alarm_minute == 60) setup_alarm_minute = 0; 
                    break;

                case 2:
                    setup_alarm_second++;
                    if (setup_alarm_second == 60) setup_alarm_second = 0; 
                    break;

                default:
                    break;
            }    
            Update_Setup_Alarm_Time_Screen();   // Update alarm screen with latest info
                                                // Clear the increment flag
}

void Decrease_Alarm_Time()
{       
            switch (Select_Alarm_Field)               // Decrement the proper field
            {
                case 0:
                    if (setup_alarm_hour == 0) setup_alarm_hour = 23;
                    else --setup_alarm_hour;
                    break;

                case 1:
                    if (setup_alarm_minute == 0) setup_alarm_minute = 59;
                    else --setup_alarm_minute;
                    break;

                case 2:
                    if (setup_alarm_second == 0) setup_alarm_second = 59;
                    else --setup_alarm_second;
                    break;  

                default:
                break;
            }                
            Update_Setup_Alarm_Time_Screen();           // Update alarm screen with latest info
                         
} 

void Go_Next_Alarm_Field()
{
     
    Select_Alarm_Field++;                                   // Move to next field
    if (Select_Alarm_Field == 3) Select_Alarm_Field = 0;    // Wrap around if necessary
    Update_Setup_Screen_Cursor_Forward(Select_Alarm_Field); // Update cursor
                                     
}  

void Go_Prev_Alarm_Field()
{
    if (Select_Alarm_Field == 0) Select_Alarm_Field = 2;
    else Select_Alarm_Field--;                                // Move to next field
    Update_Setup_Screen_Cursor_Backward(Select_Alarm_Field);  // Update cursor
} 
          
void Exit_Setup_Alarm_Time()
{
    DS3231_Read_Time();                                     // Read time
    Initialize_Screen();                                    // Initialize the screen before returning  
    In_Alarm_Time_Setup = 0;
}

void Do_Save_New_Alarm_Time()
{
    DS3231_Write_Alarm_Time();                              // Write alarm time
    DS3231_Read_Alarm_Time();                               // Read alarm time
    DS3231_Read_Time();                                     // Read current time
    Initialize_Screen();                                    // Initialize main screen before returning
    In_Alarm_Time_Setup = 0;
}
     
void Initialize_Setup_Alarm_Time_Screen(void) 
{ 
    fillScreen(ST7735_BLACK);                               // Fills background of screen with color passed to it
 
    strcpy(txt, "ECE3301L F'21 Final");                     // Text displayed 
    drawtext(start_x , start_y, txt, ST7735_WHITE  , ST7735_BLACK, TS_1);
                                                                // X and Y coordinates of where the text is to be displayed

    strcpy(txt, "  Alarm");
    drawtext(start_x+5 , start_y+10, txt, ST7735_MAGENTA, ST7735_BLACK, TS_2);
    strcpy(txt, "  Setup");                                  // Text displayed 
    drawtext(start_x+5 , start_y+25, txt, ST7735_MAGENTA, ST7735_BLACK, TS_2); 
    
    strcpy(txt, "Time");
    drawtext(time_x  , time_y , txt, ST7735_BLUE   , ST7735_BLACK, TS_1);
    fillRect(data_time_x-1, data_time_y+16, 25,2,ST7735_CYAN);
}

void Update_Setup_Alarm_Time_Screen(void)
{
    printf ("%x:%x:%x\r\n", setup_alarm_hour,setup_alarm_minute,setup_alarm_second);
    setup_alarm_time[0]  = (setup_alarm_hour/10)  + '0';
    setup_alarm_time[1]  = (setup_alarm_hour%10)  + '0';
    setup_alarm_time[3]  = (setup_alarm_minute/10)  + '0';
    setup_alarm_time[4]  = (setup_alarm_minute%10)  + '0';
    setup_alarm_time[6]  = (setup_alarm_second/10)  + '0';
    setup_alarm_time[7]  = (setup_alarm_second%10)  + '0';
    drawtext(data_time_x, data_time_y, setup_alarm_time, ST7735_CYAN, ST7735_BLACK, TS_2);
}
 
