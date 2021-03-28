#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <random>


class Knapsack {

public:
	Knapsack(
		std::vector<unsigned int> weights,
		std::vector<unsigned int> profits,
		unsigned int max_weight,
		unsigned int population = 500,
		double survival_rate = 0.5,
		unsigned int max_iteration = 15000
	);

	void add_pop();
	int fitness(unsigned long long int);
	void evaluation();

	unsigned long long int mutation(unsigned long long int, int);
	std::vector<unsigned long long int> crossover(unsigned long long int, unsigned long long int, unsigned int);
	void run();

private:
	std::vector<unsigned int> weights;
	std::vector<unsigned int> profits;
	unsigned int maxWeight;
	unsigned int population;
	double survivalRate;
	unsigned int geneSize;
	unsigned int maxIteration;

	std::map<unsigned long long int,unsigned int> pop;

	// std::vector<int> opt;
	// std::vector<int> parents;
	// std::vector<int> newparents;
	// std::vector<int> bests;
	// std::vector<int> best_p;
	// int iterated;

	
};