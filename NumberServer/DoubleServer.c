/****
###Author: Ruben Perez Pascual
###Email: ruben11291@gmail.com
###Github:ruben11291
****/
#include <stdio.h>
#include <string.h>
#include "DoubleServer.h"
#include "headers.h"


int DoubleServer ( int port )
{
	struct sockaddr_in server_addr, client_addr;
	int sock = createSocket (port, &server_addr);
	char buffer[MAX_BUFF_LEN];
	if ( sock < 0 )
		printError(sock);
	
	int client=0;
	
	while ( 1 )
	{
		socklen_t sock_len = sizeof(client_addr);
		client = accept (sock, (struct sockaddr *) &client_addr, &sock_len);
		int bytesRead;
		while( ( bytesRead = read( client, &buffer[0], sizeof(buffer ) ) ) )
		{
			int number = atoi(buffer)*2;
			sprintf(buffer, "%d\n",number);
			send (client, &buffer[0],strlen(buffer),0);
		}			
	}	
	return SUCCESS;
}

int createSocket( int port , struct sockaddr_in * server_addr)
{
	int sock, error;

  	sock = socket( AF_INET, SOCK_STREAM, 0 );
  	if ( sock < 0 ) 
		return ERR_CREATE_SOCKET;

	server_addr->sin_family = AF_INET;
	server_addr->sin_port = htons( port );
	server_addr->sin_addr.s_addr = htonl( INADDR_ANY );
	int opt_val = 1;
	setsockopt ( sock, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof opt_val );
	error = bind ( sock, ( struct sockaddr * ) server_addr, sizeof( *server_addr ) );
	if (error < 0 )
		return ERR_BIND_SOCKET;
	error = listen( sock , QUEUE );
	if (error < 0 )
		return ERR_LISTEN_SOCKET;
	
	return sock;
}

void printError( int errorNumber )
{
	fprintf(stderr, "Error %d\n", errorNumber);
}
