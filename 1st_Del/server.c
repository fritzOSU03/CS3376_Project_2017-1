// File: server.c
// Contributors:
//    James Fritz		jkf150030
//    Duc Nguyen		dqn150030
//    Luke Pettinger	flp081000
//    Brennan Stuewe	brs140230
//    Chase Vriezema	cmv140030
// Date: 04/16/2017
// Purpose: CS3376
// Description:
// 	This program initiates a TCP/UDP echo server. Requires server_functions.c.

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
#include "server_functions.h"


int main(int argc, char *argv[])
{
	int tcpfd, newtcpfd, udpfd, nready, maxfdp1;
	pid_t childpid;
	fd_set rset;
	ssize_t n;
	socklen_t clilen;
	struct sockaddr_in cli_addr, serv_addr;
	char buffer[1024];
	
	//Error if no port number provided.
	if(argc < 2) {
		fprintf(stderr, "ERROR, no port provided.\n");
		exit(1);
	}
	
	//Set signal for waitpid - handles zombie processes.
	signal(SIGCHLD, sigCatcher);
	
	/**********    This section creates the TCP socket.    **********/
	//Set serv_addr to all zeros.
	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	//Create the TCP socket.
	tcpfd = setupSocket(SOCK_STREAM, serv_addr, atoi(argv[1]));
	if(tcpfd < 0) error("ERROR opening socket ");
	
	//Bind the TCP socket to the address.
	if(bind(tcpfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR on binding ");
	
	//Listen on the socket for connections.
	listen(tcpfd, 5);
	
	/**********    This section creates the UDP socket.    **********/
	//Set serv_addr to all zeros.
	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	//Create the UDP socket.
	udpfd = setupSocket(SOCK_DGRAM, serv_addr, atoi(argv[1]));
	if(udpfd < 0) error("ERROR opening socket ");
	
	//Bind the UDP socket to the address.
	if(bind(udpfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
		error("ERROR on binding ");
	/****************************************************************/
	
	//Clear the fd set.
	FD_ZERO(&rset);
	
	//Add one to the larger of the two file descriptors.
	maxfdp1 = fmax(tcpfd, udpfd) + 1;
	
	//Loop infinitely to handle connections.
	while(1) {
		//Add both file descriptors to the set.
		FD_SET(tcpfd, &rset);
		FD_SET(udpfd, &rset);
		
		//Use select to determine which fd responds to the call.
		if((nready = select(maxfdp1, &rset, NULL, NULL, NULL)) < 0) {
			if(errno == EINTR) continue;
			else error("ERROR on select ");
		}
		
		//If tcpfd was added, process TCP communication.
		if(FD_ISSET(tcpfd, &rset)) {
			clilen = sizeof(cli_addr);
			
			//Accept the connection with a new file descriptor.
			newtcpfd = accept(tcpfd, (struct sockaddr *) &cli_addr, &clilen);
			if (newtcpfd < 0) error("ERROR on accept ");
			
			//Fork the new connection.
			if((childpid = fork()) < 0) error("ERROR on fork ");
			
			//Handle the transmission in the child.
			if(childpid == 0) {
				close(tcpfd);
				procTransT(newtcpfd);
				exit(0);
			}
			
			//Close the new fd in the parent.
			close(newtcpfd);
		}
		
		//If udpfd was added, process UDP communication.
		if(FD_ISSET(udpfd, &rset)) {
			clilen = sizeof(cli_addr);
			
			//Reset the buffer.
			bzero(buffer, 1024);
			
			//Receive the information from the client.
			n = recvfrom(udpfd, buffer, 1024, 0, (struct sockaddr *)&cli_addr, &clilen);
			if(n < 0) error("ERROR receiving from socket ");
			
			//Print the message.
			write(1, "UDP message: ", 13);
			write(1, buffer, n);
			
			//Write the response to the client.
			n = sendto(udpfd, buffer, 1024, 0, (struct sockaddr *)&cli_addr, clilen);
			if(n < 0) error("ERROR sending to socket ");
		}
	}
	
	return 0;
}
