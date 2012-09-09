#include "../include/ServerCpp.h"

/**
        @fn int compairS(const void *x1, const void *x2)
        @brief A member method that compair two integers
        @param *x1 an integer pointer
        @param *x2 an integer pointer
    @return 
 */
int compairS(const void *x1, const void *x2) {

    int elem1 = *(const int*) x1;
    int elem2 = *(const int*) x2;

    return (elem1 < elem2) ? -1 : 1;
}

/**
        @fn void ServerCpp::createServer()
        @brief A method of Server's class that creates the server
    @return 
 */
void ServerCpp::createServer() {
    int reuse_addr = 1;
    struct sockaddr_in serverAddr;

    sockServer_ = socket(AF_INET, SOCK_STREAM, 0);

    if (sockServer_ < 0) {
        perror("sockServer");
        exit(EXIT_FAILURE);
    }

    setsockopt(sockServer_, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof (reuse_addr));

    bzero(&serverAddr, sizeof (serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(port_);

    if (bind(sockServer_, (struct sockaddr *) &serverAddr, sizeof (serverAddr)) < 0) {
        perror("bind");
        close(sockServer_);
        exit(EXIT_FAILURE);
    }

    listen(sockServer_, NUM_MAX_CLIENT + 1);

    listener.fd = sockServer_;
    listener.events = POLLRDNORM;
}

/**
        @fn void ServerCpp::startServer()
        @brief A method of Server's class that initiates the server's threads
    @return 
 */
void ServerCpp::startServer() {
    threadConnection = new boost::thread(&ServerCpp::acceptConnection, this);
    threadReply = new boost::thread(&ServerCpp::isReady, this);
}

/**
        @fn void ServerCpp::joinServer()
        @brief A method of Server's class that calls the join()'s method of the threads
    @return 
 */
void ServerCpp::joinServer() {
    threadReply->join();
}

/**
        @fn void ServerCpp::acceptConnection()
        @brief A method of Server's class that establishes the server connection
    @return 
 */
void ServerCpp::acceptConnection() {
    while (numClient_ < NUM_MAX_CLIENT) {

        svrMutex.lock();

        connection_[indexConnect_] = poll(&listener, 1, 100);

        if (connection_[indexConnect_] > 0) {

            connection_[indexConnect_] = accept(sockServer_, NULL, NULL);
            listenerConnection[indexConnect_].fd = connection_[indexConnect_];
            listenerConnection[indexConnect_].events = POLLRDNORM;

            threadClient[indexConnect_] = new boost::thread(&ServerCpp::listenerClient, this, listenerConnection[indexConnect_]);
            indexConnect_++;
            numClient_++;
        }

        svrMutex.unlock();
        usleep(1000);
    }
}

/**
        @fn void ServerCpp::listenerClient(struct pollfd pollClient)
        @brief A method of Server's class that receives the client data
        @param pollClient file descriptor structure
    @return 
 */
void ServerCpp::listenerClient(struct pollfd pollClient) {
    int client;

    while (svrListenerReady_) {

        svrMutex.lock();

        client = poll(&pollClient, 1, 100);
        if (client > 0) {

            recv(pollClient.fd, serverArray_ + indexArray_, sizeof (int) * sArraySize_ / 2, MSG_WAITALL);

            if (pollClient.fd == connection_[0])
                indexArray_ = sArraySize_ / 2;
            else {
                if (pollClient.fd == connection_[1]) {
                    clientReady_ = 1;
                    svrListenerReady_ = 0;
                    if (isFinalServer_) {
                        isServerReady_ = 1;
                    }
                }
            }
        }
        svrMutex.unlock();
        usleep(1000);
    }
}

/**
        @fn void ServerCpp::isReady()
        @brief A method of Server's class that reply for its client
    @return 
 */
void ServerCpp::isReady() {
    serverArray_ = (int *) malloc(sizeof (int) * sArraySize_);

    while (workArray_) {
        svrMutex.lock();

        if (clientReady_ && isServerReady_) {
            if (isFinalServer_) {
                qsort(serverArray_, sArraySize_, sizeof (int), compairS);
                send(connection_[0], serverArray_, sizeof (int) *sArraySize_, 0);
                send(connection_[1], serverArray_, sizeof (int) *sArraySize_, 0);

            } else {
                send(connection_[0], returnArray_, sizeof (returnArray_), 0);
                send(connection_[1], returnArray_, sizeof (returnArray_), 0);
            }
            free(serverArray_);
            workArray_ = 0;
        }
        svrMutex.unlock();
        usleep(1000);
    }
}
