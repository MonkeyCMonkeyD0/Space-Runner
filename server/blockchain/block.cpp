#include <iostream>
#include "sha256.h"

#define PREFIXE_LEN 5


int main(int argc, char *argv[])
{
	unsigned long nonce = 0;
	std::string input;
	std::string output;

	do 
	{
		input = "1" + std::to_string(nonce) + "MAIN4";
		output = sha256(input1);
		++nonce;
		if (nonce % 1000000 == 0)
			std::cout << nonce << std::endl;
	} while (output.substr(0, PREFIXE_LEN) == std::string(PREFIXE_LEN, '0'));
	// } while ((output1[0] != '0') || (output1[1] != '0') || (output1[2]!='0') || (output1[3]!='0'));

	std::cout << "sha256('"<< input1 << "'):" << output1 << std::endl;

	return 0;
}
