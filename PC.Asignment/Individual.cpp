#include "stdafx.h"
#include "Individual.h"

using std::vector;


Individual::Individual(int *genes, int size)
{
	this->Genes = genes;
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
	vector<int> *caps = new vector<int>(1, Capacity);
	for (i = 0; i < ActualSize; i++)
	{
		if (Genes[i] <= 0) 
		{
			std::cout << "Genes[" << i << "] = " << Genes[i] << std::endl;
			throw Genes[i];
		}
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
			caps->push_back(Capacity - Genes[i]);
		}
	}
	fitness = caps->size();
	caps->~vector();
	delete caps;
	return fitness;
}
