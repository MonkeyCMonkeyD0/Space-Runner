#include <iostream>
#include <vector>
#include <algorithm>
#include <mutex>
#include <functional>

#include <threadextend.h>

#include "KnapThread.hpp"


KnapThread::KnapThread(std::vector<unsigned int> weights, std::vector<unsigned int> profits, unsigned int max_weight, unsigned int population, double survival_rate, unsigned int max_iteration) :
	Knapsack(weights, profits, max_weight, population, survival_rate, max_iteration)
{
	this->num_cpus = std::thread::hardware_concurrency();
	std::cout << "Launching " << this->num_cpus << " threads\n";

	this->threads = std::vector<std::thread>(this->num_cpus);
	this->bests = std::vector<std::pair<unsigned long long, int>>(this->num_cpus);
}

unsigned long long KnapThread::get() const
{
	return this->bests[0].first;
}

void KnapThread::run(const bool & debug)
{
	cpu_set_t cpus;
	// A mutex ensures orderly access to std::cout from multiple threads.
	std::mutex * iomutex = new std::mutex;

	for (unsigned int i = 0; i < this->num_cpus; ++i) {
		threads[i] = std::thread(
			std::bind(&KnapThread::run_inst, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
			iomutex, i, debug
		);

		CPU_ZERO(&cpus);
		CPU_SET(i, &cpus);

		int rc = pthread_setaffinity_np(threads[i].native_handle(), sizeof(cpu_set_t), &cpus);
		if (rc) {
			std::cerr << "Error: unable to bind thread to cpu, " << rc << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	for (auto& t : threads)
		t.join();

	delete iomutex;
	sort(this->bests.begin(), this->bests.end(), Knapsack::cmp);
	this->best_ind = this->bests[0];
	
	if (debug) {
		std::cout << "Best solution overall is ";
		this->print() << ", it's value is " << this->best_ind.second << std::endl;
	}
}

void KnapThread::run_inst(std::mutex * iomutex, const int & thread_num, const bool & debug)
{
	if (debug) {
		std::lock_guard<std::mutex> iolock(*iomutex);
		std::cout << "Starting Thread #" << thread_num << " for Knapsack" << std::endl;
	}

	Knapsack k(this);
	k.run();
	this->bests[thread_num] = std::make_pair(k.get(), this->fitness(k.get()));

	if (debug) {
		std::lock_guard<std::mutex> iolock(*iomutex);
		std::cout << "Thread #" << thread_num << " got result : ";
		k.print() << std::endl;
	}
}
