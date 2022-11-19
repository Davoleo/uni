// Nome Cognome - data 
// Summary: The client Send a single datagram to the server 
// gcc mysockaddr.c -o mysockaddr


#include <stdio.h>
#include <stdlib.h>
#include <string.h>    // strcpy
#include <unistd.h>    // optarg
// net
#include <netdb.h>     //inaddr
#include <arpa/inet.h>
#include <sys/socket.h>
#include <strings.h>   // bzero

void options_management(int, char **) ;  // options management       
void usage(char * argv[]);               // print usage ( option -h) 

// Net vars
int  port         = 25000;
char server[20]   = "localhost";

/////////////////////// main() //////////////////////////

int main(int argc, char **argv)
{

	options_management(argc, argv);         /* optarg management */

	int sockd;
	struct sockaddr_in servaddr;
	int socklen;
	struct hostent* myhostent;

	myhostent = gethostbyname(server);
	if(myhostent == 0) { 
		fprintf(stdout,"%s: host sconosciuto\n",server); 
		return(-1);
	}

	int sockfd;
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
		printf("errore in socket");

	socklen = sizeof(servaddr);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr = *(struct in_addr *) myhostent->h_addr;
	printf("SERVER %s:%d \n ", inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port));

	return 0; 

}


////////////////////////// options //////////////////////////////////////

void options_management(int argc, char* argv[]) {

  int i;
   while ((i = getopt(argc, argv, "s:p:h")) != -1) {
        switch (i) {
		
        case 's':  strcpy(server,optarg);  break;
        case 'p':  port = strtol(optarg, NULL, 10);  break;
        case 'h':  usage(argv); exit(0);
        case '?':  usage(argv); exit(1);
        default:   usage(argv); exit(1);
        }
    }
   printf("Options list: server=%s, port=%d \n", server, port);

}


////////////////////////// usage //////////////////////////////////////

void usage(char* argv[])  {
	printf ("\n%s [-s server] [-p port] [-m Message] [-h]",argv[0]);
	printf ("\n -s <int>    : Server -  default = %s" , server);
	printf ("\n -p <int>    : Port -  default = %d" , port);
	printf ("\n -h   : help ");
	printf ("\n");
}
