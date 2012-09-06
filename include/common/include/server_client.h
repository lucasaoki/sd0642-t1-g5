#ifndef SERVER_CLIENT_HEADER
#define SERVER_CLIENT_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/resource.h>


#define USAGE_SERVER \
"USAGE: Server Creation [options] \n" \
"       -ms [port] : Main Server, the hightest server\n" \
"       -cs [level{2,3,4} portServer portClient ]  \n" \
"                  : Client and Server: one of six intermediate server \n" \
"       -h         : To see this help\n" \


#define NUM_MAX_CLIENT 2

void process(struct rusage p);
void createServer(int *sockServidor,const int port);
void connectServer(int *socketClient,const char *serverName,int port);

void workServer(int sockServidor,int *array,int sizeArray,int *connection);
#endif
