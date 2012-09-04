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

    if (argc < 5) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    ServerInterCpp hibridSC(argv);
    hibridSC.start();
    hibridSC.join();

    return 0;
}
