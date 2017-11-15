#include "stdafx.h"
#include "GeneticAlgorithm.h"

using namespace std;

GeneticAlgorithm::GeneticAlgorithm(int *itemsInput, int size, int capacity)
{
	this->__inputSize = size;
	this->__itemsInput = __preProcess(itemsInput);
	this->__sols = new vector<SOL_TYPE>();
	Individual::ActualSize = __inputSize;
	Individual::Capacity = capacity;
}

GeneticAlgorithm::~GeneticAlgorithm()
{
	delete __sols;
}

void GeneticAlgorithm::__initPopulation()
{
	//double start = omp_get_wtime();
	int i;

#ifdef PARALLEL
#pragma omp parallel for private(i)
#endif

	for (i = 0; i < MAX_SOL; i++)
	{
		Gen *gen = SOL_TYPE::RandomChromosome(__itemsInput, __inputSize);
		SOL_TYPE sol(gen, __inputSize);

#ifdef PARALLEL
#pragma omp critical
#endif

		__sols->push_back(sol);

	}
	//double elapse = omp_get_wtime() - start;
	std::cout << "---InitPopulation in: " << elapse << "(s)" << std::endl;
}

SOL_TYPE *GeneticAlgorithm::__findBestFitnist()
{
	//double start = omp_get_wtime();
	int i;
	SOL_TYPE *fitnist;
	fitnist = &__sols->at(0);

#ifdef PARALLEL
#pragma omp parallel for private(i)
#endif

	for (i = 1; i < MAX_SOL; i++)
	{
		if (__sols->at(i).Fitness < fitnist->Fitness)
		{

#ifdef PARALLEL
#pragma omp critical
#endif
			fitnist = &__sols->at(i);

		}
	}

	//double elapse = omp_get_wtime() - start;
	std::cout << "---FindBestFitnist in: " << elapse << "(s)" << std::endl;

	return fitnist;
}

SOL_TYPE *GeneticAlgorithm::__selectParent()
{
	//double start = omp_get_wtime();

	int i, num;
	int x = (int)(0.3 * __inputSize);
	int numOfTournament = x < 1 ? 1 : x;

	num = SmartFunc::Random(0, MAX_SOL - 1);
	SOL_TYPE *parent = &__sols->at(num);

#ifdef PARALLEL
#pragma omp parallel for private(i, num)
#endif

	for (i = 1; i < numOfTournament; i++)
	{
		num = SmartFunc::Random(0, MAX_SOL - 1);
		if (parent->Fitness < __sols->at(num).Fitness)
		{

#ifdef PARALLEL
#pragma omp critical
#endif
			parent = &__sols->at(num);

		}
	}

	//double elapse = omp_get_wtime() - start;
	//std::cout << "---SelectParent in: " << elapse << "(s)" << std::endl;

	return parent;
}

SOL_TYPE *GeneticAlgorithm::__crossover(SOL_TYPE *indivFather, SOL_TYPE *indivMother)
{
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

	SOL_TYPE *indivChild = new SOL_TYPE(gen, __inputSize);
	return indivChild;
}

void GeneticAlgorithm::__mutation(SOL_TYPE *individual)
{
	int i, j;
	i = SmartFunc::Random(0, __inputSize - 1);
	j = SmartFunc::Random(0, __inputSize - 1);
	SmartFunc::Swap(&individual->Genes[i], &individual->Genes[j]);
}

INPUT_TYPE *GeneticAlgorithm::__preProcess(int * input)
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


int GeneticAlgorithm::Run()
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
		//double start = omp_get_wtime();
		// delete old population
		for (j = 0; j < MAX_SOL; j++)
		{
			__sols->at(j).IsDelete = true;
			__sols->at(j).~Individual();
		}
		//double elapse = omp_get_wtime() - start;
		// renew population
		__sols = newPopulation;
	}

	// return solution
	return __findBestFitnist()->Fitness;
}
