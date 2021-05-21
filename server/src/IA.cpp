#include <vector>
#include <iostream>

#include "KnapThread.hpp"

#include "IA.hpp"


unsigned char IA::nb_ia = 1;

void IA::item_choice(const std::vector<item *> & new_items)
{
	std::vector<unsigned short int> weights, values;
	for (const auto & it : this->get_inventory()) {
		weights.push_back(it->weight);
		values.push_back(it->price);
	}
	for (const auto & it : new_items) {
		weights.push_back(it->weight);
		values.push_back(it->price);
	}
	std::cout << this->dif * 200;
	KnapThread kth(weights, values, this->get_capacity(), this->dif * 500);


	kth.run();
	unsigned long long int result_new = kth.get() & ((1 << new_items.size()) - 1);
	unsigned long long int result_inv = (kth.get() - result_new) >> new_items.size();

	for (size_t i = 0, bit = this->get_inventory().size() - 1; i < this->get_inventory().size() && bit >= 0; --bit) {
		if (result_inv & (1 << bit))
			++i;
		else
			if (!this->rm_item(this->get_inventory()[i]))
				std::cerr << "ERROR: IA - Removed item not in inventory." << std::endl;
	}
	for (short int i = new_items.size() - 1; i >= 0; --i) {
		if (result_new % 2)
			if (!this->add_item(new_items[i]))
				std::cerr << "ERROR: IA - Could not add item to inventory." << std::endl;
		result_new = result_new >> 1;
	}
}

void IA::update_pos(const float & delta_time)
{
	this->set_pos(this->dir.x * MV_SPEED * delta_time, this->dir.y * MV_SPEED * delta_time, this->dir.z * MV_SPEED * delta_time);
}

void IA::set_direction(const point & next_planet)
{
	this->dir = normalize(sum(this->get_pos(), next_planet));
}

void IA::find_optimal_path(const std::vector<point> & planets)
{

}
