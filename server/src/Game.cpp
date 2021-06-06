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
	this->players.push_back(P);
}
void Game::setPlayerPos(unsigned short int id, float pos_x, float pos_y ,float pos_z)
{

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

std::string Game::broadUsernames()
{
	std::string str = "host:"+this->players[0]->get_username();
	str += "\nplayers:\n";
	for(auto user : this->players)
		str += "\n"+user->get_username();

	return str;
}

std::string Game::broadPositions()
{
	std::string str;
	for (auto p : this->players)
		str += "5_"+p->com_pos_string() + "\n";

	return str;
}

/*
std::string Game::getChoiceError()
{ 

}*/
