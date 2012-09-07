#include "server_client.h"
#include "array_header.h"
#include <sys/times.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>

int main(int argc,char *argv[]){
	
	srand(time(NULL));
	
	int socketClient, port;	
	char serverName[20];
		
	if( argc < 2){
		fprintf(stderr,"usage %s hostname port\n",argv[0]);
		exit(EXIT_FAILURE);
	}
    
    struct timeval startServerCom, endServerCom;
    struct timeval totalStartComunication, totalEndComunication;
    
    strcpy(serverName,argv[1]);	
	port = atoi(argv[2]);
	
	gettimeofday(&totalStartComunication,NULL);
	connectServer(&socketClient, serverName, port);
 	
 	int array[ARRAY_SIZE_LEVEL_1];
 	
 	randomArray(array);
 	
    printf("---------------------ARRAY----------------------------\n");    
    printArray(array,ARRAY_SIZE_LEVEL_1);
    
    gettimeofday(&startServerCom,NULL);
    send(socketClient,array,sizeof(array),0);   
	
	int arrayResponse[ARRAY_SIZE_LEVEL_4];  
	
    recv(socketClient,arrayResponse,sizeof(int)*ARRAY_SIZE_LEVEL_4,MSG_WAITALL);
	gettimeofday(&endServerCom,NULL);	
		
    printf("----------------ARRAY in Order--------------------------\n");
    printArray(arrayResponse,ARRAY_SIZE_LEVEL_4); 
    
    
    printf("----------------TIME INFORMATION------------------------\n");
   
    close(socketClient);
 	gettimeofday(&totalEndComunication,NULL);
 	
 	//time_t total = (totalEndComunication.tv_sec - totalStartComunication.tv_sec); 
 	//time_t comm = (endServerCom.tv_sec - startServerCom.tv_sec); 
 	
 	double total = (double)(totalEndComunication.tv_sec *1000000 + totalEndComunication.tv_usec) 
		- ( totalStartComunication.tv_sec*1000000 + totalStartComunication.tv_usec); 
 	double comm = (double)(endServerCom.tv_sec *1000000 + endServerCom.tv_usec) 
		- ( startServerCom.tv_sec*1000000 + startServerCom.tv_usec); 
 	
 	printf("Total Time Comunication: %2.3f s\n ",total/1000000);
 	printf("Time to comunicate to server: %2.3f s\n",comm/1000000);
 	
 	
	return EXIT_SUCCESS;
}
