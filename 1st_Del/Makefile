# File: Makefile for Echo Server Project
# Author: James Fritz	jkf150030
# Date: 04/16/2017
# Purpose: CS3376
# Description: This program compiles and links the semester project
#	programs using the two-step building process.

PROG = client server
CC = g++
CPPFLAGS = -g -Wall
LDFLAGS = 
C_OBJS = client.o client_functions.o
S_OBJS = server.o server_functions.o

all : $(PROG)

client : $(C_OBJS)
	$(CC) $(LDFLAGS) -o client $(C_OBJS)
server : $(S_OBJS)
	$(CC) $(CPPFLAGS) -o server $(S_OBJS)
client.o :
	$(CC) $(CPPFLAGS) -c client.c
server.o :
	$(CC) $(CPPFLAGS) -c server.c
client_functions.o : client_functions.h
	$(CC) $(CPPFLAGS) -c client_functions.c
server_functions.o : server_functions.h
	$(CC) $(CPPFLAGS) -c server_functions.c
clean :
	rm -f core $(PROG) $(C_OBJS) $(S_OBJS)
