// File: server_functions.h
// Contributors:
//    James Fritz		jkf150030
//    Luke Pettinger	flp081000
//    Chase Vriezema	cmv140030
// Date: 04/23/2017
// Purpose: CS3376
// Description:
// 	This is the header file for server_functions.c.

#ifndef SERVER_FUNCTIONS_H
#define SERVER_FUNCTIONS_H

#include <netinet/in.h>


void error(const char *);
void procTransT(int);
void sigCatcher(int);
int setupSocket(int, sockaddr_in &, int);
void cleanExit(int);

#endif
