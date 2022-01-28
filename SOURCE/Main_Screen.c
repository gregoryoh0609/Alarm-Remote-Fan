
#include <xc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//#include "Main.h"
//#include "Main_Screen.h"
//#include "ST7735_TFT.h"
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


extern char buffer[31];
extern char *nbr;
extern char *txt;
extern char tempC[];
extern char tempF[];
extern char time[];
extern char date[];
extern char alarm_time[];
extern char Alarm_SW_Txt[];
extern char Heater_Set_Temp_Txt[];
extern char Heater_SW_Txt[];
 
extern char DC_Txt[];
extern char Volt_Txt[];
extern char RPM_Txt[];
extern char RTC_ALARM_Txt[];
extern signed int DS1621_tempC, DS1621_tempF;
extern unsigned char second, minute, hour, dow, day, month, year;
extern unsigned char alarm_second, alarm_minute, alarm_hour, alarm_date;
extern unsigned char heater_set_temp;
extern char duty_cycle;
extern int ALARMEN;
extern char HEATER;
extern int rpm;
extern float volt;

void Initialize_Screen(void) 
{ 
    LCD_Reset();                                    // Screen reset
    TFT_GreenTab_Initialize();         
    fillScreen(ST7735_BLACK);                       // Fills background of screen with color passed to it
 
    strcpy(txt, " ECE3301L F'21 Final\0");          // Text displayed 
    drawtext(start_x , start_y, txt, ST7735_WHITE  , ST7735_BLACK, TS_1);   
                                                    // X and Y coordinates of where the text is to be displayed
    strcpy(txt, "Temperature:");
    drawtext(temp_x  , temp_y , txt, ST7735_MAGENTA, ST7735_BLACK, TS_1);                                                                                               // including text color and the background of it
    drawCircle(circ_x, circ_y , 2  , ST7735_YELLOW);
    strcpy(txt, "C/");
    drawtext(tempc_x , tempc_y, txt, ST7735_YELLOW , ST7735_BLACK, TS_2); 
    strcpy(txt, "F");         
    drawCircle(cirf_x, cirf_y , 2  , ST7735_YELLOW);
    drawtext(tempf_x , tempf_y, txt, ST7735_YELLOW , ST7735_BLACK, TS_2);
    strcpy(txt, "Time");
    drawtext(time_x  , time_y , txt, ST7735_BLUE   , ST7735_BLACK, TS_1);
    strcpy(txt, "Date");
    drawtext(date_x  , date_y , txt, ST7735_RED    , ST7735_BLACK, TS_1);
    strcpy(txt, "Alarm Time");
    drawtext(alarm_time_x  , alarm_time_y , txt, ST7735_YELLOW, ST7735_BLACK, TS_1); 
    strcpy(txt, "Alarm SW");
    drawtext(alarm_sw_x, alarm_sw_y, txt, ST7735_YELLOW, ST7735_BLACK, TS_1);    
    strcpy(txt, "HTR Set Temp");
    drawtext(heater_set_temp_x, heater_set_temp_y, txt, ST7735_BLUE  , ST7735_BLACK, TS_1); 
    strcpy(txt, "HTR SW");
    drawtext(heater_sw_x, heater_sw_y, txt, ST7735_BLUE  , ST7735_BLACK, TS_1);
    strcpy(txt, "DC");
    drawtext(dc_x, dc_y, txt, ST7735_WHITE  , ST7735_BLACK, TS_1);
    strcpy(txt, "RM");
    drawtext(rtc_x, rtc_y, txt, ST7735_WHITE       , ST7735_BLACK  , TS_1);
    strcpy(txt, "Volt");
    drawtext(volt_x, volt_y, txt, ST7735_WHITE       , ST7735_BLACK  , TS_1);
    strcpy(txt, "RPM");
    drawtext(rpm_x, rpm_y, txt, ST7735_WHITE       , ST7735_BLACK  , TS_1); 
    
}


