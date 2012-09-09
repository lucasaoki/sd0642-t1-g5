#include "../include/ServerInterCpp.h"
#include "string.h"

void ServerInterCpp::start() {
    dataReady = new boost::thread(&ServerInterCpp::dataReady, this);
    this->startServer();
    this->startClient();
}

void ServerInterCpp::join() {
    dataReady->join();
    this->joinServer();
    this->joinClient();
}

void ServerInterCpp::closeSocket() {
    this->closeSocket();
}

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
