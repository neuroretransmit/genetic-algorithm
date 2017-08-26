#include "dna.h"

#include <iostream>

#include "util.h"

DNA::DNA(const string& encoding) :
		encoding(encoding) {}

bool DNA::operator< (const DNA& other) const
{
	return fitness < other.fitness;
}

DNA DNA::crossover(DNA dna)
{
	DNA offspring = *this;
	size_t split_idx = rand() % this->encoding.length();
	int which = rand() % 2;
	string swap;

	cout << "P1 Encoding:\t" << this->encoding << endl;
	cout << "P2 Encoding:\t" << dna.encoding << endl;

	if (which == 0) {
		offspring.encoding.replace(0, split_idx, dna.encoding.substr(0, split_idx));
	} else {
		size_t len = dna.encoding.length();
		offspring.encoding.replace(split_idx, len, dna.encoding.substr(split_idx, len));
	}

	cout << "Crossover:\t" << offspring.encoding << endl;
	return offspring;
}

void DNA::mutate()
{
	cout << "Mutation:\t";
	size_t flip_idx = rand() % this->encoding.length();
	this->encoding[flip_idx] = Util::random::ascii();
	cout << this->encoding << endl << endl;
}

unsigned DNA::get_fitness()
{
	return this->fitness;
}

void DNA::rate_fitness(string target)
{
	this->fitness = Util::math::levenshtein(this->encoding, target);
}
