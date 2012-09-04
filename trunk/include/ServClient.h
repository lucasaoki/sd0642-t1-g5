/**
    @mainpage Doxygen My Test
    @brief How can I use doxygen documentation
    
    @index 
    The documentation became beautifull
 */

#ifndef SERVCLIENT_H
#define SERVCLIENT_H

#include "Server.h"
#include "Client.h"

/** 
        @class Client Client.h "include/Client.h"
        @brief A class for teste doxygen file

        A class to test draw inheritance        
 */
class ServClient : public Server, Client {
public:

    /**
    -------------------------------------------------------------
        client puro,    ./x ipServer porta
        servclient,     ./x portaDele nivel ipServer portaServer
    -------------------------------------------------------------
     */
    ServClient(char* argv[]) : Server(argv[1]), Client(argv[3], argv[4]) {
        setArraySize(atoi(argv[2]));
        isFinalServer_ = 0;
        waitingData = 1;
    }
    void start();
    void join();

protected:
    int waitingData;
    void setArraySize(int level);
    boost::thread *dataReady;

private:
    void dataIsReady();
};

#endif /* SERVCLIENT_H */