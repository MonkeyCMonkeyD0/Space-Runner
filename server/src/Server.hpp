#pragma once

#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <map>
#include <enet/enet.h>
#include <vector>

#include <threadextend.h>

#include "PlanetCreator.hpp"
#include "Game.hpp"

#define MAXPLAYER 15
#define TOMAX 0


typedef enum type : char
{
	USERNAME_DECLARATION,
	PLANET_DECLARATION,
	RESSOURCE_DECLARATION,
	SPACESHIP_DECLARATION,
	RESSOURCE_CHOICE,
	SPACESHIP_POSITION,
	ERROR_CHOICE
} com_type;


class commu {

public:

	commu(const std::string & buffer);
	commu(const char * buffer);
	commu(const com_type & type, const std::string & msg);

	char * to_buf() const;
	size_t size() const;
	std::string mess_str() const; /* renvoi le même messaĝe en string ou char* */
	const char* mess_chr();             /* selon les besoins                   */
	com_type get_type() const;

private:

	com_type type;
	std::string msg;
};


class Server {

public:

	Server(int port, Game * g);
	~Server();

	Game * game;
	char recMess[500];
	std::map<unsigned int, unsigned short int> _clients;

	ENetAddress get_address();
	ENetHost* get_host();
	ENetPeer* get_peer();
	ENetEvent get_event();

	void set_address(ENetAddress address);
	void set_host(ENetHost * server);
	void set_peer(ENetPeer * peer);
	void set_event(ENetEvent event);

	void sendGameData();
	void sendPlanetes();
	void sendItems();
	void sendPositions();

	void sendBroadcast(const commu & c);
	void handleIncomingMessage(const unsigned int & id, const std::string & data);
	
	void initialize();
	void create_host();
	void run();

private:

	bool is_started, pos_upadate;
	pthread_mutex_t lock_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t started_cond = PTHREAD_COND_INITIALIZER;
	ENetAddress _address;
	ENetHost * _server;
	ENetPeer * _peer;
	ENetEvent _event;

};
