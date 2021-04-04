#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <enet/enet.h>

#define HOST "127.0.0.1"
#define PORT (4242)
#define BUFFERSIZE (1000)

#include <threadextend.h>


char buffer[BUFFERSIZE];
char sendBuffer[BUFFERSIZE];

char recMess[BUFFERSIZE];

ENetHost * client;
ENetAddress address;
ENetEvent event;
ENetPeer * peer;
ENetPacket * packet;
int idx = 0;

static void fn_loop()
{
	while (true) 
	{
		while (enet_host_service(client, &event, 0) > 0) 
		{
			switch (event.type) 
			{
				case ENET_EVENT_TYPE_RECEIVE:
					puts((char*) event.packet->data);
					peer = event.peer;
					idx = 0;
					for (int i = 9; i < (int) event.packet->dataLength; ++i)
						recMess[idx++] = (char) event.packet->data[i];
					recMess[idx++] = '\0';
					printf("recMess = |%s|\n", recMess);
					enet_packet_destroy (event.packet);
					break;

				case ENET_EVENT_TYPE_DISCONNECT:
					printf("You have been disconnected.\n");
					break;

				default:
					break;
			}
		}
	}
}

void envoyerCommande(const std::string & buf)
{
	sprintf(sendBuffer, "xxxxyyyy%c%s", 0x04, buf.c_str());
	packet = enet_packet_create(
		sendBuffer, 
		strlen(sendBuffer) + 1, 
		ENET_PACKET_FLAG_RELIABLE
	);
	enet_peer_send(peer, 0, packet);
}

void envoyerCommandes()
{
	envoyerCommande("Hellooo"); // Connexion
/*
	envoyerCommande("C1"); // Connexion
	envoyerCommande("C2"); // Connexion
	envoyerCommande("C3"); // Connexion

	envoyerCommande("c0107"); // 0 cube 107 
	envoyerCommande("c1106"); //
	envoyerCommande("c2095"); //
	envoyerCommande("c3094"); //

	envoyerCommande("c0096"); //
	envoyerCommande("c1099"); //
	envoyerCommande("c2083"); //
	envoyerCommande("c3093"); //

	envoyerCommande("d03051"); //
	envoyerCommande("d12051"); //
	envoyerCommande("d21051"); //
	envoyerCommande("d30051"); //
*/
}

int  main(int argc, char ** argv) 
{
	bool connected = false;
	std::string buffer;
	std::string username;
	int index;
	char ch;

	if (argc == 2)
		username = argv[1];
	else {
		std::cerr << "Usage: ./client4 [username]" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (enet_initialize() != 0) 
	{
		std::cerr << "Could not initialize enet." << std::endl;
		exit(EXIT_FAILURE);
	}

	client = enet_host_create(NULL, 1, 2, 0, 0);

	if (client == NULL) 
	{
		std::cerr << "Could not create client." << std::endl;
		exit(EXIT_FAILURE);
	}

	enet_address_set_host(&address, HOST);
	address.port = PORT;

	peer = enet_host_connect(client, &address, 2, 0);

	if (peer == NULL) 
	{
		std::cerr << "Could not connect to server" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (enet_host_service(client, &event, 1000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) 
	{
		connected = true;
		printf("Connected to %s as %s.\n", HOST, username.c_str());
		envoyerCommande("user_" + username);
	} 
	else 
	{
		enet_peer_reset(peer);
		std::cerr << "Could not connect to " << HOST << std::endl;
		exit(EXIT_FAILURE);
	}

	std::thread com_thread(fn_loop);

	envoyerCommandes();

	index = 0;
	while (connected)
	{
		/*
			printf("Input: ");
			//gets(buffer);

			if (strlen(buffer) == 0) 
		{ 
			continue; 
		}

			if (strncmp("q", buffer, BUFFERSIZE) == 0) 
		{
				enet_peer_disconnect(peer, 0);
				break;
			} 
		*/

		ch = getchar();
		if (ch != EOF)
		{
			if (ch != 10)
				buffer[index++]=ch;
			else
			{
				buffer[index++] = 0;
				index = 0;

				envoyerCommande(buffer);
			}
		}

	}
	enet_deinitialize();
}
