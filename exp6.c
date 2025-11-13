#include <p18f4550.h>

void timer_isr(void);

void main()
{
    ADCON1 = 0x0F;
    INTCON2bits.RBPU = 0;
    TRISBbits.TRISB0 = 0;
    PORTBbits.RB0 = 0;
    T0CON = 0x03;
    TMR0H = 0x6D;
    TMR0L = 0x26;
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
    INTCONbits.GIE = 1;
    T0CONbits.TMR0ON = 1;
    while(1);
}

extern void _startup (void);
#pragma code RESET_INTERRUPT_VECTOR = 0x1000
void _reset (void)
{
    _asm
        goto _startup
    _endasm
}
#pragma code

#pragma code LOW_INTERRUPT_VECTOR = 0x1018
void low_ISR (void)
{
}
#pragma code

#pragma code HIGH_INTERRUPT_VECTOR = 0x1008
void high_ISR (void)
{
    _asm
        goto timer_isr
    _endasm
}
#pragma code

///Timer ISR Function Prototype//
#pragma interrupt timer_isr
void timer_isr(void)
{
    TMR0H = 0X6D;
    TMR0L = 0x26;
    PORTBbits.RB0 = ~PORTBbits.RB0;
    INTCONbits.TMR0IF = 0;
}