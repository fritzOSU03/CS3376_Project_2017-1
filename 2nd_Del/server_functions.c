// File: server_functions.c
// Contributors:
//    James Fritz		jkf150030
//    Luke Pettinger	flp081000
//    Chase Vriezema	cmv140030
// Date: 04/23/2017
// Purpose: CS3376
// Description:
// 	This program contains a number of functions used by server.c.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>
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
	
	//Setup the socket for clean exit.
	signal(SIGTERM, cleanExit);
	signal(SIGINT, cleanExit);
	
	return sockfd;
}

void sigCatcher(int n) {wait3(NULL, WNOHANG, NULL);}
void cleanExit(int n) {exit(0);}
