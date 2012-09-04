#include <cstdlib>
#include "../include/ClientCpp.h"

/**
    @namespace nameTest include all for test    
 */
using namespace std;

/*
 *
 */
int main(int argc, char** argv) {

    srand(time(NULL));

    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    ClientCpp myClient(argv[1], argv[2]);
    myClient.startClient();
    myClient.joinClient();
    myClient.closeSocket();

    return 0;
}
