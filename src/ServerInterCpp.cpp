#include "../include/ServerInterCpp.h"
#include "string.h"

/**
        @fn void ServerInterCpp::start()
        @brief A method of ServerInterCpp's class that initiates the object methods
    @return 
 */
void ServerInterCpp::start() {
    dataReady = new boost::thread(&ServerInterCpp::dataReady, this);
    this->startServer();
    this->startClient();
    isClientReady_ = 0;
}

/**
        @fn void ServerInterCpp::join()
        @brief A method of ServerInterCpp's class that calls the join()'s method
    @return 
 */
void ServerInterCpp::join() {
    dataReady->join();
    this->joinServer();
    this->joinClient();
}

/**
        @fn void ServerInterCpp::closeSocket()
        @brief A method of ServerInterCpp's class that closes the connection socket
    @return 
 */
void ServerInterCpp::closeSocket() {
    this->closeSocket();
}

/**
        @fn void ServerInterCpp::setArraySize()
        @brief A method of ServerInterCpp's class that sets the server and client's array size
        @param level an integer, server/client level
    @return 
 */
void ServerInterCpp::setArraySize(int level) {
    switch (level) {
        case 1: cArraySize_ = 125;
            break;
        case 2: cArraySize_ = 250;
            sArraySize_ = 250;
            break;
        case 3: cArraySize_ = 500;
            sArraySize_ = 500;
            break;
    }
}

/**
        @fn void ServerInterCpp::serverToClientData()
        @brief A method of ServerInterCpp's class that transfers data from inside server to inside client
    @return 
 */
void ServerInterCpp::serverToClientData() {
    while (!serverToClient) {
        svrMutex.lock();
        cltMutex.lock();
        if (!svrListenerReady_ && clientReady_) {
            for (int i = 0; i < sArraySize_; i++) {
                clientArray_[i] = serverArray_[i];
            }
            serverToClient = 1;
            isClientReady_ = 1;
        }
        svrMutex.unlock();
        cltMutex.unlock();
        usleep(1000);
    }
}

/**
        @fn void ServerInterCpp::clientToServerData()
        @brief A method of ServerInterCpp's class that transfers data from inside client to inside server
    @return 
 */
void ServerInterCpp::clientToServerData() {
    while (waitingData) {
        cltMutex.lock();
        svrMutex.lock();
        if (!cltListenerReady_) {
            for (int i = 0; i < SIZE_ARRAY_RET; i++) {
                returnArray_[i] = arrayReply_[i];
            }
            waitingData = 0;
            isServerReady_ = 1;
        }
        cltMutex.unlock();
        svrMutex.unlock();
        usleep(1000);
    }
}
