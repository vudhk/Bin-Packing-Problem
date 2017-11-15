#include "Stdafx.h"
#include "Individual.h"

using std::vector;

int Individual::Capacity = 0;
int Individual::ActualSize = 0;

Individual::Individual(Gen *genes, int size)
{
	this->Genes = genes;
	this->IsDelete = false;
	this->Fitness = this->__calcFitness();
}


Individual::~Individual()
{
	if (IsDelete)
	{
		delete [] Genes;
	}
}

Gen * Individual::RandomChromosome(Gen * input, int size)
{
	Gen *genes = new Gen[size];
	int i;
	for (i = 0; i < size; i++)
	{
		genes[i].value = input[i].value;
		genes[i].key = input[i].key;
	}
	SmartFunc::Shuffle(genes, size);
	return genes;
}

int Individual::__calcFitness()
{
	int i, j, flag, fitness;
	vector<int> *caps = new vector<int>(1, Capacity);
	for (i = 0; i < ActualSize; i++)
	{
		if (Genes[i].value <= 0)
		{
			std::cout << "Genes[" << i << "] = " << Genes[i].value << std::endl;
			throw Genes[i];
		}
		flag = false;
		for (j = 0; j < caps->size(); j++)
		{
			if (caps->at(j) >= Genes[i].value)
			{
				caps->at(j) -= Genes[i].value;
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			caps->push_back(Capacity - Genes[i].value);
		}
	}
	fitness = caps->size();
	caps->~vector();
	delete caps;
	return fitness;
}
