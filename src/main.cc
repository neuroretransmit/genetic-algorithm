#include "genepool.h"

int main()
{
	DNA p1 = DNA("3v0l32!3d");
	DNA p2 = DNA("R374rdaa3");
	GenePool pool = GenePool(p1, p2, "ev0lution");
	pool.evolve();
}

