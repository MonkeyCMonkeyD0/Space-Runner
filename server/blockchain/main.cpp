#include <iostream>
#include "sha256.h"

 
int main(int argc, char * argv[])
{
	//string input = "fpx";
	std::string input = "172608";
	std::string output = sha256(input);

	std::cout << "sha256('"<< input << "'):" << output << std::endl;
	return 0;
}
