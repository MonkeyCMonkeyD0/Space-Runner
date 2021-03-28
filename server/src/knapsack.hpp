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
<<<<<<< HEAD:server/knapsack algo/knapsack.hpp
	unsigned int maxIteration;
	unsigned int geneSize;


	std::map<unsigned long long int, int> pop;
=======
	unsigned int geneSize;
	unsigned int maxIteration;

	std::map<unsigned long long int,unsigned int> pop;
>>>>>>> 5157d59378d9227ea5494492d37668d8d297fed2:server/src/knapsack.hpp

	// std::vector<int> opt;
	// std::vector<int> parents;
	// std::vector<int> newparents;
	// std::vector<int> bests;
	// std::vector<int> best_p;
	// int iterated;

	
};