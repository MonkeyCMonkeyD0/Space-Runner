#pragma once

#include <iostream>
#include <map>
#include <string>
#include <pthread.h>
#include <enet/enet.h>
#include <threadextend.h>
#include <commu.h>

#include "KnapThread.hpp"

#define MAXPLAYER 15



class Server
{
private:
	ENetAddress _address;
	ENetHost * _server;
	ENetPeer * _peer;
	ENetEvent _event;
	char * buffer;
public:
	char recMess[500];
	std::map<unsigned int, unsigned short int> clients;
	pthread_mutex_t lock_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t started_cond = PTHREAD_COND_INITIALIZER;

	ENetAddress get_address();
	ENetHost* get_host();
	ENetPeer* get_peer();
	ENetEvent get_event();

	void set_address(ENetAddress address);
	void set_host(ENetHost * server);
	void set_peer(ENetPeer * peer);
	void set_event(ENetEvent event);


	void sendBroadcast(const commu & c);
	void handleIncomingMessage(const unsigned int & id, const std::string & data);
	
	void initialize()
	{
		printf(" - enet_initialize()\n");
		if (enet_initialize() != 0)
		{
			std::cerr << "Error: An error occurred while initializing ENet." << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	void create_host()
	{ 
		this->_server = enet_host_create(& this->_address, 32, 2, 0, 0);
		if (this->_server == NULL)
		{
			std::cerr << "Error: An error occurred while trying to create an ENet server host." << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	void run();

	Server(int port);
	//Server(Server & server);
	~Server();
	
};

/*
int count = 0;
int cpt = 0;
int idx;

char recMess[500];
char mess[500];

int fsm;
int num;
*/

int main (int argc, const char * argv[]) 
{
	Server Server(8080);
	Server.run();
}