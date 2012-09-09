/**
    @mainpage Doxygen My Test
    @brief How can I use doxygen documentation
    
    @index 
    The documentation became beautifull
 */

/**
-------------------------------------------------------------
    client puro,    ./x ipServer porta
    servclient,     ./x portaDele nivel ipServer portaServer
-------------------------------------------------------------
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
#include <fcntl.h>
#include <poll.h>
#include <boost/thread.hpp>

#define SIZE_ARRAY_RET 1000

/** 
        @class Client Client.h "include/Client.h"
        @brief A class for teste doxygen file

        A class to test draw inheritance        
 */
class ClientCpp {
public:

    /**

     */
    ClientCpp(char *serverName, char *port) {
        cArraySize_ = SIZE_ARRAY_RET / 8;
        cltListenerReady_ = 1;
        tryWork_ = 0;
        isClientReady_ = 0;
        doWork_ = 1;
        tryConnection_ = 1;
        strcpy(serverName_, serverName);
        port_ = atoi(port);
    }
    void startClient();
    void joinClient();
    void closeSocket();

protected:
    /**

     */
    char serverName_[20];
    int my_socket_;
    int port_;
    int cltListenerReady_;
    int tryWork_;
    int doWork_;
    int isClientReady_;
    int tryConnection_;
    int cArraySize_;
    int *clientArray_;
    int arrayReply_[SIZE_ARRAY_RET];
    boost::mutex cltMutex;

    struct timeval iniTime, finalTime;
    struct timeval iniConnTime, finalConnTime;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    struct pollfd listenerServer;

    boost::thread *threadConnection;
    boost::thread *threadWork;
    boost::thread *threadListenServer;

private:
    /**

     */
    void connectionToServer();
    void work();
    void listenerData(struct pollfd pollClient);
    void randomArray(int *array);
    void printArray(int *array, int numElem);
    void printTime();
};

#endif /* CLIENT_H */
