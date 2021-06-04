#include "Server.hpp"
//#include "PlanetCreator.hpp"

#include <commu.h>

int main (int argc, const char * argv[]) 
{
	//PlanetCreator planet;
	Server Server(8080);
	Server.run();
	return 0;
}