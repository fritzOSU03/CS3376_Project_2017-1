// File: server_functions.c
// Contributors:
//    
// Date: 04/23/2017
// Purpose: CS3376
// Description:
// 	This program contains a number of functions used by server.c.

#include <stdint.h>					//int32_t
#include <stdio.h>					//printf, perror, fopen, fclose
#include <stdlib.h>					//exit
#include <string.h>					//bzero, bcopy
#include <time.h>					//time_t, tm, localtime
#include <unistd.h>					//read, write, close
#include <netinet/in.h>				//sockaddr_in
//#include <sys/types.h>
#include <sys/socket.h>				//socket, AF_INET, connect, sendto, recvfrom
#include <sys/wait.h>				//wait3
//#include <errno.h>
//#include <math.h>
#include <netdb.h>					//hostent, gethostbyname
#include <signal.h>					//signal
#include "server_functions.h"

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

void procTransT(int socket)
{
	int n;
	//struct logMessage logMsg;
	char buffer[1024];
	
	//Reset the buffer.
	bzero(buffer, 1024);
	
	//Read the information from the client.
	n = read(socket, buffer, 1023);
	if(n < 0) error("ERROR reading from socket ");
	
	//Print the message.
	printf("TCP message: %s", buffer);
	
	//Write the response to the client.
	n = write(socket, buffer, sizeof(buffer));
	if(n < 0) error("ERROR writing to socket ");
}


int setupSocket(int type, sockaddr_in &serv_addr, int port_no)
{
	//Create the socket.
	int sockfd = socket(AF_INET, type, 0);
	if(sockfd < 0) return -1;
	
	//Set the address family, server IP, and port number.
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port_no);
	
	//int enable = 1;
	//if((setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int))) < 0)
	//	error("ERROR setting log socket options ");
	
	signal(SIGTERM, cleanExit);
	signal(SIGINT, cleanExit);
	
	return sockfd;
}

void sigCatcher(int n) {wait3(NULL, WNOHANG, NULL);}
void cleanExit(int n) {exit(0);}
