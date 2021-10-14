/*
Simple client tcp socket with one send and one recive
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define BUFFERLEN 2048


void check(int fd)
{
	if(fd < 0)
	{
		printf("Error code %d -> %s\n", errno, strerror(errno));
		exit(-1);
	}
}


int main(int argc, char* argv[])
{	
	if(argc < 3)
	{
		puts("Missing parameters: <ip> <port>");
		return EXIT_FAILURE;
	}

	int socket_fd, connection_fd;
	char buffer[BUFFERLEN];
	
	/* Crete the socket */
	check( (socket_fd = socket(AF_INET, SOCK_STREAM, 0)) );
	puts("Socket created!");


	/* Setup server data */
	struct sockaddr_in server_info;

	server_info.sin_addr.s_addr = inet_addr(argv[1]);
	server_info.sin_family = AF_INET;
	server_info.sin_port = htons(atoi(argv[2]));
	

	/* Connect to the server */
	check( (connection_fd = connect(socket_fd, (struct sockaddr *)&server_info, sizeof(server_info))) );
	puts("Connected!");


	while(1)
	{
		/* Receive data */
		check(recv(socket_fd, buffer, BUFFERLEN, 0));
		printf("SERVER: %s\n", buffer);


		/* Send data to server */
		do
		{
			memset(buffer, 0, BUFFERLEN);
			printf("CLIENT > ");
			fgets(buffer, BUFFERLEN, stdin);
		}
		while(strlen(buffer) > BUFFERLEN);
		
		check(send(socket_fd, buffer, strlen(buffer), MSG_NOSIGNAL));
		puts("Data sent!");

		if(strcmp(buffer, "exit\n") == 0)
		{
			puts("Closing socket...");
			break;
		}
	}

	/* Close socket */
	close(socket_fd);

	return EXIT_SUCCESS;
}
