#include <cstdlib>
#include "../include/ServerCpp.h"

/**
        @namespace nameTest include all for test	
 */
using namespace std;

/*
 *
 */
int main(int argc, char** argv) {

    if (argc < 2) {
        puts("USAGE ou no caso fail!");
        exit(EXIT_FAILURE);
    }

    ServerCpp myServer(argv[1]);
    myServer.startServer();
    myServer.joinServer();

    return 0;
}
