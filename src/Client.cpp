#include "../include/Client.h"

void randomArray(int *array)
{
    int i;

    for(i = 0; i < ARRAY_SIZE_LEVEL_1; i++)
        array[i] = rand()%999;
}

void printArray(int *array,int numElemInArray)
{
    int i;

    for(i = 0; i < numElemInArray; i++)
        printf("%d: %3d\n",i,array[i]);
}

int compair(const void *x1, const void *x2)
{

    int elem1 = *(const int*) x1;
    int elem2 = *(const int*) x2;

    return (elem1 < elem2)? -1 : 1;
}

void Client::start()
{
    threadConnection = new boost::thread(&Client::connectionToServer, this);
    threadWork = new boost::thread(&Client::work, this);
}

void Client::join()
{
    threadConnection->join();
    threadListenServer->join();
}

void Client::closeSocket()
{
    close(my_socket);
}

void Client::connectionToServer()
{
    while( tryConnection ) {

        my_socket = socket(AF_INET, SOCK_STREAM, 0);
        if( my_socket < 0  )
            perror("socket");

        server = gethostbyname(serverName);
        if( my_socket > 0 && server == NULL )
            perror("server");

        if( my_socket > 0 ) {
            bzero(&serv_addr, sizeof(serv_addr));
            serv_addr.sin_family = server->h_addrtype;
            serv_addr.sin_port = htons(port);
            serv_addr.sin_addr = *((struct in_addr *)server->h_addr);
            bzero(&(serv_addr.sin_zero), 8);
        }

        if( my_socket > 0 && ( connect(my_socket,(struct sockaddr *)&serv_addr, sizeof(struct sockaddr))) < 0) {
            close(my_socket);
            perror("connect");
            printf("It'll try again after 2 seconds\n");
        } else {

            tryConnection = 0;
            tryWork = 1;

            listenerServer.fd = my_socket;
            listenerServer.events = POLLRDNORM;
            threadListenServer = new boost::thread(&Client::listenerData, this, listenerServer);
        }
        sleep(2);
    }
}

void Client::work()
{
    while( doWork ) {
        if(tryWork) {

            randomArray(array);
            qsort(array, ARRAY_SIZE_LEVEL_1, sizeof(int), compair);

            send(my_socket, array, sizeof(array), 0);

            doWork = 0;
        }
        usleep(1000);
    }
}

void Client::listenerData(struct pollfd pollClient)
{
    int client;

    while( listenerReady ) {

        mutex.lock();
        client  = poll(&pollClient, 1, 100);

        if( client > 0 ) {

            int arrayResponse[ARRAY_SIZE_LEVEL_1*2];
            recv(pollClient.fd, arrayResponse, sizeof(arrayResponse), 0);
            printArray(arrayResponse, ARRAY_SIZE_LEVEL_1*2);

            listenerReady = 0;
        }

        mutex.unlock();
        usleep(1000);
    }
}
