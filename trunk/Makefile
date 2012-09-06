SRCDIR = src/
EXECDIR = bin/

PREFIX=include/common
INCLUDE_DIRS_HEADERS=$(PREFIX)/include
INCLUDE_DIRS_SRCS_HEADERS=$(PREFIX)/src

CIFLAGS = -I $(INCLUDE_DIRS_HEADERS)
CDEPFLAGS = $(CIFLAGS) $(INCLUDE_DIRS_SRCS_HEADERS)/array_header.c $(INCLUDE_DIRS_SRCS_HEADERS)/server_client.c
CPP_FLAGS= -o IFLAGS 
CPP = g++

CXX = g++
CXXFLAGS = -o 
IFLAGS = -I include -I /usr/include/boost
LDFLAGS = -L /usr/lib -lboost_thread

JC = javac
JFLAGS = -g -d
JAVASRCDIR = java_src/
JAVACLIENTDIR = $(JAVASRCDIR)client/

all: serverCpp clientCpp serverInterCpp client.class serverC clientC

serverC: $(SRCDIR)cServer.c
	$(CPP) -o $(EXECDIR)serverC $(SRCDIR)cServer.c $(CDEPFLAGS)     

clientC: $(SRCDIR)cClient.c
	$(CPP) -o $(EXECDIR)clientC $(SRCDIR)cClient.c $(CDEPFLAGS) -lrt 

serverCpp:	$(SRCDIR)cppMainServer.cpp $(SRCDIR)ServerCpp.cpp
	$(CXX) $(CXXFLAGS) $(EXECDIR)serverCpp $(SRCDIR)cppMainServer.cpp $(SRCDIR)ServerCpp.cpp $(IFLAGS) $(LDFLAGS) 

clientCpp:	$(SRCDIR)cppMainClient.cpp $(SRCDIR)ClientCpp.cpp
	$(CXX) $(CXXFLAGS) $(EXECDIR)clientCpp $(SRCDIR)cppMainClient.cpp $(SRCDIR)ClientCpp.cpp $(IFLAGS) $(LDFLAGS)
	
serverInterCpp:	$(SRCDIR)cppMainInter.cpp $(SRCDIR)ServerInterCpp.cpp $(SRCDIR)ServerCpp.cpp $(SRCDIR)ClientCpp.cpp
	$(CXX) $(CXXFLAGS) $(EXECDIR)serverInterCpp $(SRCDIR)cppMainInter.cpp $(SRCDIR)ServerInterCpp.cpp $(SRCDIR)ServerCpp.cpp $(SRCDIR)ClientCpp.cpp $(IFLAGS) $(LDFLAGS)
	
client.class: $(JAVACLIENTDIR)Client.java
	$(JC) $(JFLAGS) $(EXECDIR) $(JAVACLIENTDIR)Client.java	
	
clean:
	rm $(EXECDIR)*	
	
