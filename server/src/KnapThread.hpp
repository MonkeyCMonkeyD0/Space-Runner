#pragma once

#include <vector>
#include <thread>
#include <threadextend.h>
#include <mutex>

#include "Knapsack.hpp"


class KnapThread : public Knapsack {

public:

	KnapThread(
		std::vector<unsigned int> weights,
		std::vector<unsigned int> profits,
		unsigned int max_weight,
		unsigned int population = 25,
		double survival_rate = 0.3,
		unsigned int max_iteration = 100
	);

	unsigned long long get() const;
	void run(const bool & debug = false);

private:

	unsigned int num_cpus;
	std::pair<unsigned long long, int> best_ind;

	std::vector<std::thread> threads;
	std::vector<std::pair<unsigned long long, int>> bests;

	void run_inst(std::mutex *, const int &, const bool & debug = false);

};
