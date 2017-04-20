// File: log_s.c
// Contributors:
//    Duc Nguyen        dqn150030
//    Luke Pettinger    flp081000
// Date: 04/23/2017
// Purpose: CS3376
// Description:
// 	This program initiates a UDP log server. Requires server_functions.c.

#include <errno.h>
#include <math.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include "server_functions.h"

int main(int argc, char *argv[])
{
	//Define variables
	int udpfd, i, len;
	ssize_t n;
	socklen_t clilen;
	struct sockaddr_in cli_addr, serv_addr;
	struct logMessage message;
	//struct tm * timeinfo;
	char buffer[1024];
	
	//Set serv_addr to all zeros.
	bzero((char *) &serv_addr, sizeof(serv_addr));

	//Create the socket.
	udpfd = setupSocket(SOCK_DGRAM, serv_addr, 9999);
	if(udpfd < 0) error("ERROR opening socket ");

	//Bind the socket to the address.
	if(bind(udpfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
	error("ERROR on binding ");

	//Get the size of the client address structure.
	clilen = sizeof(cli_addr);
	
	//Loop infinitely to receive connections.
	while(1) {
		//Set message to all zeros.
		bzero(buffer, 1024);
		
		//Receive the logMessage from the client.
		n = recvfrom(udpfd, buffer, 1024, 0, (struct sockaddr *)&cli_addr, &clilen);
		if(n < 0) error("ERROR receiving from socket ");
		memcpy(&message, buffer, sizeof message);

		//Convert logMessage.time to a tm struct.
		//time ( &message.dateTime);
		//timeinfo = localtime ( &message.dateTime);


		//Find and clear the line return from logMessage.message.
		i = 0;
		len = strlen(message.message)+1;
		for(i=0; i<len; i++)
		{
			if(message.message[i] == '\n')
			{
				//Shift characters 1 to left.
				strncpy(&message.message[i],&message.message[i+1],len-i);
			}
		}

		//Print the message.
		printf("%s\n",message.message);

		
		//Write to the log file.
		appendLog(message);
		
		//Write the response to the client.
		n = sendto(udpfd, (const struct logMessage *)&message.message, sizeof(struct logMessage), 0, (struct sockaddr *)&cli_addr, clilen);
		if(n < 0) error("ERROR sending to socket ");
		
	}
	
	return 0;
}
