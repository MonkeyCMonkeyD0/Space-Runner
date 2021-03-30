#ifndef KNAPSACK_HPP
#define KNAPSACK_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <random>


class Knapsack {

public:
	Knapsack(
		std::vector<unsigned int> weights,
		std::vector<unsigned int> profits,
		unsigned int max_weight,
		unsigned int population = 25,
		double survival_rate = 0.3,
		unsigned int max_iteration = 100
	);

	std::ostream & print_bin(std::ostream &, unsigned long long);
	unsigned long long get();
	void run(bool debug = false);

private:
	std::vector<unsigned int> weights;
	std::vector<unsigned int> profits;
	unsigned int maxWeight;
	unsigned int population;
	unsigned int maxIteration;
	unsigned int geneSize;
	double survivalRate;

	std::map<unsigned long long, int> pop;
	std::pair<unsigned long long, int> best_ind;

	void add_pop();
	int fitness (unsigned long long);
	void evaluation();
	unsigned long long mutation (unsigned long long, unsigned int);
	unsigned long long crossover (unsigned long long, unsigned long long, unsigned int);

};

#endif
