#include <cstdlib>
#include "../include/Client.h"

/**
    @namespace nameTest include all for test    
*/
using namespace std;

/*
 *
 */
int main(int argc, char** argv)
{

    srand(time(NULL));

    if( argc < 2) {
        fprintf(stderr,"usage %s hostname port\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    Client myClient(argv);
    myClient.start();
    myClient.join();
    myClient.closeSocket();

    return 0;
}
