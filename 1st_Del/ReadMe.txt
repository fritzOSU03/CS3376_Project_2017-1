Project - ReadMe.txt

Members
	James Fritz		jkf150030
	Duc Nguyen		dqn150030
	Luke Pettinger	flp081000
	Kevin Shah		kjs160330
	Brennan Stuewe	brs140230
	Chase Vriezema	cmv140030

File List
	Makefile
	server.c	server_functions.h	server_functions.c
	client.c	client_functions.h	client_functions.c

How To Compile
	Set the working directory to the location of the files in the above file
	list are located. To compile all of the files, execute 'make' in that
	directory. To compile the client, execute 'make client' in that directory.
	To compile the server, execute 'make server' in that directory.

How To Run
	Server Side
		Set the working directory to the location of the compiled server. To
		start the server, execute './server <portNo>' in that directory. An
		available port number is required for the server to start.
	
	Client Side
		Set the working directory to the location of the compiled client. To
		start the client, execute the following command in that directory.
			'./client [-u | -udp] <server_address> <server_port>'
		By default, the client will operate using a TCP connection to the
		server. The '-u' or '-udp' options switch the client to UDP connection
		mode. The address for the server and the port number on the the server
		are both required for the client to start.