void Update_Screen(void)
{
    if ((DS1621_tempC & 0x80) == 0x80) 
    {
        tempC[0] = '-';
        char neg_DS1621_tempC = 0x80 - (DS1621_tempC & 0x7f);
        tempC[1]  = (neg_DS1621_tempC)/10  + '0';// Tens digit of C
        tempC[2]  = (neg_DS1621_tempC)%10  + '0';// Ones digit of C
    }
    else
    {
        tempC[0] = '+';
        tempC[1]  = DS1621_tempC/10  + '0';         // Tens digit of C
        tempC[2]  = DS1621_tempC%10  + '0';         // Ones digit of C
    }
    
    if (DS1621_tempF < 0) 
    {
        tempF[0] = '-';
        int neg_tempF = 0x80 - (DS1621_tempF & 0x7f);
        tempF[1]  = neg_tempF/10  + '0';            // Tens digit of C
        tempF[2]  = neg_tempF%10  + '0';            // Ones digit of C
    }
    else
    {
        tempF[0] = '+';
        tempF[1]  = DS1621_tempF/10  + '0';         // Tens digit of C
        tempF[2]  = DS1621_tempF%10  + '0';         // Ones digit of C
    }    
    
    time[0]  = (hour>>4)  + '0';                                                // Hour MSD
    time[1]  = (hour & 0x0f)+ '0';                                              // Hour LSD

    // modify the lines below
    time[3]  = (minute>>4)  + '0';                                              // Minute MSD
    time[4]  = (minute & 0x0f)+ '0';                                            // Minute LSD

    time[6]  = (second>>4)  + '0';                                              // Second MSD
    time[7]  = (second & 0x0f)+ '0';                                            // Second LSD

    date[0]  = (month>>4)  + '0';                                               // Month MSD
    date[1]  = (month & 0x0f)+ '0';                                             // Month LSD
    date[3]  =  (day>>4)  + '0';                                                // Day MSD
    date[4]  = (day & 0x0f)+ '0';                                               // Day LSD
    date[6]  = (year>>4)  + '0';                                                // Year MSD
    date[7]  = (year & 0x0f)+ '0';                 // Year LSD
    alarm_time[0]  = (alarm_hour>>4)  + '0';        // Alarm Hour MSD
    alarm_time[1]  = (alarm_hour & 0x0f)+ '0';      // Alarm Hour LSD
    alarm_time[3]  = (alarm_minute>>4) +'0'; // add code       // Alarm Minute MSD
    alarm_time[4]  = (alarm_minute & 0x0f) + '0'; // add code   // Alarm Minute LSD
    alarm_time[6]  = (alarm_second>>4) +'0'; // add code       // Alarm Second MSD
    alarm_time[7]  = (alarm_second & 0x0f) + '0'; // add code    // Alarm Second LSD
    
    if (ALARMEN == 1) 
    {   
        strcpy(Alarm_SW_Txt, "ON ");
    }
    else 
    {
        strcpy(Alarm_SW_Txt, "OFF");
    }
 
    Heater_Set_Temp_Txt[0] = heater_set_temp/100 +'0';
    Heater_Set_Temp_Txt[1] = (heater_set_temp/10)%10 +'0';
    Heater_Set_Temp_Txt[2] = heater_set_temp%10 +'0'; 
    
    if (HEATER == 1)
    {
        strcpy(Heater_SW_Txt, "ON ");
    }
    else 
    {
        strcpy(Heater_SW_Txt, "OFF");
    }
    
    if (RTC_ALARM_NOT == 0) RTC_ALARM_Txt[0] = '1';
    else RTC_ALARM_Txt[0] = '0';
       
    
    DC_Txt[0] = duty_cycle/100  + '0';
                                                                                // modify the lines below
    DC_Txt[1] = (duty_cycle/10)%10  + '0';
    DC_Txt[2] = (duty_cycle%10)  + '0';
    int volt2 = (int)(volt*10)%10;
    int volt3 = (int)(volt * 100)%10;
    Volt_Txt[0] = ((int)  volt) + '0';
    Volt_Txt[2] =volt2 + '0';
    Volt_Txt[3] = volt3 + '0';
    
    RPM_Txt[0] = rpm/1000  + '0';
                                                                                // modify the lines below
    RPM_Txt[1] = (rpm/100)%10 + '0';
    RPM_Txt[2] = (rpm/10)%10 + '0';
    RPM_Txt[3] = (rpm%10) + '0';     
    
  
    
        
    
    drawtext(data_tempc_x, data_tempc_y, tempC , ST7735_YELLOW , ST7735_BLACK , TS_2);       
    drawtext(data_tempf_x, data_tempf_y, tempF , ST7735_YELLOW , ST7735_BLACK , TS_2);
    drawtext(data_time_x , data_time_y , time  , ST7735_CYAN   , ST7735_BLACK , TS_2);
    drawtext(data_date_x , data_date_y , date  , ST7735_GREEN  , ST7735_BLACK , TS_2);
    drawtext(data_alarm_time_x , data_alarm_time_y , alarm_time  , ST7735_CYAN   , ST7735_BLACK , TS_1); 
    drawtext(data_alarm_sw_x , data_alarm_sw_y , Alarm_SW_Txt  , ST7735_CYAN   , ST7735_BLACK , TS_1); 
    drawtext(data_heater_set_temp_x, data_heater_set_temp_y ,Heater_Set_Temp_Txt, ST7735_RED, ST7735_BLACK, TS_1);
    drawtext(data_heater_sw_x, data_heater_sw_y, Heater_SW_Txt, ST7735_RED    , ST7735_BLACK , TS_1);    
    drawtext(data_dc_x, data_dc_y, DC_Txt, ST7735_GREEN, ST7735_BLACK, TS_1);
    drawtext(data_rtc_x, data_rtc_y, RTC_ALARM_Txt, ST7735_GREEN, ST7735_BLACK, TS_1);    
    drawtext(data_volt_x, data_volt_y, Volt_Txt, ST7735_GREEN, ST7735_BLACK, TS_1);    
    drawtext(data_rpm_x, data_rpm_y, RPM_Txt, ST7735_GREEN, ST7735_BLACK, TS_1);
}


