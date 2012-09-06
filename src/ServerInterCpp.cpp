#include "../include/ServerInterCpp.h"

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

void ServerInterCpp::dataIsReady() {
    while (waitingData) {

        svrMutex.lock();
        cltMutex.lock();
        if (!cltListenerReady_) {

            for (int i = 0; i < SIZE_ARRAY_RET; i++) {
                returnArray_[i] = arrayReply[i];
            }
            waitingData = 0;
            isDataReady_ = 1;
        }
        usleep(1000);
        svrMutex.unlock();
        cltMutex.unlock();
    }
}
