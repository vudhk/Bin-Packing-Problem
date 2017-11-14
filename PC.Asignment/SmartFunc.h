#pragma once

#include "Individual.h"


static class SmartFunc
{
public:
	static int Random(int start, int end);
	static void Shuffle(Gen *array, int size);
	static void Sort(Gen * input, int inputSize);
	static void Swap(Gen *obj1, Gen *obj2);
	static void Print(Gen *array, int size);
};

