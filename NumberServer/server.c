/****
###Author: Ruben Perez Pascual
###Email: ruben11291@gmail.com
###Github:ruben11291
****/
#include <stdio.h>
#include <errno.h>

#include "headers.h"
#include "DoubleServer.h"

int main (int argc , char **argv)
{
	int port=PORT;
	if (argc == 2 ) 
		{
			if(! ( port=atoi( argv[1] ) ) )
			{
				fprintf(stderr, "%s\n", "The port given should be a number");
				exit(ERR_INPUT);
			}
			else if (port < MIN_PORT || port > MAX_PORT)
			{
				fprintf(stderr,"Port should be greater than %d and lower than %d\n", MIN_PORT, MAX_PORT);
				exit(ERR_INPUT);
			}
		}	
	
	return DoubleServer(port);
}

