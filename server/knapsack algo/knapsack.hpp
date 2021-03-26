#include <iostream>
#include <vector>



class Knapsack {

public:
	Knapsack(
		std::vector<unsigned int> weights,
		std::vector<unsigned int> profits,
		unsigned int population,
		unsigned int max_weight,
		double survival_rate = 0.5,
		unsigned int max_iteration = 15000
	);
	~Knapsack();

	void add_pop(unsigned int);
	void mutation(std::vector<int> &);
	std::vector<std::vector<int>> crossover(std::vector<int>, std::vector<int>);
	void run();


private:
	int maxScore;
	int population;
	std::vector<int> weights;
	std::vector<int> profits;
	std::vector<unsigned long long int> pop;

	std::vector<int> opt;
	std::vector<int> parents;
	std::vector<int> newparents;
	std::vector<int> bests;
	std::vector<int> best_p;
	int iterated;

	
};