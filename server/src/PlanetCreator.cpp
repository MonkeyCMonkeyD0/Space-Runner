#include <random>
#include <iomanip>
#include <sstream>
#include <cmath>

#include "PlanetCreator.hpp"


char PlanetCreator::shapes[] = {'S', 'T', 'D', 'C'}; // Sphere Torus Disc Cube


PlanetCreator::PlanetCreator()
{
	unsigned short int coord[3] = {0, 0, 0};
	unsigned char rad;
	std::random_device rd;
	std::uniform_int_distribution<unsigned char> distrib_rad(1, 5);
	std::uniform_int_distribution<unsigned short int> distrib_coord(0, 2);

	this->planets.push_back(this->create(0, 0, 0, 5));
	for (unsigned int i = 0; i < NBPLANET; ++i) {
		rad = distrib_rad(rd);
		coord[distrib_coord(rd)] += PLANETDIST + this->planets.back().radius + rad;
		this->planets.push_back(this->create(coord[0], coord[1], coord[2], rad));
	}
}


std::vector<struct planet> PlanetCreator::get() const
{
	return this->planets;
}

struct planet PlanetCreator::get(const unsigned int & index) const
{
	return this->planets[index];
}


std::ostream & PlanetCreator::print(const unsigned int & index, std::ostream & out) const
{
	out << '(' << this->get(index).x << ',' << this->get(index).y << ',' << this->get(index).z << ')'
		<< "_r" << (short int) this->get(index).radius
		<< "_s" << (char) this->get(index).shape
		<< "_c#" << std::setfill('0') << std::setw(6) << std::hex << this->get(index).color << std::dec
		<< "_t" << (short int) this->get(index).texture
		<< "_m" << (short int) this->get(index).metallic
		<< "_h" << (short int) this->get(index).roughness;
	return out;
}

std::vector<std::string> PlanetCreator::broadcast_strings() const
{
	std::stringstream ss;
	std::vector<std::string> vect;
	for (short int i = 0; i < this->get().size(); ++i) {
		this->print(i, ss << std::setfill('0') << std::setw(2) << i << ':');
		vect.push_back(ss.str());
		ss.str(std::string());
		ss.clear();
	}
	return vect;
}


struct planet PlanetCreator::create(const unsigned short int & x, const unsigned short int & y, const unsigned short int & z, const unsigned char & rad) const
{
	std::random_device rd;
	std::uniform_int_distribution<unsigned int> distrib(0, 9);
	std::uniform_int_distribution<char> distrib_texture(1, 12);

	struct planet p = {x, y, z, rad};
	p.shape = this->random_shape();
	p.texture = distrib_texture(rd);
	p.color = this->random_color();
	p.metallic = distrib(rd);
	p.roughness = distrib(rd);
	return p;
}


char PlanetCreator::random_shape(const unsigned char & proba) const
{
	std::random_device rd;
	std::uniform_int_distribution<char> distrib(1, proba);

	char X = char(sizeof(this->shapes)/sizeof(char)) - distrib(rd);
	return this->shapes[ X < 0 ? 0 : X];
}

unsigned int PlanetCreator::random_color() const
{
	unsigned int res = 0;
	unsigned short int tmp;
	std::random_device rd;
	std::uniform_int_distribution<unsigned short int> distrib(0, 65535);
	for (char dec = 16; dec >= 0; dec -= 8) {
		tmp = distrib(rd);
		res += (unsigned int) floor(sqrt(tmp)) << dec;
	}
	return res;
}
