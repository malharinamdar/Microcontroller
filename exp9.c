#include <p18f4550.h>
#include "vector_relocate.h"

#define LCD_DATA    PORTD               //LCD data port
#define en          PORTEbits.RE2       // enable signal
#define rw          PORTEbits.RE1       // read/write signal
#define rs          PORTEbits.RE0       // register select signal

void LCD_cmd(unsigned char cmd);

void myMsDelay (unsigned int time)
{
    unsigned int i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 665; j++);
}

void init_LCD(void)
{
    LCD_cmd(0x38);      // initialization of 16X2 LCD in 8bit mode
    myMsDelay(15);

    LCD_cmd(0x01);      // clear LCD
    myMsDelay(15);

    LCD_cmd(0x0E);      // cursor off
    myMsDelay(15);

    LCD_cmd(0x80);      // ---8 go to first line and --0 is for 0th position
    myMsDelay(15);
}

//Function to pass command to the LCD
void LCD_cmd(unsigned char cmd)
{
    LCD_DATA = cmd;
    rs = 0;
    rw = 0;
    en = 1;
    myMsDelay(15);
    en = 0;
    myMsDelay(15);
}

//Function to write data to the LCD
void LCD_write(unsigned char data)
{
    LCD_DATA = data;
    rs = 1;
    rw = 0;
    en = 1;
    myMsDelay(15);
    en = 0;
    myMsDelay(15);
}

void main(void)
{
    unsigned int val[4], ADC_Result = 0, var;
    unsigned char i, str[] = "Result:";

    TRISD = 0x00;         //Configuring PORTD as output
    TRISE = 0;
    TRISA = 0xFF;
    init_LCD();
    
    // ADC Initialization
    ADCON1 = 0x0C;    // Reference as VDD & VSS, AN0 set as analog pins
    ADCON2 = 0x8E;    // Result is right Justified
                      //Acquisition Time 4TAD
                      //ADC Clk FOSC/64
    ADCON0 = 0X09;    //Turn ON ADC module

    LCD_cmd(0x80);
    for(i = 0; str[i] != '\0'; i++)
    {
        LCD_write(str[i]);
        myMsDelay(200);
    }
    
    while(1)
    {
        ADCON0bits.GO = 1;
        while(ADCON0bits.GO == 1);
        
        var = ((unsigned int)ADRESH) << 8;
        ADC_Result = var + ADRESL;

        for(i = 0; i < 4; i++)
        {
            val[i] = ADC_Result % 0x0A;
            val[i] = val[i] + 0x30;
            ADC_Result = ADC_Result / 0x0A;
        }

        LCD_cmd(0x87);
        LCD_write(val[3]);
        LCD_write(val[2]);
        LCD_write(val[1]);
        LCD_write(val[0]);
        
        //myMsDelay(500);
    }
}