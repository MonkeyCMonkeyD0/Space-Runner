#pragma once


#include <vector>


std::vector<unsigned int> 	weights = {70,73,77,80,82,87,90,94,98,106,110,113,115,118,120},
							profits = {135,139,149,150,156,163,173,184,192,201,210,214,221,229,240};
unsigned int capacity = 750;
unsigned int popsize = 100;
double survival_rate = 0.3;
unsigned int maxit = 1000;



class Game {

public:

	char mess[400];

	Game();

	void initGame();

private : 

};

