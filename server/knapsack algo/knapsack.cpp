#include "knapsack.hpp"


Knapsack::Knapsack(std::vector<unsigned int> weights, std::vector<unsigned int> profits, unsigned int population, unsigned int max_iteration = 1000)
	: population(population), weights(weights), profits(profits), max_iteration(max_iteration)
{
	if (weights.size() != profits.size()) {
		std::cerr << "Error please use same size array for weights & profits." << std::endl;
		exit(EXIT_FAILURE);
	}

	add_pop(weights.size());
}

Knapsack::~Knapsack()
{

}


void Knapsack::add_pop(unsigned int n)
{
	std::mt19937 gen(std::random_device());
	std::uniform_int_distribution<unsigned long long int> distrib(0, (unsigned long long int) (1 << n) - 1);

	for (unsigned int i = 0; i < this->population; ++i)
		this->pop.push_back(distrib(gen));
}

int Knapsack::fitness(std::vector<int> item)
{

}

void Knapsack::evaluation()
{

}

unsigned long long int Knapsack::mutation(unsigned long long int gene)
{

}

void Knapsack::crossover(unsigned long long int g1, unsigned long long int g2, unsigned int break_point)
{
	
}

void Knapsack::run()
{

}
