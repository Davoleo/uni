/*
Simple server tcp socket with one send and one recive
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>		/* Structrure for socket */
#include <netinet/in.h>		/* Structures for internet structures */
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include <sys/select.h>

#define BUFFERLEN 2048

pthread_mutex_t read_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t write_lock = PTHREAD_MUTEX_INITIALIZER;
static int server_fd;


void check(int fd)
{
	if(fd < 0)
	{
		printf("Error code %d -> %s\n", errno, strerror(errno));
		exit(-1);
	}
}


void* connection_man(int connection_fd)
{	
	char buffer[BUFFERLEN];
	
	printf("Connection accepted with client number %d\n", connection_fd);
	fflush(stdout);
	// Send message to the client
	strcpy(buffer, "Connection accepted!");


	// The server re-send the same message to the client
	while(1)
	{	
		/* Send data to server */
		check(send(connection_fd, buffer, strlen(buffer), MSG_NOSIGNAL));
		puts("Data sent!");
		fflush(stdout);
		memset(buffer, 0, BUFFERLEN);

		/* Receive data */
		check(recv(connection_fd, buffer, BUFFERLEN, 0));
		printf("CLIENT: %s\n", buffer);

		if(strstr(buffer, "exit"))
		{	
			printf("Closing connection with client number %d\n", connection_fd);
			//pthread_mutex_unlock(&write_lock);
			break;
		}
	}

	close(server_fd);
	pthread_exit(NULL);
}


int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		puts("Missing parameters: <port>");
		return EXIT_FAILURE;
	}

	int bind_fd, listen_fd, connection_fd[2];
	struct sockaddr_in server_info, client_info;


	/* Crete the socket */
	check( (server_fd = socket(AF_INET, SOCK_STREAM, 0)) );
	puts("Socket created!");


	/* Setup server data */
	server_info.sin_addr.s_addr = INADDR_ANY;
	server_info.sin_family = AF_INET;
	server_info.sin_port = htons(atoi(argv[1]));


	/* Bind the socket */
	check( (bind_fd = bind(server_fd, (struct sockaddr *)&server_info, sizeof(server_info))) );
	puts("Socket binded!");


	/* Listen for connections */
	check( (listen_fd = listen(server_fd, 1)) );
	puts("Listening for connections...");


	const int conn_limit = 2;
	int conn_count = 0;

	/* Threads array */
	pthread_t thread_array[conn_limit];

	while(conn_count < 2)
	{	
		int len = sizeof(struct sockaddr_in);
		check( (connection_fd[conn_count] = accept(server_fd, (struct sockaddr *)&client_info, (socklen_t *)&len)) );
		pthread_create(&thread_array[conn_count], NULL, (void*)connection_man, connection_fd[conn_count]);

		conn_count++;
	}

	pthread_join(thread_array[0], NULL);
	pthread_join(thread_array[1], NULL);


	return EXIT_SUCCESS;
}