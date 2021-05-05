#ifndef PLANETCREATOR_HPP
#define PLANETCREATOR_HPP

#include <vector>
#include <iostream>
#include <string>

#define PLANETDIST 30
#define NBPLANET 20
#define NBTEXTURE 12


struct planet
{
	unsigned short int x, y, z;
	unsigned char radius, texture;
	char shape;
	unsigned int color;
	unsigned short int metallic, roughness;
};


class PlanetCreator {

public:

	PlanetCreator();

	std::vector<struct planet> get() const;
	struct planet get(const unsigned int &) const;
	std::ostream & print(const unsigned int &, std::ostream & out = std::cout) const;
	std::vector<std::string> broadcast_strings() const;

private:

	std::vector<struct planet> planets;
	std::vector<int> palier;
	struct planet create(const unsigned short int &, const unsigned short int &, const unsigned short int &, const unsigned char &) const;
	char random_shape(const unsigned char & proba = 10) const;
	unsigned int random_color() const;

	static char shapes[];

};

#endif