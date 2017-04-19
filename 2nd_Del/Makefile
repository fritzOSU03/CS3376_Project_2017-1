# File: Makefile for Echo/Log Server Project
# Author: James Fritz	jkf150030
# Date: 04/23/2017
# Purpose: CS3376
# Description: This program compiles and links the semester project
#	programs using the two-step building process.

PROG = echo_c echo_s log_s
CC = g++
CPPFLAGS = -g -Wall
LDFLAGS = 
C_OBJS = echo_c.o client_functions.o
S_OBJS = echo_s.o server_functions.o
L_OBJS = log_s.o server_functions.o

all : $(PROG)

echo_c : $(C_OBJS)
	$(CC) $(LDFLAGS) -o echo_c $(C_OBJS)
echo_s : $(S_OBJS)
	$(CC) $(LDFLAGS) -o echo_s $(S_OBJS)
log_s : $(L_OBJS)
	$(CC) $(LDFLAGS) -o log_s $(L_OBJS)
echo_c.o :
	$(CC) $(CPPFLAGS) -c echo_c.c
echo_s.o :
	$(CC) $(CPPFLAGS) -c echo_s.c
log_s.o :
	$(CC) $(CPPFLAGS) -c log_s.c
client_functions.o : client_functions.h
	$(CC) $(CPPFLAGS) -c client_functions.c
server_functions.o : server_functions.h
	$(CC) $(CPPFLAGS) -c server_functions.c
clean :
	rm -f core $(PROG) $(C_OBJS) $(S_OBJS) $(L_OBJS)
