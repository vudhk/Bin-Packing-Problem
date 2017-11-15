// PC.Asignment.cpp : Defines the entry point for the console application.
//
// Bin-Packing problem with Genetic Algorithm
//

#include "stdafx.h"

using namespace std;

int main()
{
	srand(time(NULL));

	int solution, i;
	cout << "Input creating..." << endl;
	int input[] = {4, 72, 4, 7, 28, 52, 74, 75, 25, 10, 71, 2, 1, 79, 4, 10, 54, 10, 37, 61, 58, 51, 39, 3, 7, 80, 54, 6, 14, 75, 50, 22, 31, 56, 19, 14, 24, 70, 58, 71, 49, 35, 26, 11, 39, 5, 7, 29, 7, 7, 78, 23, 78, 80, 53, 4, 47, 26, 4, 47, 36, 50, 37, 44, 8, 59, 7, 37, 69, 8, 41, 56, 42, 42, 21, 47, 31, 54, 27, 79, 27, 27, 32, 38, 22, 50, 70, 46, 27, 7, 14, 39, 80, 55, 43, 52, 73, 58, 57, 5 };
	/*
	int input[1000];
	//cout << "{";
	for (i = 0; i < 1000; i++)
	{
		int x = SmartFunc::Random(1, 80);
		input[i] = x;
		//cout << ", " << x;
	}
	//cout << "}" << endl;
	*/

	int size = sizeof(input) / sizeof(*input);
	int capacity = 100;
	cout << "Starting..." << endl;
	//double start = omp_get_wtime();
	GeneticAlgorithm *ga = new GeneticAlgorithm(input, size, capacity);
	solution = ga->Run();
	//double elapse = omp_get_wtime() - start;
	cout << "solution: " << solution << " in: "<< elapse << " (s)" << endl;

	delete ga;
	
	system("pause");
    return 0;
}

