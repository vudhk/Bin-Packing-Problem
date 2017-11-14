#include "stdafx.h"
#include "SmartFunc.h"


void SmartFunc::Shuffle(int *array, int size)
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		j = Random(1, size) - 1;
		Swap(&array[i], &array[j]);
	}
}

int SmartFunc::Random(int start, int end)
{
	srand(time(NULL));
	return rand() % (end - start + 1) + start;
}

void SmartFunc::Swap(int *obj1, int *obj2)
{
	int tmp;
	tmp = *obj1;
	*obj1 = *obj2;
	*obj2 = tmp;
}


void SmartFunc::Sort(int * input, int inputSize)
{
	int i, j;
	for (i = 0; i <= inputSize; i++)
	{
		for (j = 0; j <= inputSize - i; j++)
		{
			if (input[j] < input[j + 1])
			{
				Swap(&input[j], &input[j + 1]);
			}
		}
	}
}


