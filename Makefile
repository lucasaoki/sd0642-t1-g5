SRCDIR = src/
EXECDIR = bin/

CXX = g++
CXXFLAGS = -o 
IFLAGS = -I include -I /usr/include/boost
LDFLAGS = -L /usr/lib -lboost_thread

JC = javac
JFLAGS = -g -d
JAVASRCDIR = java_src/
JAVACLIENTDIR = $(JAVASRCDIR)client/

all: serverCpp clientCpp serverInterCpp client.class

serverCpp:	$(SRCDIR)cppMainServer.cpp $(SRCDIR)ServerCpp.cpp
	$(CXX) $(CXXFLAGS) $(EXECDIR)serverCpp $(SRCDIR)cppMainServer.cpp $(SRCDIR)ServerCpp.cpp $(IFLAGS) $(LDFLAGS) 

clientCpp:	$(SRCDIR)cppMainClient.cpp $(SRCDIR)ClientCpp.cpp
	$(CXX) $(CXXFLAGS) $(EXECDIR)clientCpp $(SRCDIR)cppMainClient.cpp $(SRCDIR)ClientCpp.cpp $(IFLAGS) $(LDFLAGS)
	
serverInterCpp:	$(SRCDIR)cppMainInter.cpp $(SRCDIR)ServerInterCpp.cpp $(SRCDIR)ServerCpp.cpp $(SRCDIR)ClientCpp.cpp
	$(CXX) $(CXXFLAGS) $(EXECDIR)serverInterCpp $(SRCDIR)cppMainInter.cpp $(SRCDIR)ServerInterCpp.cpp $(SRCDIR)ServerCpp.cpp $(SRCDIR)ClientCpp.cpp $(IFLAGS) $(LDFLAGS)
	
client.class: $(JAVACLIENTDIR)Client.java
	$(JC) $(JFLAGS) $(EXECDIR) $(JAVACLIENTDIR)Client.java	
