﻿// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#include "SmartFunc.h"
#include <iostream>
#include <stdio.h>
#include <tchar.h>
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
