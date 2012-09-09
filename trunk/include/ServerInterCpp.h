/**
    @mainpage Doxygen My Test
    @brief How can I use doxygen documentation
    
    @index 
    The documentation became beautifull
 */

#ifndef SERVCLIENT_H
#define SERVCLIENT_H

#include "ServerCpp.h"
#include "ClientCpp.h"

/** 
        @class Client Client.h "include/Client.h"
        @brief A class for teste doxygen file

        A class to test draw inheritance        
 */
class ControlClass {
public:
    
};

class ServerInterCpp : public ServerCpp, ClientCpp {
public:

    /**
    -------------------------------------------------------------
        client puro,    ./x ipServer porta
        servclient,     ./x portaDele nivel ipServer portaServer
    -------------------------------------------------------------
     */
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