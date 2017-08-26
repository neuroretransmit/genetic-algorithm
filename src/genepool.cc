#include "genepool.h"

#include <algorithm>
#include <iostream>

GenePool::GenePool(DNA& p1, DNA& p2, string target) :
		target(target)
{
	p1.rate_fitness(target);
	p2.rate_fitness(target);
	individuals.push_back(p1);
	individuals.push_back(p2);
	sort(individuals.begin(), individuals.end());
}

void GenePool::evolve()
{
	do {
		cout << "Generation " << this->generation++ << " ===================" << endl;
		DNA& p1 = individuals[0];
		DNA& p2 = individuals[1];
		DNA offspring = p1.crossover(p2);
		offspring.mutate();
		offspring.rate_fitness(target);
		individuals.push_back(offspring);
		sort(individuals.begin(), individuals.end());
	} while (individuals[0].get_fitness() != 0);
}
