#ifndef KNAP_THREAD_HPP
#define KNAP_THREAD_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <random>
#include <pthread.h>

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

	std::vector<unsigned long long> get();
	void run(bool debug = false);

private:

	// std::vector<pthread>

	void * run_inst(void *);

};

#endif
