#include "Server.hpp"
#include "Blockchain.hpp"
#include "BlockThread.hpp"
#include "Game.hpp"
#include "IA.hpp"
#include "Knapsack.hpp"
#include "KnapThread.hpp"
#include "PlanetCreator.hpp"
#include "Player.hpp"
#include "SHA256.hpp"

#include <commu.h>

int main (int argc, const char * argv[]) 
{
	Server Server(8080);
	Server.run();
}