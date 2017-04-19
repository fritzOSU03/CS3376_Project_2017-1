Project 2nd Deliverable - ReadMe.txt

Members
	James Fritz		jkf150030
	Duc Nguyen		dqn150030
	Luke Pettinger	flp081000
	Kevin Shah		kjs160330
	Brennan Stuewe	brs140230
	Chase Vriezema	cmv140030

File List
	Makefile
	echo_s.c	server_functions.h	server_functions.c
	echo_c.c	client_functions.h	client_functions.c
	log_s.c

How To Compile
	Set the working directory to the location of the files in the above file
	list are located. To compile all of the files, execute 'make' in that
	directory. To compile the client, execute 'make echo_c' in that directory.
	To compile the server, execute 'make echo_s' in that directory. To compile
	the log server, execute 'make log_s' in that directory.

How To Run
	Log Server
		Set the working directory to the location of the compiled log server.
		To start the server, execute the following command in that directory.
			'./log_s'
		The log server will automatically use port number 9999.
	
	Echo Server
		Set the working directory to the location of the compiled echo server.
		To start the server, execute the following command in that directory.
			'./echo_s <portNo1> [<portNo2> <portNo3>]'
		At least one but no more than three available port numbers are required
		for the server to start.
	
	Echo Client
		Set the working directory to the location of the compiled echo client.
		To start the client, execute the following command in that directory.
			'./echo_c [-u | -udp] <server_address> <server_port>'
		By default, the client will operate using a TCP connection to the
		server. The '-u' or '-udp' options switch the client to UDP connection
		mode. The address for the server and the port number on the server are
		both required for the client to start.
