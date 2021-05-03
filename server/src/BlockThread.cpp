#include <vector>
#include <mutex>
#include <functional>

#include <threadextend.h>

#include "SHA256.hpp"

#include "BlockThread.hpp"


void BlockThread::mine_last(const bool & debug)
{
	this->found = false;
	this->num_cpus = std::thread::hardware_concurrency() - 1;
	std::vector<std::thread> threads(this->num_cpus);

	if (debug)
		std::cout << "Launching " << this->num_cpus << " threads." << std::endl;

	cpu_set_t cpus;
	std::mutex * iomutex = new std::mutex;

	for (unsigned short int i = 0; i < this->num_cpus; ++i) {
		threads[i] = std::thread(
			std::bind(&BlockThread::mine_inst, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
			iomutex, i, debug
		);

		CPU_ZERO(&cpus);
		CPU_SET(i + 1, &cpus);

		int rc = pthread_setaffinity_np(threads[i].native_handle(), sizeof(cpu_set_t), &cpus);
		if (rc) {
			std::cerr << "Error: unable to bind thread to cpu, " << rc << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	for (auto& t : threads)
		t.join();
	delete iomutex;
}

void BlockThread::mine_inst(std::mutex * iomutex, const unsigned short int & thread_num, const bool & debug)
{
	unsigned long int th_nonce = thread_num;
	std::string input;
	std::string data;
	std::string hash;

	if (this->get_first() == this->get_last())
		data = this->get_last()->message + std::string(64, '0');
	else
		data = this->get_last()->message + this->get_last()->prev->hash;

	while (!this->found) {
		input = std::to_string(th_nonce) + data;
		hash = sha256(input);

		if (this->found)
			break;
		else if (hash.substr(0, PREFIXE_LEN) == Blockchain::prefixe) {
			this->found = true;
			this->last->nonce = th_nonce;
			this->last->hash = hash;

			if (debug) {
				std::lock_guard<std::mutex> iolock(*iomutex);
				std::cout << "Thread #" << thread_num << " found correct nonce = " << this->get_last()->nonce << std::endl;
			}
			break;
		}

		th_nonce += this->num_cpus;
	}
}
