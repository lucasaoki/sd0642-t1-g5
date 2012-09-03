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

all: mainServer mainClient client.class

mainServer:	$(SRCDIR)mainServer.cpp $(SRCDIR)Server.cpp
	$(CXX) $(CXXFLAGS) $(EXECDIR)mainServer $(SRCDIR)mainServer.cpp $(SRCDIR)Server.cpp $(IFLAGS) $(LDFLAGS) 

mainClient:	$(SRCDIR)mainClient.cpp $(SRCDIR)Client.cpp
	$(CXX) $(CXXFLAGS) $(EXECDIR)mainClient $(SRCDIR)mainClient.cpp $(SRCDIR)Client.cpp $(IFLAGS) $(LDFLAGS)
	
client.class: $(JAVACLIENTDIR)Client.java
	$(JC) $(JFLAGS) $(EXECDIR) $(JAVACLIENTDIR)Client.java	
