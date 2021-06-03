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

void print_item(const item *, std::ostream & out = std::cout);
std::string com_item_string(const item *);


typedef struct point
{
	float x, y, z;
} point;

bool equal(const point &, const point &);
point sum(const point &, const point &);
point normalize(const point &);
float dist(const point &, const point &);


class Player {

public:

	Player(const unsigned int &, const std::string &, const bool & host = false);

	std::string get_username() const;
	unsigned int get_capacity() const;
	std::vector<item *> get_inventory() const;
	point get_pos() const;
	void set_pos(const float &, const float &, const float &);
	void set_planet(const unsigned char &);
	void set_spaceship(const unsigned char &, const unsigned char &);
	void set_capacity(const unsigned int &);

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
	point pos;
	unsigned char planet;
	unsigned char spaceship;
	unsigned int capacity;
	std::vector<item *> inventory;

};
