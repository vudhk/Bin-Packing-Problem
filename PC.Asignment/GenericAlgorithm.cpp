#include "stdafx.h"
#include "GenericAlgorithm.h"

using namespace std;

GenericAlgorithm::GenericAlgorithm(INPUT_TYPE * itemSizeInput, int inputSize, int capacity)
{
	this->__inputSize = inputSize;
	this->__itemsInput = itemSizeInput;
	this->__sols = new vector<SOL_TYPE>();
}

GenericAlgorithm::~GenericAlgorithm()
{
	//delete this->__itemsInput;
	//delete this->__sols;
}

void GenericAlgorithm::__initPopulation()
{
	int i;
	for (i = 0; i < MAX_SOL; i++)
	{
		int *gen = SOL_TYPE::RandomChromosome(__itemsInput, __inputSize);
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
	num = SmartFunc::Random(0, MAX_SOL);
	SOL_TYPE *parent = &__sols->at(num);
	for (i = 1; i < numOfTournament; i++)
	{
		num = SmartFunc::Random(0, MAX_SOL);
		if (parent->Fitness < __sols->at(num).Fitness)
		{
			parent = &__sols->at(num);
		}
	}
	return parent;
}

SOL_TYPE *GenericAlgorithm::__crossover(SOL_TYPE *indivFather, SOL_TYPE *indivMother)
{
	int *gen = new int[__inputSize];
	int i, j, k;
	for (i = 0; i < __inputSize; i++)
	{
		//
		// TO DO
		//
		gen[i] = indivFather->Genes[i];
	}
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
		__sols->~vector();
		delete __sols;
		// renew population
		__sols = newPopulation;
	}

	// return solution
	return __findBestFitnist()->Fitness;
}
