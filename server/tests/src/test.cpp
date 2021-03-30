#include <iostream>
// #include <cstdlib>
// #include <pthread.h>
// #include <pthreadextend.h>
#include <algorithm>
#include <chrono>
#include <mutex>
#include <thread>
#include <vector>

// #include "../../src/Knapsack.hpp"



int main()
{
	unsigned num_cpus = std::thread::hardware_concurrency();
	std::cout << "Launching " << num_cpus << " threads\n";

	// A mutex ensures orderly access to std::cout from multiple threads.
	std::mutex iomutex;
	std::vector<std::thread> threads(num_cpus);
	for (unsigned i = 0; i < num_cpus; ++i) {
		threads[i] = std::thread([&iomutex, i] {
			{
				// Use a lexical scope and lock_guard to safely lock the mutex only for
				// the duration of std::cout usage.
				std::lock_guard<std::mutex> iolock(iomutex);
				std::cout << "Thread #" << i << " is running\n";
			}

			// Simulate important work done by the tread by sleeping for a bit...
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));

		});
	}

	for (auto& t : threads) {
		t.join();
	}
	return 0;
}


// void * DoWork(void * args) {
// 	unsigned long tid;
// 	tid = (unsigned long) args;

// 	printf("start ID: %lu\n", (unsigned long) tid);
// 	sleep(1);
// 	printf("end   ID: %lu\n", (unsigned long) tid);
// 	pthread_exit(NULL);
// }

// int main (int argc, char ** argv)
// {
// 	pthread_attr_t attr;
// 	cpu_set_t cpus;
// 	unsigned long i;
// 	int rc;

// 	pthread_attr_init(&attr);
// 	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
// 	sched_getaffinity(0, sizeof(cpus), &cpus);
// 	unsigned int numberOfProcessors = CPU_COUNT(&cpus);
// 	printf("Number of processors: %u\n", numberOfProcessors);

// 	pthread_t threads[numberOfProcessors];

// 	for (i = 0; i < (unsigned long) numberOfProcessors; i++)
// 	{
// 		CPU_ZERO(&cpus);
// 		CPU_SET(i, &cpus);

// 		rc = pthread_create(&threads[i], &attr, DoWork, (void *) i);
// 		if (rc) {
// 			std::cout << "Error: unable to create thread," << rc << std::endl;
// 			exit(EXIT_FAILURE);
// 		}

// 		rc = pthread_setaffinity_np(threads[i], sizeof(cpu_set_t), &cpus);
// 		if (rc) {
// 			std::cout << "Error: unable to bind thread," << rc << std::endl;
// 			exit(EXIT_FAILURE);
// 		}
// 	}

// 	for (i = 0; i < (unsigned long) numberOfProcessors; i++)
// 	{
// 		rc = pthread_join(threads[i], NULL);
// 		if (rc) {
// 			std::cout << "Error: unable to join thread," << rc << std::endl;
// 			exit(EXIT_FAILURE);
// 		}
// 	}

// 	pthread_exit(NULL);
// }

// int main(int argc, char const *argv[])
// {
// 	std::vector<unsigned int> 	w = {70, 73, 77, 80, 82, 87, 90, 94, 98, 106, 110, 113, 115, 118, 120},
// 								p = {135, 139, 149, 150, 156, 163, 173, 184, 192, 201, 210, 214, 221, 229, 240};
// 	Knapsack knap1(w, p, 750, 50, 0.3, 1000);
// 	knap1.run();

// 	std::cout << "Optimal solution found = ";
// 	knap1.print_bin(std::cout, knap1.get()) << std::endl;

// 	return 0;
// }