// File: client_functions.h
// Contributors:
//
// Date: 04/16/2017
// Purpose: CS3376
// Description:
// 	This is the header file for client_functions.c.

#ifndef CLIENT_FUNCTIONS_H
#define CLIENT_FUNCTIONS_H


void error(const char *);
int setupSocket(bool, sockaddr_in &, char **);

#endif
