/**
    @mainpage Doxygen My Test
    @brief How can I use doxygen documentation
    
    @index 
    The documentation became beautifull
*/

#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <poll.h>
#include <boost/thread.hpp>

#define ARRAY_SIZE_LEVEL_1 125

/** 
        @class Clinet Client.h "include/Client.h"
        @brief A class for teste doxygen file

        A class to test draw inheritance        
*/
class Client
{
public:
    /**

    */
    Client(char *argv[]) {
        listenerReady = 1;
        tryWork = 0;
        doWork = 1;
        tryConnection = 1;
        strcpy(serverName, argv[1]);
        port = atoi(argv[2]);
    }
    void start();
    void join();
    void closeSocket();

protected:
    /**

    */
    char serverName[20];
    int my_socket;
    int port;
    int listenerReady;
    int tryWork;
    int doWork;
    int tryConnection;
    int array[ARRAY_SIZE_LEVEL_1];

    struct sockaddr_in serv_addr;
    struct hostent *server;
    struct pollfd listenerServer;

    boost::thread *threadConnection;
    boost::thread *threadWork;
    boost::thread *threadListenServer;

private:
    /**

    */
    void startClient();
    boost::mutex mutex;
    void connectionToServer();
    void work();
    void listenerData(struct pollfd pollClient);
};

#endif /* CLIENT_H */
