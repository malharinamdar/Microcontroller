#include <p18F4550.h>
#include "vector_relocate.h"

#define RS PORTEbits.RE0
#define RW PORTEbits.RE1
#define EN PORTEbits.RE2

void delay(unsigned int time)
{
    unsigned int i,j;
    for(i = 0; i < time; i++)
        for(j = 0; j < 165; j++);
}

void lcd_cmd(unsigned char cmd)
{
    PORTD = cmd;
    RS = 0;
    RW = 0;
    EN = 1;
    delay(100);
    EN = 0;
    delay(100);
}

void lcd_data(unsigned char data)
{
    PORTD = data;
    RS = 1;
    RW = 0;
    EN = 1;
    delay(100);
    EN = 0;
    delay(100);
}

void lcd_init(void)
{
    lcd_cmd(0x38);
    delay(50);
    lcd_cmd(0x0E);
    delay(50);
    lcd_cmd(0x01);
    delay(50);
    lcd_cmd(0x06);
    delay(50);
    lcd_cmd(0x80);
    delay(50);
}

void main()
{
    unsigned char msg1[] = "PICT";
    unsigned char msg2[] = "COLLEGE";
    unsigned int i;
    
    ADCON1 = 0x0F;
    TRISE = 0x00;
    TRISD = 0x00;
    lcd_init();
    delay(100);
    
    while(1)
    {
        lcd_cmd(0x84);
        delay(100);
        for(i = 0; i < 4; i++)
        {
            lcd_data(msg1[i]);
            delay(100);
        }
        
        lcd_cmd(0xC4);
        delay(100);
        for(i = 0; i < 7; i++)
        {
            lcd_data(msg2[i]);
            delay(100);
        }
    }
}