#ifndef NMEAPARSER_H
#define	NMEAPARSER_H

extern char SpeedArray[ 6 ];

int ParseNMEA(void);
void GetSpeed(short *speed);

#endif	/* NMEAPARSER_H */

