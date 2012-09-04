#include "../include/Client.h"

void Client::randomArray(int *array) {
    int i;

    for (i = 0; i < cArraySize_; i++)
        array[i] = rand() % 999;
}

void Client::printArray(int *array, int numElem) {
    int i;

    for (i = 0; i < numElem; i++)
        printf("%d: %3d\n", i, array[i]);
}

int compairC(const void *x1, const void *x2) {

    int elem1 = *(const int*) x1;
    int elem2 = *(const int*) x2;

    return (elem1 < elem2) ? -1 : 1;
}

void Client::startClient() {
    threadConnection = new boost::thread(&Client::connectionToServer, this);
    threadWork = new boost::thread(&Client::work, this);
}

void Client::joinClient() {
    threadConnection->join();
    threadListenServer->join();
}

void Client::closeSocket() {
    close(my_socket_);
}

void Client::connectionToServer() {
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
            printf("It'll try again after 2 seconds\n");
        } else {
            tryConnection_ = 0;
            tryWork_ = 1;
            listenerServer.fd = my_socket_;
            listenerServer.events = POLLRDNORM;
            threadListenServer = new boost::thread(&Client::listenerData, this, listenerServer);
        }
        sleep(2);
    }
}

void Client::work() {
    int array[cArraySize_];

    while (doWork_) {
        if (tryWork_) {
            randomArray(array);
            qsort(array, cArraySize_, sizeof (int), compairC);
            send(my_socket_, array, sizeof (array), 0);

            doWork_ = 0;
        }
        usleep(1000);
    }
}

void Client::listenerData(struct pollfd pollClient) {
    int client;

    while (cltListenerReady_) {

        cltMutex.lock();
        client = poll(&pollClient, 1, 1000);

        if (client > 0) {

            recv(pollClient.fd, arrayReply, sizeof (int) * SIZE_ARRAY_RET, MSG_WAITALL);
            printArray(arrayReply, SIZE_ARRAY_RET);
            cltListenerReady_ = 0;
        }

        cltMutex.unlock();
        usleep(1000);
    }
}
