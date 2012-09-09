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
#define SIZE_ARRAY_RET 1000

/** 
        @class Server Server.h "include/Server.h"
        @brief A class for teste doxygen file

        A class to test draw inheritance        
 */
class ServerCpp {
public:

    ServerCpp(char *port) {
        port_ = atoi(port);
        sArraySize_ = SIZE_ARRAY_RET;
        clientReady_ = 0;
        numClient_ = 0;
        svrListenerReady_ = 1;
        workArray_ = 1;
        indexArray_ = 0;
        indexConnect_ = 0;
        isFinalServer_ = 1;
        isServerReady_ = 0;
        createServer();
    }
    void startServer();
    void joinServer();

protected:
    /**
        @var sockServer
        @brief Server's socket
        @var clientReady
        @brief Client flag
     */
    int port_;
    int sockServer_;
    int isServerReady_;
    int isFinalServer_;
    int clientReady_;
    int numClient_;
    int svrListenerReady_;
    int workArray_;
    int indexArray_;
    int indexConnect_;
    int sArraySize_;
    int *serverArray_;
    int returnArray_[SIZE_ARRAY_RET];
    int connection_[NUM_MAX_CLIENT];
    boost::mutex svrMutex;

    struct pollfd listener;
    struct pollfd listenerConnection[NUM_MAX_CLIENT];
    struct pollfd listenerServer;

    boost::thread *threadConnection;
    boost::thread *threadClient[NUM_MAX_CLIENT];
    boost::thread *threadReply;

private:
    /**

     */
    void createServer();
    void acceptConnection();
    void listenerClient(struct pollfd pollClient);
    void isReady();
};

#endif	/* SERVER_H */

