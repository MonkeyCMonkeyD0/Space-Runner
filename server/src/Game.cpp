#include "Game.hpp"

Game::Game(): capacity(750),
			popsize(100),
			survival_rate(0.3),
			maxit(1000)
{
	this->initGame();
}

Game::~Game(){}

void Game::initGame()
{
	this->planets = new PlanetCreator;
	this->items = this->itemCreator();
}

std::vector<item*> Game::itemCreator()
{
	std::vector<item*> items;
	for(int i=0; i<15; i++)
	{
		item *it = new item;
		it->name = "";
		it->price = this->profits[i];
		it->weight = this->weights[i];
		items.push_back(it);
	}
	return items;
}


void Game::addPlayer(unsigned short int id, std::string name)
{
	bool host;
	if(this->players.size() == 0)
		host = true;
	else
		host = false;

	Player *P = new Player(id, name, host);
	this->players[id] = P;
}
void Game::setPlayerPos(unsigned short int id, float pos_x, float pos_y ,float pos_z)
{
	std::cout << "id game : "<< id << std::endl;
	this->players[id]->set_pos(pos_x, pos_y, pos_z);
}
void Game::updatePlayerItems(unsigned short int id, std::string items)
{ 

}
void Game::getRemovedPlanet()
{ 

}
bool Game::asError()
{ 
	return false;
}
bool Game::asShipUpdate()
{ 
	return true;
}
bool Game::asEmptyPlanet()
{ 
	return false;
}

std::vector<std::string> Game::broadItems()
{
	std::vector<std::string> vect_items;

	for(auto val : this->items)
		vect_items.push_back(com_item_string(val));

	return vect_items;
}

std::vector<std::string> Game::broadUsernames()
{
	std::vector<std::string> vect_users;

	for(auto user : this->players)
		vect_users.push_back(user.second->com_decl_string());

	return vect_users;
}

std::vector<std::string> Game::broadPositions()
{
	std::vector<std::string> vect_pos;

	for(auto user : this->players)
		vect_pos.push_back(user.second->com_pos_string());

	return vect_pos;
}

/*
std::string Game::getChoiceError()
{ 

}*/
