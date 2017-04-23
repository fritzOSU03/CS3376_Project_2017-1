// File: echo_c.c
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
// 	This program sends and receives data to the TCP/UDP echo server defined in
//		echo_s.c. Requires client_functions.c and a running instance of server.c.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "client_functions.h"


int main(int argc, char *argv[])
{
	bool useUDP(false);
	int sockfd, n;
	unsigned int length;
	struct sockaddr_in serv_addr, serv_resp;
	char buffer[1024];
	
	//Error if no address and port number provided or if too many args.
	if(argc < 3 || argc > 4) {
		fprintf(stderr, "Usage: %s [-u | -udp] server port\n", argv[0]);
		exit(0);
	}
	
	//If four args, see if argv[1] is -u or -udp.
	if(argc == 4) {
		if(strcmp(argv[1], "-u") != 0 && strcmp(argv[1], "-udp") != 0) {
			fprintf(stderr, "Usage: %s [-u | -udp] server port\n", argv[0]);
			exit(0);
		}
		argv++;
		useUDP = true;
	}
	
	//Create the socket.
	sockfd = setupSocket(useUDP, serv_addr, argv);
	if(sockfd < 0) error("ERROR opening socket ");
	
	length = sizeof(struct sockaddr_in);
	
	//Prompt for a message.
	printf("Enter a message: ");
	
	//Reset the buffer.
	bzero(buffer, sizeof(buffer));
	
	//Read from stdin to the buffer.
	fgets(buffer, sizeof(buffer) - 1, stdin);
	
	//Write the information to the server.
	if(useUDP)	n = sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *)&serv_addr, length);
	else		n = write(sockfd, buffer, strlen(buffer));
	if(n < 0)	error("ERROR writing to socket ");
	
	//Reset the buffer.
	if(!useUDP) bzero(buffer, sizeof(buffer));
	
	//Read the reply from the server.
	if(useUDP)	n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serv_resp, &length);
	else		n = read(sockfd, buffer, sizeof(buffer) - 1);
	if(n < 0)	error("ERROR reading from socket ");
	
	//Print the reply from the server.
	printf("Server response: %s", buffer);
	
	//Close the socket.
	close(sockfd);
	
	return 0;
}
