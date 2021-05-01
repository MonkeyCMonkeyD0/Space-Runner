#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include <iostream>

#include "SHA256.hpp"

#define PREFIXE_LEN 4


typedef struct Block
{
	unsigned long int nonce;
	std::string message, hash;
	Block * prev, * next;
} Block;


class Blockchain {

public:
	Blockchain();
	~Blockchain();

	void add_Block(const std::string &);
	std::ostream & print(std::ostream & out = std::cout);

protected:
	void mine_last();

private:
	static std::string prefixe;
	Block * first;
	Block * last;

	static std::ostream & print_Block(const Block *, std::ostream & out = std::cout);

};

#endif
