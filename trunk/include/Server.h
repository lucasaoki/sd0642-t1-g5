/**
    @mainpage Doxygen My Test
    @brief How can I use doxygen documentation
    
    @index 
    The documentation became beautifull
*/

#ifndef SERVER_H
#define	SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <poll.h>
#include <boost/thread.hpp>

#define MAXELEM 2
#define NUM_MAX_CLIENT 2
#define ARRAY_SIZE_LEVEL_2 250
#define ARRAY_SIZE_LEVEL_3 500
#define ARRAY_SIZE_LEVEL_4 1000

/** 
        @class Server Server.h "include/Server.h"
        @brief A class for teste doxygen file

        A class to test draw inheritance        
*/
class Server
{
public:
    Server(char *port_) {
        port = atoi(port_);
        clientReady = 0;
        numClient = 0;
        listenerReady = 1;
        workArray = 1;
        indexArray = 0;
        indexConnect = 0;
        createServer();
    }
    void start();
    void join();

protected:
    /**
        @var sockServer
        @brief Server's socket
        @var clientReady
        @brief Client flag
    */
    int sockServer;
    int clientReady;
    int numClient;
    int listenerReady;
    int workArray;
    int indexArray;
    int indexConnect;
    int array[ARRAY_SIZE_LEVEL_2];
    int connection[NUM_MAX_CLIENT];
    int port;

    struct pollfd listener;
    struct pollfd listenerConnection[NUM_MAX_CLIENT];
    struct pollfd listenerServer;

    boost::thread *threadConnection;
    boost::thread *threadClient[NUM_MAX_CLIENT];
    boost::thread *threadMerger;

private:
    /**

    */
    void createServer();
    boost::mutex mutex;
    void acceptConnection();
    void listenerClient(struct pollfd pollClient);
    void isReady();
};

#endif	/* SERVER_H */

