#include <iostream>
#include <enet/enet.h>

#include <threadextend.h>
#include <commu.h>

#include "KnapThread.hpp"
#include "enetServer.hpp"


// char recMess[BUFFERSIZE];
// char mess[BUFFERSIZE];

// volatile int start;

float pos_x = 0;
float pos_y = 0;
float pos_z = 0;


void sendBroadcast(const commu & c)
{   
	char * buffer = c.to_buf();
	ENetPacket * packet = enet_packet_create(buffer, strlen(buffer) + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_host_broadcast (server, 1, packet);
}

void handleIncomingMessage(const unsigned int & id, const std::string & data)
{

	if (pthread_mutex_lock(&lock_mutex) != 0)
		std::cerr << "Error: error in pthread_mutex_lock in producer()" << std::endl;

	if (pthread_cond_broadcast(&started_cond) != 0)
		std::cerr << "Error: error in pthread_cond_broadcast in producer()" << std::endl;

	if (pthread_mutex_unlock(&lock_mutex) != 0)
		std::cerr << "Error: error in pthread_mutek_unlock in producer()" << std::endl;
	
	commu cin(data);
	//printf("Entering handle, id = %u, communication type = %d, packet = %s\n", id, cin.type, (char *) data.c_str());
	switch (cin.type)
	{
		case USERNAME_DECLARATION:
			printf(" - Username is : %s\n", cin.msg.c_str());

			{
				//game->addPlayer(clients[id], cin.msg);

				std::string users_name;
				for (const auto & it : clients)
					users_name += it.second + '_';
				users_name[users_name.size() - 1] = '\0';
				commu cout(com_type::USERNAME_DECLARATION, users_name);
				sendBroadcast(cout);
			}
			break;

		case SPACESHIP_POSITION:
			{
				sscanf(cin.msg.c_str(),"user:(%f,%f,%f)", &pos_x,&pos_y,&pos_z);
				std::cout << "x : " << pos_x << " y : " << pos_y << " z : " << pos_z << std::endl;
			}
			break;
		default:
			printf("Cannot understand message |%s| received from %u.\n", cin.msg.c_str(), id);
			break;
	}
}

int main (int argc, const char * argv[]) 
{
	printf(" - enet_initialize()\n");

	if (enet_initialize() != 0)
	{
		std::cerr << "Error: An error occurred while initializing ENet." << std::endl;
		exit(EXIT_FAILURE);
	}


	//atexit(enet_deinitialize);

	address.host = 0 ;
	//if(address.host)
	std::cout << address.host << std::endl;
	address.port = PORT;
	if(address.port)
		std::cout << address.port << std::endl;

	printf(" - enet_host_create()\n");
	server = enet_host_create(&address, 32, 2, 0, 0);


	if (server == NULL)
	{
		std::cerr << "Error: An error occurred while trying to create an ENet server host." << std::endl;
		exit(EXIT_FAILURE);
	}

	printf("Starting main loop.\n");
	while (true) {	
		while (enet_host_service(server, &event, TOMAX) > 0) {
			switch (event.type)
			{
				case ENET_EVENT_TYPE_CONNECT:
					printf ("A new client connected from %u.%u.%u.%u : %u\n", 
						(char) event.peer->address.host & (0xFF),
						(char) (event.peer->address.host & (0xFF << 8)) >> 8,
						(char) (event.peer->address.host & (0xFF << 16)) >> 16,
						(char) (event.peer->address.host & (0xFF << 24)) >> 24,
						(unsigned int) event.peer->address.port
					);

					{
						if (clients.find(event.peer->connectID) != clients.end())
							printf("Client %u just reconnected.\n", (unsigned int) event.peer->connectID);
						else if (clients.size() <= MAXPLAYER)
							clients[event.peer->connectID] = clients.size() + 1;
						else {
							std::cerr << "Error: too many client already connected." << std::endl;
							enet_peer_disconnect(event.peer, 0);
						}
					}

					break;

				case ENET_EVENT_TYPE_RECEIVE:
					/*std::cout 
						<< "Length : "	<< (int) event.packet->dataLength << std::endl
						<< "Content : "<<  (char*)(event.packet->data) << std::endl
						<< "Peer : "	<< event.peer->connectID << std::endl
						<< "Channel : "<<(int) event.channelID <<
					std::endl;*/

					peer=event.peer;
					
					strcpy(recMess,(char*)(event.packet->data)+8);

					//std::cout<< "New message received : " << recMess << std::endl;
					{
						std::thread th(handleIncomingMessage, (unsigned int) event.peer->connectID, recMess);
						th.detach();
					}

					enet_packet_destroy(event.packet);
					break;

				case ENET_EVENT_TYPE_DISCONNECT:
					printf ("%d disconnected.\n", (unsigned int) event.peer->connectID);
					
					{
						event.peer->data = NULL;
					}

					break;

				default:
					break;
			}
		}
	}
}