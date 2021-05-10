#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstring>


typedef struct item
{
	std::string name;
	unsigned short int price, weight;
} item;

void print_item(const item * it, std::ostream & out = std::cout);
std::string com_item_string(const item * it);


class Player {

public:

	Player(const unsigned int &, const std::string &, const bool & host = false);

	std::string get_username() const;
	void set_pos(const float &, const float &, const float &);
	void set_planet(const unsigned char &);
	unsigned short int get_capacity() const;
	void set_spaceship(const unsigned char &, const unsigned char &);
	void set_capacity(const unsigned short int &);

	std::ostream & print(std::ostream & out = std::cout) const;
	std::string com_decl_string() const;
	std::string com_pos_string() const;
	std::string com_inv_string() const;

	bool add_item(item *);
	bool rm_item(item *);

private:

	std::string username;
	unsigned int enet_ID;
	bool host;
	float x, y, z;
	unsigned char planet;
	unsigned char spaceship;
	unsigned short int capacity;
	std::vector<item *> inventory;

};
