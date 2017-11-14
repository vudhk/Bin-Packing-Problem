#pragma once

class Individual
{
public:
	static int Capacity;
	static int ActualSize;
	int *Genes;
	int Fitness;
	Individual(int *gens, int size);
	~Individual();
	static int * RandomChromosome(int *input, int size);
private:
	int __calcFitness();
};

