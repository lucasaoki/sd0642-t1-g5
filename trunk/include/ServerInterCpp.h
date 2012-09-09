#ifndef SERVCLIENT_H
#define SERVCLIENT_H

#include "ServerCpp.h"
#include "ClientCpp.h"

class ControlClass {
public:
    
};

class ServerInterCpp : public ServerCpp, ClientCpp {
public:

    ServerInterCpp(char* argv[]) : ServerCpp(argv[1]), ClientCpp(argv[3], argv[4]) {
        setArraySize(atoi(argv[2]));
        isFinalServer_ = 0;
        waitingData = 1;
        serverToClient = 0;
    }
    void start();
    void join();
    void closeSocket();

protected:
    int serverToClient;
    int waitingData;
    void serverToClientData();        
    void setArraySize(int level);
    boost::thread *dataReady;

private:
    void clientToServerData();
};

#endif /* SERVCLIENT_H */