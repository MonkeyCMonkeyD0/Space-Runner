#pragma once

#include <map>
#include <string>
#include <pthread.h>
#include <enet/enet.h>

#define MAXPLAYER 15


ENetAddress address;
ENetHost * server;
ENetPeer * peer;
ENetEvent event;

std::map<unsigned int, unsigned short int> clients;

pthread_mutex_t lock_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t started_cond = PTHREAD_COND_INITIALIZER;


int count = 0;
int cpt = 0;
int idx;

char recMess[500];
char mess[500];

int fsm;
int num;