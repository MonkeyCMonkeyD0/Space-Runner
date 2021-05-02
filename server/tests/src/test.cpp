#include <iostream>
#include <vector>
#include <sstream>
#include <string>


#include "../../src/Blockchain.hpp"
#include "../../src/BlockThread.hpp"

int main(int argc, char const *argv[])
{
	Blockchain bc;
	bc.add_Block("test1", true);
	bc.add_Block("test2", true);
	bc.add_Block("test3", true);

	BlockThread bt;
	bt.add_Block("test1", true);
	bt.add_Block("test2", true);
	bt.add_Block("test3", true);

	return 0;
}


// #include "../../src/PlanetCreator.hpp"


// int main(int argc, char const *argv[])
// {
// 	PlanetCreator pc;
// 	for (const auto & s : pc.broadcast_strings())
// 		std::cout << s << std::endl;

// 	return 0;
// }


// #include "../../src/Knapsack.hpp"
// #include "../../src/KnapThread.hpp"


// int main(int argc, char const *argv[])
// {
// 	std::vector<unsigned int> 	w = {70, 73, 77, 80, 82, 87, 90, 94, 98, 106, 110, 113, 115, 118, 120},
// 								p = {135, 139, 149, 150, 156, 163, 173, 184, 192, 201, 210, 214, 221, 229, 240};
// 	KnapThread kt(w, p, 750, 10, 0.3, 30000);
// 	kt.run();

// 	std::cout << "Optimal solution found = ";
// 	kt.print() << std::endl;

// 	return 0;
// }


// void test_func(std::mutex * iomutex, int thread_num, std::string msg)
// {
// 	{
// 		std::lock_guard<std::mutex> iolock(*iomutex);
// 		std::cout << "Thread #" << thread_num << " from cpu #" << msg << std::endl;
// 	}

// 	std::random_device rd;
// 	std::uniform_int_distribution<int> distrib(0, 10);
// 	std::this_thread::sleep_for(std::chrono::milliseconds(3000));

// 	{
// 		std::lock_guard<std::mutex> iolock(*iomutex);
// 		std::cout << "Thread #" << thread_num << " got number : " << distrib(rd) << std::endl;
// 	}
// }

// int main()
// {
// 	unsigned num_cpus = std::thread::hardware_concurrency();
// 	std::cout << "Launching " << num_cpus << " threads\n";

// 	cpu_set_t cpus;
// 	std::vector<std::thread> threads(num_cpus);
// 	// A mutex ensures orderly access to std::cout from multiple threads.
// 	std::mutex * iomutex = new std::mutex;
	
// 	for (unsigned i = 0; i < num_cpus; ++i) {
// 		threads[i] = std::thread(test_func, iomutex, i, "Hello from thread!");

// 		CPU_ZERO(&cpus);
// 		CPU_SET(i, &cpus);

// 		int rc = pthread_setaffinity_np(threads[i].native_handle(), sizeof(cpu_set_t), &cpus);
// 		if (rc) {
// 			std::cout << "Error: unable to bind thread," << rc << std::endl;
// 			exit(EXIT_FAILURE);
// 		}
// 	}

// 	for (auto& t : threads) {
// 		t.join();
// 	}

// 	delete iomutex;
// 	return 0;
// }


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
// 	Knapsack knap1(w, p, 750, 50, 0.3, 30000);
// 	knap1.run();

// 	std::cout << "Optimal solution found = ";
// 	knap1.print() << std::endl;

// 	return 0;
// }