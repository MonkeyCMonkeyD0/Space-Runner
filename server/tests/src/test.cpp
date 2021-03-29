#include <iostream>

#include "../../src/Knapsack.hpp"


int main(int argc, char const *argv[])
{
	std::vector<unsigned int> 	w = {70, 73, 77, 80, 82, 87, 90, 94, 98, 106, 110, 113, 115, 118, 120},
								p = {135, 139, 149, 150, 156, 163, 173, 184, 192, 201, 210, 214, 221, 229, 240};
	Knapsack knap1(w, p, 750, 50, 0.3, 1000);

	std::cout << "Optimal solution found = ";
	knap1.print_bin(std::cout, knap1.get()) << std::endl;

	return 0;
}