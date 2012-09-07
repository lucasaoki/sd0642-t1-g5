#include "server_client.h"
#include "array_header.h"
#include <sys/time.h>

int main(int argc,char *argv[]){
	
	int sockServidor, port;
	int socketClient, portClient;
	int size;
	char serverName[20];
	
	if(argc < 5){
		puts(USAGE_SERVER);
		exit(EXIT_FAILURE);
	}
	
	port = atoi(argv[1]);
	size = atoi(argv[2]);
	strcpy(serverName,argv[3]);	
	portClient = atoi(argv[4]);
	
	createServer(&sockServidor,port);
	
	if( size == 2)
		size = ARRAY_SIZE_LEVEL_1;
	else{
		if(size == 3)
			size = ARRAY_SIZE_LEVEL_2;
		else{
			perror("size");
			return EXIT_FAILURE;
		}
	}
	
	int array[size*2];
	int connection[NUM_MAX_CLIENT];	
	workServer(sockServidor,array,size,connection);
	
	struct timeval startOrder, endOrder;
	
	gettimeofday(&startOrder,NULL);
	qsort(array,2*size,sizeof(int),compar); 
	gettimeofday(&endOrder,NULL);
	
	struct timeval serverStartComunication, serverEndComunication;
	
	gettimeofday(&serverStartComunication,NULL);
    connectServer(&socketClient,serverName, portClient);
             
    int arrayRes[ARRAY_SIZE_LEVEL_4];      
    
    send(socketClient,array,sizeof(array),0);        
    
    recv(socketClient,arrayRes,sizeof(arrayRes),MSG_WAITALL);
    gettimeofday(&serverEndComunication,NULL);
    
    send(connection[0],arrayRes,sizeof(arrayRes),0);
    send(connection[1],arrayRes,sizeof(arrayRes),0);
	
	close(sockServidor);
				
	double total = (double)(serverEndComunication.tv_sec *1000000 + serverEndComunication.tv_usec) 
		- ( serverStartComunication.tv_sec*1000000 + serverStartComunication.tv_usec); 
 	double order = (double)(endOrder.tv_sec *1000000 + endOrder.tv_usec) 
		- ( startOrder.tv_sec*1000000 + startOrder.tv_usec); 
 	
 	printf("Time to order the array: %2.3f s\n",order/1000000);
 	printf("Time Comunication to server above: %2.3f s\n",total/1000000);
 		
	return EXIT_SUCCESS;
}
