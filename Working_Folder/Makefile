# Makefile for CS3376 C++ Semester Project
# Contributors: James Fritz, Duc Nguyen, F. Luke Pettinger, Kevin Shah, Brennan Stuewe, Chase Vriezema

PROG = CS3376_Project
CC = g++
CPPFLAGS = -g -Wall
LDFLAGS = 
OBJS = main.o blurb.o database.o

$(PROG) : $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $(OBJS)
main.o :
	$(CC) $(CPPFLAGS) -c main.cpp
blurb.o : blurb.h
	$(CC) $(CPPFLAGS) -c blurb.cpp
database.o : database.h
	$(CC) $(CPPFLAGS) -c database.cpp
clean:
	rm -f core $(PROG) $(OBJS)
