/****
###Author: Ruben Perez Pascual
###Email: ruben11291@gmail.com
###Github:ruben11291
****/
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

int createSocket ( int , struct sockaddr_in *);
int DoubleServer ( int );
void printError ( int );

