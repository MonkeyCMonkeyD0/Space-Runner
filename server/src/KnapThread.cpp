#include "KnapThread.hpp"


KnapThread::KnapThread(std::vector<unsigned int> weights, std::vector<unsigned int> profits, unsigned int max_weight, unsigned int population, double survival_rate, unsigned int max_iteration) :
	Knapsack(weights, profits, max_weight, population, survival_rate, max_iteration)
{
	// pthread_attr_t attr;
	// cpu_set_t cpus;
	// unsigned long i;
	// int rc;

	// pthread_attr_init(&attr);
	// pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	// sched_getaffinity(0, sizeof(cpus), &cpus);
	// unsigned int numberOfProcessors = CPU_COUNT(&cpus);
	// printf("Number of processors: %u\n", numberOfProcessors);

	// pthread_t threads[numberOfProcessors];

	// for (i = 0; i < (unsigned long) numberOfProcessors; i++)
	// {
	// 	CPU_ZERO(&cpus);
	// 	CPU_SET(i, &cpus);

	// 	rc = pthread_create(&threads[i], &attr, this->run_inst, (void *) i);
	// 	if (rc) {
	// 		std::cout << "Error: unable to create thread," << rc << std::endl;
	// 		exit(EXIT_FAILURE);
	// 	}

	// 	rc = pthread_setaffinity_np(threads[i], sizeof(cpu_set_t), &cpus);
	// 	if (rc) {
	// 		std::cout << "Error: unable to bind thread," << rc << std::endl;
	// 		exit(EXIT_FAILURE);
	// 	}
	// }

	// for (i = 0; i < (unsigned long) numberOfProcessors; i++)
	// {
	// 	rc = pthread_join(threads[i], NULL);
	// 	if (rc) {
	// 		std::cout << "Error: unable to join thread," << rc << std::endl;
	// 		exit(EXIT_FAILURE);
	// 	}
	// }

	// pthread_exit(NULL);
}

void * KnapThread::run_inst(void * args)
{
	// unsigned long tid;
	// tid = (unsigned long) args;

	// printf("start ID: %lu\n", (unsigned long) tid);
	// sleep(1);
	// printf("end   ID: %lu\n", (unsigned long) tid);
	// pthread_exit(NULL);
	return NULL;
}

