#include "server_client.h"
#include "array_header.h"

int main(int argc,char *argv[]){
	
	int sockServidor, port;
	int socketClient, portClient;
	int size;
	char serverName[20];
	
	struct rusage usage;
	
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
	
	printArray(array,size*2); 
	qsort(array,2*size,sizeof(int),compar); 
	
		
    connectServer(&socketClient,serverName, portClient);
             
    int arrayRes[ARRAY_SIZE_LEVEL_4];      
    
    send(socketClient,array,sizeof(array),0);        
    
    recv(socketClient,arrayRes,sizeof(arrayRes),MSG_WAITALL);
            
    printArray(arrayRes,8*size);
            
    send(connection[0],arrayRes,sizeof(arrayRes),0);
    send(connection[1],arrayRes,sizeof(arrayRes),0);
	
	close(sockServidor);
	
	getrusage(RUSAGE_SELF, &usage);
	process(usage);
	
	return EXIT_SUCCESS;
}
