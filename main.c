#include        "PRAGMAS.h"
#include	"CO_MAIN.H"
#include	"Timer.H"
#include        "CO_COMM.h"
#include        "NMTextension.h"
#include        "IOutils.h"
#include	"Slave.h"
#include        "GPS.h"



void main(void)
{	

	TimerInit();		

	//mSYNC_SetCOBID(0x1000);		

	mCO_SetNodeID(0x03);	

        // 0x05 => 125kbps
        // 0x00 => 1Mbps
	mCO_SetBaud(0x05);		

	mNMTE_SetHeartBeat(0x0004);	
	mNMTE_SetGuardTime(0000);	
	mNMTE_SetLifeFactor(0x00);	

        IO_Init();
        InitializeGPS();
        Slave_Init();
        
	mCO_InitAll();
        CO_NMTStateChangeEvent();

        if( !COMM_STATE_PREOP )
            while( 1 );             //Wrong mode

        // Enable TPDO:s and RPDO:s
        mTPDOOpen(1);
        mTPDOOpen(2);
        
     
	while(1)
	{
		mCO_ProcessAllEvents();

                Slave_ProcessEvents();
		
		// 1ms timer events
		if (TimerIsOverflowEvent())
		{
			mCO_ProcessAllTimeEvents();	
		}

	}
}




