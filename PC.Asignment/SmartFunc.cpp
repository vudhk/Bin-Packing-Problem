#include "stdafx.h"
#include "SmartFunc.h"


void SmartFunc::Shuffle(Gen *array, int size)
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
	return rand() % (end - start + 1) + start;
}

void SmartFunc::Swap(Gen *obj1, Gen *obj2)
{
	Gen tmp;
	tmp = *obj1;
	*obj1 = *obj2;
	*obj2 = tmp;
}

void SmartFunc::Print(Gen * array, int size)
{
	int i;
	std::cout << "[" << array[0].key << "-" << array[0].value;
	for (i = 1; i < size; i++)
	{
		std::cout << ", " << array[i].key << "-" << array[i].value;
	}
	std::cout << "]" << std::endl;
}


void SmartFunc::Sort(Gen * input, int inputSize)
{
	int i, j;
	for (i = 0; i <= inputSize; i++)
	{
		for (j = 0; j <= inputSize - i; j++)
		{
			if (input[j].value < input[j + 1].value)
			{
				Swap(&input[j], &input[j + 1]);
			}
		}
	}
}


