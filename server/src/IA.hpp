#pragma once

#include <vector>
#include <functional>
#include <algorithm>

#include "Player.hpp"


typedef enum difficulty : unsigned short int
{
	EASY = 1, MEDIUM = 2, HARD = 3
} difficulty;


class IA : public Player {

public:

	IA(const std::vector<point> &, difficulty d = EASY);

	void item_choice(const std::vector<item *> &);
	void update_pos(const float &);
	void update_planet(const point &);

private:

	static unsigned char nb_ia;
	unsigned short int num_cpus;

	difficulty dif;
	point dir;
	std::vector<point> planets;
	std::vector<unsigned short int> path;
	std::mutex path_mutex;
	std::vector<std::vector<float>> planet_dist;

	void set_direction(const point &);
	float total_dist(const std::vector<unsigned short int> &);
	void find_optimal_path(const std::vector<point> &, bool debug = false);
	void switch_inst(const unsigned short int &, const unsigned int, const bool & debug = false);

};
