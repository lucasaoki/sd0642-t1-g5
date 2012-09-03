#include "../include/Server.h"

/**
        @fn void printArray(int *array)
        @brief A member method that insert x,y to elem
        @param *array an integer pointer
    @return 
*/
void printArray(int *array)
{

    int i;
    for(i = 0; i < ARRAY_SIZE_LEVEL_2; i++)
        printf("%d: %3d\n", i, array[i]);
}

int compair(const void *x1, const void *x2)
{

    int elem1 = *(const int*) x1;
    int elem2 = *(const int*) x2;

    return (elem1 < elem2)? -1 : 1;
}

void Server::createServer()
{
    int reuse_addr = 1;
    struct sockaddr_in serverAddr;

    sockServer = socket(AF_INET, SOCK_STREAM, 0);

    if(sockServer < 0) {
        perror("sockServer");
        exit(EXIT_FAILURE);
    }

    setsockopt(sockServer, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr));

    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(port);

    if(bind(sockServer, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("bind");
        close(sockServer);
        exit(EXIT_FAILURE);
    }

    listen(sockServer, NUM_MAX_CLIENT+1);

    listener.fd = sockServer;
    listener.events = POLLRDNORM;
}

void Server::start()
{
    threadConnection = new boost::thread(&Server::acceptConnection, this);
    threadMerger = new boost::thread(&Server::isReady, this);
}

void Server::join()
{
    threadMerger->join();
}

void Server::acceptConnection()
{
    while(numClient < NUM_MAX_CLIENT) {

        mutex.lock();

        connection[indexConnect]  = poll(&listener, 1, 100);

        if(connection[indexConnect] > 0) {

            connection[indexConnect] = accept(sockServer, NULL, NULL);
            listenerConnection[indexConnect].fd = connection[indexConnect];
            listenerConnection[indexConnect].events = POLLRDNORM;

            threadClient[indexConnect] = new boost::thread(&Server::listenerClient, this, listenerConnection[indexConnect]);
            indexConnect++;
            numClient++;
        }

        mutex.unlock();
        usleep(1000);
    }
}

void Server::listenerClient(struct pollfd pollClient)
{
    //struct pollfd pollClient = *((struct pollfd *)arg);
    int client;

    while(listenerReady) {

        mutex.lock();

        client  = poll(&pollClient, 1, 100);
        if(client > 0) {

            recv(pollClient.fd, array+indexArray, sizeof(int)*ARRAY_SIZE_LEVEL_2/2, 0);

            if(pollClient.fd == connection[0])
                indexArray = ARRAY_SIZE_LEVEL_2/2;
            else {
                if(pollClient.fd == connection[1]) {
                    clientReady = 1;
                    listenerReady = 0;
                }
            }
        }
        mutex.unlock();
        usleep(1000);
    }
}

void Server::isReady()
{
    while(workArray) {
        mutex.lock();

        if(clientReady) {

            qsort(array, ARRAY_SIZE_LEVEL_2, sizeof(int), compair);
            printArray(array);

            send(connection[0],array, sizeof(array), 0);
            send(connection[1],array, sizeof(array), 0);

            workArray = 0;
        }

        usleep(1000);
        mutex.unlock();
    }
}
