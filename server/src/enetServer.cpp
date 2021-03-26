#include <stdio.h>
#include <string.h>
#include <enet/enet.h>
#include <iostream>
#include <sys/time.h>
#include <vector>
#include <random>
#include <algorithm>

#include "jeu.hpp"

#define TOMAX	0


ENetAddress address;
ENetHost *server;
ENetPeer *peer;
ENetEvent event;
int count = 0;
int cpt = 0;
int idx;

char recMess[200];
char mess[200];

int nbConnectes;
int estConnecte[4];

int fsm;

Jeu *jeu;

int num;

void sendBroadcast(char *mess)
{
	char buffer[500];

	//for (int i=0;i<12;i++)
	for (int i = 0; i < 8; ++i)
		buffer[i] = 0;
	//buffer[8]=1;
	buffer[8] = 4;

	int len = strlen(mess);
	int cpt = 0;
	for (cpt = 0; cpt < len; ++cpt)
		buffer[9 + cpt] = mess[cpt];
	buffer[9 + cpt] = 0;

	printf("len = %d %s\n", len, mess);

	ENetPacket * packet = enet_packet_create (buffer, 10 + len, ENET_PACKET_FLAG_RELIABLE);
	enet_host_broadcast (server, 1, packet);
}

void sendTousConnectes()
{
	char mess[10];

	sprintf(mess, "X");
	sendBroadcast(mess);
}

void sendEstDejaConnecte(int d)
{
	printf("%d est déjà connecte\n", d);
}

void sendCommandeIllegale()
{

}

void sendStop()
{
	char mess[20];

	sprintf(mess, "S");
	sendBroadcast(mess);
}

void handleIncomingMessage()
{
	printf("fsm=%d\n", fsm);
	switch (fsm)
	{
		case 0:
			if (recMess[0] == 'C')
			{
				int dir = recMess[1] - '0';
				if (estConnecte[dir] == 0)
				{
					nbConnectes++;
					estConnecte[dir] = 1;
					//sendEstConnecte(dir);
				}
				else
					sendEstDejaConnecte(dir);

				// Tout le monde est connecté, on envoie plein de choses
				// aux interfaces graphiques.
				if (nbConnectes == 1)
				{
					sendTousConnectes();

					fsm = 1;
				}
			}
			break;
		case 1: // On attend l'action d'un joueur 
			if (recMess[0] == 'T')
			{
				int dir = recMess[1] - '0';
				int num, x, y;
				sscanf(recMess + 2, "%d", &num);
				y= num / 11;
				x= num % 11;
				printf("T y = %d, x = %d\n", y, x);

				if (jeu->mp[y][x] == 1)
				{
					sendBomb(dir, y, x);
				}
				else
				{
					propagate(dir, y, x);
					jeu->printDiscovered();
					if (jeu->nbDiscovered + jeu->nbBombs == 121)
						sendStop();
				}
			}
			else if (recMess[0] == 'F')
			{
				int dir = recMess[1] - '0';
				int num, x, y;
				sscanf(recMess + 2, "%d", &num);
				y = num / 11;
				x = num % 11;
				printf("F y = %d, x = %d\n", y, x);
				if (jeu->flag[y][x][dir] == 0)
				{
					jeu->flag[y][x][dir] = 1;
					sendFlag(dir, 1, y, x);
				}
				else
				{
					jeu->flag[y][x][dir] = 0;
					sendFlag(dir, 0, y, x);
				}
			}
			break;
		default:
			break;
	}
	printf("en sortant fsm = %d\n",fsm);
}

int main (int argc, char ** argv) 
{
	printf("enet_initialize()\n");

	if (enet_initialize () != 0) {
		fprintf (stderr, "An error occurred while initializing ENet.\n");
		return EXIT_FAILURE;
	}

	address.host = ENET_HOST_ANY;

	address.port = 4242;
	printf("enet_host_create()\n");

	server = enet_host_create (& address, 32, 2, 0, 0);
	if (server == NULL) {
		fprintf (stderr, "An error occurred while trying to create an ENet server host.\n");
		exit (EXIT_FAILURE);
	}

	fsm = 0;

	jeu = new Jeu();
	jeu->initGame();

	// printf("before while() mainloop\n");

	while (true)
		while (enet_host_service (server, &event, TOMAX) > 0)
			switch (event.type) {
				case ENET_EVENT_TYPE_CONNECT:
					printf ("A new client connected from %x:%u.\n", event.peer -> address.host, event.peer -> address.port);
					break;

				case ENET_EVENT_TYPE_RECEIVE:
					printf ("A packet of length %u containing %s was received from %s on channel %u.\n", (int) event.packet->dataLength, (char*) event.packet->data, (char*) event.peer->data, (int)event.channelID);
					peer = event.peer;
					// strcpy(recMess, (char*) (event.packet->data) + 9);
					idx = 0;
					for (int i = 9; i < (int) event.packet->dataLength; ++i)
					{
						printf("%c", (char) event.packet->data[i]);
						recMess[idx++] = (char)event.packet->data[i];
					}
					recMess[idx++] = '\0';
					printf("recMess = |%s|\n", recMess);
					enet_packet_destroy(event.packet);
					handleIncomingMessage();
					break;

				case ENET_EVENT_TYPE_DISCONNECT:
						printf ("%s disconnected FPX.\n", (char*) event.peer->data);
						event.peer->data = NULL;
			}
	atexit (enet_deinitialize);
}
