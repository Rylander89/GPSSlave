/* 
 * File:   NMEAParser.h
 * Author: Anton
 *
 * Created on den 2 november 2012, 11:08
 */

#ifndef NMEAPARSER_H
#define	NMEAPARSER_H

extern char SpeedArray[ 6 ];

int ParseNMEA();
void GetSpeed(short *speed);

#endif	/* NMEAPARSER_H */

