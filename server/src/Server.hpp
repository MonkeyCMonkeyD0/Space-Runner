#pragma once

#include <iostream>
#include <map>
#include <string>
#include <enet/enet.h>
#include <vector>
#include <threadextend.h>
#include <commu.h>

#include "KnapThread.hpp"

#define MAXPLAYER 15


class Server {

public:

	Server(int port = 8080);
	// Server(Server & server);
	~Server();

	char recMess[500];
	std::map<unsigned int, unsigned short int> clients;
	std::vector<float *> planete_positions;
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
	void initialize();
	void create_host();
	void run();

private:

	ENetAddress _address;
	ENetHost * _server;
	ENetPeer * _peer;
	ENetEvent _event;
	char * buffer;

};