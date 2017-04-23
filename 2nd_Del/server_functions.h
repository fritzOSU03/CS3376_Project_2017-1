// File: server_functions.h
// Contributors:
//    James Fritz       jkf150030
//    Duc Nguyen        dqn150030
//    Luke Pettinger    flp081000
//    Kevin Shah        kjs160330
//    Brennan Stuewe    brs140230
//    Chase Vriezema    cmv140030
// Date: 04/23/2017
// Purpose: CS3376
// Description:
// 	This is the header file for server_functions.c.

#ifndef SERVER_FUNCTIONS_H
#define SERVER_FUNCTIONS_H

#include <time.h>
#include <netinet/in.h>


struct logMessage
{
	int32_t address;
	time_t dateTime;
	char message[1024];
};


void error(const char *);
void procTransT(int, logMessage &);
void sigCatcher(int);
int setupSocket(int, sockaddr_in &, int);
int appendLog(logMessage &);
int callLogServer(logMessage &);
void cleanExit(int);

#endif
