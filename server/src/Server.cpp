#include "Server.hpp"
#include "PlanetCreator.hpp"


Server::Server(int port)
{
	this->initialize();
	this->_address.port = port;
	this->_address.host = 0;
	this->create_host();
}

Server::~Server(){}


ENetAddress  Server::get_address()
{
	return this->_address;
}

ENetHost* Server::get_host()
{
	return this->_server;
}

ENetPeer* Server::get_peer()
{
	return this->_peer;
}

ENetEvent Server::get_event()
{
	return this->_event;
}

void Server::set_address(ENetAddress address)
{
	this->_address = address;
}

void Server::set_host(ENetHost * server)
{
	this->_server = server;
}

void Server::set_peer(ENetPeer * peer)
{
	this->_peer = peer;
}

void Server::set_event(ENetEvent event)
{
	this->_event = event;
}

void Server::sendBroadcast(const commu & c)
{
	this->buffer = c.to_buf();
	ENetPacket * packet = enet_packet_create(this->buffer, strlen(this->buffer) + 1, ENET_PACKET_FLAG_RELIABLE);
	enet_host_broadcast(this->_server, 1, packet);
	std::cout << "Message sent" << std::endl;
}

void Server::handleIncomingMessage(const unsigned int & id, const std::string & data)
{

	if (pthread_mutex_lock(&this->lock_mutex) != 0)
		std::cerr << "Error: error in pthread_mutex_lock in producer()" << std::endl;

	if (pthread_cond_broadcast(&this->started_cond) != 0)
		std::cerr << "Error: error in pthread_cond_broadcast in producer()" << std::endl;

	if (pthread_mutex_unlock(&this->lock_mutex) != 0)
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
				//this->_clients[0].second = cin.msg.c_str();
				for (const auto & it : this->_clients)
					users_name += it.second + '_';

				users_name[users_name.size() - 1] = '\0';


				commu cout(com_type::USERNAME_DECLARATION, "Connexion recue de "+std::string(cin.msg.c_str()));
				this->sendBroadcast(cout);
			}
			break;

		case PLANET_DECLARATION:
			{
				commu cout(com_type::USERNAME_DECLARATION, "Connexion recue de "+std::string(cin.msg.c_str()));
				this->sendBroadcast(cout);
			}
			break;
		case SPACESHIP_POSITION:
			{
				int id;
				float pos_x, pos_y, pos_z;
				sscanf(cin.msg.c_str(),"%d:(%f,%f,%f)",&id ,&pos_x,&pos_y,&pos_z);
				std::cout << id << " position : " << std::endl;
				std::cout << "\t x : "<< pos_x << std::endl;
				std::cout << "\t y : "<< pos_y << std::endl;
				std::cout << "\t z : "<< pos_z << std::endl;
			}
			break;
		default:
			printf("Cannot understand message |%s| received from %u.\n", cin.msg.c_str(), id);
			break;
	}
}

void Server::initialize()
{
	printf(" - enet_initialize()\n");
	if (enet_initialize() != 0)
	{
		std::cerr << "Error: An error occurred while initializing ENet." << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Server::create_host()
{ 
	this->_server = enet_host_create(& this->_address, 32, 2, 0, 0);
	if (this->_server == NULL)
	{
		std::cerr << "Error: An error occurred while trying to create an ENet server host." << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Server::planete_declaration(PlanetCreator & P)
{
	std::vector<std::string> vect = P.broadcast_strings();
	for (auto str : P.broadcast_strings())
	{
		commu send_planets(PLANET_DECLARATION, str);
		this->sendBroadcast(send_planets);
	}
}

void Server::run()
{
	while (true) {	
		while (enet_host_service(this->_server, &this->_event, TOMAX) > 0) {
			switch (this->get_event().type)
			{
				case ENET_EVENT_TYPE_CONNECT:
					printf ("A new client connected from %u.%u.%u.%u : %u\n", 
						(char) this->_event.peer->address.host & (0xFF),
						(char) (this->_event.peer->address.host & (0xFF << 8)) >> 8,
						(char) (this->_event.peer->address.host & (0xFF << 16)) >> 16,
						(char) (this->_event.peer->address.host & (0xFF << 24)) >> 24,
						(unsigned int) this->_event.peer->address.port
					);
					{
						if (this->_clients.find(this->_event.peer->connectID) != this->_clients.end())
							printf("Client %u just reconnected.\n", (unsigned int) this->_event.peer->connectID);
						else if (this->_clients.size() <= MAXPLAYER)
						{
							this->_clients[this->_event.peer->connectID] = this->_clients.size() + 1;
						}
						else {
							std::cerr << "Error: too many client already connected." << std::endl;
							enet_peer_disconnect(this->_event.peer, 0);
						}
					}

					break;

				case ENET_EVENT_TYPE_RECEIVE:
				{
					/*std::cout 
						<< "Length : "	<< (int) event.packet->dataLength << std::endl
						<< "Content : "<<  (char*)(event.packet->data) << std::endl
						<< "Peer : "	<< event.peer->connectID << std::endl
						<< "Channel : "<<(int) event.channelID <<
					std::endl;*/

					this->set_peer(this->_event.peer);
					
					strcpy(this->recMess,(char*)(this->_event.packet->data)+8);

					//std::cout<< "New message received : " << recMess << std::endl;
						{
							std::thread th(&Server::handleIncomingMessage,this, (unsigned int) this->_event.peer->connectID, this->recMess);
							th.detach();
						}
					PlanetCreator P;
					this->planete_declaration(P);

					enet_packet_destroy(this->_event.packet);
				}break;

				case ENET_EVENT_TYPE_DISCONNECT:
					printf ("%d disconnected.\n", (unsigned int) this->_event.peer->connectID);
					
					{
						this->_event.peer->data = NULL;
					}

					break;

				default:
					break;
			}
		}
	}	
}


commu::commu(const std::string & buffer) : 
	type(com_type(buffer[9] - '0')), msg(buffer.substr(10)) {}

commu::commu(const char * buffer) : 
	type(com_type(buffer[9] - '0')), msg(std::string(buffer + 10)) {}

commu::commu(const com_type & type, const std::string & msg) : 
	type(type), msg(msg) {}


//commu cout(PLANET_DECLARATION,"")

char * commu::to_buf() const
{
	std::string buffer = "________";
	buffer += (char) 0x04;
	buffer += (char) this->type + '0';
	buffer += this->msg;
	char * buf = new char[buffer.size()];
	strcpy(buf, buffer.c_str());
	return buf;
}