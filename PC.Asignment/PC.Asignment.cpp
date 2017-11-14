// PC.Asignment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GenericAlgorithm.h"

using namespace std;

int main()
{
	int solution;
	int input[] = { 12, 7, 9, 5, 4, 3};
	int size = sizeof(input) / sizeof(*input);
	int capacity = 20;
	GenericAlgorithm *ga = new GenericAlgorithm(input, size, capacity);
	solution = ga->Run();

	cout << "solution: " << solution << endl;

	system("pause");
    return 0;
}

