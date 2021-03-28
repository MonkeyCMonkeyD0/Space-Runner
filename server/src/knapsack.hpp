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
	unsigned int maxIteration;
	unsigned int geneSize;
	double survivalRate;

	std::map<unsigned long long int, int> pop;

};