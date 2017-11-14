#include "stdafx.h"
#include "Individual.h"

using std::vector;

Individual::Individual(int *genes, int size)
{
	this->Genes = genes;
	this->ActualSize = size;
	this->Fitness = this->__calcFitness();
}


Individual::~Individual()
{
	//delete[] Genes;
}

int * Individual::RandomChromosome(int * input, int size)
{
	int *genes = input;
	SmartFunc::Shuffle(genes, size);
	return genes;
}

int Individual::__calcFitness()
{
	int i, j, flag, fitness;
	vector<int> *caps = new vector<int>(1, 20);
	for (i = 0; i < ActualSize; i++)
	{
		flag = false;
		for (j = 0; j < caps->size(); j++)
		{
			if (caps->at(j) >= Genes[i])
			{
				caps->at(j) -= Genes[i];
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			caps->push_back(20 - Genes[i]);
		}
	}
	fitness = caps->size();
	caps->~vector();
	delete caps;
	return fitness;
}
