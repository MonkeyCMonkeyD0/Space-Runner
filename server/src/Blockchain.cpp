#include "Blockchain.hpp"


std::string Blockchain::prefixe = std::string(PREFIXE_LEN, '0');


Blockchain::Blockchain()
{
	this->first = NULL;
	this->last = NULL;

	std::cout << "Blockchain created." << std::endl;
}

Blockchain::~Blockchain()
{
	Block * ptr = this->first;
	Block * next_ptr;
	while (ptr != NULL) {
		next_ptr = ptr->next;
		ptr->prev = NULL;
		ptr->next = NULL;
		ptr->message = std::string();
		ptr->hash = std::string();
		ptr->nonce = 0;
		delete ptr;
		ptr = next_ptr;
	}

	std::cout << "Blockchain destroyed." << std::endl;
}


std::ostream & Blockchain::print(std::ostream & out)
{
	for (Block * ptr = this->first; ptr != NULL; ptr = ptr->next)
		Blockchain::print_Block(ptr, out);
	return out;
}

std::ostream & Blockchain::print_Block(const Block * ptr, std::ostream & out)
{
	out << "Block :" << std::endl;
	out << "\t - message : " << ptr->message << std::endl;
	out << "\t - nonce : " << ptr->nonce << std::endl;
	out << "\t - hash : " << ptr->hash << std::endl;
	return out;
}

void Blockchain::add_Block(const std::string & msg)
{
	Block * b_ptr = new Block;
	b_ptr->nonce = 0;
	b_ptr->message = msg;
	b_ptr->hash = std::string();
	b_ptr->prev = this->last;
	b_ptr->next = (Block *) NULL;

	if (this->first == NULL)
		this->first = b_ptr;
	else
		this->last->next = b_ptr;

	this->last = b_ptr;
	this->mine_last();

	std::cout << "Created ";
	Blockchain::print_Block(this->last, std::cout);
}


void Blockchain::mine_last()
{
	std::string input;
	std::string data;

	if (this->first == this->last)
		data = this->last->message + std::string(64, '0');
	else
		data = this->last->message + this->last->prev->hash;

	do {
		this->last->nonce += 1;
		input = std::to_string(this->last->nonce) + data;
		this->last->hash = sha256(input);
	} while (this->last->hash.substr(0, PREFIXE_LEN) != Blockchain::prefixe);
}

