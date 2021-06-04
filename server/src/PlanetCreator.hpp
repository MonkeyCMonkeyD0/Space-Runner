#pragma once

#include <vector>
#include <iostream>
#include <string>

#define PLANETDIST 30
#define NBPLANET 20
#define NBTEXTURE 12


struct planet
{
	float x, y, z;
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

	void initialize();

private:

	std::vector<struct planet> planets;
	std::vector<float> palier;
	struct planet create(const float &, const float &, const float &, const unsigned char &) const;
	char random_shape(const unsigned char & proba = 10) const;
	unsigned int random_color() const;

	static char shapes[];

};
