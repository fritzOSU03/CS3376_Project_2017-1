// File: client_functions.c
// Contributors:
//
// Date: 04/16/2017
// Purpose: CS3376
// Description:
// 	This program contains a number of functions used by client.c.

#include <netdb.h>					//hostent, gethostbyname
#include <stdio.h>					//perror
#include <stdlib.h>					//exit, atoi
#include <string.h>					//bzero, bcopy
//#include <unistd.h>
#include <arpa/inet.h>				//htons
#include <netinet/in.h>				//sockaddr_in
#include <sys/socket.h>				//socket, AF_INET, connect
#include <sys/types.h>				//SOCK_DGRAM, SOCK_STREAM
#include "client_functions.h"


void error(const char *msg)
{
	perror(msg);
	exit(0);
}

int setupSocket(bool useUDP, sockaddr_in &serv_addr, char **argv)
{
	struct hostent *server;
	
	//Create the socket.
	int sockfd;
	if(useUDP)	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	else		sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) return -1;
	
	//Get a pointer to the host information.
	server = gethostbyname(argv[1]);
	if(server == 0) error("ERROR, no such host ");
	
	//Set serv_addr to all zeros.
	if(!useUDP) bzero((char *) &serv_addr, sizeof(serv_addr));
	
	//Set the address family, server IP, and port number.
	serv_addr.sin_family = AF_INET;
	if(useUDP)	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr, server->h_length);
	else 		bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(atoi(argv[2]));
	
	//If TCP, connect the socket to the address of the server.
	if(!useUDP)
		if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
			error("ERROR connecting ");
	
	return sockfd;
}
