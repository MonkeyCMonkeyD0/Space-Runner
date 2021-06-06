#include <random>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <math.h>
#include <iostream>

#include "PlanetCreator.hpp"


char PlanetCreator::shapes[] = {'S', 'T', 'D', 'C'}; // Sphere Torus Disc Cube

PlanetCreator::PlanetCreator()
{
	this->initialize();
}

void PlanetCreator::initialize()
{
	float coord[3] = {0, 0, 0};
	float R = 40;
	float N = NBPLANET;
	float radius;
	this->palier.push_back(3);

	while(N>0) {
		N -= palier[palier.size()-1];
		if (N>0)
		{
			palier.push_back(round(palier[palier.size()-1] * ((R + PLANETDIST) / R) * ((R + PLANETDIST) / R)));
		}

		else {
			palier[palier.size()-1] += N;
			N = -1;
		}
		R += PLANETDIST;
		//std::cout << palier[palier.size()-1] << std::endl;
		//std::cout << palier[palier.size()-1] << std::endl;
	}
	//std::cout << palier.size() << std::endl;

	float phi = M_PI * (3.0 - sqrt(5.0));
	R = 40;

	for (auto i : palier) {
		for (unsigned int j = 0; j < i; j++) {
			if (i == 1)
				coord[1] = 0;
			else
				coord[1] = R * (1 - 2 * j / (i - 1));
			radius = sqrt(R * R - coord[1] * coord[1]);
			coord[0] = cos(phi * j) * radius;
			coord[2] = sin(phi * j) * radius;
			this->planets.push_back(this->create(coord[0], coord[1], coord[2], R));
			//std::cout << "x : " << coord[0] << ", y : " <<  coord[1] << ", z : " << coord[2] << std::endl;
		}
		R += PLANETDIST;
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
		<< "_c#" << std::setfill('0') << std::setw(6) << std::hex << this->get(index).color << std::dec
		<< "_t" << (short int) this->get(index).texture
		<< "_m" << (short int) this->get(index).metallic
		<< "_h" << (short int) this->get(index).roughness << "_________";

	return out;
}

std::vector<std::string> PlanetCreator::broadcast_strings() const
{
	std::stringstream ss;
	std::vector<std::string> vect;
	for (short int i = 0; i < (short int) this->get().size(); ++i) {
		this->print(i, ss << std::setfill('0') << std::setw(2) << i << ':');
		vect.push_back(ss.str());
		ss.str(std::string());
		ss.clear();
	}
	return vect;
}

struct planet PlanetCreator::create(const float & x, const float & y, const float & z, const unsigned char & rad) const
{
	std::random_device rd;
	std::uniform_int_distribution<unsigned int> distrib(0, 9);
	std::uniform_int_distribution<char> distrib_texture(1, 12);

	//cpt++;
	//std::cout << "planete created : "<<cpt << std::endl;

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
