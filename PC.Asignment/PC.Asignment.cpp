// PC.Asignment.cpp : Defines the entry point for the console application.
//
// Bin-Packing problem with Genetic Algorithm
//

#include "stdafx.h"
#include "GeneticAlgorithm.h"

using namespace std;

int main(int argc, char *argv[])
{
	srand(time(NULL));

	int solution;
	int input[] = { 12, 7, 9, 5, 4, 3};
	int size = sizeof(input) / sizeof(*input);
	int capacity = 20;
	GeneticAlgorithm *ga = new GeneticAlgorithm(input, size, capacity);
	solution = ga->Run();

	cout << "solution: " << solution << endl;

	delete ga;
	system("pause");
    return 0;
}

