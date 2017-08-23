#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int random_ascii()
{
	// Range for printable ASCII characters
	const int low = 40, high = 126;
	return low + rand() % (high - low + 1);
}

unsigned levenshtein_distance(const string& s1, const string& s2) 
{
	const size_t len1 = s1.size(), len2 = s2.size();
	vector<unsigned> col(len2+1), prev_col(len2+1);
	
	for (unsigned i = 0; i < prev_col.size(); i++)
		prev_col[i] = i;
	for (unsigned i = 0; i < len1; i++) {
		col[0] = i+1;
		for (unsigned j = 0; j < len2; j++)
			col[j+1] = min({ prev_col[1 + j] + 1, col[j] + 1, prev_col[j] + (s1[i]==s2[j] ? 0 : 1) });
		col.swap(prev_col);
	}
	return prev_col[len2];
}

class DNA
{
private:
	string encoding;
	unsigned fitness;

public:
	DNA(const string& encoding) :
		encoding(encoding)
	{
		
	}
	
	bool operator< (const DNA& other) const 
	{
		return fitness < other.fitness;
	}
	
	DNA crossover(DNA dna)
	{
		DNA offspring = *this;
		size_t split_idx = rand() % this->encoding.length();
		int which = rand() % 2;
		string swap;
		
		cout << "P1 Encoding:\t" << this->encoding << endl;
		cout << "P2 Encoding:\t" << dna.encoding << endl;
		
		if (which == 0) {
			offspring.encoding.replace(0, split_idx,
				dna.encoding.substr(0, split_idx));
		} else {
			size_t len = dna.encoding.length();
			offspring.encoding.replace(split_idx, len,
				dna.encoding.substr(split_idx, len));
		}

		cout << "Crossover:\t" << offspring.encoding << endl;
		return offspring;
	}

	void mutate()
	{
		cout << "Mutation:\t";
		size_t flip_idx = rand() % this->encoding.length();
		this->encoding[flip_idx] = random_ascii();
		cout << this->encoding << endl << endl;
	}

	unsigned get_fitness()
	{
		return this->fitness;
	}
	
	void set_fitness(unsigned fitness)
	{
		this->fitness = fitness;
	}

	void rate_fitness(string target)
	{
		this->fitness = levenshtein_distance(this->encoding, target);
	}
};

class GenePool
{
private:
	vector<DNA> individuals;
	size_t generation = 1;
	bool converged = false;
	string target;

public:
	GenePool(DNA& p1, DNA& p2, string target) :
		target(target)
	{
		p1.rate_fitness(target);
		p2.rate_fitness(target);
		individuals.push_back(p1);
		individuals.push_back(p2);
		sort(individuals.begin(), individuals.end());
	}
	
	void evolve()
	{
		do {
			DNA p1 = individuals[0];
			DNA p2 = individuals[1];
			DNA offspring = p1.crossover(p2);
			offspring.mutate();
			offspring.rate_fitness(target);
			individuals.push_back(offspring);
			sort(individuals.begin(), individuals.end());
		} while (individuals[0].get_fitness() != 0);
	}
};

int main()
{
	srand(time(NULL));
	DNA p1 = DNA("3v0lv3");
	DNA p2 = DNA("R374rd");
	GenePool pool = GenePool(p1, p2, "5c00by");
	pool.evolve();
}
