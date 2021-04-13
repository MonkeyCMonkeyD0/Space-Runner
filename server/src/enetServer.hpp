#ifndef ENETSERVER_HPP
#define ENETSERVER_HPP

#include <map>
#include <string>
#include <pthread.h>
#include <enet/enet.h>

#define MAXPLAYER 15


ENetAddress address;
ENetHost * server;
ENetPeer * peer;
ENetEvent event;

std::map<unsigned int, std::string> clients;

pthread_mutex_t lock_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t started_cond = PTHREAD_COND_INITIALIZER;

#endif