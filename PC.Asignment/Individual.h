#pragma once

struct Gen {
	int value;
	int key;
};

class Individual
{
public:
	static int Capacity;
	static int ActualSize;
	Gen *Genes;
	bool IsDelete;
	int Fitness;
	Individual(Gen *gens, int size);
	~Individual();
	static Gen * RandomChromosome(Gen *input, int size);
private:
	int __calcFitness();
};

