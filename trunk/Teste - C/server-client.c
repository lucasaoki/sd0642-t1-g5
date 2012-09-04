/* A simple server in the internet domain using TCP
   The port number is passed as an argument 
   This version runs forever, forking off a separate 
   process for each connection
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h> 

/* function prototype */
int receiveMsg(int, int *,int );
int connection(int argc, char **);
void sendMsg(char **,int *);
void zeroVect(int *);	

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{ 
	connection(argc ,argv );
	return 0; /* we never get here */
}

int connection(int argc, char *argv[])
{
	int buffersize = 0, i;
	int vector[9];
	int sockfd, newsockfd, portno;
	socklen_t clilen;

	zeroVect(vector);	
	struct sockaddr_in serv_addr, cli_addr;
	if (argc < 5){
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		error("ERROR on binding");
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	while(1){
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0) 
			error("ERROR on accept");
		buffersize = receiveMsg(newsockfd, vector, buffersize);
		close(newsockfd);

		vector[8] = buffersize;
		if(buffersize == atoi(argv[4])){
			sendMsg(argv,vector);
		}
	} /* end of while */
	close(sockfd);
}


void sendMsg(char *argv[], int *vector)
{
    int sockfd, portno, n, i=0;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    portno = atoi(argv[3]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[2]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
 
    if (write(sockfd,vector,sizeof(vector)) < 0) 
         error("ERROR writing to socket");
    close(sockfd);
}

void zeroVect(int *vector){
	int i;	
	for(i=0;i<9;i++){
		vector[i]=0;
	}
}

int receiveMsg(int sock,int *vector,int buffersize)
{
	int n, i = 0,j =0, vectorNew[9]; 
	int t;

	if (read(sock,vectorNew,sizeof(vectorNew)) < 0)
		error("ERROR reading from socket");
	
	for(i=0;i<(vectorNew[8]);i++)
		vector[buffersize+i] = vectorNew[i];	

	for(i = 0; i < buffersize+vectorNew[8];i++){
		printf("Here is the message: %d\n",vector[i]); 
	}    	

	if(n < 0)
		error("ERROR writing to socket");   
	return (buffersize+vectorNew[8]);
}
