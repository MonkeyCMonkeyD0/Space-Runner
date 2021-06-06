#pragma once
#include "PlanetCreator.hpp"
#include "Player.hpp"

#include <vector>



class Game {

public:

	std::vector<unsigned int> 	weights = {70,73,77,80,82,87,90,94,98,106,110,113,115,118,120},
								profits = {135,139,149,150,156,163,173,184,192,201,210,214,221,229,240};
	
	std::vector<item*> items;
	std::vector<Player*> players; 

	unsigned int capacity;
	unsigned int popsize;
	double survival_rate;
	unsigned int maxit;

	Game();
	~Game();

	void initGame();

	void addPlayer(unsigned short int, std::string);
	void setPlayerPos(unsigned short int, float ,float,float);
	void updatePlayerItems(unsigned short int, std::string);
	void getRemovedPlanet();
	void initItems();

	bool asError();
	bool asShipUpdate();
	bool asEmptyPlanet();

	std::vector<item*> itemCreator();
	std::string broadVal(std::vector<unsigned int>);

	std::string broadUsernames();
	std::string broadPositions();
	/*std::string getChoiceError();*/

	PlanetCreator *planets;

private : 

};
