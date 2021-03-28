#include "knapsack.hpp"



Knapsack::Knapsack(std::vector<unsigned int> weights, std::vector<unsigned int> profits, unsigned int max_weight, unsigned int population, double survival_rate, unsigned int max_iteration) : 
	weights(weights),
	profits(profits),
	maxWeight(max_weight),
	population(population),
	survivalRate(survival_rate),
	maxIteration(max_iteration),
	geneSize(weights.size())
{
	if (this->weights.size() != this->profits.size()) {
		std::cerr << "Error please use same size array for weights & profits." << std::endl;
		exit(EXIT_FAILURE);
	}

	if (this->population) {
		std::cerr << "Error please use same size array for weights & profits." << std::endl;
		exit(EXIT_FAILURE);
	}

	this->add_pop();
}


void Knapsack::add_pop(bool use_crossover = false)
{
	std::mt19937 gen(std::random_device());
	std::uniform_int_distribution<unsigned long long int> distrib_gs(0, (unsigned long long int) (1 << this->geneSize) - 1);

	if (use_crossover) {
		std::uniform_int_distribution<unsigned long long int> distrib_pop(0, (unsigned long long int) this->pop.size() - 1);

		for (unsigned int i = this->pop.size(); i < this->population; ++i) {
			unsigned long long int gene = crossover(distrib_pop(gen),distrib_pop(gen),distrib_gs(gen));

			this->pop[crossover(distrib_pop(gen),distrib_pop(gen),distrib_gs(gen))] = 0;

		}

	} else {
		

		while (this->pop.size() < this->population)
			this->pop[distrib_gs(gen)] = 0;
	}
}

int Knapsack::fitness(unsigned long long int gene)
{
	unsigned int sum_w = 0, sum_p = 0;
	for (unsigned int i = 0; gene > 0 && i < this->geneSize; ++i) {
		sum_w += (gene % 2) * this->weights[this->geneSize - 1 - i];
		sum_p += (gene % 2) * this->profits[this->geneSize - 1 - i];

		gene = gene >> 1;
	}

	if (sum_w > this->maxWeight)
		return -1;
	else
		return (int) sum_p;
}


bool cmp(std::pair<unsigned long long int, int> & a, std::pair<unsigned long long int, int> & b)
{
	return a.second < b.second;
}

void Knapsack::evaluation()
{
	std::vector<std::pair<unsigned long long int, int>> sorted_map;

	for (auto &it : this->pop) {
		it.second = fitness(it.first);

		if (it.second > 0)
			sorted_map.push_back(it);
	}

	sort(sorted_map.begin(), sorted_map.end(), cmp);
	std::cout << "best idividual = " << std::bitset<this->geneSize>(sorted_map[0].first) << std::endl;

	this->pop.clear();
	for (unsigned int i = 0; i < (unsigned int) (this->survivalRate * this->population); ++i) {
		this->pop[sorted_map[i].first] = 0;
	}
}

unsigned long long int Knapsack::mutation(unsigned long long int gene, int n)
{
	std::mt19937 gen(std::random_device());
	std::uniform_int_distribution<unsigned int> distrib(0, this->geneSize - 1);

	for (int i = 0; i < n; ++i)
		gene ^= 1UL << distrib(gen);

	return gene;
}

unsigned long long int Knapsack::crossover(unsigned long long int g1, unsigned long long int g2, unsigned int break_point)
{
	return ((g1 >> break_point) << break_point) | (g2 & ((1 << break_point) - 1));
}

void Knapsack::run()
{
	std::mt19937 gen(std::random_device());
	std::uniform_int_distribution<unsigned long long int> distrib_gs(0, (unsigned long long int) (1 << this->geneSize) - 1);

	for (unsigned int iteration = 0; iteration < this->maxIteration; ++iteration) {

		std::cout << "On iteration " << iteration << " : ";
		this->evaluation();

		std::uniform_int_distribution<unsigned long long int> distrib_pop(0, (unsigned long long int) this->pop.size() - 1);

		std::vector<unsigned long long int, int> keys;
		for (auto &it : this->pop) {
			keys.push_back(it.first);

		while (this->pop.size() < this->population) {
			unsigned long long int gene = crossover(keys(distrib_pop(gen)), keys(distrib_pop(gen)), distrib_gs(gen));
			gene = mutation(gene, distrib_gs(gen));
			this->pop[gene] = 0;
		}
	}
}
