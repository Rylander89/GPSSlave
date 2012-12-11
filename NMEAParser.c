#include "NMEAParser.h"
#include "Globals.h"
#include <p18f4680.h>
#include <usart.h>

char SpeedArray[ 6 ] = { 0 };
char HeadingArray[ 8 ] = { 0 };

int ParseNMEA()
{
    unsigned int comma = 0;
    char *p = GPS_Value;
    unsigned int speed = 0;
    unsigned int heading = 0;
    while( *p != '\0' )
    {
        if( *p == ',' )
        {
            comma++;
            if(*(p+1) != ',')
                p++;
        }
        if( comma == 1 )
        {
            HeadingArray[ heading ] = *p;
            heading++;
        }
        if( comma == 7 )
        {
            SpeedArray[ speed ] = *p;
            speed++;
        }
        p++;
    }
}

void GetSpeed( short *speed )
{
    char *p = SpeedArray;
    int i;
    *speed = 0;
    for(i=0; i<6; i++)
    {
        *speed += (int)(*p-48);
        if(*(p+1) == '.')
            break;
        *speed *= 10;
        p++;
    }
}
