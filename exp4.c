#include <reg51.h>

void msdelay(unsigned int);

void main (void)
{
    while(1)
    {
        P1 = 0x03;
        msdelay(50);
        P1 = 0x09;
        msdelay(50);
        P1 = 0x0C;
        msdelay(50);
        P1 = 0x06;
        msdelay(50);
    }
}

void msdelay(unsigned int itime)
{
    unsigned int i,j;
    for(i = 0; i < itime; i++)
    {
        for(j = 0; j < 1275; j++)
        {
        }
    }
}