#include <iostream>

class Knapsack
{
private:
	int C;
	int * weights;
	int * profits ;
	int * opt ;
	int * parents ;
	int * newparents ;
	int * bests ;
	int * best_p ;
	int iterated;
	int population;

public:
	void initialize();
	void properties(int * weights, int * profits, int * sz, int * opt, int C, int population);
	int fitness(int * item);
	void evaluation();

	int * mutation(int * ch);

	std::vector<int *> crossover(int * ch1, int * ch2);
	void run();

	Knapsack();
	~Knapsack();
	
};