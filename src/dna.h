#pragma once

#include <string>

using namespace std;

class DNA
{
private:
	string encoding;
	unsigned fitness;

public:
	DNA(const string& encoding);
	bool operator< (const DNA& other) const;
	DNA crossover(DNA dna);
	void mutate();
	unsigned get_fitness();
	void rate_fitness(string target);
};
