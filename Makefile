
SRCDIR = src/

CXX = g++
CXXFLAGS = -o 
IFLAGS = -I include -I /usr/include/boost
LDFLAGS = -L /usr/lib -lboost_thread


all: mainServer mainClient

mainServer:	$(SRCDIR)mainServer.cpp $(SRCDIR)Server.cpp
	$(CXX) $(CXXFLAGS) bin/mainServer $(SRCDIR)mainServer.cpp $(SRCDIR)Server.cpp $(IFLAGS) $(LDFLAGS) 

mainClient:	$(SRCDIR)mainClient.cpp $(SRCDIR)Client.cpp
	$(CXX) $(CXXFLAGS) bin/mainClient $(SRCDIR)mainClient.cpp $(SRCDIR)Client.cpp $(IFLAGS) $(LDFLAGS)
