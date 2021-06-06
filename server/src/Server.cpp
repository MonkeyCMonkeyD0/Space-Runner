#include "Server.hpp"
#include "PlanetCreator.hpp"



commu::commu(const std::string & buffer) : 
	type(com_type(buffer[9] - '0')), msg(buffer.substr(10)) {}

commu::commu(const char * buffer) : 
	type(com_type(buffer[9] - '0')), msg(std::string(buffer + 10)) {}

commu::commu(const com_type & type, const std::string & msg) : 
	type(type), msg(msg) {}


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

size_t commu::size() const
{
	return this->msg.size() + 1;
}

std::string commu::mess_str() const
{
	return this->msg;
}


const char* commu::mess_chr()
{
	const char * chr = this->msg.c_str();
	return chr;
}


com_type commu::get_type() const
{
	return this->type;
}

Server::Server(int port, Game * g) : game(g), is_started(false), pos_upadate(false)
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

void Server::sendGameData()
{
	if (!this->is_started)
	{
		std::cout << "first send" << std::endl;
		this->sendPlanetes();
		this->sendItems();
		this->is_started = true;
	}
/*	if(pos_upadate)
		this->sendPositions();
*/	//this->ship_declaration();
}

void Server::sendBroadcast(const commu & c)
{
	ENetPacket * packet = enet_packet_create(c.to_buf(), c.size(), ENET_PACKET_FLAG_RELIABLE);
	enet_host_broadcast(this->_server, 1, packet);
	std::cout << c.mess_str() << std::endl;
}


void Server::sendPlanetes()
{
	for (auto str : this->game->planets->broadcast_strings())
	{
		//std::cout << PLANET_DECLARATION << str << std::endl;
		this->sendBroadcast(commu(PLANET_DECLARATION, str));
	}
}

void Server::sendItems()
{
	for (auto item : this->game->broadItems())
	{
		std::cout << RESSOURCE_DECLARATION <<item << std::endl;
		this->sendBroadcast(commu(RESSOURCE_DECLARATION,item));
	}
}

void Server:: sendPositions()
{
	this->sendBroadcast(commu(SPACESHIP_POSITION,this->game->broadPositions()));
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
	// printf("Entering handle, id = %u, communication type = %d, packet = %s\n", id, cin.type, (char *) data.c_str());
	switch (cin.get_type())
	{
		case USERNAME_DECLARATION:
			std::cout << " - Username is : " << cin.mess_str() << std::endl;
			{
				this->sendGameData();
				this->game->addPlayer(id, cin.mess_str());
				commu cout(com_type::USERNAME_DECLARATION, this->game->broadUsernames());
				this->sendBroadcast(cout);

				//A ajouter dans game pour la fonction broadUsernames()
					/* std::string users_name;
					for (const auto & it : this->_clients)
					users_name += it.second + '_';
					users_name[users_name.size() - 1] = '\0';
					*/
			}
			break;

		case SPACESHIP_POSITION:
			{
				this->pos_upadate = true;
				float pos_x, pos_y, pos_z;
				std::cout << cin.mess_chr() << std::endl;
				sscanf(cin.mess_chr(), "(%f,%f,%f)", &pos_x ,&pos_y, &pos_z);
				this->game->setPlayerPos(id, pos_x ,pos_y, pos_z);
				commu cout(com_type::SPACESHIP_POSITION, this->game->broadPositions());
				this->sendBroadcast(cout);
				this->pos_upadate = false;
			}
			break;

		case RESSOURCE_CHOICE:
			{
				/*this->game->updatePlayerItems(id, cin.mess())
				if (this->game->asError()) {
					commu cout(com_type::ERROR_CHOICE, this->game->getChoiceError());
					this->sendBroadcast(cout);
				}
				else if (this->game->asShipUpdate()) {
					commu cout(com_type::SPACESHIP_DECLARATION, this->game->broadSpaceships());
					this->sendBroadcast(cout);
				}
				if (this->game->asEmptyPlanet()) {
					commu cout(com_type::PLANET_DECLARATION, this->game->getRemovedPlanet());
					this->sendBroadcast(cout);
				}*/
			}
			break;

		default:
			printf("Cannot understand message |%s| received from %u.\n", cin.mess_chr(), id);
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

void Server::run()
{
	//if(!is_started)
	//	this->sendGameData();
	while (true) {
		while (enet_host_service(this->_server, &this->_event, TOMAX) > 0) {
			switch (this->get_event().type)
			{
				case ENET_EVENT_TYPE_CONNECT:
					printf ("A new client connected from %u.%u.%u.%u : %u\n", 
						(char) this->get_event().peer->address.host & (0xFF),
						(char) (this->get_event().peer->address.host & (0xFF << 8)) >> 8,
						(char) (this->get_event().peer->address.host & (0xFF << 16)) >> 16,
						(char) (this->get_event().peer->address.host & (0xFF << 24)) >> 24,
						(unsigned int) this->get_event().peer->address.port
					);

					{
						if (this->_clients.find(this->_event.peer->connectID) != this->_clients.end())
							printf("Client %u just reconnected.\n", (unsigned int) this->_event.peer->connectID);
						else if (this->_clients.size() <= MAXPLAYER)
							this->_clients[this->_event.peer->connectID] = this->_clients.size() + 1;
						else {
							std::cerr << "Error: too many client already connected." << std::endl;
							enet_peer_disconnect(this->_event.peer, 0);
						}
					}

					break;

				case ENET_EVENT_TYPE_RECEIVE:
					/*std::cout 
						<< "Length : "	<< (int) this->_event.packet->dataLength << std::endl
						<< "Content : "<< (char*) (this->_event.packet->data) << std::endl
						<< "Peer : "	<< this->_event.peer->connectID << std::endl
						<< "Channel : "<<(int) this->_event.channelID <<
					std::endl; */

					this->set_peer(this->_event.peer);
					strcpy(this->recMess, (char*) (this->_event.packet->data) + 8);
					// std::cout<< "New message received : " << this->recMess << std::endl;
					{
						std::thread th(&Server::handleIncomingMessage, this, (unsigned int) this->_event.peer->connectID, this->recMess);
						th.detach();
					}
					enet_packet_destroy(this->_event.packet);
					break;

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
