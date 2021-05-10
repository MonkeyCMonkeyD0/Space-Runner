#pragma once

#include <ostream>
#include <vector>
#include <map>


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
	Knapsack(const Knapsack * k) : Knapsack(
		k->weights,
		k->profits,
		k->maxWeight,
		k->population,
		k->survivalRate,
		k->maxIteration
	) {}

	virtual std::ostream & print() const;
	virtual unsigned long long get() const;
	void run(const bool & debug = false);

protected:

	int fitness (unsigned long long) const;
	static bool cmp(const std::pair<unsigned long long, int> &, const std::pair<unsigned long long, int> &);

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

	std::ostream & print_bin(std::ostream &, unsigned long long) const;
	void add_pop();
	void evaluation();
	unsigned long long mutation (unsigned long long, const unsigned int &) const;
	unsigned long long crossover (const unsigned long long &, const unsigned long long &, const unsigned int &) const;

};
