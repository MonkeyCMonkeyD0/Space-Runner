#include "Server.hpp"

int main (int argc, const char * argv[]) 
{
	Game *g = new Game();
	Server server(8080,g);

	server.run();
	return 0;
}