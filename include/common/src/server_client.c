#include "server_client.h"

#define SIZE_TIME_USAGE 1000000.0

void process(const struct rusage r){

	printf("User CPU time (s): %f\n", (r.ru_utime.tv_sec * 1000000 + r.ru_utime.tv_usec)/1000000.0);
	printf("System CPU time (s): %f\n", (r.ru_stime.tv_sec * 1000000 + r.ru_stime.tv_usec)/1000000.0);
	printf("maximum resident set size: %ld\n", r.ru_maxrss);
	printf("integral shared memory size: %ld\n", r.ru_ixrss);
	printf("integral unshared data size: %ld\n", r.ru_idrss);
	printf("integral unshared stack size: %ld\n", r.ru_isrss);
	printf("page reclaims (soft page faults): %ld\n", r.ru_minflt);
	printf("page faults (hard page faults): %ld\n", r.ru_majflt);
	printf("swaps: %ld\n", r.ru_nswap);
	printf("block input operations: %ld\n", r.ru_inblock);
	printf("block output operations: %ld\n", r.ru_oublock);
	printf("IPC messages sent: %ld\n", r.ru_msgsnd);
	printf("IPC messages received: %ld\n", r.ru_msgrcv);
	printf("signals received: %ld\n", r.ru_nsignals);
	printf("voluntary context switches: %ld\n", r.ru_nvcsw);
	printf("involuntary context switches: %ld\n", r.ru_nivcsw);
}

void createServer(int *sockServidor,const int port){
	
	int reuse_addr = 1;
	struct sockaddr_in server_address;
	
	*sockServidor = socket(AF_INET, SOCK_STREAM, 0);
	if( *sockServidor < 0){
		perror("sockServidoret");
		exit(EXIT_FAILURE);
	}
	
	setsockopt(*sockServidor, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof (reuse_addr));	
	bzero(&server_address, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(port);

	if( bind(*sockServidor, (struct sockaddr *)&server_address,sizeof(server_address))<0){
		perror("bind");
		close(*sockServidor);
		exit(EXIT_FAILURE);
	}

	listen(*sockServidor,NUM_MAX_CLIENT+1);
}

void connectServer(int *socketClient,const char *serverName,int port){
	
	struct sockaddr_in serv_addr;
	struct hostent *server;
	
	if( ( *socketClient = socket(AF_INET,SOCK_STREAM,0) ) < 0  ){
	    perror("socket");
		exit(EXIT_FAILURE);
    }
    
    if( *socketClient > 0 && ((server = gethostbyname(serverName)) == NULL) ){
        perror("server");
		exit(EXIT_FAILURE);
    }
    
    if( *socketClient > 0 ){
        bzero(&serv_addr,sizeof(serv_addr));
        serv_addr.sin_family = server->h_addrtype;
        serv_addr.sin_port = htons(port);
        serv_addr.sin_addr = *((struct in_addr *)server->h_addr);
        bzero(&(serv_addr.sin_zero),8);
    }
    else{
    	perror("socket");
		(EXIT_FAILURE);
    } 
    
    if( connect(*socketClient,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr)) < 0){
    	close(*socketClient);
    	perror("connect");
		exit(EXIT_FAILURE);
    }
    
}

void workServer(int sockServidor,int *array,int sizeArray,int *connection){
	
	int numClient = 0;

	while( numClient < NUM_MAX_CLIENT){
		connection[numClient] = accept(sockServidor,NULL,NULL);
		numClient++;
	}	
	
	recv(connection[0],array,sizeof(int)*sizeArray,MSG_WAITALL);
	recv(connection[1],array+sizeArray,sizeof(int)*sizeArray,MSG_WAITALL);
}
