#pragma once



#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <map>
#include <enet/enet.h>
#include <vector>
#include <threadextend.h>
#include "KnapThread.hpp"

#define MAXPLAYER 15

#define BUFFERSIZE 500
#define PORT 8080 //4242
#define TOMAX 0




typedef enum type : char
{
	USERNAME_DECLARATION,
	PLANET_DECLARATION,
	RESSOURCE_DECLARATION,
	SPACESHIP_DECLARATION,
	RESSOURCE_CHOICE,
	SPACESHIP_POSITION
} com_type;

class commu {

public:

	com_type type;
	std::string msg;

	commu(const std::string & buffer);
	commu(const char * buffer);
	commu(const com_type & type, const std::string & msg);

	char * to_buf() const;
};

class Server {

public:

	Server(int port);
	// Server(Server & server);
	~Server();

	char recMess[500];
	std::map<unsigned int, unsigned short int> _clients;
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