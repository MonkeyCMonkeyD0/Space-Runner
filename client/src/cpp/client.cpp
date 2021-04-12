#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string>

#include <enetcom.h>
#include <threadextend.h>

// #define HOST "127.0.0.1"


ENetHost * client;
ENetAddress address;
ENetEvent event;
ENetPeer * peer;
ENetPacket * packet;
bool connected = false;

static void fn_loop()
{
	while (connected)
		while (enet_host_service(client, &event, TOMAX) > 0)
			switch (event.type) 
			{
				case ENET_EVENT_TYPE_RECEIVE:
					printf("recMess = |%s|\n", (char *) event.packet->data);
					
					{
						peer = event.peer;
						commu cin((char *) event.packet->data);
					}
					
					enet_packet_destroy (event.packet);
					break;

				case ENET_EVENT_TYPE_DISCONNECT:
					printf("You have been disconnected.\n");
					
					{
						connected = false;
					}
					
					break;

				default:
					break;
			}
}

void envoyerCommande(const commu & c)
{
	char * buffer = c.to_buf();
	packet = enet_packet_create(
		buffer, 
		strlen(buffer) + 1, 
		ENET_PACKET_FLAG_RELIABLE
	);
	enet_peer_send(peer, 0, packet);
}

int  main(int argc, char const *argv[]) 
{
	std::string buffer, username;

	if (argc >= 3) {
		username = argv[2];
		for (int i = 3; i < argc; ++i) {
			username += ' ';
			username += argv[i];
		}
	} else {
		std::cerr << "Usage: ./client [host IP address] [username]" << std::endl;
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

	enet_address_set_host(&address, argv[1]);
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
		printf("Connected to %s as %s.\n", argv[1], username.c_str());

		commu c(com_type::USERNAME_DECLARATION, username);
		envoyerCommande(c);
	} 
	else 
	{
		enet_peer_reset(peer);
		std::cerr << "Could not connect to " << argv[1] << std::endl;
		exit(EXIT_FAILURE);
	}

	std::thread com_thread(fn_loop);

	// envoyerCommandes();

	while (connected)
	{
		printf("Input: ");
		// std::cin >> buffer;
		std::cin.clear();
		getline(std::cin,buffer,'\n');

		if (buffer.empty())
			continue;

		if (buffer.find('q') != std::string::npos) 
		{
			enet_peer_disconnect(peer, 0);
			sleep(1);
		}
	}
	com_thread.join();
	enet_deinitialize();
}
