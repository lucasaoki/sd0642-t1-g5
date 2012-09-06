#include "server_client.h"
#include "array_header.h"
#include <sys/times.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#define TIME_SUB(old,new,value) \
do { \
	struct timespec result;\
	result.tv_sec = fullActionNew.tv_sec - fullActionOld.tv_sec;\
	result.tv_nsec = fullActionNew.tv_nsec - fullActionOld.tv_nsec;\
\
	if (result.tv_nsec < 0) {\
		--(result.tv_sec);\
		result.tv_nsec += 1000000000;\
	}\
	 value = result.tv_sec + result.tv_nsec / 1000000000.0;\
} while (0)

int main(int argc,char *argv[]){
	
	srand(time(NULL));
	
	int socketClient, port;	
	char serverName[20];
		
	if( argc < 2){
		fprintf(stderr,"usage %s hostname port\n",argv[0]);
		exit(EXIT_FAILURE);
	}
    
    strcpy(serverName,argv[1]);	
	port = atoi(argv[2]);
	
	connectServer(&socketClient, serverName, port);
 	
 	int array[ARRAY_SIZE_LEVEL_1];
 	
 	randomArray(array);
 	
    printf("---------------------ARRAY----------------------------\n");    
    printArray(array,ARRAY_SIZE_LEVEL_1);
    
    send(socketClient,array,sizeof(array),0);   
	
	int arrayResponse[ARRAY_SIZE_LEVEL_4];  
	
    recv(socketClient,arrayResponse,sizeof(int)*ARRAY_SIZE_LEVEL_4,MSG_WAITALL);
		
    printf("----------------ARRAY in Order--------------------------\n");
    printArray(arrayResponse,ARRAY_SIZE_LEVEL_4); 
    
    
    printf("----------------TIME INFORMATION------------------------\n");
   
    close(socketClient);
 
	return EXIT_SUCCESS;
}
