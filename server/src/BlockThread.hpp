#pragma once

#include <mutex>

#include "Blockchain.hpp"


class BlockThread : public Blockchain {

public:

	BlockThread() : Blockchain() {}

protected:

	virtual void mine_last(const bool & debug = false);

private:

	bool found;
	unsigned short int num_cpus;

	void mine_inst(std::mutex *, const unsigned short int &, const bool &);

};

