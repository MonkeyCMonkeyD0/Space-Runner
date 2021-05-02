#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include <iostream>
#include <string>


#define PREFIXE_LEN 5


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

	void add_Block(const std::string &, const bool & debug = false);
	std::ostream & print(std::ostream & out = std::cout) const;
	const Block * get_first() const { return this->first; }
	const Block * get_last() const { return this->last; }

protected:

	static std::string prefixe;
	Block * first;
	Block * last;

	virtual void mine_last(const bool & debug = false);

private:

	static std::ostream & print_Block(const Block *, std::ostream & out = std::cout);

};

#endif
