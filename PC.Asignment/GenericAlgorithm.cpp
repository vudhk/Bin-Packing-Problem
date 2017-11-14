#include "stdafx.h"
#include "GenericAlgorithm.h"

using namespace std;

GenericAlgorithm::GenericAlgorithm(int *itemsInput, int size, int capacity)
{
	this->__inputSize = size;
	this->__itemsInput = __preProcess(itemsInput);
	this->__sols = new vector<SOL_TYPE>();
	Individual::ActualSize = __inputSize;
	Individual::Capacity = capacity;
}

GenericAlgorithm::~GenericAlgorithm()
{
	delete __sols;
}

void GenericAlgorithm::__initPopulation()
{
	int i;
	for (i = 0; i < MAX_SOL; i++)
	{
		Gen *gen = SOL_TYPE::RandomChromosome(__itemsInput, __inputSize);
		SOL_TYPE sol(gen, __inputSize);
		__sols->push_back(sol);
	}
}

SOL_TYPE *GenericAlgorithm::__findBestFitnist()
{
	int i;
	SOL_TYPE *fitnist;
	fitnist = &__sols->at(0);
	for (i = 1; i < MAX_SOL; i++)
	{
		if (__sols->at(i).Fitness < fitnist->Fitness)
		{
			fitnist = &__sols->at(i);
		}
	}
	return fitnist;
}

SOL_TYPE *GenericAlgorithm::__selectParent(int numOfTournament = 3)
{
	int i, num;
	num = SmartFunc::Random(0, MAX_SOL - 1);
	SOL_TYPE *parent = &__sols->at(num);
	for (i = 1; i < numOfTournament; i++)
	{
		num = SmartFunc::Random(0, MAX_SOL - 1);
		if (parent->Fitness < __sols->at(num).Fitness)
		{
			parent = &__sols->at(num);
		}
	}
	return parent;
}

SOL_TYPE *GenericAlgorithm::__crossover(SOL_TYPE *indivFather, SOL_TYPE *indivMother)
{
	//SmartFunc::Print(indivFather->Genes, __inputSize);
	//SmartFunc::Print(indivMother->Genes, __inputSize);

	Gen *gen = new Gen[__inputSize];
	int i = 0, j, k;
	bool flag;
	for (j = 0; j < __inputSize; j++)
	{
		// for father
		flag = false;
		for (k = 0; k < i; k++)
		{
			if (gen[k].key == indivFather->Genes[j].key)
			{
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			gen[i].value = indivFather->Genes[j].value;
			gen[i].key = indivFather->Genes[j].key;
			//std::cout << gen[i].key << "-" << gen[i].value << std::endl;
			i++;
		}
		
		// for mother
		flag = false;
		for (k = 0; k < i; k++)
		{
			if (gen[k].key == indivMother->Genes[j].key)
			{
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			gen[i].value = indivMother->Genes[j].value;
			gen[i].key = indivMother->Genes[j].key;
			//std::cout << gen[i].key << "-" << gen[i].value << std::endl;
			i++;
		}
	}
	//SmartFunc::Print(gen, __inputSize);
	SOL_TYPE *indivChild = new SOL_TYPE(gen, __inputSize);
	return indivChild;
}

void GenericAlgorithm::__mutation(SOL_TYPE *individual)
{
	int i, j;
	i = SmartFunc::Random(0, __inputSize - 1);
	j = SmartFunc::Random(0, __inputSize - 1);
	SmartFunc::Swap(&individual->Genes[i], &individual->Genes[j]);
}

INPUT_TYPE *GenericAlgorithm::__preProcess(int * input)
{
	INPUT_TYPE *inputGen = new INPUT_TYPE[__inputSize];
	int i;
	for (i = 0; i < __inputSize; i++)
	{
		inputGen[i].value = input[i];
		inputGen[i].key = i;
	}

	return inputGen;
}


int GenericAlgorithm::Run()
{
	int i, j;
	vector<SOL_TYPE> *newPopulation;
	SOL_TYPE *father, *mother, *child;

	__initPopulation();
	for (i = 0; i < 100; i++)
	{
		newPopulation = new vector<SOL_TYPE>();
		for (j = 0; j < MAX_SOL; j++)
		{
			father = __selectParent();
			mother = __selectParent();
			child = __crossover(father, mother);

			__mutation(child);
			newPopulation->push_back(*child);
		}
		// delete old population
		for (j = 0; j < MAX_SOL; j++)
		{
			__sols->at(j).IsDelete = true;
			__sols->at(j).~Individual();
		}
		// renew population
		__sols = newPopulation;
	}

	// return solution
	return __findBestFitnist()->Fitness;
}
