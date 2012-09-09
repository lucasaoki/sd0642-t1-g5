#include "../include/ClientCpp.h"

void ClientCpp::randomArray(int *array) {
    int i;

    for (i = 0; i < cArraySize_; i++)
        array[i] = rand() % 999;
}

void ClientCpp::printArray(int *array, int numElem) {
    int i;

    for (i = 0; i < numElem; i++)
        printf("%d: %3d\n", i, array[i]);
}

void ClientCpp::printTime() {
    double sec1, msec1, usec1;
    double sec2, msec2, usec2;

    sec1 = finalTime.tv_sec - iniTime.tv_sec;
    sec2 = finalConnTime.tv_sec - iniConnTime.tv_sec;
    usec1 = finalTime.tv_usec - iniTime.tv_usec;
    usec2 = finalConnTime.tv_usec - iniConnTime.tv_usec;
    msec1 = sec1 * 1000 + usec1 / 1000;
    msec2 = sec2 * 1000 + usec2 / 1000;

    std::cout << "Total time for ordering:" << msec1 << "milliseconds" << std::endl;
    std::cout << "Total connection time:" << msec1 << "milliseconds" << std::endl;

}

int compairC(const void *x1, const void *x2) {

    int elem1 = *(const int*) x1;
    int elem2 = *(const int*) x2;

    return (elem1 < elem2) ? -1 : 1;
}

void ClientCpp::startClient() {
    threadConnection = new boost::thread(&ClientCpp::connectionToServer, this);
    threadWork = new boost::thread(&ClientCpp::work, this);
}

void ClientCpp::joinClient() {
    threadConnection->join();
    threadListenServer->join();
}

void ClientCpp::closeSocket() {
    gettimeofday(&finalTime, NULL);
    printTime();
    close(my_socket_);
}

void ClientCpp::connectionToServer() {
    while (tryConnection_) {

        my_socket_ = socket(AF_INET, SOCK_STREAM, 0);
        if (my_socket_ < 0)
            perror("socket");

        server = gethostbyname(serverName_);
        if (my_socket_ > 0 && server == NULL)
            perror("server");

        if (my_socket_ > 0) {
            bzero(&serv_addr, sizeof (serv_addr));
            serv_addr.sin_family = server->h_addrtype;
            serv_addr.sin_port = htons(port_);
            serv_addr.sin_addr = *((struct in_addr *) server->h_addr);
            bzero(&(serv_addr.sin_zero), 8);
        }

        if (my_socket_ > 0 && (connect(my_socket_, (struct sockaddr *) &serv_addr, sizeof (struct sockaddr))) < 0) {
            close(my_socket_);
            perror("connect");
            printf("Retrying after 2 seconds\n");
        } else {

            tryConnection_ = 0;
            tryWork_ = 1;
            listenerServer.fd = my_socket_;
            listenerServer.events = POLLRDNORM;
            threadListenServer = new boost::thread(&ClientCpp::listenerData, this, listenerServer);
        }
        sleep(2);
    }
}

void ClientCpp::work() {
    clientArray_ = (int *) malloc (sizeof (int) * cArraySize_);
    randomArray(clientArray_);

    while (doWork_) {
        if (tryWork_ && isClientReady_) {
            gettimeofday(&iniTime, NULL);
            qsort(clientArray_, cArraySize_, sizeof (int), compairC);
            gettimeofday(&iniConnTime, NULL);
            send(my_socket_, clientArray_, sizeof (int)*cArraySize_, 0);

            doWork_ = 0;
        }
        usleep(1000);
    }
}

void ClientCpp::listenerData(struct pollfd pollClient) {
    int client;

    while (cltListenerReady_) {

        cltMutex.lock();
        client = poll(&pollClient, 1, 1000);

        if (client > 0) {

            int x = recv(pollClient.fd, arrayReply_, sizeof (int) * SIZE_ARRAY_RET, MSG_WAITALL);
            gettimeofday(&finalConnTime, NULL);
            printArray(arrayReply_, SIZE_ARRAY_RET);
            cltListenerReady_ = 0;
        }

        cltMutex.unlock();
        usleep(1000);
    }
}
