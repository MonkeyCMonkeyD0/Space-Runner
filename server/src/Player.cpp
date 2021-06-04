#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

#include "Player.hpp"


void print_item(const item * it, std::ostream & out)
{
	out << "Item : " << it->name << " worth " << it->price << "$ & weight " << it->weight << "kg." << std::endl;
}

std::string com_item_string(const item * it)
{
	return it->name + "_P" +  std::to_string(it->price) + "_W" + std::to_string(it->weight);
}


bool equal(const point & p1, const point & p2)
{
	return p1.x == p2.x && p1.y == p2.y && p1.z == p2.z;
}

point sum(const point & p1, const point & p2)
{
	return point{p1.x + p2.x, p1.y + p2.y, p1.z + p2.z};
}

point normalize(const point & p)
{
	float norm = sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
	return point{p.x / norm, p.y / norm, p.z / norm};
}

float dist(const point & p1, const point & p2)
{
	return sqrt(
		(p1.x - p2.x) * (p1.x - p2.x) + \
		(p1.y - p2.y) * (p1.y - p2.y) + \
		(p1.z - p2.z) * (p1.z - p2.z));
}


Player::Player(const unsigned int & id, const std::string & name, const bool & host) : username(name), enet_ID(id), host(host)
{
	this->set_pos(0.0, 0.0, 0.0);
	this->planet = 0;
	this->spaceship = 0x11;
	this->capacity = 750;
	this->inventory = std::vector<item *>();
}


std::string Player::get_username() const
{
	return this->username;
}

unsigned int Player::get_capacity() const
{
	return this->capacity;
}

std::vector<item *> Player::get_inventory() const
{
	return this->inventory;
}

point Player::get_pos() const
{
	return this->pos;
}

void Player::set_pos(const float & x, const float & y, const float & z)
{
	this->pos.x = x;
	this->pos.y = y;
	this->pos.z = z;
}

void Player::set_planet(const unsigned char & p)
{
	this->planet = p;
}

void Player::set_spaceship(const unsigned char & ship_type, const unsigned char & ship)
{
	this->spaceship = ship + (ship_type << 4);
}

void Player::set_capacity(const unsigned int & c)
{
	this->capacity = c;
}


std::ostream & Player::print(std::ostream & out) const
{
	out << this->enet_ID << ": " << this->get_username();
	if (this->host)
		out << " is a host";
	out << std::endl << '(' << this->pos.x << ',' << this->pos.y << ',' << this->pos.z << ')';
	if(this->planet)
		out << " on planet : " << (unsigned short int) this->planet;
	else
		out << " in space";
	
	out << std::endl << "capacity : " << this->get_capacity() << std::endl;
	for (const auto & it : this->inventory)
		print_item(it);
	return out;
}

std::string Player::com_decl_string() const
{
	if (this->host)
		return "h-" + this->get_username();
	return this->get_username();
}

std::string Player::com_pos_string() const
{
	return this->get_username() + ":(" + 
		std::to_string(this->pos.x) + ',' +
		std::to_string(this->pos.y) + ',' +
		std::to_string(this->pos.z) + ')';
}

std::string Player::com_inv_string() const
{
	std::string inv = this->get_username() + ':';
	for (unsigned short i = 0; i < this->inventory.size(); ++i)
		inv += com_item_string(this->inventory[i]) + ',';
	return inv;
}


bool Player::add_item(item * it)
{
	unsigned int sum = 0;
	for (const auto * i : this->inventory) {
		sum += i->weight;
	}
	if (sum + it->weight > this->capacity)
		return false;
	else {
		this->inventory.push_back(it);
		return true;
	}
}

bool Player::rm_item(item * it)
{
	std::vector<item *>::iterator i = std::find(this->inventory.begin(), this->inventory.end(), it);
	if (i == this->inventory.end())
		return false;
	else {
		this->inventory.erase(i);
		return true;
	}
}
