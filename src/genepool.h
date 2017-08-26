#pragma once

#include <vector>

#include "dna.h"

using namespace std;

class GenePool
{
private:
	vector<DNA> individuals;
	size_t generation = 1;
	bool converged = false;
	string target;

public:
	GenePool(DNA& p1, DNA& p2, string target);
	void evolve();
};
