#include <vector>
#include <iostream>
#include <cmath>
#include <random>

#include <threadextend.h>

#include "KnapThread.hpp"

#include "IA.hpp"

#define MV_SPEED 5
#define GAMMA 5
#define N 8000


unsigned char IA::nb_ia = 1;

IA::IA(const std::vector<point> & p, difficulty d) : 
	Player(0, "IA num " + std::to_string(IA::nb_ia++)), dif(d), planets(p)
{
	this->set_pos(0.0,0.0,0.0);
	this->find_optimal_path(this->planets, false);
}


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
	this->set_pos(
		this->get_pos().x + this->dir.x * MV_SPEED * delta_time, 
		this->get_pos().y + this->dir.y * MV_SPEED * delta_time, 
		this->get_pos().z + this->dir.z * MV_SPEED * delta_time
	);
	std::cout << this->com_pos_string() << std::endl;
}

void IA::update_planet(const point & removed_planet)
{
	unsigned int i;
	for (i = 0; i < (unsigned int) this->planets.size(); ++i)
		if (equal(this->planets[i], removed_planet))
			break;
	this->planets.erase(std::next(this->planets.begin(), i));
	this->path.erase(find(this->path.begin(), this->path.end(), (unsigned short int) i));
	this->set_direction(this->planets[this->path[0]]);
}

void IA::set_direction(const point & next_planet)
{
	this->dir = normalize(sum(this->get_pos(), next_planet));
}


float IA::total_dist(const std::vector<unsigned short int> & path)
{
	float distance = dist(this->get_pos(), this->planets[path[0]]);
	for (unsigned short int i = 0; i < path.size() - 1; ++i)
		distance += this->planet_dist[path[i]][path[i+1]];
	return distance;
}

void IA::find_optimal_path(const std::vector<point> & planets, bool debug)
{
	unsigned short int nb_planets = (unsigned short int) planets.size(), i, j;
	float tmp_dist[2] = {0, 0};
	this->path = std::vector<unsigned short int>(nb_planets);
	this->planet_dist = std::vector<std::vector<float>>(nb_planets, std::vector<float>(nb_planets, 0.0));

	if (debug) {
		std::cout << "IA path planets x : " << planets[0].x;
		for (i = 1; i < nb_planets; ++i)
			std::cout << " - " << planets[i].x;
		std::cout << std::endl;
	}

	for (i = 1; i < nb_planets; ++i) {
		for (j = 0; j < i; ++j)
			this->planet_dist[i][j] = this->planet_dist[j][i] = dist(planets[i], planets[j]);
		tmp_dist[1] = dist(planets[i], this->get_pos());
		if (tmp_dist[1] < tmp_dist[0] || tmp_dist[0] <= 0) {
			tmp_dist[0] = tmp_dist[1];
			this->path[0] = i;
		}
	}

	for (i = 0; i < nb_planets; ++i)
		this->path[i] = nb_planets -1 - i;

	if (debug) {
		std::cout << "IA path min_path : " << this->path[0];
		for (i = 1; i < nb_planets; ++i)
			std::cout << " - " << this->path[i];
		std::cout << std::endl;
	}

	this->num_cpus = std::thread::hardware_concurrency() - 2;
	std::vector<std::thread> threads(this->num_cpus);

	if (debug)
		std::cout << "Launching " << this->num_cpus << " threads." << std::endl;

	cpu_set_t cpus;

	for (unsigned short int i = 0; i < this->num_cpus; ++i) {
		threads[i] = std::thread(
			std::bind(&IA::switch_inst, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
			i, (unsigned int) N / this->num_cpus, debug
		);

		CPU_ZERO(&cpus);
		CPU_SET(i + 2, &cpus);

		int rc = pthread_setaffinity_np(threads[i].native_handle(), sizeof(cpu_set_t), &cpus);
		if (rc) {
			std::cerr << "Error: unable to bind thread to cpu, " << rc << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	for (auto& t : threads)
		t.join();

	this->set_direction(this->planets[this->path[0]]);
}

void IA::switch_inst(const unsigned short int & thread_num, const unsigned int n, const bool & debug)
{
	std::default_random_engine gene;
	std::uniform_int_distribution<unsigned short int> distr_swap(0, this->planets.size() - 1);
	std::uniform_real_distribution<float> distr_switch(0, 1);

	unsigned short int swap[2], tmp_swap;
	std::vector<unsigned short int> tmp_path;
	float r;

	for (unsigned int k = thread_num + 1; k < this->num_cpus * n; k += this->num_cpus) {
		tmp_path = std::vector<unsigned short int>(this->path);
		do {
			swap[0] = distr_swap(gene); swap[1] = distr_swap(gene);
		} while (swap[0] == swap[1]);

		tmp_swap = tmp_path[swap[0]];
		tmp_path[swap[0]] = tmp_path[swap[1]];
		tmp_path[swap[1]] = tmp_swap;

		r = exp((total_dist(this->path) - total_dist(tmp_path)) * pow(k, GAMMA));
		if (r >= distr_switch(gene)) {
			this->path_mutex.lock();
			tmp_swap = this->path[swap[0]];
			this->path[swap[0]] = this->path[swap[1]];
			this->path[swap[1]] = tmp_swap;
			this->path_mutex.unlock();

			if (debug) {
				this->path_mutex.lock();
				std::cout << "Thread #" << thread_num << " found new path : ";
				for (const auto & it : this->path)
					std::cout << it;
				std::cout << std::endl;
				this->path_mutex.unlock();
			}
		}
	}
}


