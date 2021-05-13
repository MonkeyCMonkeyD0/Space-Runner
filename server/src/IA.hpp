#pragma once

#include <vector>
#include <list>

#include "Player.hpp"

#define MV_SPEED 500

typedef enum difficulty : unsigned short int
{
	EASY = 1, MEDIUM = 2, HARD = 3
} difficulty;


class IA : public Player {

public:

	IA(difficulty d = EASY) : Player(0, "IA num " + std::to_string(IA::nb_ia++)), dif(d) {}

	void item_choice(const std::vector<item *> &);
	void update_pos(const float &);

private:

	static unsigned char nb_ia;
	difficulty dif;
	point dir;
	std::vector<point> planets;
	std::list<unsigned short int> dest;

	void set_direction(const point &);
	void find_optimal_path(const std::vector<point> &);

};
