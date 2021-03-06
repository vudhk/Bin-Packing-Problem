﻿#pragma once

#include "Individual.h"

#define MAX_SOL 100
#define INPUT_TYPE Gen
#define SOL_TYPE Individual

using std::vector;

class GeneticAlgorithm
{
public:
	GeneticAlgorithm(int *itemsInput, int size, int capacity);
	~GeneticAlgorithm();
	int Run();
private:
	INPUT_TYPE *__itemsInput;
	int __inputSize;
	vector<SOL_TYPE> *__sols;
	void __initPopulation();
	SOL_TYPE *__findBestFitnist();
	SOL_TYPE *__selectParent();
	SOL_TYPE *__crossover(SOL_TYPE *idvFather, SOL_TYPE *idvMother);
	void __mutation(SOL_TYPE *individual);
	INPUT_TYPE *__preProcess(int * input);
};


