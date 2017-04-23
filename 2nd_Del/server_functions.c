// File: server_functions.c
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
// 	This file contains a number of functions used by echo_s.c and log_s.c.

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netdb.h>
#include <signal.h>
#include "server_functions.h"


void error(const char *msg)
{
	perror(msg);
	exit(1);
}

void procTransT(int socket, logMessage &message)
{
	int n;
	struct logMessage logMsg;
	char buffer[1024];
	
	//Reset the buffer.
	bzero(buffer, sizeof(buffer));
	
	//Read the information from the client.
	n = read(socket, buffer, sizeof(buffer) - 1);
	if(n < 0) error("ERROR reading from socket ");
	
	//Print the message.
	printf("TCP message: %s", buffer);
	
	//Create the logMessage struct.
	logMsg.address = message.address;
	logMsg.dateTime = message.dateTime;
	bcopy((char *)buffer, (char *)logMsg.message, sizeof(buffer) - 1);
	
	//Call the log_s.
	callLogServer(logMsg);
	
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
	
	//Signal for clean exit.
	signal(SIGTERM, cleanExit);
	signal(SIGINT, cleanExit);
	
	return sockfd;
}

int callLogServer(logMessage &message)
{
	int sockfd, n;
	unsigned int length;
	struct sockaddr_in serv_addr, serv_resp;
	struct hostent *server;
	char buffer[1024];
	
	//Create the socket.
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0) error("ERROR opening socket ");
	
	//Set the address family, server IP, and port number.
	serv_addr.sin_family = AF_INET;
	server = gethostbyname("localhost");
	if(server == 0) error("ERROR, no such host ");
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr, server->h_length);
	serv_addr.sin_port = htons(9999);
	length = sizeof(struct sockaddr_in);
	
	//Write the information to the server.
	n = sendto(sockfd, (const struct logMessage *)&message, sizeof(struct logMessage), 0, (const struct sockaddr *)&serv_addr, length);
	if(n < 0) error("ERROR sending to socket ");
	
	//Reset the buffer.
	bzero(buffer, sizeof(buffer));
	
	//Read the reply from the server.
	n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serv_resp, &length);
	if(n < 0) error("ERROR receiving from socket ");
	
	//Print the reply from the server.
	printf("Log server response: %s\n", buffer);
	
	//Close the socket.
	close(sockfd);
	
	return 0;
}

// Designed by Kevin Shah and Brennan Stuewe
int appendLog(logMessage &logMsg)
{
	//Setup the echo.log file.
	FILE *logFile = fopen("echo.log", "a");
	
	if(logFile == NULL) error("Error opening file ");
	else {
		//Convert the given time to a tm struct.
		struct tm * now = localtime(&logMsg.dateTime);
		
		//Write the data to echo.log.
		fprintf(
			logFile,
			"%.4d-%.2d-%.2d %.2d:%.2d:%.2d	\"%s\" was received from %d.%d.%d.%d\n",
			(now->tm_year + 1900),
			(now->tm_mon + 1),
			now->tm_mday,
			now->tm_hour,
			now->tm_min,
			now->tm_sec,
			logMsg.message,
			int(logMsg.address&0xFF),
			int((logMsg.address&0xFF00)>>8),
			int((logMsg.address&0xFF0000)>>16),
			int((logMsg.address&0xFF000000)>>24));
	}
	
	//Close echo.log.
	fclose(logFile);
	
	return 0;
}

void sigCatcher(int n) {wait3(NULL, WNOHANG, NULL);}
void cleanExit(int n) {exit(0);}
