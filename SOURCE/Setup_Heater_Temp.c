#include <xc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//#include "Main.h"
//#include "I2C_Support.h"
//#include "Setup_Heater_Temp.h"
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





void Do_Setup_Heater_Temp(void);
void Initialize_Setup_Heater_Screen(void) ;
void Update_Setup_Heater_Screen(void);
void Decrease_Heater_Temp();
void Increase_Heater_Temp();
void Exit_Setup_Heater_Temp();
void Do_Save_New_Heater_Temp();


//  Setup DC Screen   
#define setup_heater_x          15
#define setup_heater_y          60    
#define setup_data_heater_x     40
#define setup_data_heater_y     74

extern char setup_heater_set_text[];
unsigned char setup_heater_set_temp;

char Select_Heater_Temp_Field;
char In_Heater_Temp_Setup;

extern char *txt;
extern char found;
extern unsigned char heater_set_temp = 50;
extern short nec_ok;

void Do_Setup_Heater_Temp(void)
{

In_Heater_Temp_Setup = 1;
    setup_heater_set_temp = heater_set_temp;
    Initialize_Setup_Heater_Screen();                  // Initialize setup heater screen
    Update_Setup_Heater_Screen();                      // Update the screen with latest info

    while (In_Heater_Temp_Setup == 1)
    {
         if (check_for_button_input() == 1)
        {
             //nec_ok = 0;
             if (found >= Play_Pause && found <= EQ)
             {
                Do_Beep_Good(); 
                if (found == Prev) Go_Prev_Field();
                if (found == Next) Go_Next_Field();       
                if (found == Play_Pause) Do_Save_New_Heater_Temp();                
                if (found == Minus) Decrease_Heater_Temp(); 
                if (found == Plus) Increase_Heater_Temp();
                if (found == EQ) Exit_Setup_Heater_Temp();
                found = 0xff;
             }
             else
             {
                 Do_Beep_Bad();
             }             
        }                   
    }
}

void Increase_Heater_Temp()
{
    if (setup_heater_set_temp < 110)
    {
        setup_heater_set_temp++;
    }
    else
    {
        setup_heater_set_temp = 110;
    }
	// add code to increase setup_heater_set_temp by 1
	// then check if it is greater than 110. If so, limit to 110

    	Update_Setup_Heater_Screen();                       // Update screen with latest info

}

void Decrease_Heater_Temp()          
{
    if (setup_heater_set_temp > 50)
    {
        setup_heater_set_temp--;
    }
    else
    {
        setup_heater_set_temp = 50;
    }
	// add code to decrease setup_heater_set_temp by 1
	// then check if it is less than 50. If so, limit to 50

    	Update_Setup_Heater_Screen();                      // Update screen with latest info

        
}

void Exit_Setup_Heater_Temp()
{
    DS3231_Read_Time();                                             // Read time
    Initialize_Screen();                                            // Initialize the screen before returning  
    In_Heater_Temp_Setup = 0;                                   
}

void Do_Save_New_Heater_Temp()
{
    heater_set_temp = setup_heater_set_temp;
    DS3231_Read_Time();                                             // Read time
    Initialize_Screen();                                            // Initialize the screen before returning  
    In_Heater_Temp_Setup = 0;     
}
    
void Initialize_Setup_Heater_Screen(void) 
{ 
    fillScreen(ST7735_BLACK);                               // Fills background of screen with color passed to it
 
    strcpy(txt, "ECE3301L F'21 Final\0");                    // Text displayed 
    drawtext(start_x , start_y, txt, ST7735_WHITE  , ST7735_BLACK, TS_1);   // X and Y coordinates of where the text is to be displayed

    strcpy(txt, "  Heater\0 ");                             // Text displayed 
    drawtext(start_x , start_y+25, txt, ST7735_YELLOW, ST7735_BLACK, TS_2);     
    strcpy(txt, "  Setup\0 ");                              // Text displayed 
    drawtext(start_x , start_y+40, txt, ST7735_YELLOW, ST7735_BLACK, TS_2);                       
    strcpy(txt, "Set Heater Temp");
    drawtext(setup_heater_x , setup_heater_y, txt, ST7735_CYAN  , ST7735_BLACK, TS_1);
}
    
void Update_Setup_Heater_Screen(void)
{
    char dc_char1 = setup_heater_set_temp/100;
    char dc_char2 = (setup_heater_set_temp/10)%10;
    char dc_char3 = setup_heater_set_temp%10;  
    setup_heater_set_text[0] = dc_char1 + '0';
    setup_heater_set_text[1] = dc_char2 + '0';
    setup_heater_set_text[2] = dc_char3 + '0';
    drawtext(setup_data_heater_x, setup_data_heater_y ,setup_heater_set_text, ST7735_RED, ST7735_BLACK, TS_2);
}


