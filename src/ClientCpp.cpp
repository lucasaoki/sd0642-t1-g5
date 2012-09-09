#include "../include/ClientCpp.h"


/**
        @fn void ClientCpp::randomArray(int *array)
        @brief A method of Client's class that generates a ramdom array of size 'cArraySize_'
        @param *array an integer array pointer
    @return 
 */
void ClientCpp::randomArray(int *array) {
    int i;

    for (i = 0; i < cArraySize_; i++)
        array[i] = rand() % 999;
}

/**
        @fn void ClientCpp::printArray(int *array, int numElem)
        @brief A method of Client's class that shows the elements of an array
        @param *array an integer array pointer
        @param numElem an integer, size of the array
    @return 
 */
void ClientCpp::printArray(int *array, int numElem) {
    int i;

    for (i = 0; i < numElem; i++)
        printf("%d: %3d\n", i, array[i]);
}

/**
        @fn void ClientCpp::printTime()
        @brief A method of Client's class that shows the statistic times
    @return 
 */
void ClientCpp::printTime() {
    double sec1, msec1, usec1;
    double sec2, msec2, usec2;

    sec1 = finalTime.tv_sec - iniTime.tv_sec;
    sec2 = finalConnTime.tv_sec - iniConnTime.tv_sec;
    usec1 = finalTime.tv_usec - iniTime.tv_usec;
    usec2 = finalConnTime.tv_usec - iniConnTime.tv_usec;
    msec1 = sec1 * 1000 + usec1 / 1000;
    msec2 = sec2 * 1000 + usec2 / 1000;

    std::cout << "Total time for ordering: " << msec1 << " milliseconds" << std::endl;
    std::cout << "Total connection time: " << msec1 << " milliseconds" << std::endl;

}

/**
        @fn void compairC(const void *x1, const void *x2)
        @brief A method that compair two integers
        @param *x1 an integer pointer
        @param *x2 an integer pointer
    @return 
 */
int compairC(const void *x1, const void *x2) {

    int elem1 = *(const int*) x1;
    int elem2 = *(const int*) x2;

    return (elem1 < elem2) ? -1 : 1;
}

/**
        @fn void ClientCpp::startClient()
        @brief A method of Client's class that initiates the client's threads
    @return 
 */
void ClientCpp::startClient() {
    threadConnection = new boost::thread(&ClientCpp::connectionToServer, this);
    threadWork = new boost::thread(&ClientCpp::work, this);
}

/**
        @fn void ClientCpp::joinClient()
        @brief A method of Client's class that calls the join()'s method of the threads
        @param *array an integer array pointer
    @return 
 */
void ClientCpp::joinClient() {
    threadConnection->join();
    threadListenServer->join();
}

/**
        @fn void ClientCpp::closeSocket()
        @brief A method of Client's class that closes the client socket
        @param *array an integer array pointer
    @return 
 */
void ClientCpp::closeSocket() {
    gettimeofday(&finalTime, NULL);
    printTime();
    free(clientArray_);
    close(my_socket_);
}

/**
        @fn void ClientCpp::connectionToServer()
        @brief A method of Client's class that establishes the connection with the server
    @return 
 */
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

/**
        @fn void ClientCpp::work()
        @brief A method of Client's class that runs the main functions of the class and sends the information for the server
        @param *array an integer array pointer
    @return 
 */
void ClientCpp::work() {
    clientArray_ = (int *) malloc (sizeof (int) * cArraySize_);
    randomArray(clientArray_);

    while (doWork_) {
        cltMutex.lock();
        
        if (tryWork_ && isClientReady_) {
            gettimeofday(&iniTime, NULL);
            qsort(clientArray_, cArraySize_, sizeof (int), compairC);
            gettimeofday(&iniConnTime, NULL);
            send(my_socket_, clientArray_, sizeof (int)*cArraySize_, 0);

            doWork_ = 0;
        }
        cltMutex.unlock();
        usleep(1000);
    }
}

/**
        @fn void ClientCpp::listenerData(struct pollfd pollClient)
        @brief A method of Client's class that waits for the server's answer
        @param pollClient file descriptor structure
    @return 
 */
void ClientCpp::listenerData(struct pollfd pollClient) {
    int client;

    while (cltListenerReady_) {

        cltMutex.lock();
        client = poll(&pollClient, 1, 1000);

        if (client > 0) {

            recv(pollClient.fd, arrayReply_, sizeof (int) * SIZE_ARRAY_RET, MSG_WAITALL);
            gettimeofday(&finalConnTime, NULL);
            printArray(arrayReply_, SIZE_ARRAY_RET);
            cltListenerReady_ = 0;
        }

        cltMutex.unlock();
        usleep(1000);
    }
}
