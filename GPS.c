#include <usart.h>
#include "Globals.h"
#include "GPS.h"
#include "NMEAParser.h"
#include "IOutils.h"

char GPS_Value[44] = { 0 };
char temp[6] = { 0 };
char newSpeed = 0x00;
//NMEA messages for initialization
//************************************************

#pragma idata gga
char gga_off[] = {"$PSRF103,00,00,00,01*24\r\n"};
char gga_on[] = {"$PSRF103,00,00,01,01*25\r\n"};

#pragma idata gll
char gll_off[] = {"$PSRF103,01,00,00,01*25\r\n"};
char gll_on[] = {"$PSRF103,01,00,01,01*24\r\n"};

#pragma idata gsa
char gsa_off[] = {"$PSRF103,02,00,00,01*26\r\n"};
char gsa_on[] = {"$PSRF103,02,00,01,01*27\r\n"};

#pragma idata gsv
char gsv_off[] = {"$PSRF103,03,00,00,01*27\r\n"};
char gsv_on[] = {"$PSRF103,03,00,01,01*26\r\n"};

#pragma idata rmc
char rmc_off[] = {"$PSRF103,04,00,00,01*20\r\n"};
char rmc_on[] = {"$PSRF103,04,00,01,01*21\r\n"};

#pragma idata vtg
char vtg_off[] = {"$PSRF103,05,00,00,01*21\r\n"};
char vtg_on[] = {"$PSRF103,05,00,01,01*20\r\n"};
#pragma idata

//************************************************

void InitializeGPS(void)
{
    // configure USART
    OpenUSART( USART_TX_INT_OFF &
    USART_RX_INT_OFF &
    USART_ASYNCH_MODE &
    USART_EIGHT_BIT &
    USART_CONT_RX &
    USART_BRGH_LOW,
    64 );
    
    while (BusyUSART());
    putsUSART(gga_off);
    while (BusyUSART());
    putsUSART(gsa_off);
    while (BusyUSART());
    putsUSART(gsv_off);
    while (BusyUSART());
    putsUSART(rmc_off);
    while (BusyUSART());
    putsUSART(gll_off);
    while (BusyUSART());
    putsUSART(vtg_on);
}

void ReadGPSNMEA(void)
{
    char first = 0x00;
    newSpeed = 0x00;
    first = ReadUSART();
    if(first == '$')
    {
        getsUSART(GPS_Value, 40);
        newSpeed = 0x01;
    }
}
