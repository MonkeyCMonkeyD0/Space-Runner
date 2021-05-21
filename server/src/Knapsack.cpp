#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <random>

#include "Knapsack.hpp"


Knapsack::Knapsack(std::vector<unsigned short int> weights, std::vector<unsigned short int> profits, unsigned int max_weight, unsigned short int population, double survival_rate, unsigned int max_iteration) : 
	maxIteration(max_iteration),
	weights(weights),
	profits(profits),
	maxWeight(max_weight),
	population(population),
	geneSize(weights.size()),
	survivalRate(survival_rate)
{
	if (this->weights.size() != this->profits.size()) {
		std::cerr << "Error please use same size array for weights & profits." << std::endl;
		exit(EXIT_FAILURE);
	}

	if (this->population >= (1U << this->geneSize) - 1) {
		std::cerr << "Error population to big, cannot generate different gene for each." << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Knapsack::add_pop()
{
	std::random_device rd;
	std::uniform_int_distribution<unsigned long long> distrib(1, (unsigned long long) (1 << this->geneSize) - 1);

	while (this->pop.size() < this->population)
		this->pop[distrib(rd)] = 0;
}

int Knapsack::fitness(unsigned long long gene) const
{
	unsigned int sum_w = 0, sum_p = 0;
	for (unsigned int i = this->geneSize; gene > 0 && i > 0; --i) {
		sum_w += (gene % 2) * this->weights[i-1];
		sum_p += (gene % 2) * this->profits[i-1];

		gene = gene >> 1;
	}

	if (sum_w > this->maxWeight)
		return -1;
	else
		return (int) sum_p;
}


bool Knapsack::cmp(const std::pair<unsigned long long, int> & a, const std::pair<unsigned long long, int> & b)
{
	return a.second > b.second;
}

std::ostream & Knapsack::print_bin(std::ostream & out, unsigned long long gene) const
{
	std::string s = "";
	for (unsigned int i = this->geneSize; i > 0; --i) {
		s += std::to_string(gene % 2);
		gene = gene >> 1;
	}

	std::reverse(s.begin(), s.end());
	return out << s;
}

std::ostream & Knapsack::print() const
{
	return this->print_bin(std::cout, this->get());
}

void Knapsack::evaluation()
{
	std::vector<std::pair<unsigned long long, int>> sorted_map;

	for (auto &it : this->pop) {
		it.second = fitness(it.first);

		if (it.second > 0)
			sorted_map.push_back(it);
	}

	sort(sorted_map.begin(), sorted_map.end(), cmp);
	this->best_ind = sorted_map[0];

	this->pop.clear();
	for (unsigned int i = 0; i < this->survivalRate * this->population && i < sorted_map.size(); ++i)
		this->pop[sorted_map[i].first] = 0;
}

unsigned long long Knapsack::mutation(unsigned long long gene, const unsigned int & n) const
{
	std::random_device rd;
	std::uniform_int_distribution<unsigned int> distrib(0, this->geneSize - 1);

	for (unsigned int i = 0; i < n; ++i)
		gene ^= 1UL << distrib(rd);
	return gene;
}

unsigned long long Knapsack::crossover(const unsigned long long & g1, const unsigned long long & g2, const unsigned int & break_point) const
{
	return ((g1 >> break_point) << break_point) | (g2 & ((1 << break_point) - 1));
}

void Knapsack::run(const bool & debug)
{
	this->add_pop();

	std::random_device rd;
	std::uniform_int_distribution<unsigned int> distrib_gs(0, this->geneSize - 1);

	for (unsigned int iteration = 0; iteration < this->maxIteration; ++iteration) {

		this->evaluation();

		if (debug) {
			std::cout << "On iteration " << iteration << " : ";
			print_bin(std::cout << "best idividual = ", this->best_ind.first) << " -> " << this->best_ind.second << std::endl;
		}

		std::uniform_int_distribution<unsigned long long> distrib_pop(0, (unsigned long long) this->pop.size() - 1);

		std::vector<unsigned long long> keys;
		for (auto &it : this->pop)
			keys.push_back(it.first);

		while (this->pop.size() < this->population) {
			unsigned long long gene = crossover(keys[distrib_pop(rd)], keys[distrib_pop(rd)], distrib_gs(rd));
			gene = mutation(gene, distrib_gs(rd));
			this->pop[gene] = 0;
		}
	}

	if (debug) {
		std::cout << "Optimal solution found = ";
		print_bin(std::cout, this->best_ind.first) << " -> " << this->best_ind.second << std::endl;
	}
}

unsigned long long Knapsack::get() const
{
	return this->best_ind.first;
}
