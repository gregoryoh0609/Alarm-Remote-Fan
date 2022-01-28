#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <math.h>
#include <p18f4620.h>
#include <usart.h>
#include <string.h>

//#include "I2C.h"
//#include "I2C_Support.h"
//#include "Interrupt.h"
//#include "Fan_Support.h"
//#include "Main.h"
//#include "ST7735_TFT.h"
//#include "utils.h"

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


void Monitor_Heater();
int get_RPM();
void Toggle_Heater();
void Turn_Off_Fan();
void Turn_On_Fan();
void do_update_pwm(char) ;
void Increase_Speed();
void Decrease_Speed();
void Set_RPM_RGB(int rpm);


void interrupt  high_priority chkisr(void) ;
void T0_ISR();
void INT0_isr(void);
void INT1_isr(void);
void INT2_isr(void);
void TIMER1_isr(void);
void Init_Interrupt(void);
void force_nec_state0();


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


void I2C_Init(const unsigned long);
void I2C_Wait(void);
void I2C_Start(void);
void I2C_ReStart(void);
void I2C_Stop(void);
char I2C_Read(char);
void I2C_Write(unsigned char);
void I2C_Write_Cmd_Only(char, char);  
void I2C_Write_Cmd_Write_Data(char, char, char);
void I2C_Write_Address_Write_One_Byte(char, char, char);    
BYTE I2C_Write_Address_Read_One_Byte(char, char);
 
void i2cHighSda(void);
void i2cLowSda(void);
void i2cHighScl(void);
void i2cLowScl(void);
void i2cNack(void);
void i2cAck(void);

#define SCL_PIN PORTDbits.RD6
#define SCL_DIR TRISDbits.RD6
#define SDA_PIN PORTDbits.RD7
#define SDA_DIR TRISDbits.RD7

#pragma config OSC = INTIO67
#pragma config BOREN =OFF
#pragma config WDT=OFF
#pragma config LVP=OFF
#pragma config CCP2MX = PORTBE

#define _XTAL_FREQ      8000000

#define ACK             1
#define NAK             0
#define FAN_LED         PORTEbits.RE2
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





void Test_Alarm();
char second = 0x00;
char minute = 0x00;
char hour = 0x00;
char dow = 0x00;
char day = 0x00;
char month = 0x00;
char year = 0x00;

char found;
char tempSecond = 0xff; 
signed int DS1621_tempC, DS1621_tempF;
char setup_second, setup_minute, setup_hour, setup_day, setup_month, setup_year;
char alarm_second, alarm_minute, alarm_hour, alarm_date;
char setup_alarm_second, setup_alarm_minute, setup_alarm_hour;
unsigned char heater_set_temp = 75;
unsigned char Nec_state = 0;
float volt;
char INT1_flag, INT2_flag;

short nec_ok = 0;
char Nec_code1;
char HEATER;
char duty_cycle;
int rps;
int rpm;
int ALARMEN;
int alarm_mode, MATCHED,color;


char buffer[31]     = " ECE3301L F'21 Final\0";
char *nbr;
char *txt;
char tempC[]        = "+25";
char tempF[]        = "+77";
char time[]         = "00:00:00";
char date[]         = "00/00/00";
char alarm_time[]   = "00:00:00";
char Alarm_SW_Txt[] = "OFF";
char Heater_Set_Temp_Txt[] = "075F";
char Heater_SW_Txt[]   = "OFF";                // text storage for Heater Mode
char array1[21]={0xa2,0x62,0xe2,0x22,0x02,0xc2,0xe0,0xa8,0x90,0x68,0x98,0xb0,0x30,0x18,0x7a,0x10,0x38,0x5a,0x42,0x4a,0x52};
char D1[8] = {0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70};

    
char DC_Txt[]       = "000";                // text storage for Duty Cycle value
char Volt_Txt[]     = "0.00V";
char RTC_ALARM_Txt[]= "0";                      //
char RPM_Txt[]      = "0000";               // text storage for RPM

char setup_time[]       = "00:00:00";
char setup_date[]       = "01/01/00";
char setup_alarm_time[] = "00:00:00"; 
char setup_heater_set_text[]   = "075F";


void putch (char c)
{   
    while (!TRMT);       
    TXREG = c;
}

void init_UART()
{
    OpenUSART (USART_TX_INT_OFF & USART_RX_INT_OFF & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_HIGH, 25);
    OSCCON = 0x70;
}



void Do_Init()                                                                  // Initialize the ports 
{ 
    init_UART();                                                                // Initialize the uart
    Init_ADC();
    OSCCON=0x70;                                                                // Set oscillator to 8 MHz 
    
    ADCON1=0x0E;
    TRISA = 0x11;
    TRISB = 0x05;
    TRISC = 0x01;
    TRISD = 0x00;
    TRISE = 0x00;
    PORTE = 0x00;
    //FAN_LED = 0;
    FAN_EN = 0;
    HEATER = 0;
    RBPU=0;
    PORTB = 0x00;                                                               // leave led off 
    TMR3L = 0x00;                   
    T3CON = 0x03;
    I2C_Init(100000); 

    DS1621_Init();
    Init_Interrupt();
    Turn_Off_Fan();
    heater_set_temp = 75;
}


