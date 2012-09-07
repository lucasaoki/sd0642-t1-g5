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

void ServerInterCpp::dataIsReady() {
    while (waitingData) {

        cltMutex.lock();
        svrMutex.lock();
        if (!cltListenerReady_) {

			memcpy(returnArray_,arrayReply,SIZE_ARRAY_RET*sizeof(int));
            printf("alsjdfakshgdfakhsdkf \n");
            printArray(returnArray_, SIZE_ARRAY_RET);

            waitingData = 0;
            isDataReady_ = 1;
        }
        cltMutex.unlock();
        svrMutex.unlock();
        usleep(1000);
    }
}
