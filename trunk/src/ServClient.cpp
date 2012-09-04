#include "../include/ServClient.h"

void ServClient::start() {
    dataReady = new boost::thread(&ServClient::dataReady, this);
    this->startServer();
    this->startClient();
}

void ServClient::join() {
    dataReady->join();
    this->joinServer();
    this->joinClient();
}

void ServClient::setArraySize(int level) {
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

void ServClient::dataIsReady() {
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