void main() 
{
    alarm_mode = 0;                                                             // make sure alarm is off 
    Do_Init();                                                                  
    Initialize_Screen();                                                                        
    DS3231_Turn_Off_Alarm();                                                    // turn alarm off 
    DS3231_Read_Alarm_Time();                                                   // Read alarm time for the first time

    tempSecond = 0xff;
    while (1)
    {
        DS3231_Read_Time();                                                     // read the time 
        if(tempSecond != second)                                                // if time has changed then do loop    
        {
            tempSecond = second;                                                // tempsecond equates to actual second 
            rpm = get_RPM();                                                    // call function to get the rpm 
            volt = read_volt();                                                 // call function to get the volt 
            DS1621_tempC = DS1621_Read_Temp();
            if ((DS1621_tempC & 0x80) == 0x80) DS1621_tempC = - (0x80 - DS1621_tempC & 0x7f);
            DS1621_tempF = (DS1621_tempC * 9 / 5) + 32;                         // convert temp to fahrenheit
            printf("Voltage = %f V \r\n",volt);                                 // code to display onto teraterm

            printf ("%02x:%02x:%02x %02x/%02x/%02x",hour,minute,second,month,day,year);
            printf (" Temp = %d C = %d F ", DS1621_tempC, DS1621_tempF);
            printf ("alarm = %d Heater = %d ", RTC_ALARM_NOT, HEATER);
            printf ("RPM = %d  dc = %d\r\n", rpm, duty_cycle);
            
            Monitor_Heater();                                                   // updates the pwm 
            Set_RPM_RGB(rpm);
            Test_Alarm();                                                       // function for all the logic of the alarm
            Update_Screen();
        }
        
        if (check_for_button_input() == 1)                                      // check if button was pressed
        {

            nec_ok = 0;                                                         // reset nec_ok back to 0 to look for another button input 
            switch (found)
            {
                case Ch_Minus:                                                  // goes to setup time mode 
                    Do_Beep_Good();
                    Do_Setup_Time();
                    break;
                
                case Channel:                                                   // goes to setup alarm time mode 
                    Do_Beep_Good();
                    Do_Setup_Alarm_Time();
                    break;
                    
                case Ch_Plus:                                                   // goes to setup heater mode 
                    Do_Beep_Good();
                    Do_Setup_Heater_Temp();            
                    break;
                    
                case Play_Pause:                                                // turns on/off the heater
                    Do_Beep_Good();
                    Toggle_Heater();
                     break;           
        
                default:                                                        // does bad beep if the button is not recognized
                    Do_Beep_Bad();
                    break;
            }
        }    

        
        if (INT2_flag == 1)                                                     // checks if the interrupt button was pressed
        {
            if(ALARMEN == 1)                                                    // if statement to toggle on and off the alarmen
            {
                ALARMEN = 0;
                DS3231_Turn_Off_Alarm();  
                MATCHED = 0;
            }
            else
            {
                ALARMEN = 1;
                //Test_Alarm();
            }
            INT2_flag = 0;                                                      // reset flag back to 0 to detect another interrupt 
        }
        
    }
}

void Test_Alarm()
{
    if (alarm_mode == 0 && ALARMEN  == 1)                                       // first case turns the alarm on 
    {
        DS3231_Turn_On_Alarm();
        alarm_mode = 1;
        Update_Screen();
    }
    if (alarm_mode == 1 && ALARMEN == 0)                                        // second case turns the alarm, led, and buzzer off 
    {
        DS3231_Turn_Off_Alarm();
        alarm_mode = 0;
        PORTB = 0x00;
        Deactivate_Buzzer();
        Update_Screen();
    }
    if (alarm_mode == 1 && ALARMEN == 1)
    {
        
        if(RTC_ALARM_NOT == 0)                                                  // checks if the time matches alarm time 
        {

         MATCHED = 1;                                                           // changed the variable MATCHED to 1 to show the event occured 

        }
        if (MATCHED == 1)                                                       // loop to show MATCHED has occured 
        {
            Activate_Buzzer();
            for (int p = 0;p<8;p++)                                             // for loop to cycle through the rgb colors
            {
                volt = read_volt();                                             // reads the volt to input onto screen while in for loop
                PORTB = D1[p];                                                  // shows the colors on the RGBb led 
                    if(volt > 3)                                                // function to turn turn off the alarm if the voltage is higher than 3 
            {
                DS3231_Turn_Off_Alarm();                                        // this will reset the RTC_ALARM_NOT back to 0 
                MATCHED = 0;                                                    // reset the matches back to 0 
                Deactivate_Buzzer();
                PORTB = 0x00;
                p = p+8;                                                        // this exits the loop 
                DS3231_Turn_On_Alarm();                                         // turn back on to show the alarm has not turned off 
                Update_Screen();
            }
                if (INT2_flag == 1)                                             // looking for an interrupt button 
                {
                    DS3231_Turn_Off_Alarm();                                    // turns off the alarm
                    MATCHED = 0;                                                // reset the MATCHED back to 0 
                    Deactivate_Buzzer();
                    PORTB = 0x00;                                               // turns off LED 
                    ALARMEN = 0;                                                // turns off the ALARMEN 
                    p=p+8;                                                      // exits the loop 
                    INT2_flag = 0;                                              // reset the flag back to 0 so it can look for another interrupt 
                    Update_Screen();
                }
                DS3231_Read_Time();                                             // read time so the screen will update while the alarm is on 
                DS1621_tempC = DS1621_Read_Temp();
            if ((DS1621_tempC & 0x80) == 0x80) DS1621_tempC = - (0x80 - DS1621_tempC & 0x7f);
            DS1621_tempF = (DS1621_tempC * 9 / 5) + 32; 
                Wait_One_Sec();
                Wait_One_Sec();
                Update_Screen();

            }
        }
    }
}

void Set_RPM_RGB(int rpm)
{
    char color;
    if (rpm ==0)                        color = 0x00;
    else if (rpm > 0 && rpm < 1800)     color = 0x05;
    else if (rpm >=1800 && rpm < 2700)  color = 0x06;   
    else if (rpm >=2700)                color = 0x07;  
    PORTE = color;
}





