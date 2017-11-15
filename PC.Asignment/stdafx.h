#pragma once

#include <vector>
#include "GeneticAlgorithm.h"
#include "SmartFunc.h"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <random>
#include <omp.h>
#include <math.h>
#include <stdio.h>

#if true
#define PARALLEL
#else
#define SEQUENTIAL
#endif
