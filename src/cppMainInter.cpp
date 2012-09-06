#include <cstdlib>
#include "../include/ServerInterCpp.h"

/**
    @namespace nameTest include all for test    
 */
using namespace std;

/*
 *
 */
int main(int argc, char** argv) {

    srand(time(NULL));

    if (argc < 4) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    ServerInterCpp interServer(argv);
    interServer.start();
    interServer.join();
    interServer.closeSocket();

    return 0;
}
